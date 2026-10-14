/* scene_selftest.c - the native scene against the emulated EGA.

   Draws through the real toolbox (opaque 16x16 bitmaps from the tile cache, masked sprites,
   masked glyphs, a page-to-page copy, a picture written around the toolbox, overdraw that hides
   earlier items), composes the shown page natively at 320 and requires it to equal the emulated
   page pixel for pixel. */
#include "platform.h"
#include "scene.h"
#include "present.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_outport(uint16_t port, uint16_t value);
#define outport test_outport

uint8_t vga_graphics_register(uint8_t index);
int16_t set_video_mode(int16_t mode);
int16_t select_draw_page(int16_t page);
int16_t show_video_page(int16_t page);
int16_t blit_bitmap_to_video_page(int16_t source_offset, int16_t destination_offset);
int16_t copy_planar_video_region(int16_t x, int16_t y, int16_t source_offset);
int16_t blit_planar_sprite_rows(char *src, int16_t x, int16_t y);
int16_t draw_ega_glyph(char *src, int16_t x, int16_t y);
int16_t blit_planar_masked_glyph(char *src, int16_t x, int16_t y);
void vga_render_rgb(uint32_t *out_320x200);

void pc_enable(void) {}

static int failures;
#define CHECK(cond, ...) do { if (!(cond)) { ++failures; printf("FAIL: " __VA_ARGS__); printf("\n"); } } while (0)

/* A cache bitmap: 32 bytes per plane at 0x4000 + source. */
static void put_cache_bitmap(uint16_t source, unsigned seed)
{
    for (int plane = 0; plane < 4; ++plane) {
        uint8_t *p = vga_plane(plane);
        for (int i = 0; i < 32; ++i)
            p[(uint16_t)(0x4000u + source + i)] = (uint8_t)((seed * 37u + (unsigned)i * 11u + (unsigned)plane * 73u) & 0xffu);
    }
}

static void make_sprite(char *s, unsigned seed)
{
    for (int i = 0; i < 160; ++i) s[i] = (char)((seed * 13u + (unsigned)i * 29u) & 0xffu);
}

static int compare(const char *what)
{
    static SceneSnapshot snap;
    static uint32_t native[320 * 200], ega[320 * 200];
    int differing = 0;
    scene_release(&snap);
    CHECK(scene_snapshot(&snap, 0) == 1, "%s: no snapshot", what);
    CHECK(present_compose(&snap, 320, native) == 1, "%s: compose failed", what);
    vga_render_rgb(ega);
    for (int i = 0; i < 320 * 200; ++i) differing += native[i] != ega[i];
    CHECK(differing == 0, "%s: %d differing pixels (%zu items)", what, differing, snap.count);
    printf("%-34s items %4zu  differing %d\n", what, snap.count, differing);
    return differing;
}

int main(void)
{
    char sprite[160], glyph[40];
    setvbuf(stdout, NULL, _IONBF, 0);
    if (!scene_init()) { puts("scene_init failed"); return 1; }
    scene_set_active(1);
    puts("init");
    set_video_mode(0);                         /* mode 0Dh, scene reset */
    puts("mode set");
    for (unsigned i = 0; i < 64; ++i) put_cache_bitmap((uint16_t)(i * 0x20u), i + 1u);

    /* a full page of opaque tiles, as the game clears and frames the screen */
    select_draw_page(0);
    show_video_page(0);
    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0105);                    /* write mode 1: latch copies */
    for (int y = 0; y < 25; ++y)
        for (int x = 0; x < 40; x += 2)
            blit_bitmap_to_video_page((int16_t)(((x / 2 + y) % 64) * 0x20), (int16_t)(y * 640 + x));
    compare("tiles");

    /* tiles at odd byte offsets (the strip's 8-pixel shift) */
    for (int x = 1; x < 30; x += 2)
        blit_bitmap_to_video_page((int16_t)(((x * 7) % 64) * 0x20), (int16_t)(640 * 3 + x));
    compare("shifted tiles");

    /* masked sprites over them, some overlapping */
    outport(0x3ce, 0x0005);                    /* write mode 0 for the sprite routine */
    for (int i = 0; i < 12; ++i) {
        make_sprite(sprite, (unsigned)i + 3u);
        blit_planar_sprite_rows(sprite, (int16_t)(3 + i * 2), (int16_t)(20 + i * 9));
    }
    compare("sprites");

    /* glyphs: per-row masks, and the caller-set bit mask variant */
    for (int i = 0; i < 20; ++i) {
        for (int k = 0; k < 40; ++k) glyph[k] = (char)((i * 17 + k * 23) & 0xff);
        draw_ega_glyph(glyph, (int16_t)(4 + i), 150);
    }
    outport(0x3ce, 0x5a08);                    /* bit mask 0x5a for the masked glyph */
    for (int i = 0; i < 10; ++i) {
        for (int k = 0; k < 40; ++k) glyph[k] = (char)((i * 31 + k * 5) & 0xff);
        blit_planar_masked_glyph(glyph, (int16_t)(6 + i * 2), 170);
    }
    outport(0x3ce, 0xff08);
    compare("glyphs");

    /* the water copy (page to page, a few rows below its source) */
    outport(0x3ce, 0x0105);
    copy_planar_video_region(6, 60, 40);
    copy_planar_video_region(12, 64, 0);
    compare("water copy");

    /* a picture written around the toolbox, then overdrawn in part */
    outport(0x3c4, 0x0f02);
    outport(0x3ce, 0x0005);
    for (int plane = 0; plane < 4; ++plane) {
        outport(0x3c4, (uint16_t)(((1u << plane) << 8) | 2u));
        for (int i = 0; i < 8000; ++i) vga_cpu_write((uint16_t)i, (uint8_t)((i * 7 + plane * 51) & 0xff));
    }
    outport(0x3c4, 0x0f02);
    show_video_page(0);
    compare("picture");
    outport(0x3ce, 0x0105);
    for (int x = 0; x < 20; x += 2)
        blit_bitmap_to_video_page((int16_t)(x * 0x20), (int16_t)(640 * 5 + x));
    compare("picture partly overdrawn");

    /* the other page */
    select_draw_page(1);
    for (int y = 0; y < 25; ++y)
        for (int x = 0; x < 40; x += 2)
            blit_bitmap_to_video_page((int16_t)((((x / 2) * 3 + y) % 64) * 0x20), (int16_t)(y * 640 + x));
    show_video_page(1);
    compare("page 1");

    scene_shutdown();
    printf(failures ? "FAIL: %d\n" : "PASS: native scene equals the emulated page\n", failures);
    return failures ? 1 : 0;
}
