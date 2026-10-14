# Editing src/ without changing the binaries

`src/` is not "a version" of Duke Nukum: compiled with the original toolchain it *is* the
program, byte for byte (`python tools/build.py`).  Most edits — names, comments, layout,
`#define` constants, splitting text into `#include`d files — cannot change the output.
Edits to code can, in ways that are easy to predict once you know how Turbo C 2.0 works.
Every rule below was established by experiment on the pinned compiler.

## The compiler profile

```
tcc -c -ml -Z -G -O -1- -f- -K -DEPISODE=n GAME1.C GAME2.C
```

| Switch | Meaning | What it implies for the source |
|---|---|---|
| `-ml` | large model | far code and data pointers; a pointer plus an `int` changes only the 16-bit offset |
| `-K` | `char` is unsigned | a `char` never sign-extends; comparisons with values >= 0x80 work |
| `-O` | jump optimisation | identical branch tails are merged (below) |
| `-Z` | register load suppression | `a = b; c = b;` reuses AX without reloading `b` |
| `-G` | optimise for speed | 2-byte caller cleanup is `inc sp; inc sp` |
| `-1-` | 8086 instructions | no `push imm`, no `shl reg, n` |
| (no `-d`) | no string merging | every string literal is its own copy, in order of appearance |

The link is `tlink /c /d /s C0L TOOLBOX GAME1 GAME2, DNn.EXE, DNn.MAP, CL.LIB` with the
stock Turbo C 2.0 large-model start-up (`C0L.OBJ`) and runtime (`CL.LIB`), and the result
is packed with LZEXE 0.91, which reproduces the original files exactly.

## Rules that decide the code

**Order.**  Functions, initialised data and string literals are emitted in source order:
moving a function, a global with an initialiser or a literal moves bytes.  Each unit's
`_DATA` holds its initialised globals in definition order (explicit zero initialisers
included), then all its string literals in order of appearance.

**Uninitialised data is ordered by name.**  A unit's uninitialised globals go to `_BSS`
sorted by `(first char + 4 * last char + 32 * length) mod 1024` of the name, ties in order
of the name's first appearance (an `extern` declaration or a use counts).  Renaming one
moves it.  That is why these globals keep storage names `d_XXXX_` that all hash alike and
get readable names through `#define` in `DUKE.H`; `tools/rename.py` does this
automatically.

**Calls.**  In one translation unit, a call to a function defined earlier (or `static`)
is `push cs; call near`; a call to a public function defined later, or in the other unit,
is a far call.  So a function's position relative to its callers is part of the code.
Functions ending in `retf N` are `pascal` (the callee pops its arguments).  In a function
with a BP frame but no locals and no saved SI/DI, every `cdecl` call is followed by
`mov sp, bp`, even one without arguments; a call without it is a `pascal` call.

**Registers.**  `register` variables (locals and parameters): SI goes to the one with the
highest weighted use count, DI to the next; each use counts three times per enclosing
`for`/`while`/`do` loop (loops made of labels and `goto` are not weighted); ties keep
declaration order.  Renaming never matters; reordering declarations or turning a `goto`
loop into a `while` can swap SI and DI.

**Merged tails.**  With `-O`, identical instruction sequences at the end of different
branches are emitted once and the other branch jumps into them.  Two branches that end
the same way in the source therefore compile to shared code; the original's duplicated
code means the two tails differed somewhere.  Several `goto`s in `src/` exist to get the
original block order and are commented as such.

**Expressions.**  `int` is 16 bits and arithmetic wraps; `-Z` lets a value just stored
stay in AX for the next statement, so splitting or merging statements can change loads.
`x << 1 << 1` and `x * 4` do not always compile alike; where the source keeps an odd form,
a comment says the plain one was tried.

## Checking a change

```
python tools/build.py                 # all episodes; on a difference it names the
                                      # functions holding the first differing bytes
python tools/build.py --episode dn2 --keep build/try    # keep objects, map and EXE
```

A difference in one function after a code edit is usually one of the rules above: the
block order (tail merge), the register choice, a reload suppressed by `-Z`, or a call that
changed from near to far.
