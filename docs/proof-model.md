# Proof model: what is and is not proven

## Levels

| Level | Meaning | Status |
|---|---|---|
| Oracle identity | the three packed files, their unpacked images, relocation sets and entry registers | **proven**: locked hashes; independent decoder; original LZEXE stubs executed in an emulator agree |
| Segment census | startup, asm, two C translation units, CL.LIB, DGROUP | **evidence**: C0L/CL.LIB exact matches; every first-party code byte tiled by recursive descent with closed boundaries |
| Function boundary | `[start, next start)` per function | **verified** when recursive descent (with switch tables) covers the extent exactly; all 248 C functions per episode |
| Cross-episode identity | one logical function, up to three locations | **evidence with confidence**: separate byte/shape/size/call/data signals; never proof by itself |
| Function match (strict) | candidate C compiles to the original function in an episode | **proof**, per episode, relative to the symbol table (below) |
| Translation unit (code) | one compile of a whole unit: every function EQUAL at its original offset, original segment length | **proven for G1, G2** and the **assembly unit** (one TASM module, `src/asm/toolbox.asm`: its whole 1,082-byte `_TEXT` contribution, data tables included) in DN1/DN2/DN3 (`tools/tubuild.py`) |
| Translation unit (data) | the unit's `_DATA`: initialised globals then its literal pool | **proven for G1 and G2** (`tools/tubuild.py UNIT --data`, `layout/unit-data.json`): G1's `_DATA` equals DGROUP 0x0094..0x0b46 and G2's 0x0b46..library start, byte for byte in all episodes, every fixup bound, relocation set equal (one trailing alignment byte each where the original has it) |
| Data ownership | which unit defines each DGROUP byte; BSS order | **proven by the link**: C0L `_DATA`, G1 and G2 `_DATA` (unit data checks), G1 and G2 `_BSS` (`check_bss`: length and every global's address; order by rule BSS-ORDER), CL.LIB data/BSS from the stock library. The G1/G2 split of the BSS is not observable in the binary beyond alignment and is chosen (DN1 0xa0f4) |
| Natural link | real TLINK of C0 + asm + G1 + G2 + CL.LIB | **proven** in DN1/DN2/DN3 (`python tools/link.py --repack`, `layout/link.json`; re-run by `tools/validate.py`) |
| Unpacked image equality | linked image == oracle image, relocation set equal | **proven**: every byte of the load module, the relocation set and the header fields (CS:IP, SS:SP, min/max allocation) in all three episodes |
| Repacked equality | LZEXE 0.91 output == original file | **proven**: LZEXE 0.91 packs the linked image of each episode into a file whose SHA-256 equals the original DN1.EXE / DN2.EXE / DN3.EXE |

## What a strict function match checks (`tools/compare.py`)

For one candidate object and one episode:

1. Strict OMF validation: record checksums, a reviewed record set, THEADR first,
   MODEND last, no overlapping LEDATA.
2. The target public lies in a CODE segment; its extent (to the next public or
   segment end) has exactly the original extent's length.
3. Every candidate FIXUPP inside the extent binds, for that episode, to the value
   the original contains: far calls to `seg:off` of the bound function, data
   references to the bound DGROUP offset plus addend, string literals of the
   candidate's own `_DATA` verified by content at the original address.
4. The set of original MZ relocation sites inside the extent equals the set of
   segment words the candidate's fixups produce: no hard-coded frames, no
   missing or extra relocations.
5. Compile-time-resolved `push cs; call near` and `push cs; mov reg, offset`
   resolve to candidate publics whose binding is the original target.
6. Every other byte is identical. Nothing is masked, trimmed or patched.

Promotion re-runs this on a fresh compile, re-proves every previously accepted
recipe under the canonical lock, publishes through a journal and re-proves the
published file. Validation re-proves everything from canonical inputs.

## Unit-level bindings

* A reference into the candidate's own `_BSS` (Turbo C's struct-return temporary,
  a function-local static) binds as `unit_static`: all such references of a
  function share one base, and no other original function touches the address.
  The unit build requires one base per unit.
* A reference into the candidate's own `_DATA` that lands on a public (a global
  *defined* in the unit) binds by that global's name like an external; other own
  `_DATA` references are string literals verified by content at the original
  address.  Once the unit's `_DATA` is proven equal to its original range, the
  unit build binds every own-data reference relationally to that range (stronger
  than the content check).

## The symbol table assumption

A function proof is relative to the per-episode binding of names:

* functions → atlas locations (`evidence/atlas.json`);
* `d_XXXX` → DN1 DGROUP offset `XXXX`, mapped to DN2/DN3 by
  `tools/datamap.py`: code anchors (displacements that differ between
  shape-identical functions; 656/610 unique, none multi-valued) take precedence
  over a content alignment of the initialised data; BSS maps by a constant
  delta because BSS has the same size in all episodes.

A wrong mapping can only make a proof fail, never succeed: a binding is a single
address per name per episode, shared by every function. The data layout itself
(which object lives where, and why) is proven only by the translation-unit and
link levels, which have not been attempted yet.

## Relocation order

LZEXE 0.91 stores relocations as ascending deltas with paragraph-normalised
offsets. The original TLINK relocation order and `seg:off` split are therefore
**not observable** in these oracles (rule RELOCATION-ORDER-UNOBSERVABLE).
Acceptance compares relocation *sets*. Turbo C's descending FIXUPP order can
still be checked against a natural link of our own objects, but never against
the originals.

## Per-episode claims

Recipes record a status per episode. A function proven for DN1 stays proven
when DN3 is still open; a replacement source may never shrink the set of proven
episodes (`tools/promote.py` refuses it). Episode-specific code uses `EPISODE`
conditionals; such sources are compiled once per episode with `-DEPISODE=n`.

## Not claimed

* The canonical sources are still the per-function files of the matching phase
  (preludes, stubs, logical names `g1_XXXX` / `d_XXXX`); the readable standalone
  tree is the next phase (`docs/roadmap.md`).  Every change to them is checked by
  the full link.
* Function names, types, struct fields and parameter names are reconstructions;
  only the emitted program is proven.  Several sources keep measured gotos and
  idioms that exist to reproduce the original code generation (`goto kept:` notes).
* The G1/G2 ownership of BSS objects and some object boundaries inside data
  (array extents, unreferenced regions marked in the data fragments) are choices
  consistent with the binary, not observations: the binary does not record them.
* Relocation order is unobservable (rule RELOCATION-ORDER-UNOBSERVABLE); only the
  relocation set is compared.
