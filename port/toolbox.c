/* C versions of the nine TASM routines in src/TOOLBOX.ASM.  Each draws into the emulated EGA
   exactly like the original; in the enhanced renderer it also hands what it drew to the native
   scene (scene.h). */
#include "wide_pass.h"
#include "platform.h"
#include "scene.h"
#include "present.h"

#include <stddef.h>

uint8_t vga_graphics_register(uint8_t index);   /* vga.c: the bit mask a caller set */

static uint16_t draw_page_selector;

static uint16_t add16(uint16_t a, uint16_t b)
{
    return (uint16_t)(a + b);
}

static uint16_t mul40(uint16_t value)
{
    return (uint16_t)(value * 40u);
}

static void outb(uint16_t port, uint8_t value)
{
    (void)vga_port_write(port, value);
}

static void outw(uint16_t port, uint16_t value)
{
    outb(port, (uint8_t)value);
    outb((uint16_t)(port + 1u), (uint8_t)(value >> 8));
}

static uint8_t src_byte(const char *src, uint16_t offset)
{
    return (uint8_t)(unsigned char)src[offset];
}

static void xchg_vram(uint16_t offset, uint8_t value)
{
    (void)vga_cpu_read(offset); /* XCHG reads the VGA aperture and loads all four latches. */
    vga_cpu_write(offset, value);
}

/* Page-relative pixel position of a byte offset on the current draw page. */
static int page_x(uint16_t page_relative) { return (int)(page_relative % 40u) * 8; }
static int page_y(uint16_t page_relative) { return (int)(page_relative / 40u); }

int16_t set_video_mode(int16_t mode)
{
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    if ((uint8_t)mode == 0)
        bios_set_mode(0x0d);
    else if ((uint8_t)mode == 1)
        bios_set_mode(0x10);
    else
        bios_set_mode(0x12);
    scene_reset();
    return 0;
}

int16_t set_vga_mode_with_parameters(int16_t index, int16_t colour)
{
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    bios_set_palette_register((uint8_t)index, (uint8_t)colour);
    return 0;
}

int16_t blit_bitmap_to_video_page(int16_t source_offset, int16_t destination_offset)
{
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    uint16_t src = (uint16_t)source_offset;
    uint16_t dst = (uint16_t)destination_offset;
    uint16_t page_relative = dst;
    unsigned row;
    scene_before_draw();
    if ((draw_page_selector & 0xffu) != 0)
        dst = add16(dst, 0x2000);
    for (row = 0; row < 16; ++row) {
        unsigned byte_in_row;
        for (byte_in_row = 0; byte_in_row < 2; ++byte_in_row) {
            uint16_t source = add16(0x4000, src++);
            uint8_t value = vga_cpu_read(source);
            vga_cpu_write(dst++, value);
        }
        dst = add16(dst, 0x26);
    }
    scene_add_bitmap((uint16_t)source_offset, page_x(page_relative), page_y(page_relative));
    return 0;
}

int16_t copy_planar_video_region(int16_t x, int16_t y, int16_t source_offset)
{
    uint16_t dst = add16(add16(mul40((uint16_t)y), (uint16_t)x), 0x50);
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    uint16_t src = (uint16_t)(dst - 0x78u - (uint16_t)source_offset);
    uint16_t page_relative = dst;
    unsigned row;
    scene_before_draw();
    if ((draw_page_selector & 0xffu) != 0)
        dst = add16(dst, 0x2000);
    if ((draw_page_selector & 0xffu) != 0)
        src = add16(src, 0x2000);
    for (row = 0; row < 30; ++row) {
        unsigned byte_in_row;
        for (byte_in_row = 0; byte_in_row < 2; ++byte_in_row) {
            uint8_t value = vga_cpu_read(src++);
            vga_cpu_write(dst++, value);
        }
        dst = add16(dst, 0x26);
        src = (uint16_t)(src - 0x52u);
    }
    scene_add_water(page_x(page_relative), page_y(page_relative), 16, 30);
    return 0;
}

int16_t blit_planar_sprite_rows(char *src, int16_t x, int16_t y)
{
    return blit_planar_sprite_rows_at(SCENE_SCREEN_SITE, src, x, y);   /* not a game call site */
}

int16_t blit_planar_sprite_rows_at(uint32_t site, char *src, int16_t x, int16_t y)
{
    uint16_t dst = add16((uint16_t)x, mul40((uint16_t)y));
    uint16_t source = 0;
    /* Widescreen: a level sprite beyond the original playfield stays off the page. */
    int off_page = scene_sprite_off_page(site, (int)x * 8, (int)y);
    unsigned row;
    if (port_in_wide_pass) {                     /* a margin actor: recorded, never drawn */
        if (!(site & SCENE_SCREEN_SITE)) scene_add_sprite(site, src, (int)x * 8, (int)y, 0);
        return 0;
    }
    scene_before_draw();
    if ((draw_page_selector & 0xffu) != 0)
        dst = add16(dst, 0x2000);
    outb(0x3c4, 2);
    for (row = 0; row < 16; ++row) {
        unsigned half;
        for (half = 0; half < 2; ++half) {
            uint8_t mask = src_byte(src, source++);
            unsigned plane;
            outw(0x3ce, (uint16_t)((uint16_t)mask << 8 | 8u));
            for (plane = 0; plane < 4; ++plane) {
                outb(0x3c5, (uint8_t)(1u << plane));
                if (!off_page) {
                    (void)vga_cpu_read(dst); /* preserve the XCHG latch side effect */
                    vga_cpu_write(dst, src_byte(src, source));
                }
                ++source;
            }
            ++dst;
        }
        dst = add16(dst, 0x26);
    }
    outb(0x3c5, 0x0f);
    outw(0x3ce, 0xff08);
    scene_add_sprite(site, src, (int)x * 8, (int)y, !off_page);
    return 0;
}

int16_t draw_ega_glyph(char *src, int16_t x, int16_t y)
{
    uint16_t dst = add16((uint16_t)x, mul40((uint16_t)y));
    uint16_t source = 0;
    uint8_t row_masks[8];
    unsigned row;
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    scene_before_draw();
    if ((draw_page_selector & 0xffu) != 0)
        dst = add16(dst, 0x2000);
    outb(0x3c4, 2);
    for (row = 0; row < 8; ++row) {
        unsigned plane;
        uint8_t mask = src_byte(src, source++);
        row_masks[row] = mask;
        outw(0x3ce, (uint16_t)((uint16_t)mask << 8 | 8u));
        for (plane = 0; plane < 4; ++plane) {
            outb(0x3c5, (uint8_t)(1u << plane));
            xchg_vram(dst, src_byte(src, source++));
        }
        dst = add16(dst, 0x28);
    }
    outb(0x3c5, 0x0f);
    outw(0x3ce, 0xff08);
    scene_add_glyph((int)x * 8, (int)y, row_masks);
    return 0;
}

int16_t blit_planar_masked_glyph(char *src, int16_t x, int16_t y)
{
    uint16_t dst = add16((uint16_t)x, mul40((uint16_t)y));
    uint16_t source = 0;
    uint8_t row_masks[8];
    uint8_t caller_mask = vga_graphics_register(8);   /* the caller set the bit mask */
    unsigned row;
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    scene_before_draw();
    if ((draw_page_selector & 0xffu) != 0)
        dst = add16(dst, 0x2000);
    outb(0x3c4, 2);
    for (row = 0; row < 8; ++row) {
        unsigned plane;
        ++source; /* The assembly consumes this mask byte; GC bit mask remains caller-set. */
        row_masks[row] = caller_mask;
        for (plane = 0; plane < 4; ++plane) {
            outb(0x3c5, (uint8_t)(1u << plane));
            xchg_vram(dst, src_byte(src, source++));
        }
        dst = add16(dst, 0x28);
    }
    outb(0x3c5, 0x0f);
    outw(0x3ce, 0xff08);
    scene_add_glyph((int)x * 8, (int)y, row_masks);
    return 0;
}

int16_t select_draw_page(int16_t page)
{
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    draw_page_selector = (uint16_t)page;
    scene_select_page((page & 0xff) != 0);
    return 0;
}

int16_t show_video_page(int16_t page)
{
    if (port_in_wide_pass) return 0;               /* the pass keeps level sprites only */
    bios_set_active_page((uint8_t)page);
    scene_show_page((page & 0xff) != 0);
    present_verify_shown();                      /* --verify-native only */
    return 0;
}
