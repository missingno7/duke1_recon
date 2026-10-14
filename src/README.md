# Duke Nukum v2.0 — game source

The complete source of DN1.EXE, DN2.EXE and DN3.EXE (Duke Nukum, Apogee 1991, version
2.0).  Built with the historical toolchain it reproduces the three original executables
byte for byte.

| File | Contents |
|---|---|
| `DUKE.H` | declarations shared by both units: data structures, every function's prototype, every global in address order |
| `GAME1.C` | first translation unit: start-up, main loop, levels, actors, player, files |
| `GAME2.C` | second translation unit: menus, text screens, high scores, timer and PC-speaker sound |
| `TOOLBOX.ASM` | ProGraphx EGA/VGA Toolbox routines (TASM 1.0) |
| `BUILD.BAT` | builds one episode under DOS: `BUILD 1`, `BUILD 2` or `BUILD 3` |

Requirements: Turbo C 2.0 (TCC, TLINK, `INCLUDE\`, `LIB\C0L.OBJ`, `LIB\CL.LIB`),
TASM 1.0 and LZEXE 0.91, with `TC` set to the Turbo C directory.  From the repository,
`python tools/build.py` runs the same steps with the pinned toolchain and compares the
results with the originals.

One source serves all three episodes: the episode is selected with `-DEPISODE=n`, and
the differences (file names, texts, level tables, a few code paths) are `#if EPISODE`
blocks.  Each unit defines `UNIT` before including `DUKE.H`: the original units declared
three things differently (`confirm_quit_to_dos`, `current_level_index`,
`alternate_sprite_draw_offset`), and the header records both views.

Names: the original identifiers are lost.  Functions, globals, structures, fields and
parameters carry descriptive names inferred from the code; each function and structure
has a one-line description above it, each global one beside its declaration.  Level
actors are named after what they are in the game (`update_rocket`,
`flying_techbot_records`); `../docs/actors.md` lists every level-map word 0x30XX with its
identity and the evidence.  Uninitialised globals are the one exception to plain naming:
Turbo C 2.0 lays out a unit's uninitialised data by a hash of the names, so these objects
keep storage names (`d_` + DN1 address + `_`, all hashing alike) and `DUKE.H` gives them
their readable names with `#define` (block "names of the uninitialised globals").

Functions and data stay in the order of the original object files, because Turbo C emits
them in source order; section banners in the files group them by subsystem.  A few forms
are there because a plainer one compiles differently (some `goto`s, shift chains, casts);
each carries a comment saying so.  `../docs/turbo-c.md` explains the rules that decide
this.
