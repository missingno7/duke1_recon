/* present.c - composes the displayed page natively from its scene items (see scene.h).

   1:1 (canvas 320) the items are drawn in drawing order at their page positions: that is the
   original picture exactly.  In a wider canvas:
   - a screen without the gameplay frame (title, menus, pictures) is centred, black at the sides;
   - in the gameplay frame the playfield grows (empty until a level is drawn, as at GET READY): the backdrop as a screen-fixed layer, the map tiles of the
     wide view straight from the level map, the level sprites at their level positions, dialogs
     and texts centred on the original view, the right column (frame bar + HUD) at the right
     edge, and the top and bottom bars rebuilt from their own tiles - the plain one repeated, the
     others kept at the left or (the "PRESS F1 FOR HELP" plate) centred. */
#include "present.h"
#include "scene.h"

#include <stdlib.h>
#include <string.h>

#define MARGIN 0xfeu                    /* canvas pixel outside the picture: black */

static _Thread_local uint8_t *canvas;   /* palette indices, width x 200 (per thread) */
static _Thread_local int canvas_capacity;

/* Decoded tile-cache bitmaps, by cache offset; flushed when the tiles are reloaded. */
typedef struct cached_bitmap { uint16_t source; uint8_t used; uint8_t pixels[256]; } CachedBitmap;
static CachedBitmap bitmap_cache[4096];
static uint32_t cache_generation;

static const uint8_t *cache_bitmap(uint16_t source, uint32_t generation)
{
    CachedBitmap *slot;
    if (generation != cache_generation) {
        for (int i = 0; i < 4096; ++i) bitmap_cache[i].used = 0;
        cache_generation = generation;
    }
    slot = &bitmap_cache[(source >> 5) & 4095u];
    if (!slot->used || slot->source != source) {
        scene_decode_cache_bitmap(source, slot->pixels);
        slot->source = source;
        slot->used = 1;
    }
    return slot->pixels;
}

/* Draw pixels at canvas (x, y), clipped to a rectangle. */
static void blit(int width, const uint8_t *data, int w, int h, int x, int y,
                 int clip_x0, int clip_y0, int clip_x1, int clip_y1, int opaque)
{
    for (int yy = 0; yy < h; ++yy) {
        int cy = y + yy;
        if (cy < clip_y0 || cy >= clip_y1) continue;
        for (int xx = 0; xx < w; ++xx) {
            int cx = x + xx;
            uint8_t c = data[yy * w + xx];
            if (cx < clip_x0 || cx >= clip_x1) continue;
            if (c == SCENE_TRANSPARENT && !opaque) continue;
            canvas[cy * width + cx] = c;
        }
    }
}

static void blit_item(int width, const SceneItem *it, int x, int y,
                      int clip_x0, int clip_y0, int clip_x1, int clip_y1)
{
    blit(width, it->pixels->data, it->pixels->w, it->pixels->h, x, y,
         clip_x0, clip_y0, clip_x1, clip_y1, 0);
}

/* The gameplay screen: the page carries the frame of draw_video_page_template (its side
   columns, tiles 0x3000 and 0x3020) - with or without a level in it yet (GET READY). */
static int has_gameplay_frame(const SceneSnapshot *s)
{
    for (size_t i = 0; i < s->count; ++i) {
        const SceneItem *it = &s->items[i];
        if (it->space == SCENE_SCREEN && it->kind == SCENE_BITMAP &&
            ((it->source == 0x3000u && it->x == 0) || (it->source == 0x3020u && it->x == RIGHT_COLUMN_X)))
            return 1;
    }
    return 0;
}

/* The top or bottom bar: plain tile repeated across, other pieces left or centred. */
static void compose_bar(const SceneSnapshot *s, int width, int bar_y0, int bar_y1, int extra)
{
    int right = width - (SCENE_WIDTH - RIGHT_COLUMN_X);
    /* the plain tile of each 16-pixel band: the most frequent bitmap in it */
    for (int band = bar_y0; band < bar_y1; band += 8) {
        uint16_t sources[64]; int counts[64]; int n = 0;
        const SceneItem *plain = NULL; int best = 0;
        for (size_t i = 0; i < s->count; ++i) {
            const SceneItem *it = &s->items[i];
            if (it->space != SCENE_SCREEN || it->kind != SCENE_BITMAP || it->y != band ||
                it->x < PLAYFIELD_X0 || it->x >= RIGHT_COLUMN_X) continue;
            int k = 0;
            while (k < n && sources[k] != it->source) ++k;
            if (k == n && n < 64) { sources[n] = it->source; counts[n++] = 0; }
            if (k < n && ++counts[k] > best) { best = counts[k]; plain = it; }
        }
        if (!plain) continue;
        for (int x = PLAYFIELD_X0; x < right; x += 16)
            blit_item(width, plain, x, plain->y, 0, bar_y0, right, bar_y1);
    }
    for (size_t i = 0; i < s->count; ++i) {
        const SceneItem *it = &s->items[i];
        if (it->space != SCENE_SCREEN || it->y < bar_y0 - 15 || it->y >= bar_y1 ||
            it->x >= RIGHT_COLUMN_X || it->x < PLAYFIELD_X0) continue;
        if (it->y + it->pixels->h <= bar_y0) continue;
        if (it->kind == SCENE_BITMAP) {
            /* plain pieces are already there; skip them */
            int same = 0;
            for (size_t j = 0; j < s->count && !same; ++j) {
                const SceneItem *o = &s->items[j];
                same = o != it && o->kind == SCENE_BITMAP && o->source == it->source && o->y == it->y &&
                       o->space == SCENE_SCREEN && o->x >= PLAYFIELD_X0 && o->x < RIGHT_COLUMN_X;
            }
            if (same) continue;
        }
        blit_item(width, it, it->x < 40 ? it->x : it->x + extra / 2, it->y, 0, bar_y0, right, bar_y1);
    }
}

static void compose_level(const SceneSnapshot *s, int width)
{
    const SceneView *v = &s->view;
    int extra = width - SCENE_WIDTH;
    int px0 = PLAYFIELD_X0, py0 = PLAYFIELD_Y0;
    int px1 = width - (SCENE_WIDTH - PLAYFIELD_X1), py1 = PLAYFIELD_Y1;
    int32_t view_left = scene_wide_view_left(v->scroll_x, width);
    int32_t view_top = v->map_y_offset / 8;
    int top_row = v->map_y_offset / SCENE_MAP_COLUMNS;
    static _Thread_local uint8_t backdrop[2][4096 * 160];
    int pw = px1 - px0;

    /* backdrop: the 13-column pattern of the original, fixed to the screen, repeated */
    for (int variant = 0; variant < 2 && v->valid; ++variant)
        for (int row = 0; row < SCENE_VIEW_ROWS; ++row)
            for (int column = 0; column * 16 < pw; ++column) {
                int pattern = column % 13;
                uint16_t source = (uint16_t)(0x4000u + (unsigned)(row * 13 + pattern) * 0x20u +
                                             (variant ? 0x4100u : 0u));
                const uint8_t *cell = cache_bitmap(source, v->tile_generation);
                for (int yy = 0; yy < 16; ++yy)
                    for (int xx = 0; xx < 16 && column * 16 + xx < pw; ++xx)
                        backdrop[variant][(row * 16 + yy) * 4096 + column * 16 + xx] = cell[yy * 16 + xx];
            }
    /* map tiles of the wide view; empty cells show the backdrop */
    for (int row = 0; row < SCENE_VIEW_ROWS && v->valid; ++row) {
        int cy = py0 + (top_row + row) * 16 - view_top;
        for (int column = (int)(view_left / 16); column < SCENE_MAP_COLUMNS && column * 16 < view_left + pw; ++column) {
            int cx = px0 + column * 16 - (int)view_left;
            uint16_t tile = v->map[row][column];
            if (tile > 0x20u) {
                uint16_t source = tile < 0x5e0u ? (uint16_t)(tile + v->animation_phase) : tile;
                blit(width, cache_bitmap(source, v->tile_generation), 16, 16, cx, cy, px0, py0, px1, py1, 1);
            } else {
                const uint8_t *layer = backdrop[tile == 0x20u ? 1 : 0];
                for (int yy = 0; yy < 16; ++yy) {
                    int y = cy + yy;
                    if (y < py0 || y >= py1) continue;
                    for (int xx = 0; xx < 16; ++xx) {
                        int x = cx + xx;
                        if (x < px0 || x >= px1) continue;
                        canvas[y * width + x] = layer[(y - py0) * 4096 + (x - px0)];
                    }
                }
            }
        }
    }
    /* everything drawn: level items by level position, the rest by region (without a level
       view on the page, level items too: the playfield is centred like the original view) */
    for (size_t i = 0; i < s->count; ++i) {
        const SceneItem *it = &s->items[i];
        if (v->valid && (it->space == SCENE_BACKDROP || (it->space == SCENE_WORLD && it->kind == SCENE_BITMAP)))
            continue;                                      /* replaced by the layers above */
        if (it->space == SCENE_WORLD && v->valid) {
            blit_item(width, it, px0 + (int)(it->world_x - view_left), py0 + (int)(it->world_y - view_top),
                      px0, py0, px1, py1);
        } else if (it->offpage) {
            continue;
        } else if (it->x >= RIGHT_COLUMN_X) {
            blit_item(width, it, it->x + extra, it->y, 0, 0, width, SCENE_HEIGHT);
        } else if (it->x < PLAYFIELD_X0) {
            blit_item(width, it, it->x, it->y, 0, 0, PLAYFIELD_X0, SCENE_HEIGHT);
        } else if (it->y >= PLAYFIELD_Y0 && it->y < PLAYFIELD_Y1) {
            blit_item(width, it, it->x + extra / 2, it->y, px0, py0, px1, py1);
        }
    }
    compose_bar(s, width, 0, PLAYFIELD_Y0, extra);
    compose_bar(s, width, PLAYFIELD_Y1, SCENE_HEIGHT, extra);
}

int present_compose(const SceneSnapshot *s, int width, uint32_t *rgba)
{
    size_t n;
    if (width < SCENE_WIDTH) width = SCENE_WIDTH;
    n = (size_t)width * SCENE_HEIGHT;
    if ((int)n > canvas_capacity) {
        uint8_t *bigger = (uint8_t *)realloc(canvas, n);
        if (!bigger) return 0;
        canvas = bigger;
        canvas_capacity = (int)n;
    }
    if (width > SCENE_WIDTH && has_gameplay_frame(s)) {
        memset(canvas, 0, n);
        compose_level(s, width);
    } else {
        int offset = (width - SCENE_WIDTH) / 2;
        memset(canvas, MARGIN, n);
        for (int y = 0; y < SCENE_HEIGHT; ++y)
            memset(canvas + (size_t)y * width + offset, 0, SCENE_WIDTH);
        for (size_t i = 0; i < s->count; ++i) {
            const SceneItem *it = &s->items[i];
            if (it->offpage) continue;
            blit_item(width, it, it->x + offset, it->y, offset, 0, offset + SCENE_WIDTH, SCENE_HEIGHT);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        uint8_t c = canvas[i];
        rgba[i] = c == MARGIN ? 0xff000000u
                : 0xff000000u | s->palette_rgb[c == SCENE_TRANSPARENT ? 0 : (c & 15u)];
    }
    return 1;
}

/* ---- SDL side: the texture the window shows ------------------------------------------------ */

#include <SDL3/SDL.h>
#include <stdio.h>

void vga_render_rgb(uint32_t *out_320x200);
const uint8_t *vga_palette_registers(void);
uint32_t vga_colour_rgb(uint8_t register_value);

static SceneSnapshot *snapshots[2];
static int current = -1;                 /* the snapshot shown */
static uint64_t have_sequence;
static uint32_t *rgba;
static size_t rgba_capacity;
static SDL_Texture *texture;
static int texture_width, composed_width = -1;
static uint64_t verify_frames, verify_mismatches;

SDL_Texture *present_texture(SDL_Renderer *renderer, int width, const uint32_t **pixels)
{
    int next;
    size_t n;
    int fresh = 0;
    if (width < SCENE_WIDTH) width = SCENE_WIDTH;
    for (int i = 0; i < 2; ++i)
        if (!snapshots[i] && !(snapshots[i] = (SceneSnapshot *)calloc(1, sizeof(SceneSnapshot))))
            return NULL;
    next = current < 0 ? 0 : 1 - current;
    scene_release(snapshots[next]);
    if (scene_snapshot(snapshots[next], have_sequence)) {
        if (getenv("DUKE1_SCENE_DEBUG"))
            fprintf(stderr, "[scene] snapshot seq %llu page %d items %zu view %d\n",
                    (unsigned long long)snapshots[next]->sequence, snapshots[next]->page,
                    snapshots[next]->count, snapshots[next]->view.valid);
        if (current >= 0) scene_release(snapshots[current]);
        current = next;
        have_sequence = snapshots[current]->sequence;
        fresh = 1;
    }
    if (current < 0) return NULL;
    {
        /* The palette changes without the page changing (fades): use the live registers. */
        const uint8_t *regs = vga_palette_registers();
        for (int i = 0; i < 16; ++i) {
            uint32_t rgb = vga_colour_rgb(regs[i]);
            if (snapshots[current]->palette_rgb[i] != rgb) {
                snapshots[current]->palette_rgb[i] = rgb;
                fresh = 1;
            }
        }
    }
    n = (size_t)width * SCENE_HEIGHT;
    if (n > rgba_capacity) {
        uint32_t *bigger = (uint32_t *)realloc(rgba, n * sizeof(uint32_t));
        if (!bigger) return NULL;
        rgba = bigger;
        rgba_capacity = n;
    }
    if (!texture || texture_width != width) {
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                    width, SCENE_HEIGHT);
        if (!texture) return NULL;
        (void)SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
        texture_width = width;
        composed_width = -1;
    }
    if (fresh || composed_width != width) {
        if (!present_compose(snapshots[current], width, rgba)) return NULL;
        (void)SDL_UpdateTexture(texture, NULL, rgba, width * (int)sizeof(uint32_t));
        composed_width = width;
    }
    if (pixels) *pixels = rgba;
    return texture;
}

/* Anchor test (--verify-native): at every page flip, on the game thread - where the scene and
   the emulated page agree by construction - compose the shown page at 320 and compare.  With a
   wider canvas the wide picture is checked against the page too, region by region: the gameplay
   frame's left column in place, the right column (frame bar + HUD) at the right edge, the
   playfield centred (backdrop cells excepted: they are screen-fixed and continue the pattern;
   and only while the wide view is not clamped at a level edge), and every other screen centred. */
static SDL_AtomicInt verify_on;
static uint64_t verify_wide_frames, verify_wide_mismatches;
void present_set_verify(int on) { SDL_SetAtomicInt(&verify_on, on != 0); }

#define NO_OWNER 0xffffu
#define WIDE_ONLY 0xfffeu

/* For each page pixel, the item drawn last there (NO_OWNER: nothing); WIDE_ONLY where a sprite
   the wide view adds (kept off the page) covers it. */
static void owner_map(const SceneSnapshot *s, uint16_t map[SCENE_WIDTH * SCENE_HEIGHT])
{
    for (size_t i = 0; i < SCENE_WIDTH * SCENE_HEIGHT; ++i) map[i] = NO_OWNER;
    for (size_t i = 0; i < s->count; ++i) {
        const SceneItem *it = &s->items[i];
        const ScenePixels *px = it->pixels;
        for (int yy = 0; yy < px->h; ++yy)
            for (int xx = 0; xx < px->w; ++xx) {
                int x = it->x + xx, y = it->y + yy;
                if (x < 0 || x >= SCENE_WIDTH || y < 0 || y >= SCENE_HEIGHT ||
                    px->data[yy * px->w + xx] == SCENE_TRANSPARENT) continue;
                map[y * SCENE_WIDTH + x] = it->offpage ? WIDE_ONLY : (uint16_t)i;
            }
    }
}

static char verify_detail[512];

static uint32_t *verify_wide_picture;

static void write_ppm(const char *path, const uint32_t *rgb, int width)
{
    FILE *file = fopen(path, "wb");
    if (!file) return;
    fprintf(file, "P6 %d %d 255\n", width, SCENE_HEIGHT);
    for (size_t i = 0; i < (size_t)width * SCENE_HEIGHT; ++i) {
        unsigned char c[3] = { (unsigned char)(rgb[i] >> 16), (unsigned char)(rgb[i] >> 8), (unsigned char)rgb[i] };
        fwrite(c, 1, 3, file);
    }
    fclose(file);
}

static unsigned verify_wide(const SceneSnapshot *s, const uint32_t *ega, int width, const char **region)
{
    static uint32_t *wide;
    static size_t wide_capacity;
    static uint16_t owners[SCENE_WIDTH * SCENE_HEIGHT];
    size_t n = (size_t)width * SCENE_HEIGHT;
    int extra = width - SCENE_WIDTH;
    unsigned differing = 0;
    if (n > wide_capacity) {
        uint32_t *bigger = (uint32_t *)realloc(wide, n * sizeof(uint32_t));
        if (!bigger) return 0;
        wide = bigger;
        wide_capacity = n;
    }
    verify_wide_picture = wide;
    if (!present_compose(s, width, wide)) return 0;
    *region = "centred screen";
    if (!has_gameplay_frame(s)) {
        for (int y = 0; y < SCENE_HEIGHT; ++y)
            for (int x = 0; x < SCENE_WIDTH; ++x)
                differing += wide[y * width + x + extra / 2] != ega[y * SCENE_WIDTH + x];
        return differing;
    }
    *region = "left column";
    for (int y = 0; y < SCENE_HEIGHT; ++y)
        for (int x = 0; x < PLAYFIELD_X0; ++x)
            differing += wide[y * width + x] != ega[y * SCENE_WIDTH + x];
    if (differing) return differing;
    *region = "right column";
    for (int y = 0; y < SCENE_HEIGHT; ++y)
        for (int x = RIGHT_COLUMN_X; x < SCENE_WIDTH; ++x)
            differing += wide[y * width + x + extra] != ega[y * SCENE_WIDTH + x];
    if (differing) return differing;
    *region = "playfield";
    if (s->view.valid &&
        scene_wide_view_left(s->view.scroll_x, width) != (int32_t)s->view.scroll_x * 8 - extra / 2)
        return 0;                                          /* clamped: a different view */
    owner_map(s, owners);
    verify_detail[0] = 0;
    for (int y = PLAYFIELD_Y0; y < PLAYFIELD_Y1; ++y)
        for (int x = PLAYFIELD_X0; x < PLAYFIELD_X1; ++x) {
            uint16_t o = owners[y * SCENE_WIDTH + x];
            if (o == WIDE_ONLY || (o != NO_OWNER && s->items[o].space == SCENE_BACKDROP)) continue;
            if (wide[y * width + x + extra / 2] == ega[y * SCENE_WIDTH + x]) continue;
            if (!differing++ && o != NO_OWNER) {
                const SceneItem *it = &s->items[o];
                (void)snprintf(verify_detail, sizeof(verify_detail),
                               " (first at %d,%d: item space %d kind %d at %d,%d source %04x site %08x world %d,%d; view scroll %d phase %u)",
                               x, y, it->space, it->kind, it->x, it->y, it->source, (unsigned)it->site,
                               (int)it->world_x, (int)it->world_y, s->view.scroll_x, s->view.animation_phase);
            }
        }
    return differing;
}

void present_verify_shown(void)
{
    static SceneSnapshot *snap;
    static uint32_t native[SCENE_WIDTH * SCENE_HEIGHT], ega[SCENE_WIDTH * SCENE_HEIGHT];
    unsigned differing = 0;
    int width;
    if (!SDL_GetAtomicInt(&verify_on)) return;
    if (!snap && !(snap = (SceneSnapshot *)calloc(1, sizeof(SceneSnapshot)))) return;
    if (!scene_snapshot(snap, (uint64_t)-1)) return;
    vga_render_rgb(ega);
    if (present_compose(snap, SCENE_WIDTH, native)) {
        for (size_t i = 0; i < SCENE_WIDTH * SCENE_HEIGHT; ++i) differing += ega[i] != native[i];
        ++verify_frames;
        if (verify_frames % 100 == 0)
            fprintf(stderr, "[native] %llu flips verified, %llu with differences\n",
                    (unsigned long long)verify_frames, (unsigned long long)verify_mismatches);
        if (differing) {
            ++verify_mismatches;
            fprintf(stderr, "[native] flip %llu: %u differing pixels (%zu items)\n",
                    (unsigned long long)verify_frames, differing, snap->count);
        }
    }
    width = scene_wide_canvas_width();
    if (width > SCENE_WIDTH) {
        const char *region = "";
        unsigned wide_differing = verify_wide(snap, ega, width, &region);
        ++verify_wide_frames;
        if (wide_differing) {
            const char *dump = getenv("DUKE1_VERIFY_DUMP");     /* directory for the evidence */
            ++verify_wide_mismatches;
            if (dump && verify_wide_mismatches <= 20) {
                char path[1024];
                (void)snprintf(path, sizeof(path), "%s/flip%llu-page.ppm", dump, (unsigned long long)verify_frames);
                write_ppm(path, ega, SCENE_WIDTH);
                (void)snprintf(path, sizeof(path), "%s/flip%llu-wide.ppm", dump, (unsigned long long)verify_frames);
                write_ppm(path, verify_wide_picture, width);
            }
            fprintf(stderr, "[native] flip %llu, %d wide: %s, %u differing pixels%s\n",
                    (unsigned long long)verify_frames, width, region, wide_differing,
                    strcmp(region, "playfield") ? "" : verify_detail);
        }
    }
    scene_release(snap);
}

void present_report(void)
{
    if (verify_frames)
        fprintf(stderr, "[native] verified %llu frames, %llu with differences\n",
                (unsigned long long)verify_frames, (unsigned long long)verify_mismatches);
    if (verify_wide_frames)
        fprintf(stderr, "[native] wide layout verified on %llu frames, %llu with differences\n",
                (unsigned long long)verify_wide_frames, (unsigned long long)verify_wide_mismatches);
}

void present_shutdown(void)
{
    for (int i = 0; i < 2; ++i) {
        if (snapshots[i]) { scene_release(snapshots[i]); free(snapshots[i]); snapshots[i] = NULL; }
    }
    if (texture) SDL_DestroyTexture(texture);
    texture = NULL;
    free(rgba); rgba = NULL; rgba_capacity = 0;
    current = -1; have_sequence = 0;
}
