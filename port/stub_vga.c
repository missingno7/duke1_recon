/* Temporary black video backend for port step 1. */
#include "platform.h"
#include <string.h>

#ifdef PORT_NEED_VGA_STUB
#undef vga_port_read
static uint8_t planes[4][65536];
static uint8_t palette[16] = {
    0x00, 0x03, 0x0c, 0x0f, 0x30, 0x33, 0x3c, 0x2a,
    0x15, 0x17, 0x1d, 0x1f, 0x35, 0x37, 0x3d, 0x3f
};

uint8_t *vga_plane(int plane) { return (plane >= 0 && plane < 4) ? planes[plane] : NULL; }
int vga_port_read(uint16_t port, uint8_t *value) { (void)port; if (value) *value = 0; return 1; }
int vga_port_write(uint16_t port, uint8_t value) { (void)port; (void)value; return 1; }
void vga_set_palette_entry(uint8_t index, uint8_t colour) { if (index < 16) palette[index] = colour & 0x3f; }
void vga_cpu_write(uint16_t offset, uint8_t value) { (void)offset; (void)value; }
uint8_t vga_cpu_read(uint16_t offset) { (void)offset; return 0; }
void vga_set_display_start(uint16_t offset) { (void)offset; }
uint16_t vga_display_start(void) { return 0; }
void vga_render_indexed(uint8_t *out_320x200) { if (out_320x200) memset(out_320x200, 0, 320u * 200u); }
const uint8_t *vga_palette_registers(void) { return palette; }
void vga_vertical_retrace_wait(void) {}
void bios_set_mode(uint8_t mode) { (void)mode; memset(planes, 0, sizeof(planes)); }
void bios_set_palette_register(uint8_t index, uint8_t colour) { vga_set_palette_entry(index, colour); }
void bios_set_active_page(uint8_t page) { (void)page; }
#endif

#ifdef PORT_NEED_TOOLBOX_STUB
void set_video_mode(int mode) { bios_set_mode((uint8_t)mode); }
void set_vga_mode_with_parameters(int mode, int parameter) { (void)parameter; bios_set_mode((uint8_t)mode); }
void blit_bitmap_to_video_page(int source_offset, int destination_offset) { (void)source_offset; (void)destination_offset; }
void copy_planar_video_region(int source_offset, int destination_offset, int byte_count) { (void)source_offset; (void)destination_offset; (void)byte_count; }
void blit_planar_sprite_rows(char *bitmap, int x, int y) { (void)bitmap; (void)x; (void)y; }
void draw_ega_glyph(char *bitmap, int x, int y) { (void)bitmap; (void)x; (void)y; }
void blit_planar_masked_glyph(char *bitmap, int x, int y) { (void)bitmap; (void)x; (void)y; }
void select_draw_page(int page) { (void)page; }
void show_video_page(int page) { bios_set_active_page((uint8_t)page); }
#endif
