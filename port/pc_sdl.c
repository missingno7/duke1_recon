#include "wide_pass.h"
#include "pc_internal.h"
#include "config.h"
#include "scene.h"
#include "present.h"
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

unsigned pc_trace_flags;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *screen_texture;
static SDL_Texture *sharp_texture;
static int sharp_width;
static int sharp_height;
static SDL_Mutex *trace_mutex;
static SDL_Mutex *launcher_key_mutex;
static SDL_AtomicInt game_finished;
static SDL_AtomicInt game_status;
static SDL_AtomicInt game_thread_started;
static SDL_AtomicInt window_settings_requested;
static int fullscreen;
static int window_open;
static uint32_t rgba_frame[320u * 200u];
static uint32_t *script_shot_pixels;
static size_t script_shot_capacity;
static char pending_script_shot[4096];
static char pending_script_page[4096];   /* the emulated page, whatever the renderer */
static int renderer_override = -1;
static int verify_native;
static int verify_episode;
static uint8_t launcher_keys[64];
static unsigned launcher_key_read;
static unsigned launcher_key_write;
static uint8_t keyboard_game_route[256];
static SDL_AtomicInt modal_keyboard_capture;
static _Thread_local jmp_buf *game_exit_target;
static SDL_AtomicInt episode_exit_requested;
static unsigned char *episode_state_begin[4];
static size_t episode_state_size[4];
static int current_episode;               /* the episode whose state is live */
static unsigned char *episode_state_snapshot[4];

enum script_action { SCRIPT_KEY, SCRIPT_KEYDOWN, SCRIPT_KEYUP, SCRIPT_SHOT, SCRIPT_PAGE, SCRIPT_QUIT };
struct script_event {
    uint64_t at_ms;
    unsigned order;
    enum script_action action;
    SDL_Scancode key;
    int extended;
    char argument[4096];
};
struct scripted_release {
    uint64_t at_ms;
    SDL_Scancode key;
    int extended;
    int game_input;
    int active;
};
static struct script_event *script_events;
static size_t script_event_count;
static size_t script_event_cursor;
static struct scripted_release scripted_releases[64];
static uint64_t script_origin;
static unsigned pc_spin_iterations;
static void save_windowed_size(void);
static int renderer_is_enhanced(void);
static int native_canvas_width(int out_w, int out_h);
static int take_script_shot(char *path, size_t capacity);

#define PC_SPIN_BATCH 440u

void pc_trace(unsigned category, const char *format, ...) {
    va_list args;
    if (!(pc_trace_flags & category)) return;
    if (trace_mutex) SDL_LockMutex(trace_mutex);
    va_start(args, format);
    fputs("[port] ", stderr);
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
    fflush(stderr);
    if (trace_mutex) SDL_UnlockMutex(trace_mutex);
}

void pc_spin(void) {
    port_wide_pass_abandon("pc_spin");
    /* One millisecond sleeps can round to a longer Windows timer quantum. A 440-pass batch
       amortizes that yield while matching the fixed-cycle 386 reference's menu transitions. */
    if (++pc_spin_iterations >= PC_SPIN_BATCH) {
        pc_spin_iterations = 0;
        SDL_Delay(1);
    }
}

static int command_token(const char *command, const char *name, const char **after)
{
    size_t length = strlen(name);
    const char *at = command;
    while ((at = strstr(at, name)) != NULL) {
        if ((at == command || isspace((unsigned char)at[-1])) &&
            (at[length] == '\0' || isspace((unsigned char)at[length]) || at[length] == '=')) {
            if (after) *after = at + length;
            return 1;
        }
        at += length;
    }
    return 0;
}

static void read_native_command_options(void)
{
#ifdef _WIN32
    const char *command = GetCommandLineA();
    const char *after = NULL;
    if (command_token(command, "--verify-native", NULL))
        verify_native = 1;
    if (command_token(command, "--episode", &after)) {
        while (*after == ' ' || *after == '\t') ++after;
        verify_episode = (int)strtol(after, NULL, 10);
        if (verify_episode < 0 || verify_episode > 3) verify_episode = 0;
    }
    if (command_token(command, "--renderer", &after)) {
        while (*after == ' ' || *after == '\t') ++after;
        if (*after == '=') ++after;
        if (_strnicmp(after, "enhanced", 8) == 0 &&
            (after[8] == '\0' || isspace((unsigned char)after[8])))
            renderer_override = 1;
        else if (_strnicmp(after, "classic", 7) == 0 &&
                 (after[7] == '\0' || isspace((unsigned char)after[7])))
            renderer_override = 0;
    }
    if (command_token(command, "--stereo", NULL)) pc_settings.stereo = 1;
#endif
}

int pc_is_game_thread(void) {
    return SDL_GetAtomicInt(&game_thread_started) && pc_game_thread_id == SDL_GetCurrentThreadID();
}

static void push_launcher_key_unlocked(uint8_t scan_code) {
    unsigned next = (launcher_key_write + 1) % (unsigned)sizeof(launcher_keys);
    if (next == launcher_key_read) return;
    launcher_keys[launcher_key_write] = scan_code;
    launcher_key_write = next;
}

static void push_launcher_key(uint8_t scan_code) {
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    push_launcher_key_unlocked(scan_code);
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
}

static void send_xt_code(uint8_t scan_code, int extended) {
    unsigned key_index = (extended ? 128u : 0u) + (scan_code & 0x7fu);
    int game_input;
    if (scan_code & 0x80u) {
        game_input = keyboard_game_route[key_index];
        keyboard_game_route[key_index] = 0;
    } else {
        game_input = !SDL_GetAtomicInt(&modal_keyboard_capture) &&
                     SDL_GetAtomicInt(&game_thread_started);
        keyboard_game_route[key_index] = (uint8_t)game_input;
    }
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    if (game_input) {
        if (extended) pc_keyboard_scancode(0xe0);
        pc_keyboard_scancode(scan_code);
    }
    if (window_open) push_launcher_key_unlocked(scan_code);
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
}

void pc_set_quit_hint(void) {
    /* The title menu asks for confirmation after Escape. Let that path run on
       the game thread, then answer it with Y so normal shutdown restores DOS
       state and returns through pc_exit/longjmp. */
    pc_keyboard_scancode(0x01);
    SDL_Delay(60);
    pc_keyboard_scancode(0x81);
    SDL_Delay(60);
    pc_keyboard_scancode(0x15);
}

static int xt_scancode(SDL_Scancode key, uint8_t *code, int *extended) {
    *extended = 0;
    switch (key) {
    case SDL_SCANCODE_ESCAPE: *code = 0x01; break;
    case SDL_SCANCODE_1: *code = 0x02; break; case SDL_SCANCODE_2: *code = 0x03; break;
    case SDL_SCANCODE_3: *code = 0x04; break; case SDL_SCANCODE_4: *code = 0x05; break;
    case SDL_SCANCODE_5: *code = 0x06; break; case SDL_SCANCODE_6: *code = 0x07; break;
    case SDL_SCANCODE_7: *code = 0x08; break; case SDL_SCANCODE_8: *code = 0x09; break;
    case SDL_SCANCODE_9: *code = 0x0a; break; case SDL_SCANCODE_0: *code = 0x0b; break;
    case SDL_SCANCODE_MINUS: *code = 0x0c; break; case SDL_SCANCODE_EQUALS: *code = 0x0d; break;
    case SDL_SCANCODE_BACKSPACE: *code = 0x0e; break; case SDL_SCANCODE_TAB: *code = 0x0f; break;
    case SDL_SCANCODE_Q: *code = 0x10; break; case SDL_SCANCODE_W: *code = 0x11; break;
    case SDL_SCANCODE_E: *code = 0x12; break; case SDL_SCANCODE_R: *code = 0x13; break;
    case SDL_SCANCODE_T: *code = 0x14; break; case SDL_SCANCODE_Y: *code = 0x15; break;
    case SDL_SCANCODE_U: *code = 0x16; break; case SDL_SCANCODE_I: *code = 0x17; break;
    case SDL_SCANCODE_O: *code = 0x18; break; case SDL_SCANCODE_P: *code = 0x19; break;
    case SDL_SCANCODE_LEFTBRACKET: *code = 0x1a; break; case SDL_SCANCODE_RIGHTBRACKET: *code = 0x1b; break;
    case SDL_SCANCODE_RETURN: *code = 0x1c; break; case SDL_SCANCODE_LCTRL: *code = 0x1d; break;
    case SDL_SCANCODE_A: *code = 0x1e; break; case SDL_SCANCODE_S: *code = 0x1f; break;
    case SDL_SCANCODE_D: *code = 0x20; break; case SDL_SCANCODE_F: *code = 0x21; break;
    case SDL_SCANCODE_G: *code = 0x22; break; case SDL_SCANCODE_H: *code = 0x23; break;
    case SDL_SCANCODE_J: *code = 0x24; break; case SDL_SCANCODE_K: *code = 0x25; break;
    case SDL_SCANCODE_L: *code = 0x26; break; case SDL_SCANCODE_SEMICOLON: *code = 0x27; break;
    case SDL_SCANCODE_APOSTROPHE: *code = 0x28; break; case SDL_SCANCODE_GRAVE: *code = 0x29; break;
    case SDL_SCANCODE_LSHIFT: *code = 0x2a; break; case SDL_SCANCODE_BACKSLASH: *code = 0x2b; break;
    case SDL_SCANCODE_Z: *code = 0x2c; break; case SDL_SCANCODE_X: *code = 0x2d; break;
    case SDL_SCANCODE_C: *code = 0x2e; break; case SDL_SCANCODE_V: *code = 0x2f; break;
    case SDL_SCANCODE_B: *code = 0x30; break; case SDL_SCANCODE_N: *code = 0x31; break;
    case SDL_SCANCODE_M: *code = 0x32; break; case SDL_SCANCODE_COMMA: *code = 0x33; break;
    case SDL_SCANCODE_PERIOD: *code = 0x34; break; case SDL_SCANCODE_SLASH: *code = 0x35; break;
    case SDL_SCANCODE_RSHIFT: *code = 0x36; break; case SDL_SCANCODE_KP_MULTIPLY: *code = 0x37; break;
    case SDL_SCANCODE_LALT: *code = 0x38; break; case SDL_SCANCODE_SPACE: *code = 0x39; break;
    case SDL_SCANCODE_CAPSLOCK: *code = 0x3a; break;
    case SDL_SCANCODE_F1: *code = 0x3b; break; case SDL_SCANCODE_F2: *code = 0x3c; break;
    case SDL_SCANCODE_F3: *code = 0x3d; break; case SDL_SCANCODE_F4: *code = 0x3e; break;
    case SDL_SCANCODE_F5: *code = 0x3f; break; case SDL_SCANCODE_F6: *code = 0x40; break;
    case SDL_SCANCODE_F7: *code = 0x41; break; case SDL_SCANCODE_F8: *code = 0x42; break;
    case SDL_SCANCODE_F9: *code = 0x43; break; case SDL_SCANCODE_F10: *code = 0x44; break;
    case SDL_SCANCODE_NUMLOCKCLEAR: *code = 0x45; break; case SDL_SCANCODE_SCROLLLOCK: *code = 0x46; break;
    case SDL_SCANCODE_KP_7: *code = 0x47; break; case SDL_SCANCODE_KP_8: *code = 0x48; break;
    case SDL_SCANCODE_KP_9: *code = 0x49; break; case SDL_SCANCODE_KP_MINUS: *code = 0x4a; break;
    case SDL_SCANCODE_KP_4: *code = 0x4b; break; case SDL_SCANCODE_KP_5: *code = 0x4c; break;
    case SDL_SCANCODE_KP_6: *code = 0x4d; break; case SDL_SCANCODE_KP_PLUS: *code = 0x4e; break;
    case SDL_SCANCODE_KP_1: *code = 0x4f; break; case SDL_SCANCODE_KP_2: *code = 0x50; break;
    case SDL_SCANCODE_KP_3: *code = 0x51; break; case SDL_SCANCODE_KP_0: *code = 0x52; break;
    case SDL_SCANCODE_KP_PERIOD: *code = 0x53; break; case SDL_SCANCODE_F11: *code = 0x57; break;
    case SDL_SCANCODE_F12: *code = 0x58; break;
    case SDL_SCANCODE_RCTRL: *code = 0x1d; *extended = 1; break;
    case SDL_SCANCODE_RALT: *code = 0x38; *extended = 1; break;
    case SDL_SCANCODE_KP_ENTER: *code = 0x1c; *extended = 1; break;
    case SDL_SCANCODE_KP_DIVIDE: *code = 0x35; *extended = 1; break;
    case SDL_SCANCODE_HOME: *code = 0x47; *extended = 1; break;
    case SDL_SCANCODE_UP: *code = 0x48; *extended = 1; break;
    case SDL_SCANCODE_PAGEUP: *code = 0x49; *extended = 1; break;
    case SDL_SCANCODE_LEFT: *code = 0x4b; *extended = 1; break;
    case SDL_SCANCODE_RIGHT: *code = 0x4d; *extended = 1; break;
    case SDL_SCANCODE_END: *code = 0x4f; *extended = 1; break;
    case SDL_SCANCODE_DOWN: *code = 0x50; *extended = 1; break;
    case SDL_SCANCODE_PAGEDOWN: *code = 0x51; *extended = 1; break;
    case SDL_SCANCODE_INSERT: *code = 0x52; *extended = 1; break;
    case SDL_SCANCODE_DELETE: *code = 0x53; *extended = 1; break;
    default: return 0;
    }
    return 1;
}

static SDL_Scancode script_scancode(const char *name) {
    char normalized[64];
    size_t n = strlen(name);
    if (!n || n >= sizeof(normalized)) return SDL_SCANCODE_UNKNOWN;
    for (size_t i = 0; i <= n; ++i) normalized[i] = (char)tolower((unsigned char)name[i]);
    if (!strcmp(normalized, "esc")) return SDL_SCANCODE_ESCAPE;
    if (!strcmp(normalized, "enter")) return SDL_SCANCODE_RETURN;
    if (!strcmp(normalized, "ctrl") || !strcmp(normalized, "lctrl")) return SDL_SCANCODE_LCTRL;
    if (!strcmp(normalized, "rctrl")) return SDL_SCANCODE_RCTRL;
    if (!strcmp(normalized, "alt") || !strcmp(normalized, "lalt")) return SDL_SCANCODE_LALT;
    if (!strcmp(normalized, "ralt")) return SDL_SCANCODE_RALT;
    if (!strcmp(normalized, "alt")) return SDL_SCANCODE_LALT;
    if (!strcmp(normalized, "shift")) return SDL_SCANCODE_LSHIFT;
    if (strlen(normalized) == 1 && normalized[0] >= 'a' && normalized[0] <= 'z')
        return (SDL_Scancode)(SDL_SCANCODE_A + (normalized[0] - 'a'));
    if (strlen(normalized) == 2 && normalized[0] == 'f' && normalized[1] >= '1' && normalized[1] <= '9')
        return (SDL_Scancode)(SDL_SCANCODE_F1 + (normalized[1] - '1'));
    if (!strcmp(normalized, "f10")) return SDL_SCANCODE_F10;
    if (!strcmp(normalized, "f11")) return SDL_SCANCODE_F11;
    if (!strcmp(normalized, "f12")) return SDL_SCANCODE_F12;
    return SDL_GetScancodeFromName(name);
}

static uint64_t script_now_ms(void) {
    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t frequency = SDL_GetPerformanceFrequency();
    if (!frequency || now < script_origin) return 0;
    return (now - script_origin) * 1000u / frequency;
}

static void send_script_key_routed(SDL_Scancode key, int down, int extended, int game_input) {
    uint8_t code;
    int ignored_extended;
    if (!xt_scancode(key, &code, &ignored_extended)) return;
    if (!down) code |= 0x80u;
    if (game_input) {
        send_xt_code(code, extended);
    } else {
        if (extended) push_launcher_key(0xe0);
        push_launcher_key(code);
    }
}

static void send_script_key(SDL_Scancode key, int down, int extended) {
    send_script_key_routed(key, down, extended, SDL_GetAtomicInt(&game_thread_started));
}

static void schedule_script_release(SDL_Scancode key, int extended, int game_input, uint64_t at_ms) {
    for (size_t i = 0; i < sizeof(scripted_releases) / sizeof(scripted_releases[0]); ++i) {
        if (!scripted_releases[i].active) {
            scripted_releases[i].active = 1;
            scripted_releases[i].key = key;
            scripted_releases[i].extended = extended;
            scripted_releases[i].game_input = game_input;
            scripted_releases[i].at_ms = at_ms + 45;
            return;
        }
    }
    send_script_key_routed(key, 0, extended, game_input);
}

static uint32_t png_crc_update(uint32_t crc, const uint8_t *data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        crc ^= data[i];
        for (unsigned bit = 0; bit < 8; ++bit)
            crc = (crc >> 1) ^ (0xedb88320u & (uint32_t)-(int32_t)(crc & 1u));
    }
    return crc;
}

static int write_png_chunk(FILE *file, const char type[4], const uint8_t *data, uint32_t length) {
    uint8_t head[8];
    uint8_t crc_bytes[4];
    uint32_t crc;
    head[0] = (uint8_t)(length >> 24); head[1] = (uint8_t)(length >> 16);
    head[2] = (uint8_t)(length >> 8); head[3] = (uint8_t)length;
    memcpy(head + 4, type, 4);
    crc = png_crc_update(0xffffffffu, (const uint8_t *)type, 4);
    if (length) crc = png_crc_update(crc, data, length);
    crc = ~crc;
    crc_bytes[0] = (uint8_t)(crc >> 24); crc_bytes[1] = (uint8_t)(crc >> 16);
    crc_bytes[2] = (uint8_t)(crc >> 8); crc_bytes[3] = (uint8_t)crc;
    return fwrite(head, 1, sizeof(head), file) == sizeof(head) &&
           (!length || fwrite(data, 1, length, file) == length) &&
           fwrite(crc_bytes, 1, sizeof(crc_bytes), file) == sizeof(crc_bytes);
}

static int save_rgb_png_pixels_sized(const char *path, const uint32_t *pixels,
                                     unsigned width, unsigned height) {
    static const uint8_t signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    uint8_t ihdr[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0 };
    size_t raw_size;
    uint8_t *raw = NULL;
    uint8_t *zdata = NULL;
    FILE *file;
    size_t out = 0, source = 0;
    uint32_t adler_a = 1, adler_b = 0;
    int ok = 0;
    if (!width || !height || width > 4096 || height > 200 || !pixels) goto done;
    raw_size = (size_t)height * (1u + (size_t)width * 3u);
    {
        size_t blocks = (raw_size + 65534u) / 65535u;
        size_t z_size = 2u + raw_size + blocks * 5u + 4u;
        free(raw);
        free(zdata);
        raw = (uint8_t *)malloc(raw_size);
        zdata = (uint8_t *)malloc(z_size);
        if (!raw || !zdata) goto done;
    }
    ihdr[0] = (uint8_t)(width >> 24); ihdr[1] = (uint8_t)(width >> 16);
    ihdr[2] = (uint8_t)(width >> 8); ihdr[3] = (uint8_t)width;
    ihdr[4] = (uint8_t)(height >> 24); ihdr[5] = (uint8_t)(height >> 16);
    ihdr[6] = (uint8_t)(height >> 8); ihdr[7] = (uint8_t)height;
    for (unsigned y = 0; y < height; ++y) {
        raw[out++] = 0;
        for (unsigned x = 0; x < width; ++x) {
            uint32_t pixel = pixels[source++];
            raw[out++] = (uint8_t)(pixel >> 16);
            raw[out++] = (uint8_t)(pixel >> 8);
            raw[out++] = (uint8_t)pixel;
        }
    }
    zdata[0] = 0x78; zdata[1] = 0x01;
    out = 2;
    for (size_t consumed = 0; consumed < raw_size;) {
        uint16_t count = (uint16_t)((raw_size - consumed) > 65535u ? 65535u : raw_size - consumed);
        uint16_t inverse = (uint16_t)~count;
        zdata[out++] = consumed + count == raw_size ? 1 : 0;
        zdata[out++] = (uint8_t)count; zdata[out++] = (uint8_t)(count >> 8);
        zdata[out++] = (uint8_t)inverse; zdata[out++] = (uint8_t)(inverse >> 8);
        memcpy(zdata + out, raw + consumed, count);
        out += count;
        consumed += count;
    }
    for (size_t i = 0; i < raw_size; ++i) {
        adler_a = (adler_a + raw[i]) % 65521u;
        adler_b = (adler_b + adler_a) % 65521u;
    }
    zdata[out++] = (uint8_t)(adler_b >> 8); zdata[out++] = (uint8_t)adler_b;
    zdata[out++] = (uint8_t)(adler_a >> 8); zdata[out++] = (uint8_t)adler_a;
    file = fopen(path, "wb");
    if (!file) goto done;
    ok = fwrite(signature, 1, sizeof(signature), file) == sizeof(signature) &&
         write_png_chunk(file, "IHDR", ihdr, sizeof(ihdr)) &&
         write_png_chunk(file, "IDAT", zdata, (uint32_t)out) &&
         write_png_chunk(file, "IEND", NULL, 0);
    fclose(file);
done:
    free(raw);
    free(zdata);
    return ok;
}

static int save_rgb_png_pixels(const char *path, const uint32_t *pixels) {
    return save_rgb_png_pixels_sized(path, pixels, 320, 200);
}

static int save_rgb_png(const char *path) {
    vga_render_rgb(rgba_frame);
    return save_rgb_png_pixels(path, rgba_frame);
}

static int event_compare(const void *left, const void *right) {
    const struct script_event *a = (const struct script_event *)left;
    const struct script_event *b = (const struct script_event *)right;
    if (a->at_ms < b->at_ms) return -1;
    if (a->at_ms > b->at_ms) return 1;
    return a->order < b->order ? -1 : (a->order > b->order ? 1 : 0);
}

int platform_set_script(const char *path) {
    char line[8192];
    FILE *file;
    unsigned order = 0;
    if (!path || !*path) return 1;
    file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Could not read script %s\n", path);
        return 0;
    }
    while (fgets(line, sizeof(line), file)) {
        unsigned long long at_ms;
        char action[32], argument[4096] = "";
        char *cursor = line;
        struct script_event event;
        while (isspace((unsigned char)*cursor)) ++cursor;
        if (!*cursor || *cursor == '#') continue;
        if (sscanf(cursor, "%llu %31s %4095s", &at_ms, action, argument) < 2) {
            fprintf(stderr, "Malformed script line: %s", line);
            fclose(file);
            return 0;
        }
        memset(&event, 0, sizeof(event));
        event.at_ms = (uint64_t)at_ms;
        event.order = order++;
        if (!SDL_strcasecmp(action, "key")) event.action = SCRIPT_KEY;
        else if (!SDL_strcasecmp(action, "keydown")) event.action = SCRIPT_KEYDOWN;
        else if (!SDL_strcasecmp(action, "keyup")) event.action = SCRIPT_KEYUP;
        else if (!SDL_strcasecmp(action, "shot")) event.action = SCRIPT_SHOT;
        else if (!SDL_strcasecmp(action, "page")) event.action = SCRIPT_PAGE;
        else if (!SDL_strcasecmp(action, "quit")) event.action = SCRIPT_QUIT;
        else {
            fprintf(stderr, "Unknown script action: %s\n", action);
            fclose(file);
            return 0;
        }
        if (event.action == SCRIPT_KEY || event.action == SCRIPT_KEYDOWN || event.action == SCRIPT_KEYUP) {
            uint8_t code;
            int extended;
            event.key = script_scancode(argument);
            if (!argument[0] || event.key == SDL_SCANCODE_UNKNOWN || !xt_scancode(event.key, &code, &extended)) {
                fprintf(stderr, "Unknown script key: %s\n", argument);
                fclose(file);
                return 0;
            }
            event.extended = extended;
        } else if (event.action == SCRIPT_SHOT || event.action == SCRIPT_PAGE) {
            if (!argument[0]) {
                fprintf(stderr, "Shot event needs a PNG path\n");
                fclose(file);
                return 0;
            }
            if (!(argument[0] == '/' || argument[0] == '\\' ||
                  (argument[0] && argument[1] == ':'))) {
                char script_dir[4096];
                const char *last_slash = strrchr(path, '/');
                const char *last_backslash = strrchr(path, '\\');
                const char *last = last_slash;
                if (!last || (last_backslash && last_backslash > last)) last = last_backslash;
                size_t dir_length = last ? (size_t)(last - path + 1) : 0;
                if (dir_length >= sizeof(script_dir)) dir_length = 0;
                memcpy(script_dir, path, dir_length);
                script_dir[dir_length] = 0;
                if (snprintf(event.argument, sizeof(event.argument), "%s%s", script_dir, argument) >= (int)sizeof(event.argument)) {
                    fprintf(stderr, "Shot path is too long\n");
                    fclose(file);
                    return 0;
                }
            } else if (snprintf(event.argument, sizeof(event.argument), "%s", argument) >= (int)sizeof(event.argument)) {
                fprintf(stderr, "Shot path is too long\n");
                fclose(file);
                return 0;
            }
        }
        if (script_event_count >= 4096) {
            fprintf(stderr, "Script has too many events\n");
            fclose(file);
            return 0;
        }
        struct script_event *new_events = (struct script_event *)realloc(script_events, (script_event_count + 1) * sizeof(*new_events));
        if (!new_events) {
            fclose(file);
            return 0;
        }
        script_events = new_events;
        script_events[script_event_count++] = event;
    }
    fclose(file);
    qsort(script_events, script_event_count, sizeof(*script_events), event_compare);
    memset(scripted_releases, 0, sizeof(scripted_releases));
    script_event_cursor = 0;
    script_origin = SDL_GetPerformanceCounter();
    return 1;
}

static void process_script_events(void) {
    uint64_t now = script_now_ms();
    for (size_t i = 0; i < sizeof(scripted_releases) / sizeof(scripted_releases[0]); ++i) {
        if (scripted_releases[i].active && now >= scripted_releases[i].at_ms) {
            send_script_key_routed(scripted_releases[i].key, 0,
                                   scripted_releases[i].extended,
                                   scripted_releases[i].game_input);
            scripted_releases[i].active = 0;
        }
    }
    while (script_event_cursor < script_event_count && script_events[script_event_cursor].at_ms <= now) {
        struct script_event *event = &script_events[script_event_cursor++];
        switch (event->action) {
        case SCRIPT_KEY:
            {
                int game_input = SDL_GetAtomicInt(&game_thread_started);
                send_script_key_routed(event->key, 1, event->extended, game_input);
                schedule_script_release(event->key, event->extended, game_input, now);
            }
            break;
        case SCRIPT_KEYDOWN:
            send_script_key(event->key, 1, event->extended);
            break;
        case SCRIPT_KEYUP:
            send_script_key(event->key, 0, event->extended);
            break;
        case SCRIPT_SHOT:
            if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
            (void)snprintf(pending_script_shot, sizeof(pending_script_shot), "%s", event->argument);
            if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
            break;
        case SCRIPT_PAGE:
            if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
            (void)snprintf(pending_script_page, sizeof(pending_script_page), "%s", event->argument);
            if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
            break;
        case SCRIPT_QUIT:
            if (verify_native) present_report();
            port_wide_pass_report();
            save_windowed_size();
            fflush(NULL);
            SDL_Quit();
            _Exit(0);
        }
    }
}

static int classic_canvas_height(void) {
    return pc_settings.pixel_aspect == PC_PIXEL_ASPECT_SQUARE ? 200 : 240;
}

static void classic_presentation_rect(int out_w, int out_h, SDL_FRect *destination) {
    int canvas_h = classic_canvas_height();
    float width, height;
    if (out_w <= 0 || out_h <= 0) {
        *destination = (SDL_FRect){ 0, 0, 0, 0 };
        return;
    }
    width = (float)out_w;
    height = width * (float)canvas_h / 320.0f;
    if (height > (float)out_h) {
        height = (float)out_h;
        width = height * 320.0f / (float)canvas_h;
    }
    if (pc_settings.integer_scale) {
        int scale_x = out_w / 320;
        int scale_y = out_h / canvas_h;
        int scale = scale_x < scale_y ? scale_x : scale_y;
        if (scale >= 1) {
            width = (float)(320 * scale);
            height = (float)(canvas_h * scale);
        }
    }
    destination->x = ((float)out_w - width) * 0.5f;
    destination->y = ((float)out_h - height) * 0.5f;
    destination->w = width;
    destination->h = height;
}

static float configured_aspect_ratio(int out_w, int out_h)
{
    switch (pc_settings.aspect) {
    case PC_ASPECT_4_3: return 4.0f / 3.0f;
    case PC_ASPECT_16_10: return 16.0f / 10.0f;
    case PC_ASPECT_16_9: return 16.0f / 9.0f;
    case PC_ASPECT_21_9: return 21.0f / 9.0f;
    case PC_ASPECT_32_9: return 32.0f / 9.0f;
    case PC_ASPECT_AUTO:
    default:
        return out_h > 0 ? (float)out_w / (float)out_h : 4.0f / 3.0f;
    }
}

static int native_canvas_width(int out_w, int out_h)
{
    double pixel_height = pc_settings.pixel_aspect == PC_PIXEL_ASPECT_SQUARE ? 1.0 : 1.2;
    double width = 200.0 * pixel_height * configured_aspect_ratio(out_w, out_h);
    int rounded = (int)floor(width + 0.5);
    if (rounded < 320) rounded = 320;
    if (rounded > 4096) rounded = 4096;
    return rounded;
}

static void enhanced_presentation_rect(int out_w, int out_h, int canvas_width,
                                      SDL_FRect *destination)
{
    float canvas_height = 200.0f *
        (pc_settings.pixel_aspect == PC_PIXEL_ASPECT_SQUARE ? 1.0f : 1.2f);
    float scale;
    if (out_w <= 0 || out_h <= 0 || canvas_width <= 0) {
        *destination = (SDL_FRect){ 0, 0, 0, 0 };
        return;
    }
    scale = (float)out_w / (float)canvas_width;
    if ((float)out_h / canvas_height < scale)
        scale = (float)out_h / canvas_height;
    if (pc_settings.integer_scale) {
        int scale_x = out_w / canvas_width;
        int scale_y = (int)((float)out_h / canvas_height);
        int whole = scale_x < scale_y ? scale_x : scale_y;
        if (whole >= 1)
            scale = (float)whole;
    }
    destination->w = canvas_width * scale;
    destination->h = canvas_height * scale;
    destination->x = ((float)out_w - destination->w) * 0.5f;
    destination->y = ((float)out_h - destination->h) * 0.5f;
}

static int ensure_script_shot_pixels(size_t needed)
{
    uint32_t *resized;
    if (needed <= script_shot_capacity)
        return 1;
    resized = (uint32_t *)realloc(script_shot_pixels, needed * sizeof(*script_shot_pixels));
    if (!resized)
        return 0;
    script_shot_pixels = resized;
    script_shot_capacity = needed;
    return 1;
}

static int has_script_shot(void)
{
    int pending;
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    pending = pending_script_shot[0] != 0;
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
    return pending;
}

static int take_script_shot(char *path, size_t capacity)
{
    int pending;
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    pending = pending_script_shot[0] != 0;
    if (pending) {
        (void)snprintf(path, capacity, "%s", pending_script_shot);
        pending_script_shot[0] = 0;
    }
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
    return pending;
}

static void save_pending_script_shot(const uint32_t *pixels, unsigned width, unsigned height)
{
    char path[4096];
    if (!take_script_shot(path, sizeof(path)))
        return;
    if (!save_rgb_png_pixels_sized(path, pixels, width, height))
        fprintf(stderr, "Could not write script shot %s\n", path);
    else
        fprintf(stderr, "[port] shot %s (%ux%u native canvas)\n", path, width, height);
}

static int ensure_sharp_texture(int width, int height) {
    if (sharp_texture && sharp_width == width && sharp_height == height) return 1;
    if (sharp_texture) SDL_DestroyTexture(sharp_texture);
    sharp_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_TARGET, width, height);
    sharp_width = sharp_texture ? width : 0;
    sharp_height = sharp_texture ? height : 0;
    if (!sharp_texture) fprintf(stderr, "Could not create sharp-filter target: %s\n", SDL_GetError());
    return sharp_texture != NULL;
}

static void render_classic_picture(void) {
    int out_w = 0, out_h = 0;
    SDL_FRect destination;
    vga_render_rgb(rgba_frame);         /* palette decoded the way the current mode shows it */
    if (has_script_shot())
        save_pending_script_shot(rgba_frame, 320, 200);
    (void)SDL_UpdateTexture(screen_texture, NULL, rgba_frame, 320 * (int)sizeof(uint32_t));
    (void)SDL_GetRenderOutputSize(renderer, &out_w, &out_h);
    classic_presentation_rect(out_w, out_h, &destination);
    (void)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    (void)SDL_RenderClear(renderer);
    if (pc_settings.filter == PC_FILTER_SHARP) {
        int canvas_h = classic_canvas_height();
        int scale_x = (int)(destination.w / 320.0f);
        int scale_y = (int)(destination.h / (float)canvas_h);
        int scale = scale_x < scale_y ? scale_x : scale_y;
        if (scale < 1) scale = 1;
        if (ensure_sharp_texture(320 * scale, canvas_h * scale)) {
            SDL_FRect target = { 0, 0, (float)(320 * scale), (float)(canvas_h * scale) };
            (void)SDL_SetTextureScaleMode(screen_texture, SDL_SCALEMODE_NEAREST);
            (void)SDL_SetRenderTarget(renderer, sharp_texture);
            (void)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            (void)SDL_RenderClear(renderer);
            (void)SDL_RenderTexture(renderer, screen_texture, NULL, &target);
            (void)SDL_SetRenderTarget(renderer, NULL);
            (void)SDL_SetTextureScaleMode(sharp_texture, SDL_SCALEMODE_LINEAR);
            (void)SDL_RenderTexture(renderer, sharp_texture, NULL, &destination);
        } else {
            (void)SDL_SetTextureScaleMode(screen_texture, SDL_SCALEMODE_NEAREST);
            (void)SDL_RenderTexture(renderer, screen_texture, NULL, &destination);
        }
    } else {
        (void)SDL_SetTextureScaleMode(screen_texture,
            pc_settings.filter == PC_FILTER_LINEAR ? SDL_SCALEMODE_LINEAR : SDL_SCALEMODE_NEAREST);
        (void)SDL_RenderTexture(renderer, screen_texture, NULL, &destination);
    }
    (void)SDL_RenderPresent(renderer);
}

static int renderer_is_enhanced(void) {
    if (renderer_override >= 0)
        return renderer_override;
    return pc_settings.renderer == PC_RENDERER_ENHANCED;
}

static void render_enhanced_picture(void) {
    int out_w = 0, out_h = 0;
    int canvas_width, picture_width;
    SDL_Texture *picture;
    const uint32_t *pixels = NULL;
    int shot_pending = has_script_shot();
    char shot_path[4096];
    int shot_path_ready = 0;
    (void)SDL_GetRenderOutputSize(renderer, &out_w, &out_h);
    canvas_width = pc_settings.widescreen ? native_canvas_width(out_w, out_h) : SCENE_WIDTH;
    scene_set_wide(canvas_width, pc_settings.widescreen, pc_settings.wide_activity);
    scene_set_active(1);
    picture = present_texture(renderer, canvas_width, &pixels);
    picture_width = canvas_width;
    if (shot_pending && picture && pixels) {
        shot_path_ready = take_script_shot(shot_path, sizeof(shot_path));
        if (shot_path_ready && !save_rgb_png_pixels_sized(shot_path, pixels, (unsigned)picture_width, 200))
            fprintf(stderr, "Could not write script shot %s\n", shot_path);
    }
    if (!picture) {                              /* nothing drawn yet: black, never the EGA page */
        (void)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        (void)SDL_RenderClear(renderer);
        (void)SDL_RenderPresent(renderer);
        return;
    }

    SDL_FRect destination;
    enhanced_presentation_rect(out_w, out_h, picture_width, &destination);
    (void)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    (void)SDL_RenderClear(renderer);
    if (pc_settings.filter == PC_FILTER_SHARP) {
        int canvas_h = classic_canvas_height();
        int scale_x = (int)(destination.w / (float)picture_width);
        int scale_y = (int)(destination.h / (float)canvas_h);
        int scale = scale_x < scale_y ? scale_x : scale_y;
        if (scale < 1) scale = 1;
        if (ensure_sharp_texture(picture_width * scale, canvas_h * scale)) {
            SDL_FRect staging = { 0, 0, (float)(picture_width * scale), (float)(canvas_h * scale) };
            (void)SDL_SetTextureScaleMode(picture, SDL_SCALEMODE_NEAREST);
            (void)SDL_SetRenderTarget(renderer, sharp_texture);
            (void)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            (void)SDL_RenderClear(renderer);
            (void)SDL_RenderTexture(renderer, picture, NULL, &staging);
            (void)SDL_SetRenderTarget(renderer, NULL);
            (void)SDL_SetTextureScaleMode(sharp_texture, SDL_SCALEMODE_LINEAR);
            (void)SDL_RenderTexture(renderer, sharp_texture, NULL, &destination);
        } else {
            (void)SDL_SetTextureScaleMode(picture, SDL_SCALEMODE_NEAREST);
            (void)SDL_RenderTexture(renderer, picture, NULL, &destination);
        }
    } else {
        (void)SDL_SetTextureScaleMode(picture,
            pc_settings.filter == PC_FILTER_LINEAR ? SDL_SCALEMODE_LINEAR : SDL_SCALEMODE_NEAREST);
        (void)SDL_RenderTexture(renderer, picture, NULL, &destination);
    }
    (void)SDL_RenderPresent(renderer);
    if (shot_path_ready)
        fprintf(stderr, "[port] shot %s (%dx200 native canvas)\n", shot_path, picture_width);
}

/* "page" script events: the emulated EGA page as the game left it (a test reference). */
static void save_pending_script_page(void)
{
    char path[4096];
    static uint32_t page[320 * 200];
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    (void)snprintf(path, sizeof(path), "%s", pending_script_page);
    pending_script_page[0] = 0;
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
    if (!path[0]) return;
    vga_render_rgb(page);
    if (!save_rgb_png_pixels_sized(path, page, 320, 200))
        fprintf(stderr, "Could not write script page %s\n", path);
    else
        fprintf(stderr, "[port] page %s\n", path);
}

static void render_frame(void) {
    save_pending_script_page();
    if (renderer_is_enhanced()) {
        render_enhanced_picture();
    } else {
        scene_set_active(0);
        render_classic_picture();
    }
}

static void remember_windowed_size(void) {
    if (window && !fullscreen) {
        int width = 0, height = 0;
        SDL_GetWindowSize(window, &width, &height);
        if (width >= 320 && width <= 7680) pc_settings.window_width = width;
        if (height >= 200 && height <= 4320) pc_settings.window_height = height;
    }
}

void platform_apply_window_settings(void) {
    int requested_fullscreen = pc_settings.fullscreen != 0;
    if (!window) return;
    if (pc_is_game_thread()) {
        SDL_SetAtomicInt(&window_settings_requested, 1);
        return;
    }
    if (requested_fullscreen != fullscreen) {
        if (requested_fullscreen) remember_windowed_size();
        if (SDL_SetWindowFullscreen(window, requested_fullscreen)) fullscreen = requested_fullscreen;
        else {
            fprintf(stderr, "Could not change fullscreen state: %s\n", SDL_GetError());
            pc_settings.fullscreen = fullscreen;
        }
    }
    if (!fullscreen)
        (void)SDL_SetWindowSize(window, pc_settings.window_width, pc_settings.window_height);
}

static void toggle_fullscreen(void) {
    pc_settings.fullscreen = !fullscreen;
    platform_apply_window_settings();
    pc_config_save();
}

static void save_windowed_size(void) {
    if (window && !fullscreen) {
        remember_windowed_size();
        pc_config_save();
    }
}

static void handle_event(const SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT || event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        /* Closing the window ends the program at once, like switching the PC off (the
           game's own Q)uit is the orderly way out); it must work even if the game is stuck. */
        if (window_open) {
            window_open = 0;
            if (SDL_GetAtomicInt(&game_thread_started)) {
                save_windowed_size();
                fflush(NULL);
                SDL_Quit();
                _Exit(0);
            }
            push_launcher_key(0x01);
        }
        return;
    }
    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
        int down = event->type == SDL_EVENT_KEY_DOWN;
        if (down && !event->key.repeat && event->key.scancode == SDL_SCANCODE_RETURN && (event->key.mod & SDL_KMOD_ALT)) {
            toggle_fullscreen();
            return;
        }
        uint8_t code;
        int extended;
        if (event->key.repeat || !xt_scancode(event->key.scancode, &code, &extended)) return;
        if (!down) code |= 0x80;
        send_xt_code(code, extended);
    }
}

int platform_init(const char *data_dir) {
    const char *base_path;
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }
    trace_mutex = SDL_CreateMutex();
    launcher_key_mutex = SDL_CreateMutex();
    launcher_key_read = launcher_key_write = 0;
    SDL_SetAtomicInt(&modal_keyboard_capture, 0);
    if (!pc_speaker_init())                         /* no sound device: play silently */
        fprintf(stderr, "PC speaker: no audio output (%s)\n", SDL_GetError());
    if (!trace_mutex || !launcher_key_mutex) return 0;
    if (data_dir && *data_dir) {
        if (snprintf(pc_data_directory, sizeof(pc_data_directory), "%s", data_dir) >= (int)sizeof(pc_data_directory)) return 0;
    } else {
        base_path = SDL_GetBasePath();     /* owned and cached by SDL3: never free it */
        if (!base_path || snprintf(pc_data_directory, sizeof(pc_data_directory), "%s", base_path) >= (int)sizeof(pc_data_directory))
            return 0;
    }
    pc_config_load();
    read_native_command_options();
    if (!scene_init()) {
        fprintf(stderr, "Could not create the native scene.\n");
        return 0;
    }
    scene_set_active(renderer_is_enhanced());
    present_set_verify(verify_native);
    pc_speaker_set_stereo(pc_settings.stereo);
    window = SDL_CreateWindow("Duke Nukum v2.0", pc_settings.window_width, pc_settings.window_height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 0;
    }
    (void)SDL_SetWindowMinimumSize(window, 320, 240);
    fullscreen = 0;
    platform_apply_window_settings();
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return 0;
    }
    screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 320, 200);
    if (!screen_texture) {
        fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
        return 0;
    }
    (void)SDL_SetTextureScaleMode(screen_texture, SDL_SCALEMODE_NEAREST);
    if (!pc_interrupt_init()) {
        fprintf(stderr, "Could not create interrupt synchronization primitives.\n");
        return 0;
    }
    pc_interrupt_start_timer();
    SDL_SetAtomicInt(&episode_exit_requested, 0);
    SDL_SetAtomicInt(&window_settings_requested, 0);
    window_open = 1;
    return 1;
}

static int game_thread_main(void *opaque) {
    struct game_call { episode_main entry; int argc; char **argv; } *call = opaque;
    jmp_buf exit_target;
    int result = setjmp(exit_target);
    pc_game_thread_id = SDL_GetCurrentThreadID();
    SDL_SetAtomicInt(&game_thread_started, 1);
    game_exit_target = &exit_target;
    if (result == 0) call->entry(call->argc, call->argv);
    game_exit_target = NULL;
    SDL_SetAtomicInt(&game_thread_started, 0);
    SDL_SetAtomicInt(&game_finished, 1);
    return SDL_GetAtomicInt(&game_status);
}

void pc_exit(int16_t status) {
    port_wide_pass_abandon("pc_exit");
    if (pc_is_game_thread() && game_exit_target) {
        SDL_SetAtomicInt(&game_status, status);
        SDL_SetAtomicInt(&episode_exit_requested, 1);
        longjmp(*game_exit_target, 1);
    }
    pc_set_quit_hint();
}

int platform_run_episode(episode_main entry, int argc, char **argv) {
    struct game_call { episode_main entry; int argc; char **argv; } call;
    SDL_Thread *thread;
    if (!entry) return -1;
    scene_set_active(renderer_is_enhanced());
    call.entry = entry;
    call.argc = argc;
    call.argv = argv;
    SDL_SetAtomicInt(&game_finished, 0);
    SDL_SetAtomicInt(&game_status, 0);
    SDL_SetAtomicInt(&episode_exit_requested, 0);
    SDL_SetAtomicInt(&window_settings_requested, 0);
    pc_spin_iterations = 0;
    pc_episode_allocations_begin();
    thread = SDL_CreateThread(game_thread_main, "duke-game", &call);
    if (!thread) {
        fprintf(stderr, "Could not start episode thread: %s\n", SDL_GetError());
        pc_episode_allocations_release();
        return -1;
    }
    uint64_t last_frame = SDL_GetPerformanceCounter();
    uint64_t frequency = SDL_GetPerformanceFrequency();
    while (!SDL_GetAtomicInt(&game_finished)) {
        SDL_Event event;
        process_script_events();
        while (SDL_PollEvent(&event)) handle_event(&event);
        if (SDL_GetAtomicInt(&window_settings_requested)) {
            SDL_SetAtomicInt(&window_settings_requested, 0);
            platform_apply_window_settings();
        }
        uint64_t now = SDL_GetPerformanceCounter();
        if (window_open && (double)(now - last_frame) * 70.0 >= (double)frequency) {
            render_frame();
            last_frame = now;
        }
        SDL_Delay(1);
    }
    int thread_status = 0;
    SDL_WaitThread(thread, &thread_status);
    pc_episode_allocations_release();
    return thread_status;
}

void platform_prepare_episode_state(int16_t episode, unsigned char *begin,
                                    unsigned char *end)
{
    size_t size;
    if (episode < 1 || episode > 3 || !begin || !end || end <= begin) {
        fprintf(stderr, "[port] invalid episode %d state block\n", (int)episode);
        return;
    }
    size = (size_t)(end - begin);
    if (episode_state_begin[episode] &&
        (episode_state_begin[episode] != begin || episode_state_size[episode] != size)) {
        fprintf(stderr, "[port] episode %d state block changed bounds\n", (int)episode);
        return;
    }
    episode_state_begin[episode] = begin;
    episode_state_size[episode] = size;
    current_episode = episode;
    if (!episode_state_snapshot[episode]) {
        episode_state_snapshot[episode] = (unsigned char *)malloc(size);
        if (!episode_state_snapshot[episode]) {
            fprintf(stderr, "[port] could not allocate episode %d state snapshot (%zu bytes)\n",
                    (int)episode, size);
            return;
        }
        memcpy(episode_state_snapshot[episode], begin, size);
        fprintf(stderr, "[port] episode %d state snapshot: %zu bytes\n",
                (int)episode, size);
    } else {
        memcpy(begin, episode_state_snapshot[episode], size);
        fprintf(stderr, "[port] episode %d state restored: %zu bytes\n",
                (int)episode, size);
    }
}

/* The running episode's variables (the wide presentation pass saves and restores them). */
int platform_current_episode_state(unsigned char **begin, size_t *size)
{
    if (current_episode < 1 || current_episode > 3 || !episode_state_begin[current_episode]) return 0;
    *begin = episode_state_begin[current_episode];
    *size = episode_state_size[current_episode];
    return 1;
}

void platform_reset_episode(void)
{
    pc_interrupt_reset();
    pc_io_reset();
    pc_speaker_reset();
    memset(keyboard_game_route, 0, sizeof(keyboard_game_route));
    bios_set_mode(0x0d);

    present_shutdown();
    scene_reset();

    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    launcher_key_read = launcher_key_write = 0;
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
    SDL_SetAtomicInt(&modal_keyboard_capture, 0);
    SDL_SetAtomicInt(&episode_exit_requested, 0);
    SDL_SetAtomicInt(&window_settings_requested, 0);
    pc_spin_iterations = 0;
}

void platform_shutdown(void) {
    save_windowed_size();
    pc_interrupt_shutdown();
    pc_speaker_shutdown();
    if (verify_native) present_report();
    port_wide_pass_report();
    present_shutdown();
    scene_shutdown();
    pc_release_all_allocations();
    if (sharp_texture) SDL_DestroyTexture(sharp_texture);
    if (screen_texture) SDL_DestroyTexture(screen_texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (launcher_key_mutex) SDL_DestroyMutex(launcher_key_mutex);
    if (trace_mutex) SDL_DestroyMutex(trace_mutex);
    screen_texture = NULL;
    sharp_texture = NULL;
    renderer = NULL;
    window = NULL;
    trace_mutex = NULL;
    launcher_key_mutex = NULL;
    free(script_events);
    script_events = NULL;
    script_event_count = script_event_cursor = 0;
    for (int episode = 1; episode <= 3; ++episode) {
        free(episode_state_snapshot[episode]);
        episode_state_snapshot[episode] = NULL;
        episode_state_begin[episode] = NULL;
        episode_state_size[episode] = 0;
    }
    SDL_Quit();
}

int platform_poll_key(void) {
    static uint64_t last_present;
    SDL_Event event;
    uint64_t now;
    process_script_events();
    while (SDL_PollEvent(&event)) handle_event(&event);
    /* The launcher's dialogs wait here: keep the window presented (and script shots taken)
       at display rate, not only when the dialog redraws. */
    now = SDL_GetTicksNS();
    if (window_open && now - last_present >= 16000000ull) {
        render_frame();
        last_present = now;
    }
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    int key = 0;
    if (launcher_key_read != launcher_key_write) {
        key = launcher_keys[launcher_key_read];
        launcher_key_read = (launcher_key_read + 1) % (unsigned)sizeof(launcher_keys);
    }
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
    if (!key) SDL_Delay(1);
    return key;
}

int platform_poll_modal_key(void) {
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    int key = 0;
    if (launcher_key_read != launcher_key_write) {
        key = launcher_keys[launcher_key_read];
        launcher_key_read = (launcher_key_read + 1) % (unsigned)sizeof(launcher_keys);
    }
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
    if (!key) SDL_Delay(1);
    return key;
}

void platform_begin_modal_keyboard_capture(void) {
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    SDL_SetAtomicInt(&modal_keyboard_capture, 1);
    launcher_key_read = launcher_key_write;
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
}

void platform_end_modal_keyboard_capture(void) {
    if (launcher_key_mutex) SDL_LockMutex(launcher_key_mutex);
    launcher_key_read = launcher_key_write;
    SDL_SetAtomicInt(&modal_keyboard_capture, 0);
    if (launcher_key_mutex) SDL_UnlockMutex(launcher_key_mutex);
}

int platform_episode_exit_requested(void) {
    return SDL_GetAtomicInt(&episode_exit_requested);
}

void platform_present_frame(void) {
    if (window_open) render_frame();
}
