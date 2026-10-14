/* C versions of the nine TASM routines in game/TOOLBOX.ASM. */
#include "platform.h"

#include <stddef.h>

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

int16_t set_video_mode(int16_t mode)
{
    if ((uint8_t)mode == 0)
        bios_set_mode(0x0d);
    else if ((uint8_t)mode == 1)
        bios_set_mode(0x10);
    else
        bios_set_mode(0x12);
    return 0;
}

int16_t set_vga_mode_with_parameters(int16_t index, int16_t colour)
{
    bios_set_palette_register((uint8_t)index, (uint8_t)colour);
    return 0;
}

int16_t blit_bitmap_to_video_page(int16_t source_offset, int16_t destination_offset)
{
    uint16_t src = (uint16_t)source_offset;
    uint16_t dst = (uint16_t)destination_offset;
    unsigned row;
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
    return 0;
}

int16_t copy_planar_video_region(int16_t x, int16_t y, int16_t source_offset)
{
    uint16_t dst = add16(add16(mul40((uint16_t)y), (uint16_t)x), 0x50);
    uint16_t src = (uint16_t)(dst - 0x78u - (uint16_t)source_offset);
    unsigned row;
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
    return 0;
}

int16_t blit_planar_sprite_rows(char *src, int16_t x, int16_t y)
{
    uint16_t dst = add16((uint16_t)x, mul40((uint16_t)y));
    uint16_t source = 0;
    unsigned row;
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
                xchg_vram(dst, src_byte(src, source++));
            }
            ++dst;
        }
        dst = add16(dst, 0x26);
    }
    outb(0x3c5, 0x0f);
    outw(0x3ce, 0xff08);
    return 0;
}

int16_t draw_ega_glyph(char *src, int16_t x, int16_t y)
{
    uint16_t dst = add16((uint16_t)x, mul40((uint16_t)y));
    uint16_t source = 0;
    unsigned row;
    if ((draw_page_selector & 0xffu) != 0)
        dst = add16(dst, 0x2000);
    outb(0x3c4, 2);
    for (row = 0; row < 8; ++row) {
        unsigned plane;
        for (plane = 0; plane < 4; ++plane) {
            outb(0x3c5, (uint8_t)(1u << plane));
            xchg_vram(dst, src_byte(src, source++));
        }
        dst = add16(dst, 0x28);
    }
    outb(0x3c5, 0x0f);
    outw(0x3ce, 0xff08);
    return 0;
}

int16_t blit_planar_masked_glyph(char *src, int16_t x, int16_t y)
{
    uint16_t dst = add16((uint16_t)x, mul40((uint16_t)y));
    uint16_t source = 0;
    unsigned row;
    if ((draw_page_selector & 0xffu) != 0)
        dst = add16(dst, 0x2000);
    outb(0x3c4, 2);
    for (row = 0; row < 8; ++row) {
        unsigned plane;
        ++source; /* The assembly consumes this mask byte; GC bit mask remains caller-set. */
        for (plane = 0; plane < 4; ++plane) {
            outb(0x3c5, (uint8_t)(1u << plane));
            xchg_vram(dst, src_byte(src, source++));
        }
        dst = add16(dst, 0x28);
    }
    outb(0x3c5, 0x0f);
    outw(0x3ce, 0xff08);
    return 0;
}

int16_t select_draw_page(int16_t page)
{
    draw_page_selector = (uint16_t)page;
    return 0;
}

int16_t show_video_page(int16_t page)
{
    bios_set_active_page((uint8_t)page);
    return 0;
}
