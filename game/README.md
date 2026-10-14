# Duke Nukum v2.0 — standalone source

This directory is the complete source of DN1.EXE, DN2.EXE and DN3.EXE (Duke Nukum,
Apogee 1991, version 2.0).  Built with the historical toolchain it reproduces the
three original executables byte for byte.

| File | Contents |
|---|---|
| `DUKE.H` | declarations shared by both units: data structures, every function's prototype, every global (in address order: Turbo C places uninitialised globals by a hash of the name, ties by first appearance) |
| `GAME1.C` | first translation unit: startup, main loop, levels, actors, player, files |
| `GAME2.C` | second translation unit: menus, text screens, high scores, timer and PC-speaker sound |
| `TOOLBOX.ASM` | ProGraphx EGA/VGA Toolbox routines (TASM 1.0) |
| `BUILD.BAT` | builds one episode: `BUILD 1`, `BUILD 2` or `BUILD 3` |

Requirements: Turbo C 2.0 (TCC, TLINK, `INCLUDE\`, `LIB\C0L.OBJ`, `LIB\CL.LIB`),
TASM 1.0 and LZEXE 0.91, with `TC` set to the Turbo C directory.  The episode is
selected with `-DEPISODE=n`; one source serves all three.  Each unit defines `UNIT`
before including `DUKE.H`: the original units declared three things differently
(`confirm_quit_to_dos`, `current_level_index`, `alternate_sprite_draw_offset`), and the
header records both views.

Names: the original identifiers are lost.  Functions, globals, structures and fields carry
descriptive names inferred from the code (`layout/game-names.json` maps them to the
address-based ids of the matching archive in `src/`).  The level actors are named after
what they are in the game (`update_rocket`, `flying_techbot_records`); `../docs/actors.md`
lists every level-map word 0x30XX with its identity and the evidence for it.
Uninitialised globals are the one exception to plain naming: Turbo C 2.0 lays out a unit's
uninitialised data by a hash of the names, so these objects keep storage names
(`d_` + DN1 address + `_`, all hashing alike) and `DUKE.H` gives them their readable names
with `#define` (block "names of the uninitialised globals").

From the repository, `python tools/standalone.py build` runs the same steps with the
pinned toolchain and compares the results with the original files' SHA-256
(`layout/oracle.lock.json`); `python tools/validate.py` does it on every check.

The readability pass is ongoing (`../docs/roadmap.md`): some names are still modest
guesses, and a few matching-era forms (documented
`goto`s, shift chains and casts that a plainer form would compile differently) remain.
Every step must keep the build byte-identical; `tools/rename.py` renames safely.
