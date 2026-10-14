/* Port replacement for GAME2.C's A000:0000 planar bitmap copy. */
void display_duke_bitmap(void)
{
    register int i;

    clear_video_page();
    outport(0x3ce, 5);
    select_draw_page(0);
    show_video_page(1);
    /* Copy each 8,000-byte chunk to its VGA plane. */
    outport(0x3c4, 0x0102);
    for (i = 0; i < 8000; ++i) {
        vga_cpu_write(i, duke_graphics_buffer[i]);
    }
    outport(0x3c4, 0x0202);
    for (i = 0; i < 8000; ++i) {
        vga_cpu_write(i, duke_graphics_buffer[i + 8000]);
    }
    outport(0x3c4, 0x0402);
    for (i = 0; i < 8000; ++i) {
        vga_cpu_write(i, duke_graphics_buffer[i + 16000]);
    }
    outport(0x3c4, 0x0802);
    for (i = 0; i < 8000; ++i) {
        vga_cpu_write(i, duke_graphics_buffer[i + 24000]);
    }
    show_video_page(0);
}
