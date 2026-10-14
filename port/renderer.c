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
static uint32_t overlay_pixels[CAPTURE_WIDTH * CAPTURE_HEIGHT];
static unsigned replacement_slot;

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
    target_texture = ega_texture = overlay_texture = NULL;
    bound_renderer = NULL;
}

SDL_Texture *native_renderer_render(const CaptureFrame *frame,
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
