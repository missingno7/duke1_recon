# duke1 — the SDL3 port

One executable, `duke1`, that plays all three episodes of Duke Nukum v2.0 on a modern
system.  It runs the original program — `src/`, unchanged — on an emulated PC: the game
still writes EGA registers, installs its timer and keyboard interrupt handlers and drives
the PC speaker, and the platform below turns that into an SDL3 window, input and audio.
Design and the DOS behaviours the port must reproduce: [../docs/sdl3-port.md](../docs/sdl3-port.md).

## How it is put together

```
src/ (GAME1.C, GAME2.C, DUKE.H)
   |  tools/port_gen.py, once per episode -> build/port-gen/ep1..ep3 (never committed):
   |    16-bit types kept (int -> int16_t ...), far/near/pascal dropped, every game name
   |    prefixed ep1_/ep2_/ep3_, DOS runtime calls -> pc_*, override/ functions swapped in
   v
duke1.exe = episode 1 + episode 2 + episode 3 + launcher + emulated PC
```

| File | Part |
|---|---|
| `platform.h` | the contract: everything the game can reach (ports, interrupts, memory, EGA, BIOS, DOS) |
| `launcher.c` | finds the episodes, shows the episode dialog (drawn with the game's own routines), runs the chosen one |
| `pc_sdl.c` | SDL3: window and presentation (70 Hz, 4:3), keyboard to XT scan codes, game thread, `--script` |
| `pc_interrupt.c` | interrupt vectors 8 and 9, CLI/STI (`disable`/`enable`), the PIT timer thread |
| `pc_io.c` | I/O ports: PIT, keyboard controller, speaker gate, game port, EGA registers |
| `pc_speaker.c` | PC speaker: PIT channel 2 square wave, replayed sample-exact on an SDL audio stream |
| `pc_dos.c` | DOS and Turbo C runtime: files (case-insensitive), `delay`, `getw`/`putw`, 64 KB wrapping memory blocks |
| `vga.c` | the EGA in mode 0Dh: four planes, sequencer, graphics controller, latches, palette, display start |
| `toolbox.c` | the nine routines of `src/TOOLBOX.ASM` in C, with the same EGA behaviour |
| `override/*.c` | game functions that write video memory through raw pointers, rewritten for `vga.c` |
| `include/` | `dos.h`, `conio.h`, `alloc.h` for the translated game |
| `tests/vga_selftest.c` | EGA write modes, latches, bit mask, set/reset; renders sample screens if the game files are present |

## Build

MinGW-w64 gcc (`C:/msys64/mingw64`) and the SDL3 MinGW package (path in `CMakeLists.txt`,
`SDL3_ROOT`); CMake 3.20 or newer:

```
cmake -S port -B build/port -G "MinGW Makefiles"
cmake --build build/port
```

Result: `build/port/duke1.exe` with `SDL3.dll` beside it (the MinGW runtime is linked in),
and `build/port/vga_selftest.exe`.  `python tools/validate.py` builds and tests both.

## Run

Copy `duke1.exe` and `SDL3.dll` into the game folder and start it, or point it at one:

```
duke1.exe [--data DIR] [--episode N] [--select] [--trace]
```

| Option | Effect |
|---|---|
| `--data DIR` | game files in DIR (default: the program's folder) |
| `--episode N` | start episode N directly |
| `--select` | always show the episode dialog |
| `--trace` | log port, interrupt and file activity (to `duke1.log` when there is no console) |
| `--script FILE` | timed input and screenshots, for tests (below) |
| `--no-restart` | quitting an episode ends the program instead of returning to the dialog |

Quitting an episode returns to the episode dialog (the program restarts itself, so every
episode starts with fresh globals); closing the window ends the program at once.

## Testing

`--script FILE` runs lines `<ms> key|keydown|keyup <name>`, `<ms> shot <file.png>` (the exact
320x200 picture) and `<ms> quit`; key names are DOSBox-X mapper names (`space`, `enter`,
`esc`, `f1`, `up`, `lctrl`, `lalt`, `a` ...).  `DUKE1_AUDIO_WAV=file.wav` records everything
the speaker plays.

`tools/dosref.py` runs an original `DNn.EXE` in DOSBox-X with the same key script and
captures frames; `tools/portcompare.py` puts the original and the port side by side.  The
reference speed is a 386 (DOSBox-X `cycles=fixed 20000`): loops that count passes instead of
timer ticks call `pc_spin()`, which paces them to it.
