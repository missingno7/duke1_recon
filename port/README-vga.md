# VGA/EGA core

`vga.c` models the four 64 KiB EGA planes, the sequencer, graphics controller, CRTC start
address, attribute palette, and CPU latches. `vga_cpu_read()` loads all four latches on every
read. `vga_cpu_write()` applies the current map mask, write mode (0/1/2), set/reset, rotate and
logical function, and bit mask. Read mode 1 compares the color bits selected by color-don't-care.

The port-I/O bridge is exposed as:

```c
int vga_port_write(uint16_t port, uint8_t value);
int vga_port_read(uint16_t port, uint8_t *value);
```

Each function returns 1 for a handled video port and 0 otherwise. `pc_outportb()` and
`pc_inportb()` should route through these handlers before handling non-video ports. The current
`platform.h` retains a one-argument source adapter for the in-progress `pc_io.c`; new callers
should use the two-argument read handler and check its return value. This adapter is a proposed
contract adjustment to keep the platform bridge source-compatible while adopting the requested
handled-flag API.

The implemented register ports are 3C0/3C1 (attribute palette), 3C4/3C5 (sequencer), 3CE/3CF
(graphics controller), 3D4/3D5 (CRTC), and 3DA (input status). The synthetic retrace status
alternates bit 3 on each 3DA read so the game's polling loops can observe both edges.
`bios_set_mode(0x0d)` clears all planes and resets graphics registers; palette registers return
to the standard EGA mapping. `bios_set_active_page(page)` sets the display start to
`page * 0x2000`, and `vga_render_indexed()` converts that visible page to 320x200 palette indices.

CPU accesses, register changes, resets, palette snapshots, and frame conversion use a small
spin lock. `vga_palette_registers()` returns a thread-local snapshot for the presenter. The raw
pointer from `vga_plane()` is intended for inspection and single-threaded tests; game code should
use `vga_cpu_read()` and `vga_cpu_write()` so register and latch state remains active.
