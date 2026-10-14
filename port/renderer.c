/* Gameplay composition from toolbox commands.  Source images are cached as indexed/masked
   pixels and uploaded as palette-corrected RGBA SDL textures. */
#include "renderer.h"

#include <stdlib.h>
#include <string.h>

enum { NATIVE_TEXTURE_CACHE = 2048 };

typedef struct native_texture {
    uint64_t key;
    uint64_t content_hash;
    uint8_t type;
    uint8_t width;
    uint8_t height;
    uint8_t occupied;
    uint8_t indices[CAPTURE_MAX_PIXELS];
    uint8_t opaque[CAPTURE_MAX_PIXELS];
    uint32_t palette_rgb[16];
    SDL_Texture *texture;
} NativeTexture;

static NativeTexture texture_cache[NATIVE_TEXTURE_CACHE];
static SDL_Renderer *bound_renderer;
static SDL_Texture *target_texture;
static SDL_Texture *ega_texture;
static SDL_Texture *overlay_texture;
static SDL_Texture *wide_texture;
static uint32_t overlay_pixels[CAPTURE_WIDTH * CAPTURE_HEIGHT];
static uint32_t *wide_pixels;
static size_t wide_pixels_capacity;
static int wide_texture_width;
static unsigned replacement_slot;

enum { WIDE_PLAYFIELD_LEFT = 16, WIDE_HUD_WIDTH = 95, WIDE_PLAYFIELD_TOP = 16,
       WIDE_PLAYFIELD_HEIGHT = 160, WIDE_ORIGINAL_PLAYFIELD_WIDTH = 224 };

static uint64_t image_hash(const CaptureCommand *command)
{
    uint64_t hash = 1469598103934665603ull;
    unsigned count = (unsigned)command->width * command->height;
    unsigned i;
    for (i = 0; i < count; ++i) {
        hash = (hash ^ command->pixels[i]) * 1099511628211ull;
        hash = (hash ^ command->opaque[i]) * 1099511628211ull;
    }
    return hash;
}

static int same_palette(const uint32_t left[16], const uint32_t right[16])
{
    return memcmp(left, right, 16u * sizeof(uint32_t)) == 0;
}

static int upload_palette_texture(NativeTexture *entry, const CaptureCommand *command,
                                  const uint32_t palette[16], uint64_t hash)
{
    uint32_t rgba[CAPTURE_MAX_PIXELS];
    unsigned count = (unsigned)command->width * command->height;
    unsigned i;
    if (!entry->texture || entry->width != command->width || entry->height != command->height) {
        if (entry->texture)
            SDL_DestroyTexture(entry->texture);
        entry->texture = SDL_CreateTexture(bound_renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STATIC,
                                           command->width, command->height);
        if (!entry->texture)
            return 0;
        (void)SDL_SetTextureBlendMode(entry->texture, SDL_BLENDMODE_BLEND);
        (void)SDL_SetTextureScaleMode(entry->texture, SDL_SCALEMODE_NEAREST);
        entry->width = command->width;
        entry->height = command->height;
    }
    for (i = 0; i < count; ++i)
        rgba[i] = (entry->opaque[i] ? 0xff000000u : 0u) |
                  (palette[entry->indices[i] & 0x0fu] & 0x00ffffffu);
    if (!SDL_UpdateTexture(entry->texture, NULL, rgba,
                           (int)command->width * (int)sizeof(uint32_t)))
        return 0;
    entry->content_hash = hash;
    memcpy(entry->palette_rgb, palette, sizeof(entry->palette_rgb));
    return 1;
}

static NativeTexture *get_texture(const CaptureCommand *command,
                                  const uint32_t palette[16])
{
    NativeTexture *free_entry = NULL;
    NativeTexture *entry = NULL;
    uint64_t hash = image_hash(command);
    unsigned i;
    for (i = 0; i < NATIVE_TEXTURE_CACHE; ++i) {
        NativeTexture *candidate = &texture_cache[i];
        if (candidate->occupied && candidate->type == command->type &&
            candidate->key == command->source_key) {
            entry = candidate;
            break;
        }
        if (!candidate->occupied && !free_entry)
            free_entry = candidate;
    }
    if (!entry) {
        if (free_entry)
            entry = free_entry;
        else {
            entry = &texture_cache[replacement_slot++ % NATIVE_TEXTURE_CACHE];
            if (entry->texture)
                SDL_DestroyTexture(entry->texture);
            memset(entry, 0, sizeof(*entry));
        }
        entry->occupied = 1;
        entry->key = command->source_key;
        entry->type = command->type;
        memcpy(entry->indices, command->pixels,
               (size_t)command->width * command->height);
        memcpy(entry->opaque, command->opaque,
               (size_t)command->width * command->height);
    } else if (entry->content_hash != hash ||
               entry->width != command->width || entry->height != command->height) {
        memcpy(entry->indices, command->pixels,
               (size_t)command->width * command->height);
        memcpy(entry->opaque, command->opaque,
               (size_t)command->width * command->height);
    }
    if (!entry->texture || entry->content_hash != hash ||
        !same_palette(entry->palette_rgb, palette)) {
        if (!upload_palette_texture(entry, command, palette, hash))
            return NULL;
    }
    return entry;
}

int native_renderer_init(SDL_Renderer *renderer)
{
    bound_renderer = renderer;
    if (!bound_renderer)
        return 0;
    target_texture = SDL_CreateTexture(bound_renderer, SDL_PIXELFORMAT_ARGB8888,
                                       SDL_TEXTUREACCESS_TARGET,
                                       CAPTURE_WIDTH, CAPTURE_HEIGHT);
    ega_texture = SDL_CreateTexture(bound_renderer, SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    CAPTURE_WIDTH, CAPTURE_HEIGHT);
    overlay_texture = SDL_CreateTexture(bound_renderer, SDL_PIXELFORMAT_ARGB8888,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        CAPTURE_WIDTH, CAPTURE_HEIGHT);
    if (!target_texture || !ega_texture || !overlay_texture) {
        native_renderer_shutdown();
        return 0;
    }
    (void)SDL_SetTextureBlendMode(target_texture, SDL_BLENDMODE_NONE);
    (void)SDL_SetTextureBlendMode(ega_texture, SDL_BLENDMODE_NONE);
    (void)SDL_SetTextureBlendMode(overlay_texture, SDL_BLENDMODE_BLEND);
    (void)SDL_SetTextureScaleMode(target_texture, SDL_SCALEMODE_NEAREST);
    (void)SDL_SetTextureScaleMode(ega_texture, SDL_SCALEMODE_NEAREST);
    (void)SDL_SetTextureScaleMode(overlay_texture, SDL_SCALEMODE_NEAREST);
    return 1;
}

static int ensure_wide_texture(int width)
{
    if (wide_texture && wide_texture_width == width)
        return 1;
    if (wide_texture)
        SDL_DestroyTexture(wide_texture);
    wide_texture = SDL_CreateTexture(bound_renderer, SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_STREAMING, width, CAPTURE_HEIGHT);
    wide_texture_width = wide_texture ? width : 0;
    if (!wide_texture)
        return 0;
    (void)SDL_SetTextureBlendMode(wide_texture, SDL_BLENDMODE_NONE);
    (void)SDL_SetTextureScaleMode(wide_texture, SDL_SCALEMODE_NEAREST);
    return 1;
}

static int ensure_wide_pixels(int width)
{
    size_t needed = (size_t)width * CAPTURE_HEIGHT;
    uint32_t *resized;
    if (needed <= wide_pixels_capacity)
        return 1;
    resized = (uint32_t *)realloc(wide_pixels, needed * sizeof(*wide_pixels));
    if (!resized)
        return 0;
    wide_pixels = resized;
    wide_pixels_capacity = needed;
    return 1;
}

static uint32_t palette_pixel(const CaptureFrame *frame, uint8_t index)
{
    return 0xff000000u | (frame->palette_rgb[index & 0x0fu] & 0x00ffffffu);
}

static void draw_wide_tile(const CaptureFrame *frame, int canvas_width, int playfield_width,
                           int camera_left, int map_row, int map_column,
                           const uint8_t *indices)
{
    int tile_world_x = map_column * 16;
    int tile_screen_x = WIDE_PLAYFIELD_LEFT + tile_world_x - camera_left;
    int x0 = tile_screen_x < WIDE_PLAYFIELD_LEFT ? WIDE_PLAYFIELD_LEFT : tile_screen_x;
    int x1 = tile_screen_x + 16;
    int clip_right = WIDE_PLAYFIELD_LEFT + playfield_width;
    int y0 = WIDE_PLAYFIELD_TOP + map_row * 16;
    int y, x;
    if (x1 > clip_right) x1 = clip_right;
    if (x0 >= x1 || y0 >= WIDE_PLAYFIELD_TOP + WIDE_PLAYFIELD_HEIGHT)
        return;
    for (y = 0; y < 16; ++y) {
        int screen_y = y0 + y;
        if (screen_y >= CAPTURE_HEIGHT || screen_y < WIDE_PLAYFIELD_TOP || screen_y >= 176)
            continue;
        for (x = x0; x < x1; ++x) {
            unsigned source_x = (unsigned)(x - tile_screen_x);
            wide_pixels[screen_y * canvas_width + x] =
                palette_pixel(frame, indices[y * 16u + source_x]);
        }
    }
}

static void draw_wide_commands(const CaptureFrame *frame, int canvas_width,
                               int playfield_width, int32_t camera_left)
{
    int clip_left = WIDE_PLAYFIELD_LEFT;
    int clip_right = WIDE_PLAYFIELD_LEFT + playfield_width;
    unsigned index;
    for (index = 0; index < frame->command_count; ++index) {
        const CaptureCommand *command = &frame->commands[index];
        int x0, y0, y, x;
        if (command->type == CAPTURE_BITMAP)
            continue; /* the wide map snapshot supplies every tile, including the old view */
        x0 = WIDE_PLAYFIELD_LEFT + command->world_x - (int)camera_left;
        y0 = WIDE_PLAYFIELD_TOP + command->world_y - frame->camera_y;
        for (y = 0; y < command->height; ++y) {
            int screen_y = y0 + y;
            if (screen_y < WIDE_PLAYFIELD_TOP || screen_y >= 176 || screen_y >= CAPTURE_HEIGHT)
                continue;
            for (x = 0; x < command->width; ++x) {
                int screen_x = x0 + x;
                unsigned source = (unsigned)y * command->width + (unsigned)x;
                if (screen_x < clip_left || screen_x >= clip_right ||
                    screen_x < 0 || screen_x >= canvas_width || !command->opaque[source])
                    continue;
                wide_pixels[screen_y * canvas_width + screen_x] =
                    palette_pixel(frame, command->pixels[source]);
            }
        }
    }
}

static void compose_wide_frame(const CaptureFrame *frame, int width)
{
    int playfield_width = width - 111;
    int hud_start = width - WIDE_HUD_WIDTH;
    int camera_left = capture_wide_camera_left(frame, width);
    int overlay_shift = (playfield_width - WIDE_ORIGINAL_PLAYFIELD_WIDTH) / 2;
    int row, column;
    size_t pixel_count = (size_t)width * CAPTURE_HEIGHT;
    for (size_t p = 0; p < pixel_count; ++p)
        wide_pixels[p] = 0xff000000u;

    if (frame->wide_snapshot_valid) {
        int first_map_column = camera_left / 16;
        for (row = 0; row < CAPTURE_MAP_ROWS; ++row) {
            for (column = 0; column < CAPTURE_MAP_COLUMNS; ++column) {
                int world_column = column;
                int tile_world_x = world_column * 16;
                uint16_t tile = frame->wide_map_tiles[row][column];
                const uint8_t *indices;
                if (tile_world_x + 16 <= camera_left || tile_world_x >= camera_left + playfield_width)
                    continue;
                if (tile <= 0x20u) {
                    int backdrop_column = (column - first_map_column) % CAPTURE_BACKDROP_COLUMNS;
                    if (backdrop_column < 0) backdrop_column += CAPTURE_BACKDROP_COLUMNS;
                    indices = frame->wide_backdrop_pixels[row][backdrop_column][tile == 0x20u ? 1 : 0];
                } else {
                    indices = frame->wide_tile_pixels[row][column];
                }
                draw_wide_tile(frame, width, playfield_width, camera_left, row, column, indices);
            }
        }
        draw_wide_commands(frame, width, playfield_width, camera_left);
    }

    /* Text and dialogs remain centred over the original 224-pixel view. */
    for (row = 0; row < CAPTURE_HEIGHT; ++row) {
        for (column = 0; column < CAPTURE_WIDTH; ++column) {
            int destination_x;
            if (!frame->draw_mask[row * CAPTURE_WIDTH + column])
                continue;
            destination_x = column + overlay_shift;
            if (destination_x >= 0 && destination_x < width)
                wide_pixels[row * width + destination_x] = frame->ega_rgba[row * CAPTURE_WIDTH + column];
        }
    }

    /* Keep the source EGA pixels for the fixed corners and live HUD, repeat only the plain
       top/bottom strips, and re-centre the F1 plate beneath the widened playfield. */
    for (row = 0; row < 16; ++row) {
        int x;
        for (x = 0; x <= 28; ++x)
            wide_pixels[row * width + x] = frame->ega_rgba[row * CAPTURE_WIDTH + x];
        for (x = 29; x < hud_start; ++x) {
            int source_x = 29 + (x - 29) % 196;
            wide_pixels[row * width + x] = frame->ega_rgba[row * CAPTURE_WIDTH + source_x];
        }
        for (x = 0; x < WIDE_HUD_WIDTH; ++x)
            wide_pixels[row * width + hud_start + x] =
                frame->ega_rgba[row * CAPTURE_WIDTH + 225 + x];
    }
    for (row = WIDE_PLAYFIELD_TOP; row < 176; ++row) {
        int x;
        for (x = 0; x < WIDE_PLAYFIELD_LEFT; ++x)
            wide_pixels[row * width + x] = frame->ega_rgba[row * CAPTURE_WIDTH + x];
        for (x = 0; x < WIDE_HUD_WIDTH; ++x)
            wide_pixels[row * width + hud_start + x] =
                frame->ega_rgba[row * CAPTURE_WIDTH + 225 + x];
    }
    {
        int plate_start = WIDE_PLAYFIELD_LEFT + (playfield_width - 63) / 2;
        int plate_end = plate_start + 63;
        for (row = 176; row < CAPTURE_HEIGHT; ++row) {
            int x;
            for (x = 0; x < 15; ++x)
                wide_pixels[row * width + x] = frame->ega_rgba[row * CAPTURE_WIDTH + x];
            for (x = 15; x < plate_start; ++x) {
                int source_x = 15 + (x - 15) % 74;
                wide_pixels[row * width + x] = frame->ega_rgba[row * CAPTURE_WIDTH + source_x];
            }
            for (x = 0; x < 63; ++x)
                wide_pixels[row * width + plate_start + x] =
                    frame->ega_rgba[row * CAPTURE_WIDTH + 89 + x];
            for (x = plate_end; x < hud_start; ++x) {
                int source_x = 152 + (x - plate_end) % 73;
                wide_pixels[row * width + x] = frame->ega_rgba[row * CAPTURE_WIDTH + source_x];
            }
            for (x = 0; x < WIDE_HUD_WIDTH; ++x)
                wide_pixels[row * width + hud_start + x] =
                    frame->ega_rgba[row * CAPTURE_WIDTH + 225 + x];
        }
    }
}

void native_renderer_shutdown(void)
{
    unsigned i;
    for (i = 0; i < NATIVE_TEXTURE_CACHE; ++i) {
        if (texture_cache[i].texture)
            SDL_DestroyTexture(texture_cache[i].texture);
    }
    memset(texture_cache, 0, sizeof(texture_cache));
    replacement_slot = 0;
    if (target_texture) SDL_DestroyTexture(target_texture);
    if (ega_texture) SDL_DestroyTexture(ega_texture);
    if (overlay_texture) SDL_DestroyTexture(overlay_texture);
    if (wide_texture) SDL_DestroyTexture(wide_texture);
    free(wide_pixels);
    wide_pixels = NULL;
    wide_pixels_capacity = 0;
    wide_texture_width = 0;
    target_texture = ega_texture = overlay_texture = wide_texture = NULL;
    bound_renderer = NULL;
}

SDL_Texture *native_renderer_render(const CaptureFrame *frame,
                                   int canvas_width,
                                   uint32_t *readback_argb)
{
    SDL_FRect destination = { 0.0f, 0.0f, (float)CAPTURE_WIDTH, (float)CAPTURE_HEIGHT };
    SDL_Surface *pixels = NULL;
    SDL_Surface *converted = NULL;
    uint32_t *overlay_rgba = overlay_pixels;
    unsigned i;
    int success = 0;
    if (!frame || !frame->gameplay || !target_texture || !ega_texture || !overlay_texture)
        return NULL;
    if (canvas_width > 335 && frame->wide_snapshot_valid) {
        size_t count = (size_t)canvas_width * CAPTURE_HEIGHT;
        if (!ensure_wide_pixels(canvas_width) || !ensure_wide_texture(canvas_width))
            return NULL;
        compose_wide_frame(frame, canvas_width);
        if (!SDL_UpdateTexture(wide_texture, NULL, wide_pixels,
                               canvas_width * (int)sizeof(uint32_t)))
            return NULL;
        if (readback_argb)
            memcpy(readback_argb, wide_pixels, count * sizeof(uint32_t));
        return wide_texture;
    }
    if (!SDL_UpdateTexture(ega_texture, NULL, frame->ega_rgba,
                           CAPTURE_WIDTH * (int)sizeof(uint32_t)))
        return NULL;
    for (i = 0; i < CAPTURE_WIDTH * CAPTURE_HEIGHT; ++i)
        overlay_rgba[i] = frame->overlay_mask[i] ? frame->ega_rgba[i] : 0u;
    if (!SDL_UpdateTexture(overlay_texture, NULL, overlay_rgba,
                           CAPTURE_WIDTH * (int)sizeof(uint32_t)))
        return NULL;
    if (!SDL_SetRenderTarget(bound_renderer, target_texture))
        return NULL;
    (void)SDL_SetRenderDrawColor(bound_renderer, 0, 0, 0, 255);
    (void)SDL_RenderClear(bound_renderer);
    if (!SDL_RenderTexture(bound_renderer, ega_texture, NULL, &destination))
        goto done;
    for (i = 0; i < frame->command_count; ++i) {
        const CaptureCommand *command = &frame->commands[i];
        NativeTexture *entry = get_texture(command, frame->palette_rgb);
        SDL_FRect at;
        if (!entry)
            goto done;
        at.x = (float)(command->world_x - frame->camera_x + 16);
        at.y = (float)(command->world_y - frame->camera_y + 16);
        at.w = (float)command->width;
        at.h = (float)command->height;
        if (!SDL_RenderTexture(bound_renderer, entry->texture, NULL, &at))
            goto done;
    }
    if (!SDL_RenderTexture(bound_renderer, overlay_texture, NULL, &destination))
        goto done;
    if (readback_argb) {
        pixels = SDL_RenderReadPixels(bound_renderer, NULL);
        if (!pixels)
            goto done;
        converted = SDL_ConvertSurface(pixels, SDL_PIXELFORMAT_ARGB8888);
        if (!converted)
            goto done;
        if (SDL_MUSTLOCK(converted) && !SDL_LockSurface(converted))
            goto done;
        for (int y = 0; y < CAPTURE_HEIGHT; ++y)
            memcpy(readback_argb + y * CAPTURE_WIDTH,
                   (const uint8_t *)converted->pixels + y * converted->pitch,
                   CAPTURE_WIDTH * sizeof(uint32_t));
        if (SDL_MUSTLOCK(converted))
            SDL_UnlockSurface(converted);
    }
    success = 1;
done:
    if (converted) SDL_DestroySurface(converted);
    if (pixels) SDL_DestroySurface(pixels);
    (void)SDL_SetRenderTarget(bound_renderer, NULL);
    return success ? target_texture : NULL;
}
