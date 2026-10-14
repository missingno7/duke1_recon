/* Gameplay draw-command capture shared by the toolbox and the SDL presenter. */
#ifndef DUKE_CAPTURE_H
#define DUKE_CAPTURE_H

#include <stdint.h>

enum capture_command_type {
    CAPTURE_BITMAP = 1,
    CAPTURE_SPRITE = 2,
    CAPTURE_WATER = 3
};

enum {
    CAPTURE_WIDTH = 320,
    CAPTURE_HEIGHT = 200,
    CAPTURE_MAX_COMMANDS = 2048,
    CAPTURE_MAX_PIXELS = 16 * 30
};

typedef struct capture_command {
    uint64_t source_key;
    uint32_t site;
    uint16_t occurrence;
    uint8_t type;
    uint8_t width;
    uint8_t height;
    int16_t screen_x;
    int16_t screen_y;
    int32_t world_x;
    int32_t world_y;
    uint8_t pixels[CAPTURE_MAX_PIXELS];
    uint8_t opaque[CAPTURE_MAX_PIXELS];
} CaptureCommand;

typedef struct capture_frame {
    uint64_t sequence;
    int gameplay;
    int32_t camera_x;
    int32_t camera_y;
    uint16_t command_count;
    uint8_t overlay_mask[CAPTURE_WIDTH * CAPTURE_HEIGHT];
    uint32_t ega_rgba[CAPTURE_WIDTH * CAPTURE_HEIGHT];
    uint32_t palette_rgb[16];
    CaptureCommand commands[CAPTURE_MAX_COMMANDS];
} CaptureFrame;

int capture_init(void);
void capture_shutdown(void);
void capture_set_enhanced(int enabled);
int capture_enhanced(void);
int capture_is_recording(void);

/* Producer calls run on the game thread.  acquire/release bracket all presenter reads. */
void capture_begin_gameplay_frame(int16_t scroll_x, int16_t map_y_offset);
void capture_publish_gameplay_frame(void);
void capture_publish_non_gameplay_state(void);
const CaptureFrame *capture_acquire_latest(int *is_gameplay);
void capture_release_latest(void);

void capture_record_bitmap(uint16_t source_offset, uint16_t page_offset,
                           uint16_t page_selector);
void capture_record_sprite(uint32_t site, const char *source, int16_t x, int16_t y);
void capture_record_water(int16_t x, int16_t y, int16_t source_offset,
                          uint16_t page_selector);
void capture_mark_overlay(int16_t x_byte, int16_t y, int width, int height);

/* True when a gameplay command byte may still be written to the emulated page. */
int capture_page_byte_is_playfield(uint16_t page_relative_offset);

#endif
