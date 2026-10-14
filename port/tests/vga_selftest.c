#include "../platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define make_dir(path) _mkdir(path)
#else
#include <sys/stat.h>
#define make_dir(path) mkdir(path, 0777)
#endif

int16_t blit_bitmap_to_video_page(int16_t source_offset, int16_t destination_offset);
int16_t blit_planar_sprite_rows(char *src, int16_t x, int16_t y);
int16_t draw_ega_glyph(char *src, int16_t x, int16_t y);
int16_t select_draw_page(int16_t page);
int16_t show_video_page(int16_t page);

#define REQUIRE(expr) do { \
    if (!(expr)) { \
        fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); \
        return 0; \
    } \
} while (0)

static void set_gc(uint8_t index, uint8_t value)
{
    (void)vga_port_write(0x03ce, index);
    (void)vga_port_write(0x03cf, value);
}

static void set_seq(uint8_t index, uint8_t value)
{
    (void)vga_port_write(0x03c4, index);
    (void)vga_port_write(0x03c5, value);
}

static void write_plane(unsigned plane, uint16_t offset, uint8_t value)
{
    set_seq(2, (uint8_t)(1u << plane));
    vga_cpu_write(offset, value);
}

static int test_write_modes_and_latches(void)
{
    static const uint8_t ega_palette[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
    };
    uint16_t address = 0x0100;
    unsigned plane;
    uint8_t value;
    uint8_t status;

    bios_set_mode(0x0d);
    REQUIRE(memcmp(vga_palette_registers(), ega_palette, sizeof(ega_palette)) == 0);
    REQUIRE(vga_display_start() == 0);
    REQUIRE(vga_port_read(0x03da, &status) == 1 && (status & 8) != 0);
    REQUIRE(vga_port_read(0x03da, &status) == 1 && (status & 8) == 0);
    REQUIRE(vga_port_read(0x03e0, &status) == 0);
    bios_set_active_page(2);
    REQUIRE(vga_display_start() == 0x4000);
    bios_set_mode(0x0d);
    set_seq(2, 0x05);
    vga_cpu_write(address, 0xa5);
    REQUIRE(vga_plane(0)[address] == 0xa5);
    REQUIRE(vga_plane(1)[address] == 0x00);
    REQUIRE(vga_plane(2)[address] == 0xa5);
    REQUIRE(vga_plane(3)[address] == 0x00);

    /* Write mode 2 expands the CPU low nibble into one byte per plane. */
    bios_set_mode(0x0d);
    set_gc(5, 2);
    set_seq(2, 0x0f);
    vga_cpu_write(0x0110, 0x05);
    for (plane = 0; plane < 4; ++plane)
        REQUIRE(vga_plane((int)plane)[0x0110] == ((plane == 0 || plane == 2) ? 0xff : 0x00));

    /* Set/reset applies independently to enabled planes in write mode 0. */
    bios_set_mode(0x0d);
    set_gc(0, 0x05);
    set_gc(1, 0x05);
    set_seq(2, 0x0f);
    vga_cpu_write(0x0120, 0x00);
    REQUIRE(vga_plane(0)[0x0120] == 0xff);
    REQUIRE(vga_plane(1)[0x0120] == 0x00);
    REQUIRE(vga_plane(2)[0x0120] == 0xff);
    REQUIRE(vga_plane(3)[0x0120] == 0x00);

    /* A partial bit mask keeps the old low nibble and replaces the high nibble. */
    bios_set_mode(0x0d);
    for (plane = 0; plane < 4; ++plane)
        write_plane(plane, 0x0130, 0x55);
    set_seq(2, 0x0f);
    set_gc(8, 0xf0);
    (void)vga_cpu_read(0x0130);
    vga_cpu_write(0x0130, 0xaa);
    for (plane = 0; plane < 4; ++plane)
        REQUIRE(vga_plane((int)plane)[0x0130] == 0xa5);

    /* Data rotate and XOR use the current latch value as their other operand. */
    bios_set_mode(0x0d);
    write_plane(0, 0x0138, 0x0f);
    set_seq(2, 0x0f);
    (void)vga_cpu_read(0x0138);
    set_seq(2, 0x01);
    set_gc(3, 0x10);
    vga_cpu_write(0x0138, 0xf0);
    REQUIRE(vga_plane(0)[0x0138] == 0xff);
    set_gc(3, 0x01);
    vga_cpu_write(0x0139, 0x03);
    REQUIRE(vga_plane(0)[0x0139] == 0x81);

    /* Write mode 1 copies the four bytes loaded by one CPU read. */
    bios_set_mode(0x0d);
    write_plane(0, 0x0140, 0x12);
    write_plane(1, 0x0140, 0x34);
    write_plane(2, 0x0140, 0x56);
    write_plane(3, 0x0140, 0x78);
    set_seq(2, 0x0f);
    set_gc(5, 1);
    value = vga_cpu_read(0x0140);
    vga_cpu_write(0x0150, value);
    REQUIRE(vga_plane(0)[0x0150] == 0x12);
    REQUIRE(vga_plane(1)[0x0150] == 0x34);
    REQUIRE(vga_plane(2)[0x0150] == 0x56);
    REQUIRE(vga_plane(3)[0x0150] == 0x78);

    /* Read map select chooses the requested plane and still loads all latches. */
    set_gc(5, 0);
    set_gc(4, 2);
    REQUIRE(vga_cpu_read(0x0140) == 0x56);

    /* Read mode 1 compares the requested color bits and ignores don't-care planes. */
    write_plane(0, 0x0160, 0xf0);
    write_plane(1, 0x0160, 0xcc);
    write_plane(2, 0x0160, 0xaa);
    write_plane(3, 0x0160, 0x00);
    set_gc(2, 0x05);
    set_gc(7, 0x05);
    set_gc(5, 0x08);
    REQUIRE(vga_cpu_read(0x0160) == 0xa0);
    return 1;
}

static uint32_t crc32_bytes(const uint8_t *bytes, size_t length)
{
    uint32_t crc = 0xffffffffu;
    size_t i;
    for (i = 0; i < length; ++i) {
        unsigned bit;
        crc ^= bytes[i];
        for (bit = 0; bit < 8; ++bit)
            crc = (crc >> 1) ^ (0xedb88320u & (uint32_t)-(int32_t)(crc & 1u));
    }
    return ~crc;
}

static void put_be32(uint8_t *p, uint32_t value)
{
    p[0] = (uint8_t)(value >> 24);
    p[1] = (uint8_t)(value >> 16);
    p[2] = (uint8_t)(value >> 8);
    p[3] = (uint8_t)value;
}

static int write_chunk(FILE *file, const char type[4], const uint8_t *data, uint32_t length)
{
    uint8_t size_bytes[4];
    uint8_t *crc_input;
    uint32_t crc;
    put_be32(size_bytes, length);
    crc_input = (uint8_t *)malloc((size_t)length + 4u);
    if (crc_input == NULL)
        return 0;
    memcpy(crc_input, type, 4);
    if (length != 0)
        memcpy(crc_input + 4, data, length);
    crc = crc32_bytes(crc_input, (size_t)length + 4u);
    free(crc_input);
    {
        uint8_t crc_bytes[4];
        put_be32(crc_bytes, crc);
        return fwrite(size_bytes, 1, 4, file) == 4 &&
               fwrite(type, 1, 4, file) == 4 &&
               (length == 0 || fwrite(data, 1, length, file) == length) &&
               fwrite(crc_bytes, 1, 4, file) == 4;
    }
}

static uint32_t adler32_bytes(const uint8_t *bytes, size_t length)
{
    uint32_t a = 1;
    uint32_t b = 0;
    size_t i;
    for (i = 0; i < length; ++i) {
        a = (a + bytes[i]) % 65521u;
        b = (b + a) % 65521u;
    }
    return (b << 16) | a;
}

static void palette_rgb(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b)
{
    uint32_t rgb = vga_colour_rgb(vga_palette_registers()[index]);
    *r = (uint8_t)(rgb >> 16);
    *g = (uint8_t)(rgb >> 8);
    *b = (uint8_t)rgb;
}

static int write_indexed_png(const char *path, const uint8_t *indices)
{
    const size_t raw_length = 200u * 321u;
    uint8_t *raw = (uint8_t *)malloc(raw_length);
    size_t block_count = (raw_length + 65534u) / 65535u;
    size_t z_length = 2u + raw_length + block_count * 5u + 4u;
    uint8_t *zdata = (uint8_t *)malloc(z_length);
    uint8_t ihdr[13] = { 0 };
    uint8_t palette[16 * 3];
    size_t y;
    size_t raw_pos = 0;
    size_t zpos = 0;
    size_t consumed = 0;
    FILE *file;
    if (raw == NULL || zdata == NULL) {
        free(raw);
        free(zdata);
        return 0;
    }
    for (y = 0; y < 200; ++y) {
        raw[raw_pos++] = 0;
        memcpy(raw + raw_pos, indices + y * 320u, 320u);
        raw_pos += 320u;
    }
    zdata[zpos++] = 0x78;
    zdata[zpos++] = 0x01;
    while (consumed < raw_length) {
        uint16_t chunk = (uint16_t)((raw_length - consumed > 65535u) ?
                                    65535u : raw_length - consumed);
        uint16_t inverse = (uint16_t)~chunk;
        zdata[zpos++] = (consumed + chunk == raw_length) ? 1 : 0;
        zdata[zpos++] = (uint8_t)chunk;
        zdata[zpos++] = (uint8_t)(chunk >> 8);
        zdata[zpos++] = (uint8_t)inverse;
        zdata[zpos++] = (uint8_t)(inverse >> 8);
        memcpy(zdata + zpos, raw + consumed, chunk);
        zpos += chunk;
        consumed += chunk;
    }
    put_be32(zdata + zpos, adler32_bytes(raw, raw_length));
    zpos += 4;
    put_be32(ihdr, 320);
    put_be32(ihdr + 4, 200);
    ihdr[8] = 8;  /* bit depth */
    ihdr[9] = 3;  /* indexed color */
    for (y = 0; y < 16; ++y)
        palette_rgb((uint8_t)y, &palette[y * 3], &palette[y * 3 + 1], &palette[y * 3 + 2]);

    file = fopen(path, "wb");
    if (file == NULL) {
        free(raw);
        free(zdata);
        return 0;
    }
    {
        static const uint8_t signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
        int ok = fwrite(signature, 1, sizeof(signature), file) == sizeof(signature) &&
                 write_chunk(file, "IHDR", ihdr, sizeof(ihdr)) &&
                 write_chunk(file, "PLTE", palette, sizeof(palette)) &&
                 write_chunk(file, "IDAT", zdata, (uint32_t)zpos) &&
                 write_chunk(file, "IEND", NULL, 0);
        if (fclose(file) != 0)
            ok = 0;
        free(raw);
        free(zdata);
        return ok;
    }
}

static int read_exact_file(const char *path, uint8_t *buffer, size_t count, size_t skip)
{
    FILE *file = fopen(path, "rb");
    size_t actual;
    if (file == NULL)
        return 0;
    if (fseek(file, (long)skip, SEEK_SET) != 0) {
        fclose(file);
        return 0;
    }
    actual = fread(buffer, 1, count, file);
    fclose(file);
    return actual == count;
}

static int load_planar_resource(const char *path, uint16_t destination, unsigned loops)
{
    FILE *file = fopen(path, "rb");
    unsigned i;
    int value;
    if (file == NULL)
        return 0;
    (void)fgetc(file);
    (void)fgetc(file);
    (void)fgetc(file);
    for (i = 0; i < loops; ++i) {
        unsigned plane;
        (void)fgetc(file); /* The game's loader skips one resource/control byte per group. */
        for (plane = 0; plane < 4; ++plane) {
            value = fgetc(file);
            set_seq(2, (uint8_t)(1u << plane));
            vga_cpu_write((uint16_t)(0x4000u + destination + i), (uint8_t)value);
        }
    }
    fclose(file);
    return 1;
}

static void draw_test_border_box(int16_t left, int16_t top, int16_t height)
{
    int16_t vertical;
    int16_t horizontal;
    int16_t height_bytes = (int16_t)(height * 16 * 40);
    (void)select_draw_page(0);
    set_seq(2, 0x0f);
    set_gc(5, 1);
    for (vertical = 0; height * 16 * 40 > vertical; vertical += 640) {
        (void)blit_bitmap_to_video_page(0x32c0,
                                       (int16_t)(top * 16 * 40 + vertical + left));
        (void)blit_bitmap_to_video_page(0x32e0,
                                       (int16_t)(top * 16 * 40 + vertical + left + 24));
    }
    for (horizontal = 2; horizontal < 23; horizontal += 2) {
        for (vertical = 0; height * 16 * 40 > vertical; vertical += 640)
            (void)blit_bitmap_to_video_page(0x3220,
                    (int16_t)(top * 16 * 40 + left + horizontal + vertical));
    }
    (void)blit_bitmap_to_video_page(0x3240, (int16_t)(top * 16 * 40 + left));
    (void)blit_bitmap_to_video_page(0x3260, (int16_t)(top * 16 * 40 + left + 24));
    (void)blit_bitmap_to_video_page(0x3280,
            (int16_t)(top * 16 * 40 + left + height_bytes));
    (void)blit_bitmap_to_video_page(0x32a0,
            (int16_t)(top * 16 * 40 + left + height_bytes + 24));
    for (horizontal = 0; horizontal < 22; horizontal += 2) {
        (void)blit_bitmap_to_video_page(0x3300,
                (int16_t)(top * 16 * 40 + horizontal + left + 2));
        (void)blit_bitmap_to_video_page(0x3320,
                (int16_t)(height_bytes + horizontal + left + top * 16 * 40 + 2));
    }
}

static int test_render_assets(void)
{
    uint8_t *title = (uint8_t *)malloc(32000);
    uint8_t *font = (uint8_t *)calloc(4000, 1);
    uint8_t *objects = (uint8_t *)calloc(8000, 1);
    uint8_t *pixels = (uint8_t *)malloc(320u * 200u);
    static const char title_path[] = "assets/dn.dn1";
    unsigned i;
    int ok = 1;
    if (title == NULL || font == NULL || objects == NULL || pixels == NULL) {
        ok = 0;
        goto cleanup;
    }

    REQUIRE(read_exact_file(title_path, title, 32000, 0));
    REQUIRE(read_exact_file("assets/font1.dn1", font, 2000, 3));
    REQUIRE(read_exact_file("assets/font2.dn1", font + 2000, 2000, 3));
    REQUIRE(read_exact_file("assets/object0.dn1", objects, 8000, 3));

    /* The game loads dn.dn1 with fread(32000): four raw 8,000-byte planes. */
    bios_set_mode(0x0d);
    (void)select_draw_page(0);
    (void)show_video_page(1);
    for (i = 0; i < 4; ++i) {
        unsigned byte_offset;
        set_seq(2, (uint8_t)(1u << i));
        for (byte_offset = 0; byte_offset < 8000; ++byte_offset)
            vga_cpu_write((uint16_t)byte_offset, title[i * 8000u + byte_offset]);
    }
    (void)show_video_page(0);
    vga_render_indexed(pixels);
    REQUIRE(write_indexed_png("build/vga-selftest/title.png", pixels));

    /* Follow display_title_screen's GC selection and draw_text_string's glyph offsets. */
    {
        static const char text[] = "DUKE NUKEM";
        size_t character;
        (void)vga_port_write(0x03ce, 5);
        for (character = 0; text[character] != '\0'; ++character) {
            unsigned offset;
            if (text[character] >= 'a')
                offset = (unsigned)(text[character] - 'a') * 40u + 0x0ac8u;
            else
                offset = (unsigned)(text[character] - ' ') * 40u + 0x0190u;
            (void)draw_ega_glyph((char *)font + offset,
                                 (int16_t)(8 + character), 64);
        }
    }
    vga_render_indexed(pixels);
    REQUIRE(write_indexed_png("build/vga-selftest/title-glyphs.png", pixels));

    /* Load border.dn1 as GAME1's loader does, then use latch-copy tile blits. */
    bios_set_mode(0x0d);
    REQUIRE(load_planar_resource("assets/border.dn1", 0x3000, 1920));
    draw_test_border_box(4, 3, 5);

    /* object0 is read after its 3-byte header and contains 10-byte sprite-row records. */
    set_gc(5, 0);
    (void)blit_planar_sprite_rows((char *)objects + 800, 8, 68);
    (void)blit_planar_sprite_rows((char *)objects + 1920, 18, 68);
    (void)blit_planar_sprite_rows((char *)objects + 2560, 28, 68);
    vga_render_indexed(pixels);
    REQUIRE(write_indexed_png("build/vga-selftest/toolbox-tiles.png", pixels));

cleanup:
    free(title);
    free(font);
    free(objects);
    free(pixels);
    return ok;
}

/* vga.c re-enables interrupts in its BIOS services; nothing to do in the test. */
void pc_enable(void) {}

int main(void)
{
    (void)make_dir("build");
    (void)make_dir("build/vga-selftest");
    if (!test_write_modes_and_latches())
        return 1;
    puts("PASS: VGA palette/status, write modes, latches, bit mask, set/reset, and read modes");
    if (fopen("assets/dn.dn1", "rb") == NULL) {          /* the game files are optional here */
        puts("SKIP: render fixtures (no assets/dn.dn1)");
        return 0;
    }
    if (!test_render_assets())
        return 1;
    puts("PASS: title, glyph, border, and object0 render fixtures (PNGs in build/vga-selftest/)");
    return 0;
}
