#include "platform.h"
#include "pc_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ep1_main(int16_t argc, char **argv);
void ep2_main(int16_t argc, char **argv);
void ep3_main(int16_t argc, char **argv);

static void show_missing_data(void) {
    const char *message = "No episode data found. Select a folder containing worldal1.dn1/font1.dn1 (or the matching .dn2/.dn3 files).";
    (void)SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Duke Nukum", message, NULL);
    fprintf(stderr, "%s\n", message);
}

static int episode_one(int argc, char **argv) { ep1_main((int16_t)argc, argv); return 0; }
static int episode_two(int argc, char **argv) { ep2_main((int16_t)argc, argv); return 0; }
static int episode_three(int argc, char **argv) { ep3_main((int16_t)argc, argv); return 0; }

int main(int argc, char **argv) {
    const char *data_dir = NULL;
    int requested_episode = 0;
    int selected_episode = 0;
    int present[4] = {0, 0, 0, 0};
    int trace = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--data") == 0 && i + 1 < argc) {
            data_dir = argv[++i];
        } else if (strcmp(argv[i], "--episode") == 0 && i + 1 < argc) {
            requested_episode = atoi(argv[++i]);
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
    for (int ep = 1; ep <= 3; ++ep) {
        char map_name[32];
        char font_name[32];
        snprintf(map_name, sizeof(map_name), "worldal1.dn%d", ep);
        snprintf(font_name, sizeof(font_name), "font1.dn%d", ep);
        FILE *map = pc_fopen(map_name, "rb");
        FILE *font = pc_fopen(font_name, "rb");
        present[ep] = map != NULL && font != NULL;
        if (map) fclose(map);
        if (font) fclose(font);
        if (present[ep]) {
            fprintf(stderr, "Episode %d data: present\n", ep);
        }
    }
    if (requested_episode && present[requested_episode]) selected_episode = requested_episode;
    if (!selected_episode) {
        for (int ep = 1; ep <= 3; ++ep) if (present[ep]) { selected_episode = ep; break; }
    }
    if (!selected_episode) {
        show_missing_data();
        platform_shutdown();
        return 1;
    }
    if (requested_episode && requested_episode != selected_episode) {
        fprintf(stderr, "Episode %d is unavailable; starting episode %d.\n", requested_episode, selected_episode);
    }
    /* GAME1.C reads argv[1] unconditionally even when argc is one. */
    char *game_argv[] = { "duke1", "", "", NULL };
    int result;
    switch (selected_episode) {
    case 1: result = platform_run_episode(episode_one, 1, game_argv); break;
    case 2: result = platform_run_episode(episode_two, 1, game_argv); break;
    default: result = platform_run_episode(episode_three, 1, game_argv); break;
    }
    platform_shutdown();
    return result;
}
