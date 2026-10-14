# SDL3 port: step 1 notes

This step builds one MinGW/SDL3 executable from the unchanged DOS sources. tools/port_gen.py
emits build/port-gen/ep1..ep3/{DUKE.H,GAME1.C,GAME2.C}. The generator lexes C tokens, so
strings, characters, and comments are kept intact while it removes Turbo C memory/calling
qualifiers, maps DOS integer widths, prefixes game functions and globals by episode, and
maps runtime calls to pc_*. It packs the game's structures and substitutes any matching
port/override/<function>.c definition at the original function's location. Generation is
deterministic and never writes to game/.

Configure and build from the repository root:

    cmake -S port -B build/port -G "MinGW Makefiles"
    cmake --build build/port --parallel

CMake uses MinGW-w64 gcc 12 and the SDL3 3.4.16 package pinned in port/CMakeLists.txt.
Each episode's two units compile with -O0 -fwrapv -fno-strict-aliasing -DEPISODE=n; the
platform and launcher compile with -O2. The output is build/port/duke1.exe, with SDL3.dll
copied beside it. CMake selects port/vga.c and port/toolbox.c when present, and compiles
only the missing half of port/stub_vga.c as a fallback.

The launcher accepts --data DIR, --episode N, and --trace. With no data path it uses the
executable directory. It detects an episode from worldal1.dnN plus font1.dnN, starts the
requested available episode or the first one found, and passes safe empty argv[1] and argv[2]
slots because the historical main reads argv[1] even when argc == 1. pc_fopen resolves names
case-insensitively in the data directory. The generator and tests do not copy the user's
files from assets/.

The platform runs each episode on its own SDL thread and uses setjmp/longjmp in that thread
to make pc_exit return to the launcher. A separate timer thread follows the PIT channel-0
divisor (65536 initially, then the game's 0x2051 divisor); vector delivery waits out
pc_disable critical sections and queues keyboard bytes while interrupts are masked. SDL
keys become XT make/break codes, including 0xE0 for extended keys. The game port reports no
joystick. Channel 2 and port 0x61 state are recorded; speaker output is not part of this
step. pc_mk_fp supplies a 4 KB B800 text buffer and stops with a clear message if a direct
A000 pointer reaches the core.

The SDL window presents the VGA backend's indexed 320x200 image with its EGA palette at
about 70 Hz, scales it to 4:3, and toggles fullscreen with Alt+Enter. Escape/F10 and the
window-close event feed Escape followed by the game's affirmative quit response so the game
thread follows its own shutdown path.

## Validation notes

- MinGW configure and build succeeded; nm found ep1_main, ep2_main, and ep3_main in the same
  executable, and the SDL3 DLL was copied.
- Trace startup runs for episodes 1, 2, and 3 each reached vector 9 setup, channel-0 PIT
  programming (0x36, 0x2051), vector 8 setup, and timer-handler deliveries. Runs were
  observed for 21 seconds and then stopped by the harness; interactive Escape/window-close
  shutdown was not exercised in those runs.
- The supplied assets/ folder has SPEED.DN1 but no DN2/DN3 speed-setting files. Episodes 2
  and 3 continued startup with those optional files absent.
- python tools/standalone.py build still reported EQUAL for DN1, DN2, and DN3.
- GCC reports warnings from the recovered source: the source's period & 0x100 byte write
  truncates to zero, and GAME1/GAME2 declare confirm_quit_to_dos with different return types.
  Neither warning prevented linking.

## Contract addition proposed for the platform owner

The core needs a bridge for VGA register I/O and palette writes. Keep
vga_port_read(port, &value) / vga_port_write(port, value) in platform.h, with a handled
status, plus vga_set_palette_entry(index, colour). The one-argument read adapter currently
lets the platform core forward reads while the VGA implementation retains the handled status
for its own retrace path.
