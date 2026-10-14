/* platform.h - the PC the game runs on, emulated over SDL3.

   This is the contract between the three parts of the port (docs/sdl3-port.md):

     generated game code   game/GAME1.C + GAME2.C, translated by tools/port_gen.py and
                           compiled once per episode; reaches the hardware through the
                           Turbo C names in port/include/ (dos.h, conio.h, alloc.h), which
                           map to the pc_* functions below
     toolbox               port/toolbox.c: the nine TOOLBOX.ASM routines in C, on vga_*
     platform              port/pc_*.c, port/vga.c: emulated EGA, PIT, keyboard controller,
                           PC speaker, game port and DOS services; SDL3 underneath

   Widths follow the DOS program: ports and offsets are 16 bit, the game's int is int16_t. */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- I/O ports ----
   outport(port, w) writes the low byte to port and the high byte to port + 1, as an x86
   OUT DX, AX does.  Emulated: 0x3C4/0x3C5 sequencer, 0x3CE/0x3CF graphics controller,
   0x3D4/0x3D5 CRTC (start address), 0x3DA input status (retrace), 0x40-0x43 PIT,
   0x60/0x61 keyboard controller and speaker gate, 0x20 PIC (EOI), 0x201 game port. */
uint8_t  pc_inportb(uint16_t port);
uint16_t pc_inport(uint16_t port);
void     pc_outportb(uint16_t port, uint8_t value);
void     pc_outport(uint16_t port, uint16_t value);

/* ---- interrupts ----
   Vectors 8 (timer) and 9 (keyboard) can be hooked with pc_setvect; the platform calls the
   handler asynchronously (from its own thread) at the PIT rate / on each key event, never
   between pc_disable() and pc_enable().  pc_getvect returns a callable no-op for vectors
   the game did not set (the BIOS handlers it chains to). */
typedef void (*pc_isr)(void);
pc_isr pc_getvect(int vector);
void   pc_setvect(int vector, pc_isr handler);
void   pc_disable(void);
void   pc_enable(void);

/* ---- memory ----
   Real-mode addresses the game forms with MK_FP.  B800:xxxx (text screen) returns a pointer
   into the emulated text buffer.  A000:xxxx is planar video memory and cannot be a plain
   pointer: the functions that write it are replaced in port/override/ and use vga_* below;
   pc_mk_fp aborts with a message for it. */
void *pc_mk_fp(uint16_t segment, uint16_t offset);

/* ---- EGA/VGA (mode 0Dh, 320x200, 16 colours) ----
   Four 64 KB planes.  vga_cpu_write / vga_cpu_read are a CPU access to A000:offset with the
   current register state: map mask, write mode 0/1/2, set/reset, data rotate and function,
   bit mask, read map select, read mode, latches - exactly what the EGA does. */
uint8_t *vga_plane(int plane);                         /* direct plane access, 0..3 */
/* Port-I/O bridge used by pc_inport[b]/pc_outport[b] for VGA/EGA registers. */
int      vga_port_read(uint16_t port, uint8_t *value);
int      vga_port_write(uint16_t port, uint8_t value);
/* Compatibility for existing pc_io.c callers; new code should pass an output pointer and
   inspect the handled flag. */
static inline uint8_t vga_port_read_value(uint16_t port)
{
    uint8_t value = 0xff;
    (void)vga_port_read(port, &value);
    return value;
}
#define VGA_PORT_READ_SELECT(_1, _2, NAME, ...) NAME
#define vga_port_read(...) \
    VGA_PORT_READ_SELECT(__VA_ARGS__, vga_port_read, vga_port_read_value)(__VA_ARGS__)
void     vga_set_palette_entry(uint8_t index, uint8_t colour);
void     vga_cpu_write(uint16_t offset, uint8_t value);
uint8_t  vga_cpu_read(uint16_t offset);
void     vga_set_display_start(uint16_t offset);       /* CRTC start address, in bytes */
uint16_t vga_display_start(void);
/* The visible 320x200 picture as palette indices 0..15 (row-major), and the 16 attribute
   (palette) registers, each a 6-bit EGA colour rrggbb. */
void     vga_render_indexed(uint8_t *out_320x200);
const uint8_t *vga_palette_registers(void);
/* The colour (0xRRGGBB) a palette register value shows in the current mode (200-line modes:
   CGA colours with intensity in bit 4), and the visible picture as 0xAARRGGBB pixels. */
uint32_t vga_colour_rgb(uint8_t register_value);
void     vga_render_rgb(uint32_t *out_320x200);
void     vga_vertical_retrace_wait(void);              /* blocks until the next display refresh */

/* ---- video BIOS (INT 10h) ---- */
void bios_set_mode(uint8_t mode);                      /* 0x0D graphics, 0x03 text */
void bios_set_palette_register(uint8_t index, uint8_t colour);   /* AX=1000h */
void bios_set_active_page(uint8_t page);               /* AH=05h: start = page * 0x2000 */

/* ---- DOS and Turbo C runtime services ---- */
void     pc_delay(unsigned milliseconds);
uint32_t pc_coreleft(void);
void     pc_textmode(int mode);
void     pc_exit(int status);                          /* ends the episode, back to the launcher */
FILE    *pc_fopen(const char *name, const char *mode); /* data directory, case-insensitive */
int16_t  pc_getw(FILE *stream);                        /* 16-bit little-endian word */
int16_t  pc_putw(int16_t word, FILE *stream);

/* ---- launcher side ---- */
typedef int (*episode_main)(int argc, char **argv);
int  platform_init(const char *data_dir);              /* SDL, window, audio; 0 on success */
int  platform_run_episode(episode_main entry, int argc, char **argv);   /* game thread */
void platform_shutdown(void);
int  platform_poll_key(void);                          /* launcher dialogs: next XT scan code, 0 if none */

#ifdef __cplusplus
}
#endif
#endif
