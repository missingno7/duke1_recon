/* EGA/VGA register and planar-memory model used by the SDL port. */
#include "platform.h"

#include <stdatomic.h>
#include <string.h>

/* The header keeps a one-argument source adapter for the in-progress pc_io.c. */
#undef vga_port_read

enum { VGA_PLANE_BYTES = 65536, VGA_WIDTH = 320, VGA_HEIGHT = 200 };

static uint8_t planes[4][VGA_PLANE_BYTES];
static uint8_t seq_index;
static uint8_t seq_regs[8];
static uint8_t gc_index;
static uint8_t gc_regs[16];
static uint8_t crtc_index;
static uint8_t crtc_regs[32];
static uint8_t attr_index;
static uint8_t attr_regs[32];
static uint8_t attr_data_phase;
static uint8_t retrace_state;
static uint8_t video_mode = 0x03;
static uint16_t display_start;
static uint8_t latches[4];
static atomic_flag vga_lock = ATOMIC_FLAG_INIT;
static _Thread_local uint8_t palette_snapshot[16];

/* The palette registers the BIOS loads for the 200-line modes (0Dh): the CGA colours,
   intensity in bit 4.  (0x14 / 0x38..0x3F are the 350-line defaults.) */
static const uint8_t ega_default_palette[16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
};

/* The 16 CGA colours (0xRRGGBB): what a 200-line EGA mode shows; colour 6 is brown. */
static const uint32_t cga_rgb[16] = {
    0x000000, 0x0000aa, 0x00aa00, 0x00aaaa, 0xaa0000, 0xaa00aa, 0xaa5500, 0xaaaaaa,
    0x555555, 0x5555ff, 0x55ff55, 0x55ffff, 0xff5555, 0xff55ff, 0xffff55, 0xffffff
};

static void lock_vga(void)
{
    while (atomic_flag_test_and_set_explicit(&vga_lock, memory_order_acquire)) {
    }
}

static void unlock_vga(void)
{
    atomic_flag_clear_explicit(&vga_lock, memory_order_release);
}

static uint16_t current_display_start(void)
{
    return (uint16_t)(((uint16_t)crtc_regs[0x0c] << 8) | crtc_regs[0x0d]);
}

static void reset_registers_locked(void)
{
    memset(seq_regs, 0, sizeof(seq_regs));
    memset(gc_regs, 0, sizeof(gc_regs));
    memset(crtc_regs, 0, sizeof(crtc_regs));
    memset(attr_regs, 0, sizeof(attr_regs));
    memset(latches, 0, sizeof(latches));
    seq_index = 0;
    seq_regs[2] = 0x0f;
    gc_index = 0;
    gc_regs[7] = 0x0f;
    gc_regs[8] = 0xff;
    crtc_index = 0;
    attr_index = 0;
    attr_data_phase = 0;
    retrace_state = 0;
    display_start = 0;
    memcpy(attr_regs, ega_default_palette, sizeof(ega_default_palette));
    attr_regs[0x10] = 0x01;
    attr_regs[0x11] = 0x00;
    attr_regs[0x12] = 0x0f;
    attr_regs[0x13] = 0x00;
    attr_regs[0x14] = 0x00;
}

uint8_t *vga_plane(int plane)
{
    if (plane < 0 || plane > 3)
        return NULL;
    return planes[plane];
}

/* Writes per memory region (page 0, page 1, the tile cache above), for the native scene:
   it notices drawing that bypassed the toolbox (the full-screen pictures). */
static uint32_t region_writes[3];

uint32_t vga_region_write_count(int region)
{
    return region >= 0 && region < 3 ? region_writes[region] : 0;
}

uint8_t vga_graphics_register(uint8_t index)
{
    return gc_regs[index & 15u];
}

void vga_cpu_write(uint16_t offset, uint8_t value)
{
    unsigned plane;
    ++region_writes[offset < 0x2000u ? 0 : offset < 0x4000u ? 1 : 2];
    unsigned mode;
    uint8_t rotated;
    uint8_t bit_mask;
    uint8_t function;
    lock_vga();
    mode = gc_regs[5] & 3u;
    bit_mask = gc_regs[8];
    function = (gc_regs[3] >> 3) & 3u;
    rotated = value;
    {
        unsigned rotate = gc_regs[3] & 7u;
        if (rotate != 0)
            rotated = (uint8_t)((value >> rotate) | (value << (8u - rotate)));
    }

    for (plane = 0; plane < 4; ++plane) {
        uint8_t source;
        uint8_t result;
        if ((seq_regs[2] & (1u << plane)) == 0)
            continue;
        if (mode == 1u) {
            planes[plane][offset] = latches[plane];
            continue;
        }
        if (mode == 2u) {
            source = (value & (1u << plane)) ? 0xff : 0x00;
        } else if ((gc_regs[1] & (1u << plane)) != 0) {
            source = (gc_regs[0] & (1u << plane)) ? 0xff : 0x00;
        } else {
            source = rotated;
        }
        switch (function) {
        case 1: source = (uint8_t)(source & latches[plane]); break;
        case 2: source = (uint8_t)(source | latches[plane]); break;
        case 3: source = (uint8_t)(source ^ latches[plane]); break;
        default: break;
        }
        result = (uint8_t)((source & bit_mask) |
                           (latches[plane] & (uint8_t)~bit_mask));
        planes[plane][offset] = result;
    }
    unlock_vga();
}

uint8_t vga_cpu_read(uint16_t offset)
{
    unsigned plane;
    uint8_t result;
    lock_vga();
    for (plane = 0; plane < 4; ++plane)
        latches[plane] = planes[plane][offset];

    if ((gc_regs[5] & 0x08u) == 0) {
        result = latches[gc_regs[4] & 3u];
    } else {
        uint8_t care = gc_regs[7] & 0x0fu;
        uint8_t compare = gc_regs[2] & 0x0fu;
        unsigned bit;
        result = 0xff;
        for (bit = 0; bit < 8; ++bit) {
            unsigned p;
            unsigned matches = 1;
            for (p = 0; p < 4; ++p) {
                if ((care & (1u << p)) != 0) {
                    unsigned plane_bit = (latches[p] >> bit) & 1u;
                    if (plane_bit != ((compare >> p) & 1u)) {
                        matches = 0;
                        break;
                    }
                }
            }
            if (!matches)
                result &= (uint8_t)~(1u << bit);
        }
    }
    unlock_vga();
    return result;
}

int vga_port_write(uint16_t port, uint8_t value)
{
    int handled = 1;
    lock_vga();
    switch (port) {
    case 0x03c0:
        if (!attr_data_phase) {
            attr_index = value & 0x1fu;
            attr_data_phase = 1;
        } else {
            attr_regs[attr_index] = value & ((attr_index < 16) ? 0x3f : 0xff);
            attr_data_phase = 0;
        }
        break;
    case 0x03c2:
    case 0x03c3:
        break;
    case 0x03c4:
        seq_index = value & 7u;
        break;
    case 0x03c5:
        seq_regs[seq_index] = value;
        break;
    case 0x03ce:
        gc_index = value & 0x0fu;
        break;
    case 0x03cf:
        gc_regs[gc_index] = value;
        break;
    case 0x03d4:
        crtc_index = value & 0x1fu;
        break;
    case 0x03d5:
        crtc_regs[crtc_index] = value;
        if (crtc_index == 0x0c || crtc_index == 0x0d)
            display_start = current_display_start();
        break;
    default:
        handled = 0;
        break;
    }
    unlock_vga();
    return handled;
}

int vga_port_read(uint16_t port, uint8_t *value)
{
    int handled = 1;
    uint8_t result = 0xff;
    if (value == NULL)
        return 0;
    lock_vga();
    switch (port) {
    case 0x03c0:
        result = attr_index;
        break;
    case 0x03c1:
        result = attr_regs[attr_index];
        break;
    case 0x03c2:
        result = 0;
        break;
    case 0x03c3:
        result = 1;
        break;
    case 0x03c4:
        result = seq_index;
        break;
    case 0x03c5:
        result = seq_regs[seq_index];
        break;
    case 0x03ce:
        result = gc_index;
        break;
    case 0x03cf:
        result = gc_regs[gc_index];
        break;
    case 0x03d4:
        result = crtc_index;
        break;
    case 0x03d5:
        result = crtc_regs[crtc_index];
        break;
    case 0x03da:
        retrace_state ^= 0x08;
        result = retrace_state;
        attr_data_phase = 0;
        break;
    default:
        handled = 0;
        break;
    }
    unlock_vga();
    if (handled)
        *value = result;
    return handled;
}

void vga_set_display_start(uint16_t offset)
{
    lock_vga();
    display_start = offset;
    crtc_regs[0x0c] = (uint8_t)(offset >> 8);
    crtc_regs[0x0d] = (uint8_t)offset;
    unlock_vga();
}

uint16_t vga_display_start(void)
{
    uint16_t result;
    lock_vga();
    result = display_start;
    unlock_vga();
    return result;
}

void vga_render_indexed_page(uint8_t *out_320x200, uint16_t page_start)
{
    unsigned y;
    if (out_320x200 == NULL)
        return;
    lock_vga();
    for (y = 0; y < VGA_HEIGHT; ++y) {
        unsigned x;
        for (x = 0; x < VGA_WIDTH; ++x) {
            uint16_t offset = (uint16_t)(page_start + y * 40u + x / 8u);
            uint8_t mask = (uint8_t)(0x80u >> (x & 7u));
            uint8_t color = 0;
            unsigned plane;
            for (plane = 0; plane < 4; ++plane)
                if ((planes[plane][offset] & mask) != 0)
                    color |= (uint8_t)(1u << plane);
            out_320x200[y * VGA_WIDTH + x] = color;
        }
    }
    unlock_vga();
}

void vga_render_indexed(uint8_t *out_320x200)
{
    vga_render_indexed_page(out_320x200, vga_display_start());
}

const uint8_t *vga_palette_registers(void)
{
    lock_vga();
    memcpy(palette_snapshot, attr_regs, sizeof(palette_snapshot));
    unlock_vga();
    return palette_snapshot;
}

/* The colour a palette register value shows.  In the 200-line modes the EGA reads it like a
   CGA colour - bits 0-2 blue/green/red, bit 4 intensity, bits 3 and 5 ignored (a VGA BIOS
   loads its DAC to match) - in the 350-line modes as six bits rgbRGB. */
uint32_t vga_colour_rgb(uint8_t value)
{
    if (video_mode == 0x0d || video_mode == 0x0e || video_mode <= 0x07)
        return cga_rgb[(value & 0x07u) | ((value & 0x10u) ? 0x08u : 0u)];
    {
        uint32_t r = ((value >> 2) & 1u) * 0xaau + ((value >> 5) & 1u) * 0x55u;
        uint32_t g = ((value >> 1) & 1u) * 0xaau + ((value >> 4) & 1u) * 0x55u;
        uint32_t b = (value & 1u) * 0xaau + ((value >> 3) & 1u) * 0x55u;
        return (r << 16) | (g << 8) | b;
    }
}

void vga_render_rgb_page(uint16_t page_start, uint32_t *out_320x200)
{
    static uint8_t indexed[320 * 200];
    uint32_t colours[16];
    const uint8_t *regs;
    int i;

    vga_render_indexed_page(indexed, page_start);
    regs = vga_palette_registers();
    for (i = 0; i < 16; ++i)
        colours[i] = 0xff000000u | vga_colour_rgb(regs[i]);
    for (i = 0; i < 320 * 200; ++i)
        out_320x200[i] = colours[indexed[i] & 0x0f];
}

void vga_render_rgb(uint32_t *out_320x200)
{
    vga_render_rgb_page(vga_display_start(), out_320x200);
}

void vga_vertical_retrace_wait(void)
{
    uint8_t status;
    do {
        if (!vga_port_read(0x03da, &status))
            return;
    } while ((status & 0x08u) == 0);
}

void vga_replace_colour_in_text_span(uint8_t from, uint8_t to, int x, int y,
                                     int columns, int rows)
{
    uint16_t page_start;
    int first_scanline, last_scanline, first_byte, last_byte;
    if (from > 15 || to > 15 || columns <= 0 || rows <= 0 ||
        x < 0 || y < 0 || x + columns > 40 || y + rows > 25)
        return;
    lock_vga();
    page_start = current_display_start();
    first_scanline = y * 8;
    last_scanline = (y + rows) * 8;
    first_byte = x;
    last_byte = x + columns;
    for (int scanline = first_scanline; scanline < last_scanline; ++scanline) {
        for (int column = first_byte; column < last_byte; ++column) {
            uint16_t offset = (uint16_t)(page_start + scanline * 40 + column);
            uint8_t matches = 0xff;
            for (unsigned plane = 0; plane < 4; ++plane) {
                uint8_t bits = planes[plane][offset];
                matches &= (from & (1u << plane)) ? bits : (uint8_t)~bits;
            }
            if (!matches) continue;
            for (unsigned plane = 0; plane < 4; ++plane) {
                if (to & (1u << plane)) planes[plane][offset] |= matches;
                else planes[plane][offset] &= (uint8_t)~matches;
            }
        }
    }
    unlock_vga();
}

void pc_enable(void);

/* The IBM BIOS video service starts with STI: every INT 10h call re-enables interrupts
   (the game relies on it after its own disable()). */
void bios_set_mode(uint8_t mode)
{
    pc_enable();
    lock_vga();
    video_mode = mode;
    if (mode == 0x0d) {
        memset(planes, 0, sizeof(planes));
        reset_registers_locked();
    }
    unlock_vga();
}

void bios_set_palette_register(uint8_t index, uint8_t colour)
{
    pc_enable();
    if (index >= 16)
        return;
    lock_vga();
    attr_regs[index] = colour & 0x3f;
    unlock_vga();
}

void vga_set_palette_entry(uint8_t index, uint8_t colour)
{
    bios_set_palette_register(index, colour);
}

void bios_set_active_page(uint8_t page)
{
    pc_enable();
    vga_set_display_start((uint16_t)((uint16_t)page * 0x2000u));
}
