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
(`g2_3d1e`, `d_02fa`, `d_9682_`), and the header records both views.

From the repository, `python tools/standalone.py build` runs the same steps with the
pinned toolchain and compares the results with the original files' SHA-256
(`layout/oracle.lock.json`); `python tools/validate.py` does it on every check.

The code is still in its matching-phase form (logical names such as `g1_ff16` and
`d_02fb` that encode original addresses).  The readability pass is described in
`../docs/roadmap.md`; every step of it must keep the build byte-identical.
