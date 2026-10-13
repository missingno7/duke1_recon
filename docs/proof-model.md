# Proof model: what is and is not proven

## Levels

| Level | Meaning | Status |
|---|---|---|
| Oracle identity | the three packed files, their unpacked images, relocation sets and entry registers | **proven**: locked hashes; independent decoder; original LZEXE stubs executed in an emulator agree |
| Segment census | startup, asm, two C translation units, CL.LIB, DGROUP | **evidence**: C0L/CL.LIB exact matches; every first-party code byte tiled by recursive descent with closed boundaries |
| Function boundary | `[start, next start)` per function | **verified** when recursive descent (with switch tables) covers the extent exactly; all 248 C functions per episode |
| Cross-episode identity | one logical function, up to three locations | **evidence with confidence**: separate byte/shape/size/call/data signals; never proof by itself |
| Function match (strict) | candidate C compiles to the original function in an episode | **proof**, per episode, relative to the symbol table (below) |
| Translation unit | function order, statics, string pooling, data emission | not yet attempted |
| Data ownership | which unit defines each DGROUP byte; BSS order | not yet attempted |
| Natural link | real TLINK of C0 + asm + G1 + G2 + CL.LIB | not yet attempted |
| Unpacked image equality | linked image == oracle image, relocation set equal | not yet |
| Repacked equality | LZEXE 0.91 output == original file | not yet (LZEXE 0.91 not acquired; 0.90 only) |

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

* No hybrid image has been built, so nothing claims "complete source".
* The hand-written assembly region (`ASM_TEXT`, 1,082 bytes, identical in all
  episodes) and the game's C0 variant are identified, not reconstructed.
* CL.LIB modules are identified by exact match outside fixups; they are not yet
  linked from the pinned library.
* Four bytes at `0x805` (`jmp far [..]`, after CVTFAK) and 2–5 zero bytes before
  `DELAY_TEXT` are inside the runtime region but not yet attributed.
* Function names, types and parameter names are reconstructions; only the
  emitted code is proven.
