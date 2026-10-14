/* Port replacement for GAME1.C's A000:4000 planar image loader. */
void vga_cpu_write(unsigned int offset, unsigned char value);

void pascal load_planar_image_file(char far *filename, register int offset, int count)
{
    FILE *stream;
    register int i;

    stream = fopen(filename, "rb");
    if (filename[0] != 0) {
        count /= 4;
        fgetc(stream);
        fgetc(stream);
        fgetc(stream);
        for (i = 0; i < count; ++i) {
            fgetc(stream);
            /* TC 2.0 emits different code for subscripting this far pointer. */
            outport(0x3c4, 0x0102);
            vga_cpu_write(0x4000 + i + offset, fgetc(stream));
            outport(0x3c4, 0x0202);
            vga_cpu_write(0x4000 + i + offset, fgetc(stream));
            outport(0x3c4, 0x0402);
            vga_cpu_write(0x4000 + i + offset, fgetc(stream));
            outport(0x3c4, 0x0802);
            vga_cpu_write(0x4000 + i + offset, fgetc(stream));
        }
        fclose(stream);
    }
}
