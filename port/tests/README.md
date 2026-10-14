# VGA self-test

From the repository root, build and run the C11 self-test with MinGW-w64 GCC:

```sh
mkdir -p build/workers/luna-port-b
C:/msys64/mingw64/bin/gcc -std=c11 -O2 -Wall -Wextra -Iport port/tests/vga_selftest.c port/vga.c port/toolbox.c -o build/workers/luna-port-b/vga_selftest.exe
build/workers/luna-port-b/vga_selftest.exe
```

The test covers EGA write modes 0, 1, and 2, latch copies, bit masking, set/reset,
read-map selection, and read mode 1 color compare. It also reads the checked-in assets
without copying them and writes these previews under `build/workers/luna-port-b/`:

* `title.png` - the four 8,000-byte planes read by the game's `load_title_screen` path
* `title-glyphs.png` - the title with glyphs drawn through `draw_ega_glyph`
* `toolbox-tiles.png` - border tiles copied in write mode 1 and object0 sprites drawn by
  `blit_planar_sprite_rows`

The title loader uses `fread(..., 32000, 1, ...)` directly, so this fixture has no
three-byte header. The font, border, and object resource loaders skip their three-byte
headers; the border loader also skips one control byte before each four-plane group.
