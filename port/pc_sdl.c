#include "pc_internal.h"
#include <ctype.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned pc_trace_flags;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *screen_texture;
static SDL_Mutex *trace_mutex;
static SDL_AtomicInt game_finished;
static SDL_AtomicInt game_status;
static SDL_AtomicInt game_thread_started;
static int fullscreen;
static int window_open;
static uint32_t rgba_frame[320u * 200u];
static uint8_t launcher_keys[64];
static unsigned launcher_key_read;
static unsigned launcher_key_write;
static _Thread_local jmp_buf *game_exit_target;
static SDL_AtomicInt episode_exit_requested;

enum script_action { SCRIPT_KEY, SCRIPT_KEYDOWN, SCRIPT_KEYUP, SCRIPT_SHOT, SCRIPT_QUIT };
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
    int active;
};
static struct script_event *script_events;
static size_t script_event_count;
static size_t script_event_cursor;
static struct scripted_release scripted_releases[64];
static uint64_t script_origin;
static unsigned pc_spin_iterations;

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
    /* One millisecond sleeps can round to a longer Windows timer quantum. A 440-pass batch
       amortizes that yield while matching the fixed-cycle 386 reference's menu transitions. */
    if (++pc_spin_iterations >= PC_SPIN_BATCH) {
        pc_spin_iterations = 0;
        SDL_Delay(1);
    }
}

int pc_is_game_thread(void) {
    return SDL_GetAtomicInt(&game_thread_started) && pc_game_thread_id == SDL_GetCurrentThreadID();
}

static void push_launcher_key(uint8_t scan_code) {
    unsigned next = (launcher_key_write + 1) % (unsigned)sizeof(launcher_keys);
    if (next == launcher_key_read) return;
    launcher_keys[launcher_key_write] = scan_code;
    launcher_key_write = next;
}

static void send_xt_code(uint8_t scan_code, int extended) {
    if (extended) pc_keyboard_scancode(0xe0);
    pc_keyboard_scancode(scan_code);
    if (window_open) push_launcher_key(scan_code);
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

static void send_script_key(SDL_Scancode key, int down, int extended) {
    uint8_t code;
    int ignored_extended;
    if (!xt_scancode(key, &code, &ignored_extended)) return;
    if (!down) code |= 0x80u;
    if (SDL_GetAtomicInt(&game_thread_started)) {
        send_xt_code(code, extended);
    } else {
        if (extended) push_launcher_key(0xe0);
        push_launcher_key(code);
    }
}

static void schedule_script_release(SDL_Scancode key, int extended, uint64_t at_ms) {
    for (size_t i = 0; i < sizeof(scripted_releases) / sizeof(scripted_releases[0]); ++i) {
        if (!scripted_releases[i].active) {
            scripted_releases[i].active = 1;
            scripted_releases[i].key = key;
            scripted_releases[i].extended = extended;
            scripted_releases[i].at_ms = at_ms + 45;
            return;
        }
    }
    send_script_key(key, 0, extended);
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

static int save_rgb_png(const char *path) {
    static const uint8_t signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    uint8_t ihdr[13] = { 0, 0, 1, 64, 0, 0, 0, 200, 8, 2, 0, 0, 0 };
    const size_t raw_size = 200u * (1u + 320u * 3u);
    const size_t blocks = (raw_size + 65534u) / 65535u;
    const size_t z_size = 2u + raw_size + blocks * 5u + 4u;
    uint8_t *raw = (uint8_t *)malloc(raw_size);
    uint8_t *zdata = (uint8_t *)malloc(z_size);
    FILE *file;
    size_t out = 0, source = 0;
    uint32_t adler_a = 1, adler_b = 0;
    int ok = 0;
    if (!raw || !zdata) goto done;
    vga_render_rgb(rgba_frame);
    for (unsigned y = 0; y < 200; ++y) {
        raw[out++] = 0;
        for (unsigned x = 0; x < 320; ++x) {
            uint32_t pixel = rgba_frame[source++];
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
        } else if (event.action == SCRIPT_SHOT) {
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
            send_script_key(scripted_releases[i].key, 0, scripted_releases[i].extended);
            scripted_releases[i].active = 0;
        }
    }
    while (script_event_cursor < script_event_count && script_events[script_event_cursor].at_ms <= now) {
        struct script_event *event = &script_events[script_event_cursor++];
        switch (event->action) {
        case SCRIPT_KEY:
            send_script_key(event->key, 1, event->extended);
            schedule_script_release(event->key, event->extended, now);
            break;
        case SCRIPT_KEYDOWN:
            send_script_key(event->key, 1, event->extended);
            break;
        case SCRIPT_KEYUP:
            send_script_key(event->key, 0, event->extended);
            break;
        case SCRIPT_SHOT:
            if (!save_rgb_png(event->argument)) fprintf(stderr, "Could not write script shot %s\n", event->argument);
            else fprintf(stderr, "[port] shot %s\n", event->argument);
            break;
        case SCRIPT_QUIT:
            fflush(NULL);
            SDL_Quit();
            _Exit(0);
        }
    }
}

static void render_frame(void) {
    int out_w = 0, out_h = 0;
    SDL_FRect destination;
    vga_render_rgb(rgba_frame);         /* palette decoded the way the current mode shows it */
    (void)SDL_UpdateTexture(screen_texture, NULL, rgba_frame, 320 * (int)sizeof(uint32_t));
    (void)SDL_GetRenderOutputSize(renderer, &out_w, &out_h);
    float width = (float)out_w;
    float height = width * 3.0f / 4.0f;
    if (height > (float)out_h) {
        height = (float)out_h;
        width = height * 4.0f / 3.0f;
    }
    destination.x = ((float)out_w - width) * 0.5f;
    destination.y = ((float)out_h - height) * 0.5f;
    destination.w = width;
    destination.h = height;
    (void)SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    (void)SDL_RenderClear(renderer);
    (void)SDL_RenderTexture(renderer, screen_texture, NULL, &destination);
    (void)SDL_RenderPresent(renderer);
}

static void handle_event(const SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT || event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        /* Closing the window ends the program at once, like switching the PC off (the
           game's own Q)uit is the orderly way out); it must work even if the game is stuck. */
        if (window_open) {
            window_open = 0;
            if (SDL_GetAtomicInt(&game_thread_started)) {
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
        if (down && event->key.scancode == SDL_SCANCODE_RETURN && (event->key.mod & SDL_KMOD_ALT)) {
            fullscreen = !fullscreen;
            (void)SDL_SetWindowFullscreen(window, fullscreen);
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
    if (!pc_speaker_init())                         /* no sound device: play silently */
        fprintf(stderr, "PC speaker: no audio output (%s)\n", SDL_GetError());
    if (!trace_mutex) return 0;
    if (data_dir && *data_dir) {
        if (snprintf(pc_data_directory, sizeof(pc_data_directory), "%s", data_dir) >= (int)sizeof(pc_data_directory)) return 0;
    } else {
        base_path = SDL_GetBasePath();     /* owned and cached by SDL3: never free it */
        if (!base_path || snprintf(pc_data_directory, sizeof(pc_data_directory), "%s", base_path) >= (int)sizeof(pc_data_directory))
            return 0;
    }
    window = SDL_CreateWindow("Duke Nukum v2.0", 960, 720, SDL_WINDOW_RESIZABLE);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 0;
    }
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

void pc_exit(int status) {
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
    call.entry = entry;
    call.argc = argc;
    call.argv = argv;
    SDL_SetAtomicInt(&game_finished, 0);
    SDL_SetAtomicInt(&game_status, 0);
    SDL_SetAtomicInt(&episode_exit_requested, 0);
    pc_spin_iterations = 0;
    thread = SDL_CreateThread(game_thread_main, "duke-game", &call);
    if (!thread) {
        fprintf(stderr, "Could not start episode thread: %s\n", SDL_GetError());
        return -1;
    }
    uint64_t last_frame = SDL_GetPerformanceCounter();
    uint64_t frequency = SDL_GetPerformanceFrequency();
    while (!SDL_GetAtomicInt(&game_finished)) {
        SDL_Event event;
        process_script_events();
        while (SDL_PollEvent(&event)) handle_event(&event);
        uint64_t now = SDL_GetPerformanceCounter();
        if (window_open && (double)(now - last_frame) * 70.0 >= (double)frequency) {
            render_frame();
            last_frame = now;
        }
        SDL_Delay(1);
    }
    int thread_status = 0;
    SDL_WaitThread(thread, &thread_status);
    return thread_status;
}

void platform_shutdown(void) {
    pc_interrupt_shutdown();
    pc_speaker_shutdown();
    if (screen_texture) SDL_DestroyTexture(screen_texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (trace_mutex) SDL_DestroyMutex(trace_mutex);
    screen_texture = NULL;
    renderer = NULL;
    window = NULL;
    trace_mutex = NULL;
    free(script_events);
    script_events = NULL;
    script_event_count = script_event_cursor = 0;
    SDL_Quit();
}

int platform_poll_key(void) {
    SDL_Event event;
    process_script_events();
    while (SDL_PollEvent(&event)) handle_event(&event);
    if (launcher_key_read == launcher_key_write) {
        SDL_Delay(1);
        return 0;
    }
    int key = launcher_keys[launcher_key_read];
    launcher_key_read = (launcher_key_read + 1) % (unsigned)sizeof(launcher_keys);
    return key;
}

int platform_episode_exit_requested(void) {
    return SDL_GetAtomicInt(&episode_exit_requested);
}

void platform_present_frame(void) {
    if (window_open) render_frame();
}
