#define WIN32_LEAN_AND_MEAN
#include "wide_pass.h"
#include "platform.h"
#include "scene.h"
#include "pc_internal.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

void ep1_main(int16_t argc, char **argv);
void ep2_main(int16_t argc, char **argv);
void ep3_main(int16_t argc, char **argv);
extern unsigned char ep1_state_begin, ep1_state_end;
extern unsigned char ep2_state_begin, ep2_state_end;
extern unsigned char ep3_state_begin, ep3_state_end;
static int episode_one(int argc, char **argv) { ep1_main((int16_t)argc, argv); return 0; }
static int episode_two(int argc, char **argv) { ep2_main((int16_t)argc, argv); return 0; }
static int episode_three(int argc, char **argv) { ep3_main((int16_t)argc, argv); return 0; }

/* Episode-owned routines draw the chooser with the same font and border graphics as the game. */
#define DECLARE_EP_DIALOG(n) \
    extern char *ep##n##_d_6b54_; \
    void ep##n##_read_file_block(char *filename, void *buffer, uint16_t count); \
    void ep##n##_load_planar_image_file(char *filename, int16_t offset, int16_t count); \
    void ep##n##_clear_video_page(void); \
    void ep##n##_draw_framed_dialog_box(int16_t left, int16_t top, int16_t height); \
    void ep##n##_draw_text_string(char *text, int16_t x, int16_t y)

DECLARE_EP_DIALOG(1);
DECLARE_EP_DIALOG(2);
DECLARE_EP_DIALOG(3);

int16_t set_video_mode(int16_t mode);
int16_t select_draw_page(int16_t page);
int16_t show_video_page(int16_t page);

static const char *episode_border[4] = { NULL, "border.dn1", "border.dn2", "border.dn3" };
static const char *episode_font1[4] = { NULL, "font1.dn1", "font1.dn2", "font1.dn3" };
static const char *episode_font2[4] = { NULL, "font2.dn1", "font2.dn2", "font2.dn3" };
static int episode_dialog_graphics_loaded;
static int dialog_episode;

static void show_plain_message(const char *title, const char *message) {
    (void)SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
    fprintf(stderr, "%s: %s\n", title, message);
}

static int episode_files_present(int episode) {
    char map_name[32];
    char font_name[32];
    FILE *map, *font;
    snprintf(map_name, sizeof(map_name), "worldal1.dn%d", episode);
    snprintf(font_name, sizeof(font_name), "font1.dn%d", episode);
    map = pc_fopen(map_name, "rb");
    font = pc_fopen(font_name, "rb");
    int present = map != NULL && font != NULL;
    if (map) fclose(map);
    if (font) fclose(font);
    return present;
}

static int load_dialog_graphics_for(int episode) {
    FILE *probe;
    char *font_buffer;
    if (episode < 1 || episode > 3) return 0;
    const char *required[] = { episode_border[episode], episode_font1[episode], episode_font2[episode] };
    for (size_t i = 0; i < sizeof(required) / sizeof(required[0]); ++i) {
        probe = pc_fopen(required[i], "rb");
        if (!probe) return 0;
        fclose(probe);
    }

    set_video_mode(0);
    select_draw_page(0);
    show_video_page(0);
    font_buffer = (char *)malloc(4500);
    if (!font_buffer) return 0;
    switch (episode) {
    case 1:
        ep1_d_6b54_ = font_buffer;
        ep1_read_file_block((char *)episode_font1[episode], font_buffer, 2000);
        ep1_read_file_block((char *)episode_font2[episode], font_buffer + 2000, 2000);
        ep1_load_planar_image_file((char *)episode_border[episode], 0x3000, 7680);
        ep1_clear_video_page();
        break;
    case 2:
        ep2_d_6b54_ = font_buffer;
        ep2_read_file_block((char *)episode_font1[episode], font_buffer, 2000);
        ep2_read_file_block((char *)episode_font2[episode], font_buffer + 2000, 2000);
        ep2_load_planar_image_file((char *)episode_border[episode], 0x3000, 7680);
        ep2_clear_video_page();
        break;
    default:
        ep3_d_6b54_ = font_buffer;
        ep3_read_file_block((char *)episode_font1[episode], font_buffer, 2000);
        ep3_read_file_block((char *)episode_font2[episode], font_buffer + 2000, 2000);
        ep3_load_planar_image_file((char *)episode_border[episode], 0x3000, 7680);
        ep3_clear_video_page();
        break;
    }
    dialog_episode = episode;
    episode_dialog_graphics_loaded = 1;
    return 1;
}

static void draw_dialog_text(int episode, const char *text, int x, int y) {
    switch (episode) {
    case 1: ep1_draw_text_string((char *)text, (int16_t)x, (int16_t)y); break;
    case 2: ep2_draw_text_string((char *)text, (int16_t)x, (int16_t)y); break;
    default: ep3_draw_text_string((char *)text, (int16_t)x, (int16_t)y); break;
    }
}

static void draw_dialog_frame_at(int episode, int left, int top, int height) {
    switch (episode) {
    case 1: ep1_draw_framed_dialog_box((int16_t)left, (int16_t)top, (int16_t)height); break;
    case 2: ep2_draw_framed_dialog_box((int16_t)left, (int16_t)top, (int16_t)height); break;
    default: ep3_draw_framed_dialog_box((int16_t)left, (int16_t)top, (int16_t)height); break;
    }
}

static void draw_dialog_frame(int episode, int top, int height) {
    draw_dialog_frame_at(episode, 7, top, height);
}

static void render_episode_dialog(const int present[4], int selected) {
    static const int row_y[4] = { 0, 8, 10, 12 };
    static const char *const titles[4] = {
        "", "1  Episode ONE:", "2  Episode TWO:", "3  Episode THREE:"
    };
    static const char *const subtitles[4] = {
        "", "   Shrapnel City", "   Mission: Moonbase", "   Trapped in Future"
    };
    draw_dialog_frame(dialog_episode, 1, 10);    /* rows of 16 lines: border at 16..31, bottom at 176..191 */
    draw_dialog_text(dialog_episode, "DUKE NUKUM  v2.0", 12, 6);
    for (int episode = 1; episode <= 3; ++episode) {
        draw_dialog_text(dialog_episode, titles[episode], 9, row_y[episode]);
        draw_dialog_text(dialog_episode, subtitles[episode], 9, row_y[episode] + 1);
        if (!present[episode]) {
            for (uint8_t colour = 8; colour < 16; ++colour) {
                vga_replace_colour_in_text_span(colour, (uint8_t)(colour - 8),
                                                9, row_y[episode], 23, 2);
            }
        }
    }
    draw_dialog_text(dialog_episode, "S  Port settings", 9, 14);
    draw_dialog_text(dialog_episode, "Arrows + Enter: Select", 9, 16);
    draw_dialog_text(dialog_episode, "Esc  Quit", 9, 18);
    if (selected >= 1 && selected <= 3)
        draw_dialog_text(dialog_episode, ">", 8, row_y[selected]);
    else if (selected == 4)
        draw_dialog_text(dialog_episode, ">", 8, 14);
    (void)show_video_page(0);
    platform_present_frame();
}

static void render_settings_dialog(int episode, int selected, int in_game) {
    const int first_visible = selected < 11 ? 0 : selected - 10;
    const int base_x = 9;
    draw_dialog_frame(episode, 1, 10);
    draw_dialog_text(episode, "PORT SETTINGS", 13, 4);
    if (first_visible > 0) draw_dialog_text(episode, "^", 28, 5);
    for (int slot = 0; slot < 11; ++slot) {
        int row = first_visible + slot;
        int y = 6 + slot;
        if (row >= pc_config_count()) break;
        draw_dialog_text(episode, "                    ", base_x, y);
        if (pc_config_is_section(row)) {
            draw_dialog_text(episode, pc_config_label(row), base_x + 2, y);
        } else {
            char value[32];
            draw_dialog_text(episode, pc_config_label(row), base_x + 2, y);
            pc_config_value_text(row, value, sizeof(value));
            draw_dialog_text(episode, value, base_x + 12, y);
        }
        if (row == selected) draw_dialog_text(episode, ">", base_x, y);
    }
    if (first_visible + 11 < pc_config_count()) draw_dialog_text(episode, "v", 28, 17);
    draw_dialog_text(episode, "UP/DOWN MOVE", 9, 19);
    draw_dialog_text(episode, "L/R OR ENTER CHANGE", 9, 20);
    draw_dialog_text(episode, "ESC RETURN", 9, 21);
    (void)show_video_page(0);
    if (!in_game) platform_present_frame();
}

void platform_apply_port_setting(int row) {
    if (row == PC_SETTING_FULLSCREEN)
        platform_apply_window_settings();
    if (row == PC_SETTING_VOLUME) pc_speaker_set_volume(pc_settings.volume);
    if (row == PC_SETTING_STEREO) pc_speaker_set_stereo(pc_settings.stereo);
    if (row == PC_SETTING_RENDERER) scene_set_active(pc_settings.renderer == PC_RENDERER_ENHANCED);
    pc_config_save();
}

static int next_setting_row(int selected, int direction) {
    int count = pc_config_count();
    for (int tried = 0; tried < count; ++tried) {
        selected = (selected + direction + count) % count;
        if (!pc_config_is_section(selected)) return selected;
    }
    return 0;
}

static void show_port_settings_dialog(int episode, int in_game) {
    int selected = 0;
    int closing = 0;
    if (in_game) platform_begin_modal_keyboard_capture();
    render_settings_dialog(episode, selected, in_game);
    for (;;) {
        int key = in_game ? platform_poll_modal_key() : platform_poll_key();
        if (!key || key == 0xe0) continue;
        if (in_game && closing) {
            if (key == 0x81) {
                pc_config_save();
                platform_end_modal_keyboard_capture();
                return;
            }
            continue;
        }
        if (key & 0x80) continue;
        if (key == 0x01) {
            pc_config_save();
            if (in_game) closing = 1;
            else return;
        }
        else if (key == 0x48) selected = next_setting_row(selected, -1);
        else if (key == 0x50) selected = next_setting_row(selected, 1);
        else if (key == 0x4b || key == 0x4d || key == 0x1c) {
            int direction = key == 0x4b ? -1 : 1;
            if (!pc_config_is_section(selected)) {
                pc_config_change(selected, direction);
                platform_apply_port_setting(selected);
            }
        } else continue;
        if (!closing) render_settings_dialog(episode, selected, in_game);
    }
}

void platform_show_port_settings_dialog(int16_t episode) {
    port_wide_pass_abandon("platform_show_port_settings_dialog");
    show_port_settings_dialog(episode, 1);
}

static int move_episode_selection(const int present[4], int selected, int direction) {
    do {
        selected += direction;
        if (selected < 1) selected = 4;
        if (selected > 4) selected = 1;
    } while (selected != 4 && !present[selected]);
    return selected;
}

static int show_episode_dialog(const int present[4], int first_episode) {
    int selected = first_episode;
    int key;
    if (!load_dialog_graphics_for(first_episode)) return -1;
    render_episode_dialog(present, selected);
    for (;;) {
        key = platform_poll_key();
        if (!key || (key & 0x80) || key == 0xe0) continue;
        if (key == 0x01) return 0;
        if (key == 0x1f) {
            show_port_settings_dialog(dialog_episode, 0);
        } else if (key == 0x48 || key == 0x4b) {
            selected = move_episode_selection(present, selected, -1);
        } else if (key == 0x50 || key == 0x4d) {
            selected = move_episode_selection(present, selected, 1);
        } else if (key >= 0x02 && key <= 0x04) {
            int choice = key - 1;
            if (present[choice]) return choice;
            continue;
        } else if (key == 0x1c) {
            if (selected == 4) show_port_settings_dialog(dialog_episode, 0);
            else return selected;
        } else {
            continue;
        }
        render_episode_dialog(present, selected);
    }
}

static void show_port_message(int episode, const char *message) {
    if (episode < 1 || episode > 3 ||
        (!episode_dialog_graphics_loaded && !load_dialog_graphics_for(episode))) {
        show_plain_message("Duke Nukum", message);
        return;
    }
    draw_dialog_frame(episode, 6, 4);
    draw_dialog_text(episode, "DUKE NUKUM", 14, 14);
    draw_dialog_text(episode, message, 9, 16);
    draw_dialog_text(episode, "Press any key", 13, 19);
    (void)show_video_page(0);
    platform_present_frame();
    while (!(platform_poll_key() & 0x80)) {
        /* platform_poll_key yields while the user is deciding. */
    }
}

static int find_first_episode(const int present[4]) {
    for (int episode = 1; episode <= 3; ++episode)
        if (present[episode]) return episode;
    return 0;
}

static void run_episode(int episode, char **game_argv, int *result) {
#ifdef _WIN32
    fprintf(stderr, "[port] episode %d start pid=%lu\n", episode,
            (unsigned long)GetCurrentProcessId());
#else
    fprintf(stderr, "[port] episode %d start\n", episode);
#endif
    /* The selector key also enters the emulated keyboard queue. Discard it
       before the game installs its keyboard handler so Enter cannot select a
       menu action inside the episode. */
    pc_interrupt_reset();
    pc_io_reset();
    switch (episode) {
    case 1:
        platform_prepare_episode_state(1, &ep1_state_begin, &ep1_state_end + 1);
        *result = platform_run_episode(episode_one, 1, game_argv);
        break;
    case 2:
        platform_prepare_episode_state(2, &ep2_state_begin, &ep2_state_end + 1);
        *result = platform_run_episode(episode_two, 1, game_argv);
        break;
    default:
        platform_prepare_episode_state(3, &ep3_state_begin, &ep3_state_end + 1);
        *result = platform_run_episode(episode_three, 1, game_argv);
        break;
    }
}

int main(int argc, char **argv) {
#ifdef _WIN32
    /* A window application has no console: keep the messages in duke1.log instead. */
    if (GetStdHandle(STD_ERROR_HANDLE) == NULL || GetStdHandle(STD_ERROR_HANDLE) == INVALID_HANDLE_VALUE) {
        (void)freopen("duke1.log", "w", stderr);
        (void)freopen("duke1.log", "a", stdout);
    }
#endif
    const char *data_dir = NULL;
    const char *script_path = NULL;
    int requested_episode = 0;
    int selected_episode = 0;
    int present[4] = { 0, 0, 0, 0 };
    int trace = 0;
    int force_select = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--data") == 0 && i + 1 < argc) {
            data_dir = argv[++i];
        } else if (strcmp(argv[i], "--episode") == 0 && i + 1 < argc) {
            requested_episode = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--script") == 0 && i + 1 < argc) {
            script_path = argv[++i];
        } else if (strcmp(argv[i], "--select") == 0) {
            force_select = 1;
        } else if (strcmp(argv[i], "--no-restart") == 0) {
            /* Kept as a no-op for scripts written before episodes returned in-process. */
        } else if (strcmp(argv[i], "--renderer") == 0 && i + 1 < argc) {
            ++i;                                   /* read by the platform (pc_sdl.c) */
        } else if (strcmp(argv[i], "--verify-native") == 0 || strcmp(argv[i], "--stereo") == 0) {
            /* read by the platform (pc_sdl.c) */
        } else if (strcmp(argv[i], "--trace") == 0) {
            trace = 1;
        } else {
            fprintf(stderr, "Ignoring unknown option: %s\n", argv[i]);
        }
    }
    if (trace) pc_trace_flags = PC_TRACE_PORTS | PC_TRACE_VECTORS | PC_TRACE_FILES;
    if (requested_episode < 0 || requested_episode > 3) {
        fprintf(stderr, "--episode must be 1, 2 or 3.\n");
        return 2;
    }
    if (!platform_init(data_dir)) {
        fprintf(stderr, "Platform initialization failed.\n");
        platform_shutdown();
        return 1;
    }
    if (!platform_set_script(script_path)) {
        platform_shutdown();
        return 2;
    }
    for (int episode = 1; episode <= 3; ++episode) {
        present[episode] = episode_files_present(episode);
        if (present[episode]) fprintf(stderr, "Episode %d data: present\n", episode);
    }

    int first_episode = find_first_episode(present);
    int present_count = present[1] + present[2] + present[3];
    if (!first_episode) {
        for (int episode = 1; episode <= 3; ++episode) {
            FILE *border = pc_fopen(episode_border[episode], "rb");
            FILE *font1 = pc_fopen(episode_font1[episode], "rb");
            FILE *font2 = pc_fopen(episode_font2[episode], "rb");
            if (border && font1 && font2) {
                fclose(border); fclose(font1); fclose(font2);
                first_episode = episode;
                break;
            }
            if (border) fclose(border);
            if (font1) fclose(font1);
            if (font2) fclose(font2);
        }
        if (first_episode) {
            show_port_message(first_episode, "No episode data found.");
        } else {
            show_plain_message("Duke Nukum", "No episode graphics or game data found. Select a folder with DN1, DN2, or DN3 files.");
        }
        platform_shutdown();
        return 1;
    }

    if (requested_episode && !present[requested_episode]) {
        char message[96];
        snprintf(message, sizeof(message), "Episode %d files are missing.", requested_episode);
        show_port_message(first_episode, message);
        if (present_count == 1) selected_episode = first_episode;
        else {
            selected_episode = show_episode_dialog(present, first_episode);
            if (selected_episode <= 0) {
                platform_shutdown();
                return selected_episode == 0 ? 0 : 1;
            }
        }
    } else if (requested_episode) {
        selected_episode = requested_episode;
    } else if (present_count == 1) {
        selected_episode = first_episode;
    } else if (force_select || present_count > 1) {
        selected_episode = show_episode_dialog(present, first_episode);
        if (selected_episode < 0) {
            show_port_message(first_episode, "Episode graphics could not be loaded.");
            platform_shutdown();
            return 1;
        }
        if (selected_episode == 0) {
            platform_shutdown();
            return 0;
        }
    } else {
        selected_episode = first_episode;
    }

    /* GAME1.C reads argv[1] unconditionally even when argc is one. */
    char *game_argv[] = { "duke1", "", "", NULL };
    int result = 0;
    for (;;) {
        run_episode(selected_episode, game_argv, &result);
        if (!platform_episode_exit_requested()) break;
        platform_reset_episode();
        episode_dialog_graphics_loaded = 0;
        dialog_episode = 0;
        selected_episode = show_episode_dialog(present, first_episode);
        if (selected_episode <= 0) {
            result = selected_episode == 0 ? 0 : 1;
            break;
        }
    }
    platform_shutdown();
    return result;
}
