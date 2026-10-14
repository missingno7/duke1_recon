/* scene.h - the native picture: what the game has drawn, as items instead of pixels.

   Every drawing primitive of the toolbox (tiles and other 16x16 bitmaps, sprites, glyphs, the
   water copy) and every write that bypasses it (the full-screen pictures) becomes an item on the
   video page it was drawn to: position, size, its own pixels (palette indices, read back from the
   emulated page right after the primitive ran, so they are exact) and its space - WORLD for the
   level (map tiles, actors, effects; with a world position), BACKDROP for the screen-fixed
   backdrop cells behind the level, SCREEN for everything else (frame, HUD, dialogs, text,
   menus, pictures).  A per-page ownership map drops items that later drawing hid completely,
   so a page holds exactly what is visible on it.

   The presenter (present.c) never looks at the emulated page: it takes a snapshot of the
   displayed page's items and composes the picture natively - 1:1 it reproduces the original
   page exactly; wide, it lays the items out for the window (docs/enhanced.md). */
#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>
#include <stddef.h>

enum {
    SCENE_WIDTH = 320,
    SCENE_HEIGHT = 200,
    SCENE_PAGES = 2,
    SCENE_MAX_ITEMS = 4096,          /* live items per page */
    SCENE_MAP_COLUMNS = 128,
    SCENE_MAP_ROWS = 90,
    SCENE_VIEW_ROWS = 10,
    SCENE_BACKDROP_COLUMNS = 14,
    SCENE_TRANSPARENT = 0xff         /* item pixel not drawn */
};

/* The original layout in page pixels. */
enum {
    PLAYFIELD_X0 = 16, PLAYFIELD_X1 = 224,      /* 208 x 160: 13 tiles visible */
    PLAYFIELD_Y0 = 16, PLAYFIELD_Y1 = 176,
    RIGHT_COLUMN_X = 224                        /* frame bar + HUD: 96 px to the right edge */
};

enum scene_space { SCENE_SCREEN = 0, SCENE_WORLD = 1, SCENE_BACKDROP = 2 };
enum scene_kind { SCENE_BITMAP = 1, SCENE_SPRITE, SCENE_GLYPH, SCENE_WATER, SCENE_PICTURE };

typedef struct scene_pixels {           /* immutable once published; shared by snapshots */
    int refcount;
    uint16_t w, h;
    uint8_t data[];                     /* w*h palette indices, SCENE_TRANSPARENT = not drawn */
} ScenePixels;

typedef struct scene_item {
    uint64_t seq;                       /* drawing order */
    int16_t x, y;                       /* page position */
    uint8_t space, kind;
    uint8_t offpage;                    /* drawn outside the 320x200 page (widescreen margin) */
    uint16_t source;                    /* bitmap: tile-cache offset (for the frame layout) */
    uint32_t site;                      /* sprite: call site (interpolation identity) */
    int32_t world_x, world_y;           /* WORLD: level position of the top-left pixel */
    ScenePixels *pixels;
} SceneItem;

/* The level view of the last tile strip drawn on a page. */
typedef struct scene_view {
    int valid;
    int16_t scroll_x;                   /* level_scroll_x: original view left = scroll_x * 8 */
    int16_t map_y_offset;               /* level_map_y_offset: top row = map_y_offset / 128 */
    uint16_t animation_phase;
    uint16_t map[SCENE_VIEW_ROWS][SCENE_MAP_COLUMNS];    /* the visible map rows */
    uint32_t tile_generation;           /* changes when the tile cache is reloaded */
} SceneView;

typedef struct scene_snapshot {
    uint64_t sequence;                  /* changes whenever the displayed page changed */
    int page;
    size_t count;
    SceneItem items[SCENE_MAX_ITEMS];   /* in drawing order */
    SceneView view;
    uint32_t palette_rgb[16];
} SceneSnapshot;

int  scene_init(void);
void scene_shutdown(void);
void scene_reset(void);                 /* mode set: every page empty */
void scene_set_active(int on);          /* the enhanced renderer is on: record */

/* Game thread: the toolbox calls scene_before_draw before each primitive draws and the
   matching scene_add_* right after it. */
void scene_before_draw(void);
void scene_select_page(int page);
void scene_show_page(int page);
void scene_add_bitmap(uint16_t source, int x, int y);              /* after the blit */
void scene_add_sprite(uint32_t site, const char *source, int x, int y, int written);
void scene_add_glyph(int x, int y, const uint8_t row_masks[8]);    /* after the glyph */
void scene_add_water(int x, int y, int w, int h);                  /* after the copy */
void scene_begin_strip(int16_t scroll_x, int16_t map_y_offset);    /* draw_animated_level_strip */
void scene_capture_view(const uint16_t *tile_map, int16_t map_y_offset, uint16_t animation_phase);
void scene_end_strip(void);
/* Sprite call sites: the port generator sets SCENE_SCREEN_SITE on the sites that draw at fixed
   screen positions (HUD, title, transitions); every other site draws a level sprite. */
#define SCENE_SCREEN_SITE 0x40000000u
/* Widescreen: a level sprite the game drew outside the original playfield (the wide view shows
   more of the level) is recorded but kept off the page, which has the frame and HUD there. */
int  scene_sprite_off_page(uint32_t site, int x, int y);

/* The wide presentation pass (wide_pass.c): wanted now?  While it runs, the view tests answer
   for the wide margins only. */
int  scene_wide_pass_wanted(void);
void scene_wide_pass_begin(void);
void scene_wide_pass_end(void);
void scene_wide_pass_routine(void);     /* a new routine: no actor's gate is open */
void scene_wide_pass_report(void);

/* Presenter thread. */
int  scene_snapshot(SceneSnapshot *out, uint64_t have_sequence);   /* 0: nothing new */
void scene_release(SceneSnapshot *snapshot);
/* Tile and backdrop pixels from the tile cache (16x16 palette indices). */
void scene_decode_cache_bitmap(uint16_t source, uint8_t out[256]);

/* Widescreen geometry shared with the view tests the generator routes here. */
void scene_set_wide(int canvas_width, int widescreen, int wide_activity);
int  scene_wide_canvas_width(void);
int32_t scene_wide_view_left(int16_t scroll_x, int canvas_width);   /* level x of the wide view */

#endif
