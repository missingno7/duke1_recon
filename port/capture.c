/* Toolbox-side gameplay frame capture.  The game thread owns one frame until its page flip;
   the presenter holds the same mutex while it consumes the other buffer. */
#include "capture.h"
#include "platform.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <string.h>

static CaptureFrame frames[2];
static SDL_Mutex *frame_mutex;
static SDL_Condition *frame_condition;
static SDL_AtomicInt enhanced_enabled;
static unsigned readers[2];
static _Thread_local int acquired_index = -1;
static int latest_index = -1;
static int writing_index = -1;
static int recording;
static int latest_is_gameplay;
static uint64_t next_sequence = 1;

static uint8_t plane_pixel(uint16_t address, unsigned bit)
{
    uint8_t result = 0;
    unsigned plane;
    uint8_t mask = (uint8_t)(0x80u >> bit);
    for (plane = 0; plane < 4; ++plane) {
        const uint8_t *memory = vga_plane((int)plane);
        if (memory && (memory[address] & mask))
            result |= (uint8_t)(1u << plane);
    }
    return result;
}

static CaptureCommand *new_command(uint8_t type, uint64_t key, int width, int height,
                                   int screen_x, int screen_y)
{
    CaptureFrame *frame;
    CaptureCommand *command;
    if (!recording || writing_index < 0)
        return NULL;
    frame = &frames[writing_index];
    if (frame->command_count >= CAPTURE_MAX_COMMANDS)
        return NULL;
    command = &frame->commands[frame->command_count++];
    memset(command, 0, sizeof(*command));
    command->type = type;
    command->source_key = key;
    command->width = (uint8_t)width;
    command->height = (uint8_t)height;
    command->screen_x = (int16_t)screen_x;
    command->screen_y = (int16_t)screen_y;
    command->world_x = screen_x - 16 + frame->camera_x;
    command->world_y = screen_y - 16 + frame->camera_y;
    return command;
}

int capture_init(void)
{
    if (frame_mutex)
        return 1;
    frame_mutex = SDL_CreateMutex();
    frame_condition = SDL_CreateCondition();
    if (!frame_mutex || !frame_condition) {
        if (frame_mutex) SDL_DestroyMutex(frame_mutex);
        if (frame_condition) SDL_DestroyCondition(frame_condition);
        frame_mutex = NULL;
        frame_condition = NULL;
        return 0;
    }
    return 1;
}

void capture_shutdown(void)
{
    if (frame_mutex)
        SDL_DestroyMutex(frame_mutex);
    if (frame_condition)
        SDL_DestroyCondition(frame_condition);
    frame_mutex = NULL;
    frame_condition = NULL;
    memset(readers, 0, sizeof(readers));
    latest_is_gameplay = 0;
    latest_index = -1;
    writing_index = -1;
    recording = 0;
    SDL_SetAtomicInt(&enhanced_enabled, 0);
}

void capture_set_enhanced(int enabled)
{
    SDL_SetAtomicInt(&enhanced_enabled, enabled != 0);
}

int capture_enhanced(void)
{
    return SDL_GetAtomicInt(&enhanced_enabled) != 0;
}

int capture_is_recording(void)
{
    return recording;
}

void capture_begin_gameplay_frame(int16_t scroll_x, int16_t map_y_offset)
{
    CaptureFrame *frame;
    if (!capture_enhanced() || !frame_mutex)
        return;
    SDL_LockMutex(frame_mutex);
    writing_index = latest_index < 0 ? 0 : 1 - latest_index;
    while (readers[writing_index] != 0)
        SDL_WaitCondition(frame_condition, frame_mutex);
    recording = 1;
    frame = &frames[writing_index];
    frame->sequence = next_sequence++;
    frame->gameplay = 1;
    frame->camera_x = (int32_t)scroll_x * 8;
    frame->camera_y = ((int32_t)map_y_offset * 16) / 128;
    frame->command_count = 0;
    memset(frame->overlay_mask, 0, sizeof(frame->overlay_mask));
    for (int y = 0; y < CAPTURE_HEIGHT; ++y) {
        for (int x = 0; x < CAPTURE_WIDTH; ++x) {
            if (x < 16 || x >= 240 || y < 16 || y >= 176)
                frame->overlay_mask[y * CAPTURE_WIDTH + x] = 1;
        }
    }
    SDL_UnlockMutex(frame_mutex);
}

void capture_publish_gameplay_frame(void)
{
    CaptureFrame *frame;
    const uint8_t *palette;
    unsigned i;
    if (!recording || writing_index < 0)
        return;
    frame = &frames[writing_index];
    vga_render_rgb(frame->ega_rgba);
    palette = vga_palette_registers();
    for (i = 0; i < 16; ++i)
        frame->palette_rgb[i] = vga_colour_rgb(palette[i]);
    SDL_LockMutex(frame_mutex);
    latest_index = writing_index;
    writing_index = -1;
    latest_is_gameplay = 1;
    recording = 0;
    SDL_UnlockMutex(frame_mutex);
}

void capture_publish_non_gameplay_state(void)
{
    if (!frame_mutex || recording)
        return;
    SDL_LockMutex(frame_mutex);
    latest_is_gameplay = 0;
    SDL_UnlockMutex(frame_mutex);
}

const CaptureFrame *capture_acquire_latest(int *is_gameplay)
{
    if (!frame_mutex)
        return NULL;
    SDL_LockMutex(frame_mutex);
    if (latest_index < 0) {
        SDL_UnlockMutex(frame_mutex);
        return NULL;
    }
    acquired_index = latest_index;
    ++readers[acquired_index];
    if (is_gameplay)
        *is_gameplay = latest_is_gameplay;
    SDL_UnlockMutex(frame_mutex);
    return &frames[acquired_index];
}

void capture_release_latest(void)
{
    if (!frame_mutex || acquired_index < 0)
        return;
    SDL_LockMutex(frame_mutex);
    if (readers[acquired_index] > 0)
        --readers[acquired_index];
    acquired_index = -1;
    SDL_SignalCondition(frame_condition);
    SDL_UnlockMutex(frame_mutex);
}

void capture_record_bitmap(uint16_t source_offset, uint16_t page_offset,
                           uint16_t page_selector)
{
    uint16_t source = (uint16_t)(0x4000u + source_offset);
    unsigned row, x;
    int screen_x = (int)(page_offset % 40u) * 8;
    int screen_y = page_offset / 40u;
    CaptureCommand *command;
    (void)page_selector;
    command = new_command(CAPTURE_BITMAP, 0x100000000ull | source_offset,
                          16, 16, screen_x, screen_y);
    if (!command)
        return;
    for (row = 0; row < 16; ++row) {
        for (x = 0; x < 16; ++x) {
            unsigned byte_in_row = x >> 3;
            unsigned bit = x & 7u;
            uint16_t address = (uint16_t)(source + row * 2u + byte_in_row);
            unsigned index = row * 16u + x;
            command->pixels[index] = plane_pixel(address, bit);
            command->opaque[index] = 1;
        }
    }
}

void capture_record_sprite(uint32_t site, const char *source, int16_t x, int16_t y)
{
    uintptr_t pointer_key = (uintptr_t)source;
    CaptureCommand *command = new_command(CAPTURE_SPRITE, (uint64_t)pointer_key,
                                          16, 16, (int)x * 8, y);
    unsigned row;
    if (!command || !source)
        return;
    command->site = site;
    command->occurrence = 0;
    for (unsigned prior_index = 0; prior_index + 1 < frames[writing_index].command_count;
         ++prior_index) {
        const CaptureCommand *prior = &frames[writing_index].commands[prior_index];
        if (prior->type == CAPTURE_SPRITE && prior->site == site &&
            command->occurrence < UINT16_MAX)
            ++command->occurrence;
    }
    for (row = 0; row < 16; ++row) {
        unsigned half;
        for (half = 0; half < 2; ++half) {
            const unsigned char *bytes = (const unsigned char *)source + row * 10u + half * 5u;
            uint8_t mask = bytes[0];
            unsigned bit;
            for (bit = 0; bit < 8; ++bit) {
                unsigned index = row * 16u + half * 8u + bit;
                unsigned plane;
                uint8_t color = 0;
                uint8_t bit_mask = (uint8_t)(0x80u >> bit);
                for (plane = 0; plane < 4; ++plane)
                    if (bytes[plane + 1] & bit_mask)
                        color |= (uint8_t)(1u << plane);
                command->pixels[index] = color;
                command->opaque[index] = (mask & bit_mask) != 0;
            }
        }
    }
}

void capture_record_water(int16_t x, int16_t y, int16_t source_offset,
                          uint16_t page_selector)
{
    uint16_t destination = (uint16_t)((uint16_t)y * 40u + (uint16_t)x + 0x50u);
    uint16_t source = (uint16_t)(destination - 0x78u - (uint16_t)source_offset);
    uint64_t key;
    CaptureCommand *command;
    unsigned row, px;
    if ((page_selector & 0xffu) != 0)
        source = (uint16_t)(source + 0x2000u);
    key = 0x3000000000000000ull | ((uint64_t)(uint16_t)x << 32) |
          ((uint64_t)(uint16_t)y << 16) | (uint16_t)source_offset;
    command = new_command(CAPTURE_WATER, key, 16, 30,
                          (int)(destination % 40u) * 8, destination / 40u);
    if (!command)
        return;
    for (row = 0; row < 30; ++row) {
        for (px = 0; px < 16; ++px) {
            uint16_t address = (uint16_t)(source + (px >> 3));
            unsigned index = row * 16u + px;
            command->pixels[index] = plane_pixel(address, px & 7u);
            command->opaque[index] = 1;
        }
        source = (uint16_t)(source + 2u - 0x52u);
    }
}

void capture_mark_overlay(int16_t x_byte, int16_t y, int width, int height)
{
    CaptureFrame *frame;
    int x0, y0, x1, y1, row, column;
    if (!recording || writing_index < 0 || width <= 0 || height <= 0)
        return;
    frame = &frames[writing_index];
    x0 = (int)x_byte * 8;
    y0 = y;
    x1 = x0 + width;
    y1 = y0 + height;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > CAPTURE_WIDTH) x1 = CAPTURE_WIDTH;
    if (y1 > CAPTURE_HEIGHT) y1 = CAPTURE_HEIGHT;
    for (row = y0; row < y1; ++row)
        for (column = x0; column < x1; ++column)
            frame->overlay_mask[row * CAPTURE_WIDTH + column] = 1;
}

int capture_page_byte_is_playfield(uint16_t page_relative_offset)
{
    unsigned row = page_relative_offset / 40u;
    unsigned column = page_relative_offset % 40u;
    return row >= 16u && row < 176u && column >= 2u && column < 30u;
}
