# SDL3 port: design

Goal: one executable that plays all three episodes of Duke Nukum v2.0 on a modern system,
built from the same source as the byte-identical DOS build (`game/`), which stays untouched
and keeps building DN1/DN2/DN3.EXE byte for byte.

## Shape

```
duke1(.exe)
  launcher        finds the episode files, shows the episode dialog, runs the chosen episode
  episode 1..3    game/GAME1.C + GAME2.C compiled once per episode (-DEPISODE=n)
  platform        PC hardware the game talks to: EGA planes and registers, palette, PIT
                  timer, keyboard controller, PC speaker, game port, DOS calls; SDL3 below
```

### One binary, three episodes

The episode differences stay what they are in the source, `#if EPISODE` blocks (55 of them:
file names, texts, level tables, a few code paths).  The port compiles the game sources three
times, once per episode, and links the three instances into one program.  To keep their
globals and functions apart, each instance's own identifiers get a prefix (`ep1_`, `ep2_`,
`ep3_`); library and platform names stay shared.  The prefixing is done by the port's source
generator (below), so `game/` needs no change for it, and the episode logic runs exactly as
in the DOS build of that episode.

### Episode dialog and messages

At start the launcher looks for each episode's files (`*.dn1`, `*.dn2`, `*.dn3`) in the data
directory.  One episode present: it starts directly, like the original.  Several: the launcher
shows a dialog drawn with the game's own routines - `draw_framed_dialog_box` and
`draw_text_string` with the border and font graphics of the first episode present, in the
style of the game's menus:

```
 +--------------------------------------+
 |           DUKE NUKUM  v2.0           |
 |                                      |
 |  1  Episode ONE:   Shrapnel City     |
 |  2  Episode TWO:   Mission: Moonbase |
 |  3  Episode THREE: Trapped in the    |
 |                    Future!           |
 |                                      |
 |  Esc  Quit                           |
 +--------------------------------------+
```

(missing episodes are shown dimmed and cannot be chosen).  The same dialog routine shows the
port's own messages (missing files, a failed save, an unsupported option).  Only when no
episode's graphics can be loaded at all does the port fall back to an SDL message box.
Quitting an episode ("Quit to DOS") returns to the episode dialog.

## Same source, mechanical translation

`tools/port_gen.py` turns `game/` into the port's per-episode sources (in the build tree,
never committed), so the C the game is written in stays the C of 1991:

* Turbo C keywords `far`, `near`, `huge`, `pascal`, `cdecl`, `interrupt` are dropped;
* the 16-bit data model is kept explicit: `int` -> `int16_t`, `unsigned int` -> `uint16_t`,
  `long` -> `int32_t`, `unsigned long` -> `uint32_t` (record layouts, file formats, wrap
  arounds and `sizeof` stay those of the DOS program); structures are packed to 1 byte as
  in Turbo C;
* every identifier the game defines gets the episode prefix;
* functions that touch video memory through pointers (`MK_FP(0xA000, ...)`, the B800 text
  screen) are replaced by port versions from `port/override/` - written in the same style,
  calling the platform's planar video interface instead of raw pointers.  Everything else,
  including the register writes (`outport(0x3C4, ...)`), runs unchanged against the emulated
  hardware.

`TOOLBOX.ASM` (nine EGA/VGA routines) is reimplemented in C in `port/toolbox.c` with the
same semantics (plane masks, write modes, latches, page selection).

## Platform

* **Video**: EGA mode 0Dh, 320x200 in 16 colours: four 64 KB planes, sequencer map mask,
  graphics controller (set/reset, data rotate, read map, write modes 0/1/2, bit mask,
  latches), display start/page, the 16 palette registers (BIOS INT 10h AX=1000h) over the
  64-colour EGA palette.  The visible page is converted to an indexed 320x200 image every
  display refresh and scaled to the window with 4:3 aspect.
* **Timer**: `setvect(8, ...)` and the PIT divisor (0x2051, about 144 Hz) are honoured: the
  platform calls the game's timer interrupt handler at that rate (and treats the chained BIOS
  handler as a no-op).
* **Keyboard**: SDL key events become XT scan codes (make/break, 0xE0 prefixes) presented
  at port 0x60 to the game's keyboard interrupt handler, as the keyboard controller would.
* **Interrupts and threads**: the game runs on its own thread like the CPU it was written
  for; the platform delivers timer and keyboard interrupts asynchronously.  `disable()` /
  `enable()` are honoured (no interrupt is delivered inside them).  The game's busy-wait
  loops therefore keep working; idle points can later yield the CPU.
* **Sound**: PIT channel 2 and port 0x61 drive a square-wave PC speaker emulation on an
  SDL audio stream.
* **Joystick**: the game port (0x201) is emulated from an SDL gamepad (axis timing, buttons).
* **DOS services**: `delay`, `coreleft`, `textmode`, `exit` (returns to the launcher),
  file names resolved case-insensitively in the data directory.

## Build

CMake + SDL3 (Windows first: MinGW-w64 gcc and the SDL3 3.4.16 MinGW package in
`C:\tools`; Linux/macOS later).  `port_gen.py` runs as a build step.  The DOS build
(`tools/standalone.py build`, `game/BUILD.BAT`) is unaffected; `tools/validate.py` keeps
checking it.

## Order of work

1. Generator, CMake, platform stubs: the three episodes compile and link into one program.
2. Video: EGA emulation, toolbox routines, overrides; the episode dialog appears (fonts, border).
3. Timer and keyboard interrupts: title screen, menus and the demo run.
4. Sound, joystick, files (saves, high scores, demos, settings).
5. Play-through of each episode against DOSBox-X reference captures; idle yielding.

Integer arithmetic is the main fidelity risk: with `int16_t` operands C computes in 32-bit
and only truncates on assignment, so an intermediate overflow that wrapped under Turbo C does
not here.  Differences found in play-testing are fixed in the generator or by overrides, never
in `game/`.
