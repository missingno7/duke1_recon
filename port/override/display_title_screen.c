/* Port replacement for GAME2.C's A000:0000 planar bitmap copy. */
void vga_cpu_write(unsigned int offset, unsigned char value);

void display_title_screen(void)
{
    register int byte_offset;

    clear_video_page();
    outport(0x3ce, 5);
    select_draw_page(0);
    show_video_page(1);
    /* Copy each 8,000-byte chunk to its VGA plane. */
    outport(0x3c4, 0x0102);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        vga_cpu_write(byte_offset, title_screen_buffer[byte_offset]);
    outport(0x3c4, 0x0202);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        vga_cpu_write(byte_offset, title_screen_buffer[byte_offset + 8000]);
    outport(0x3c4, 0x0402);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        vga_cpu_write(byte_offset, title_screen_buffer[byte_offset + 16000]);
    outport(0x3c4, 0x0802);
    for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
        vga_cpu_write(byte_offset, title_screen_buffer[byte_offset + 24000]);
    show_video_page(0);
}
