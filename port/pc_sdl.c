#include "pc_internal.h"
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
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
        if (window_open) {
            window_open = 0;
            pc_set_quit_hint();
        }
        return;
    }
    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
        int down = event->type == SDL_EVENT_KEY_DOWN;
        if (event->key.scancode == SDL_SCANCODE_ESCAPE || event->key.scancode == SDL_SCANCODE_F10) {
            if (down) pc_set_quit_hint();
            return;
        }
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
    if (!trace_mutex) return 0;
    if (data_dir && *data_dir) {
        if (snprintf(pc_data_directory, sizeof(pc_data_directory), "%s", data_dir) >= (int)sizeof(pc_data_directory)) return 0;
    } else {
        base_path = SDL_GetBasePath();
        if (!base_path || snprintf(pc_data_directory, sizeof(pc_data_directory), "%s", base_path) >= (int)sizeof(pc_data_directory)) {
            if (base_path) SDL_free((void *)base_path);
            return 0;
        }
        SDL_free((void *)base_path);
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
    thread = SDL_CreateThread(game_thread_main, "duke-game", &call);
    if (!thread) {
        fprintf(stderr, "Could not start episode thread: %s\n", SDL_GetError());
        return -1;
    }
    uint64_t last_frame = SDL_GetPerformanceCounter();
    uint64_t frequency = SDL_GetPerformanceFrequency();
    while (!SDL_GetAtomicInt(&game_finished)) {
        SDL_Event event;
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
    if (screen_texture) SDL_DestroyTexture(screen_texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (trace_mutex) SDL_DestroyMutex(trace_mutex);
    screen_texture = NULL;
    renderer = NULL;
    window = NULL;
    trace_mutex = NULL;
    SDL_Quit();
}

int platform_poll_key(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) handle_event(&event);
    if (launcher_key_read == launcher_key_write) return 0;
    int key = launcher_keys[launcher_key_read];
    launcher_key_read = (launcher_key_read + 1) % (unsigned)sizeof(launcher_keys);
    return key;
}
