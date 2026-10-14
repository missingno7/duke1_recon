# Duke Nukum v2.0 — source

The complete C and assembly source of **Duke Nukum** v2.0 (Apogee, 1991; the first
Duke Nukem), episodes 1–3, reconstructed from the original executables, and an SDL3
port that plays it on a modern PC.

* **`src/`** is the game.  Compiled with the original toolchain (Turbo C 2.0, TASM 1.0,
  TLINK 2.0, LZEXE 0.91) it produces `DN1.EXE`, `DN2.EXE` and `DN3.EXE` **byte for byte**;
  the original files are the oracle that proves it.
* **`port/`** runs that same source on Windows (and later Linux/macOS) through SDL3: one
  `duke1.exe` plays all three episodes, chosen in a dialog drawn with the game's own
  routines.

The game files (the original executables, graphics, levels) are not part of this
repository and must never be committed or redistributed; put your own copy in `assets/`
(ignored by git) to build and test.

## Layout

| Path | What it is |
|---|---|
| [`src/`](src/README.md) | the game: `GAME1.C`, `GAME2.C` (the two original translation units), `DUKE.H`, `TOOLBOX.ASM`, `BUILD.BAT` |
| [`port/`](port/README.md) | the SDL3 port: emulated PC (EGA, timer, keyboard, PC speaker, DOS) and the launcher |
| `tools/` | build and check tools (Python) |
| `config/` | pinned toolchain, compiler profile, SHA-256 of the original executables |
| [`docs/`](docs) | [actors](docs/actors.md), [the port's design](docs/sdl3-port.md), [the original executables](docs/originals.md), [editing src/ without changing the binaries](docs/turbo-c.md) |

## Build

The original executables, from `src/`, compared with the originals in `assets/`:

```
python tools/build.py            # dn1/dn2/dn3: EQUAL = byte for byte
```

The SDL3 port (MinGW-w64 gcc and SDL3, see `port/README.md`):

```
cmake -S port -B build/port -G "MinGW Makefiles"
cmake --build build/port
build/port/duke1.exe --data assets
```

Everything at once — originals present, DOS build equal, port builds and its EGA
self-test passes:

```
python tools/validate.py
```

## Working on the source

Any change to `src/` must keep `tools/build.py` EQUAL: the source is the original program,
not a version of it.  Turbo C's code generation decides what "the same program" means in
detail (register allocation, block order, data layout, the order of uninitialised data by
name hash); [docs/turbo-c.md](docs/turbo-c.md) lists the rules.  Renames go through
`tools/rename.py`, which keeps them safe.  Port-specific behaviour belongs in `port/`
(platform code and `port/override/`), never in `src/`.

History: the per-function reconstruction that led here is preserved in git (tag
`matching-archive`).
