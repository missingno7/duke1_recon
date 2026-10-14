/* scene.c - the native picture, game-thread side (see scene.h). */
#include "scene.h"
#include "platform.h"

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <string.h>

/* vga.c */
uint32_t vga_region_write_count(int region);
uint8_t *vga_plane(int plane);
const uint8_t *vga_palette_registers(void);
uint32_t vga_colour_rgb(uint8_t register_value);

#define NO_ITEM 0xffffu

typedef struct page {
    SceneItem items[SCENE_MAX_ITEMS];       /* slots */
    uint32_t owned[SCENE_MAX_ITEMS];        /* visible pixels per slot; 0 = free */
    uint16_t next[SCENE_MAX_ITEMS], prev[SCENE_MAX_ITEMS];   /* drawing order */
    uint16_t head, tail;
    uint16_t free_list[SCENE_MAX_ITEMS];
    int free_count;
    uint16_t owner[SCENE_WIDTH * SCENE_HEIGHT];
    uint32_t seen_writes;                   /* vga writes accounted for */
    SceneView view;
    uint64_t version;
} Page;

static Page pages[SCENE_PAGES];
static SDL_Mutex *lock;
static uint64_t next_seq = 1;
static int draw_page, shown_page;
static uint64_t shown_version;              /* bumps on every change of what is displayed */
static uint32_t cache_writes_seen;
static uint32_t tile_generation = 1;

static int in_strip;                        /* inside draw_animated_level_strip */
static int16_t strip_scroll_x, strip_map_y;
static int view_known;                      /* a strip has run since the last mode set */

static SDL_AtomicInt wide_canvas, wide_enabled, wide_activity;
static SDL_AtomicInt active;             /* the enhanced renderer is on */

/* ---- pixels ---------------------------------------------------------------------------- */

static ScenePixels *pixels_new(int w, int h)
{
    ScenePixels *p = (ScenePixels *)malloc(sizeof(ScenePixels) + (size_t)w * (size_t)h);
    if (!p) return NULL;
    p->refcount = 1;
    p->w = (uint16_t)w;
    p->h = (uint16_t)h;
    memset(p->data, SCENE_TRANSPARENT, (size_t)w * (size_t)h);
    return p;
}

static void pixels_ref(ScenePixels *p) { if (p) SDL_AtomicIncRef((SDL_AtomicInt *)&p->refcount); }

static void pixels_unref(ScenePixels *p)
{
    if (p && SDL_AtomicDecRef((SDL_AtomicInt *)&p->refcount))
        free(p);
}

static uint8_t page_pixel(int page, int x, int y)
{
    uint16_t offset = (uint16_t)((page ? 0x2000u : 0u) + (unsigned)y * 40u + (unsigned)x / 8u);
    unsigned bit = 7u - ((unsigned)x & 7u);
    uint8_t colour = 0;
    for (int plane = 0; plane < 4; ++plane)
        colour |= (uint8_t)(((vga_plane(plane)[offset] >> bit) & 1u) << plane);
    return colour;
}

void scene_decode_cache_bitmap(uint16_t source, uint8_t out[256])
{
    for (int row = 0; row < 16; ++row)
        for (int x = 0; x < 16; ++x) {
            uint16_t offset = (uint16_t)(0x4000u + source + (unsigned)row * 2u + (unsigned)x / 8u);
            unsigned bit = 7u - ((unsigned)x & 7u);
            uint8_t colour = 0;
            for (int plane = 0; plane < 4; ++plane)
                colour |= (uint8_t)(((vga_plane(plane)[offset] >> bit) & 1u) << plane);
            out[row * 16 + x] = colour;
        }
}

/* ---- pages ----------------------------------------------------------------------------- */

static void page_clear(Page *pg)
{
    for (uint16_t s = pg->head; s != NO_ITEM; s = pg->next[s])
        pixels_unref(pg->items[s].pixels);
    memset(pg->owned, 0, sizeof(pg->owned));
    pg->head = pg->tail = NO_ITEM;
    pg->free_count = SCENE_MAX_ITEMS;
    for (int i = 0; i < SCENE_MAX_ITEMS; ++i)
        pg->free_list[i] = (uint16_t)(SCENE_MAX_ITEMS - 1 - i);
    for (size_t i = 0; i < SCENE_WIDTH * SCENE_HEIGHT; ++i)
        pg->owner[i] = NO_ITEM;
    pg->view.valid = 0;
    ++pg->version;
}

static void slot_free(Page *pg, uint16_t s)
{
    if (pg->prev[s] != NO_ITEM) pg->next[pg->prev[s]] = pg->next[s]; else pg->head = pg->next[s];
    if (pg->next[s] != NO_ITEM) pg->prev[pg->next[s]] = pg->prev[s]; else pg->tail = pg->prev[s];
    pixels_unref(pg->items[s].pixels);
    pg->items[s].pixels = NULL;
    pg->free_list[pg->free_count++] = s;
}

/* Add an item whose pixels are known; it takes ownership of every drawn pixel. */
static void page_add(int page, SceneItem *item)
{
    Page *pg = &pages[page];
    ScenePixels *px = item->pixels;
    uint16_t s;
    if (!px) return;
    if (pg->free_count == 0) {                     /* never expected; keep the newest */
        uint16_t oldest = pg->head;
        for (size_t i = 0; i < SCENE_WIDTH * SCENE_HEIGHT; ++i)
            if (pg->owner[i] == oldest) pg->owner[i] = NO_ITEM;
        pg->owned[oldest] = 0;
        slot_free(pg, oldest);
    }
    s = pg->free_list[--pg->free_count];
    item->seq = next_seq++;
    pg->items[s] = *item;
    pg->owned[s] = 0;
    pg->next[s] = NO_ITEM;
    pg->prev[s] = pg->tail;
    if (pg->tail != NO_ITEM) pg->next[pg->tail] = s; else pg->head = s;
    pg->tail = s;
    for (int yy = 0; yy < px->h; ++yy) {
        int y = item->y + yy;
        if (y < 0 || y >= SCENE_HEIGHT) continue;
        for (int xx = 0; xx < px->w; ++xx) {
            int x = item->x + xx;
            uint16_t old;
            if (x < 0 || x >= SCENE_WIDTH || px->data[yy * px->w + xx] == SCENE_TRANSPARENT) continue;
            old = pg->owner[y * SCENE_WIDTH + x];
            if (old != NO_ITEM && --pg->owned[old] == 0)
                slot_free(pg, old);
            pg->owner[y * SCENE_WIDTH + x] = s;
            ++pg->owned[s];
        }
    }
    if (pg->owned[s] == 0)                         /* drew nothing on the page */
        slot_free(pg, s);
    ++pg->version;
}

/* The pixels the page now shows in a rectangle, limited to a mask (NULL: all). */
static ScenePixels *read_page(int page, int x0, int y0, int w, int h, const uint8_t *mask)
{
    ScenePixels *px = pixels_new(w, h);
    if (!px) return NULL;
    for (int yy = 0; yy < h; ++yy)
        for (int xx = 0; xx < w; ++xx) {
            int x = x0 + xx, y = y0 + yy;
            if (x < 0 || x >= SCENE_WIDTH || y < 0 || y >= SCENE_HEIGHT) continue;
            if (mask && !mask[yy * w + xx]) continue;
            px->data[yy * w + xx] = page_pixel(page, x, y);
        }
    return px;
}

/* Writes that bypassed the toolbox (full-screen pictures): the whole page becomes one item. */
static void account_writes(void)
{
    uint32_t cache = vga_region_write_count(2);
    if (cache != cache_writes_seen) {               /* tiles reloaded */
        cache_writes_seen = cache;
        ++tile_generation;
    }
    for (int page = 0; page < SCENE_PAGES; ++page) {
        uint32_t writes = vga_region_write_count(page);
        if (writes != pages[page].seen_writes) {
            SceneItem item;
            memset(&item, 0, sizeof(item));
            item.kind = SCENE_PICTURE;
            item.space = SCENE_SCREEN;
            item.pixels = read_page(page, 0, 0, SCENE_WIDTH, SCENE_HEIGHT, NULL);
            page_add(page, &item);
            pages[page].seen_writes = writes;
        }
    }
}

static void writes_done(void)
{
    for (int page = 0; page < SCENE_PAGES; ++page)
        pages[page].seen_writes = vga_region_write_count(page);
}

static void changed(int page)
{
    if (page == shown_page) ++shown_version;
}

/* ---- life cycle ---------------------------------------------------------------------- */

int scene_init(void)
{
    lock = SDL_CreateMutex();
    if (!lock) return 0;
    for (int i = 0; i < SCENE_PAGES; ++i) {
        pages[i].head = pages[i].tail = NO_ITEM;    /* empty lists before the first clear */
        page_clear(&pages[i]);
    }
    SDL_SetAtomicInt(&wide_canvas, SCENE_WIDTH);
    return 1;
}

void scene_shutdown(void)
{
    if (!lock) return;
    for (int i = 0; i < SCENE_PAGES; ++i) page_clear(&pages[i]);
    SDL_DestroyMutex(lock);
    lock = NULL;
}

void scene_reset(void)
{
    if (!lock) return;
    SDL_LockMutex(lock);
    for (int i = 0; i < SCENE_PAGES; ++i) page_clear(&pages[i]);
    writes_done();
    view_known = 0;
    in_strip = 0;
    ++shown_version;
    SDL_UnlockMutex(lock);
}

/* ---- game thread: primitives --------------------------------------------------------- */

void scene_set_active(int on)
{
    if (!lock) return;
    SDL_LockMutex(lock);
    if (on && !SDL_GetAtomicInt(&active)) {
        /* Switched on mid-game: capture both pages as they are at the next draw or flip. */
        for (int page = 0; page < SCENE_PAGES; ++page)
            pages[page].seen_writes = vga_region_write_count(page) - 1u;
    }
    SDL_SetAtomicInt(&active, on != 0);
    SDL_UnlockMutex(lock);
}

/* Before a toolbox primitive draws: anything written to a page since the last primitive came
   from elsewhere (the full-screen pictures) and becomes a picture item first. */
void scene_before_draw(void)
{
    if (!lock || !SDL_GetAtomicInt(&active)) return;
    SDL_LockMutex(lock);
    account_writes();
    SDL_UnlockMutex(lock);
}

void scene_select_page(int page)
{
    draw_page = page ? 1 : 0;
}

void scene_show_page(int page)
{
    if (!lock) return;
    SDL_LockMutex(lock);
    if (SDL_GetAtomicInt(&active))
        account_writes();
    shown_page = page ? 1 : 0;
    ++shown_version;
    SDL_UnlockMutex(lock);
}

static int world_space_now(void) { return in_strip || view_known; }

static void world_position(SceneItem *item)
{
    item->world_x = (int32_t)item->x - PLAYFIELD_X0 + (int32_t)strip_scroll_x * 8;
    item->world_y = (int32_t)item->y - PLAYFIELD_Y0 + (int32_t)strip_map_y / 8;
}

void scene_add_bitmap(uint16_t source, int x, int y)
{
    SceneItem item;
    if (!lock || !SDL_GetAtomicInt(&active)) return;
    SDL_LockMutex(lock);
    memset(&item, 0, sizeof(item));
    item.kind = SCENE_BITMAP;
    item.source = source;
    item.x = (int16_t)x;
    item.y = (int16_t)y;
    if (in_strip) {
        /* The strip draws map tiles (cache offsets below 0x4000) and, where the map is empty,
           the backdrop cells (0x4000 and up), which are fixed to the screen. */
        item.space = source >= 0x4000u ? SCENE_BACKDROP : SCENE_WORLD;
        world_position(&item);
    }
    item.pixels = read_page(draw_page, x, y, 16, 16, NULL);
    page_add(draw_page, &item);
    writes_done();
    changed(draw_page);
    SDL_UnlockMutex(lock);
}

void scene_add_sprite(uint32_t site, const char *source, int x, int y, int written)
{
    SceneItem item;
    uint8_t mask[256];
    if (!lock || !SDL_GetAtomicInt(&active)) return;
    SDL_LockMutex(lock);
    memset(&item, 0, sizeof(item));
    item.kind = SCENE_SPRITE;
    item.site = site;
    item.x = (int16_t)x;
    item.y = (int16_t)y;
    /* The sprite's own mask: per row two bytes, each a mask byte followed by four planes. */
    for (int row = 0; row < 16; ++row)
        for (int half = 0; half < 2; ++half) {
            const uint8_t *cell = (const uint8_t *)source + row * 10 + half * 5;
            for (int bit = 0; bit < 8; ++bit)
                mask[row * 16 + half * 8 + bit] = (uint8_t)((cell[0] >> (7 - bit)) & 1u);
        }
    /* In the level picture a sprite is part of the level unless it is drawn into the right
       column (the HUD: health, firepower, inventory); margin sprites are always level. */
    if (world_space_now() && (!written || (x < RIGHT_COLUMN_X && y + 16 > PLAYFIELD_Y0 &&
                                           y < PLAYFIELD_Y1))) {
        item.space = SCENE_WORLD;
        world_position(&item);
    }
    if (written) {
        item.pixels = read_page(draw_page, x, y, 16, 16, mask);
    } else {
        /* Not written to the page (widescreen margin): decode from the sprite data. */
        item.pixels = pixels_new(16, 16);
        if (item.pixels)
            for (int row = 0; row < 16; ++row)
                for (int half = 0; half < 2; ++half) {
                    const uint8_t *cell = (const uint8_t *)source + row * 10 + half * 5;
                    for (int bit = 0; bit < 8; ++bit) {
                        uint8_t colour = 0;
                        if (!((cell[0] >> (7 - bit)) & 1u)) continue;
                        for (int plane = 0; plane < 4; ++plane)
                            colour |= (uint8_t)(((cell[1 + plane] >> (7 - bit)) & 1u) << plane);
                        item.pixels->data[row * 16 + half * 8 + bit] = colour;
                    }
                }
    }
    if (written) page_add(draw_page, &item);
    else {
        /* Off-page sprites live outside the 320x200 ownership map: keep them in the page's
           list until the next strip replaces the level picture. */
        Page *pg = &pages[draw_page];
        if (pg->free_count > 0 && item.pixels) {
            uint16_t s = pg->free_list[--pg->free_count];
            item.seq = next_seq++;
            item.offpage = 1;
            pg->items[s] = item;
            pg->owned[s] = 1;                      /* pinned until the next strip */
            pg->next[s] = NO_ITEM;
            pg->prev[s] = pg->tail;
            if (pg->tail != NO_ITEM) pg->next[pg->tail] = s; else pg->head = s;
            pg->tail = s;
            ++pg->version;
        } else {
            pixels_unref(item.pixels);
        }
    }
    writes_done();
    changed(draw_page);
    SDL_UnlockMutex(lock);
}

void scene_add_glyph(int x, int y, const uint8_t row_masks[8])
{
    SceneItem item;
    uint8_t mask[64];
    if (!lock || !SDL_GetAtomicInt(&active)) return;
    SDL_LockMutex(lock);
    memset(&item, 0, sizeof(item));
    item.kind = SCENE_GLYPH;
    item.x = (int16_t)x;
    item.y = (int16_t)y;
    for (int row = 0; row < 8; ++row)
        for (int bit = 0; bit < 8; ++bit)
            mask[row * 8 + bit] = (uint8_t)((row_masks[row] >> (7 - bit)) & 1u);
    item.pixels = read_page(draw_page, x, y, 8, 8, mask);
    page_add(draw_page, &item);
    writes_done();
    changed(draw_page);
    SDL_UnlockMutex(lock);
}

void scene_add_water(int x, int y, int w, int h)
{
    SceneItem item;
    if (!lock || !SDL_GetAtomicInt(&active)) return;
    SDL_LockMutex(lock);
    memset(&item, 0, sizeof(item));
    item.kind = SCENE_WATER;
    item.x = (int16_t)x;
    item.y = (int16_t)y;
    if (world_space_now()) {
        item.space = SCENE_WORLD;
        world_position(&item);
    }
    item.pixels = read_page(draw_page, x, y, w, h, NULL);
    page_add(draw_page, &item);
    writes_done();
    changed(draw_page);
    SDL_UnlockMutex(lock);
}

void scene_begin_strip(int16_t scroll_x, int16_t map_y_offset)
{
    if (!lock || !SDL_GetAtomicInt(&active)) return;
    SDL_LockMutex(lock);
    /* A new level picture: drop the previous one's off-page (margin) sprites. */
    {
        Page *pg = &pages[draw_page];
        uint16_t s = pg->head;
        while (s != NO_ITEM) {
            uint16_t n = pg->next[s];
            if (pg->items[s].offpage) slot_free(pg, s);
            s = n;
        }
    }
    in_strip = 1;
    view_known = 1;
    strip_scroll_x = scroll_x;
    strip_map_y = map_y_offset;
    SDL_UnlockMutex(lock);
}

void scene_capture_view(const uint16_t *tile_map, int16_t map_y_offset, uint16_t animation_phase)
{
    SceneView *v;
    int top;
    if (!lock || !tile_map || !SDL_GetAtomicInt(&active)) return;
    SDL_LockMutex(lock);
    v = &pages[draw_page].view;
    v->valid = 1;
    v->scroll_x = strip_scroll_x;
    v->map_y_offset = map_y_offset;
    v->animation_phase = animation_phase;
    v->tile_generation = tile_generation;
    top = map_y_offset / SCENE_MAP_COLUMNS;
    for (int row = 0; row < SCENE_VIEW_ROWS; ++row)
        for (int column = 0; column < SCENE_MAP_COLUMNS; ++column) {
            int r = top + row;
            v->map[row][column] = (r >= 0 && r < SCENE_MAP_ROWS)
                ? tile_map[r * SCENE_MAP_COLUMNS + column] : 0;
        }
    SDL_UnlockMutex(lock);
}

void scene_end_strip(void)
{
    in_strip = 0;
}

/* ---- presenter --------------------------------------------------------------------------- */

int scene_snapshot(SceneSnapshot *out, uint64_t have_sequence)
{
    const Page *pg;
    const uint8_t *regs;
    if (!lock) return 0;
    SDL_LockMutex(lock);
    if (shown_version == have_sequence) {
        SDL_UnlockMutex(lock);
        return 0;
    }
    pg = &pages[shown_page];
    out->sequence = shown_version;
    out->page = shown_page;
    out->count = 0;
    for (uint16_t s = pg->head; s != NO_ITEM && out->count < SCENE_MAX_ITEMS; s = pg->next[s]) {
        out->items[out->count] = pg->items[s];
        pixels_ref(pg->items[s].pixels);
        ++out->count;
    }
    out->view = pg->view;
    regs = vga_palette_registers();
    for (int i = 0; i < 16; ++i)
        out->palette_rgb[i] = vga_colour_rgb(regs[i]);
    SDL_UnlockMutex(lock);
    return 1;
}

void scene_release(SceneSnapshot *snapshot)
{
    for (size_t i = 0; i < snapshot->count; ++i)
        pixels_unref(snapshot->items[i].pixels);
    snapshot->count = 0;
}

/* ---- widescreen geometry ---------------------------------------------------------------- */

void scene_set_wide(int canvas_width, int widescreen, int activity)
{
    if (canvas_width < SCENE_WIDTH) canvas_width = SCENE_WIDTH;
    SDL_SetAtomicInt(&wide_canvas, canvas_width);
    SDL_SetAtomicInt(&wide_enabled, widescreen != 0);
    SDL_SetAtomicInt(&wide_activity, activity != 0);
}

int scene_wide_canvas_width(void)
{
    return SDL_GetAtomicInt(&wide_enabled) ? SDL_GetAtomicInt(&wide_canvas) : SCENE_WIDTH;
}

int32_t scene_wide_view_left(int16_t scroll_x, int canvas_width)
{
    int width = canvas_width - SCENE_WIDTH + (PLAYFIELD_X1 - PLAYFIELD_X0);   /* wide playfield */
    int32_t left = (int32_t)scroll_x * 8 - (width - (PLAYFIELD_X1 - PLAYFIELD_X0)) / 2;
    int32_t max_left = SCENE_MAP_COLUMNS * 16 - width;
    if (left > max_left) left = max_left;
    if (left < 0) left = 0;
    return left;
}

int scene_sprite_off_page(int x, int y)
{
    if (!SDL_GetAtomicInt(&active) || !SDL_GetAtomicInt(&wide_enabled) || !view_known || y + 16 <= PLAYFIELD_Y0 || y >= PLAYFIELD_Y1)
        return 0;
    /* Left of the playfield, or beyond the page.  (Between the playfield and the page edge the
       game draws the HUD; a level sprite there is drawn on the page like the original.) */
    return x < PLAYFIELD_X0 || x + 16 > SCENE_WIDTH;
}

/* The view tests the generator routes here: draw-gating ones see the wide view; behaviour
   ones only with wide_activity. */
static int wide_view_outside(int world_x, int world_y, int original_result)
{
    int canvas = scene_wide_canvas_width();
    int width = canvas - SCENE_WIDTH + (PLAYFIELD_X1 - PLAYFIELD_X0);
    int32_t left;
    if (!SDL_GetAtomicInt(&wide_enabled) || canvas <= SCENE_WIDTH || !view_known)
        return original_result;
    left = scene_wide_view_left(strip_scroll_x, canvas);
    if ((int32_t)world_x * 8 < left || (int32_t)world_x * 8 >= left + width)
        return 1;
    if (world_y < strip_map_y - 64 || world_y >= strip_map_y + 1280)
        return 1;
    return 0;
}

int port_is_world_position_outside_wide_view(int world_x, int world_y, int original_result)
{
    return wide_view_outside(world_x, world_y, original_result);
}

int port_is_world_position_outside_wide_if_active(int world_x, int world_y, int original_result)
{
    if (!SDL_GetAtomicInt(&wide_activity)) return original_result;
    return wide_view_outside(world_x, world_y, original_result);
}

/* ---- the hook names the port generator emits (draw_animated_level_strip, input loops) ---- */

void capture_begin_gameplay_frame(int16_t scroll_x, int16_t map_y_offset)
{
    scene_begin_strip(scroll_x, map_y_offset);
}

void capture_snapshot_wide_tiles(const uint16_t *tile_map, int16_t map_y_offset, uint16_t phase)
{
    scene_capture_view(tile_map, map_y_offset, phase);
}

void capture_end_tile_strip(void) { scene_end_strip(); }

/* Dialogs and input loops need nothing special: what they draw on the shown page is shown. */
void capture_publish_intermediate_gameplay_frame(int16_t drawing_page) { (void)drawing_page; }
void capture_set_modal_capture_active(int active_now) { (void)active_now; }
