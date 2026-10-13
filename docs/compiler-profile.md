# Compiler profile

Current default profile `tc20-l-gzo` ([layout/profiles.json](../layout/profiles.json)):

```
TCC 2.0  -ml -Z -G -O -1- -f- -K      (wrapper adds -c -IINCLUDE)
```

Origin: an external claim (lethal-guitar/Duke1Decomp `BUILD.BAT`), treated as a
hypothesis and tested here. Every statement below is re-run by
`python tools/probe.py` from [evidence/compiler-rules.json](../evidence/compiler-rules.json).

| Rule | Outcome | Evidence |
|---|---|---|
| MODEL-LARGE | confirmed | C0L.OBJ `_TEXT` equals image `[0,455)` outside fixups in all episodes; the five other startup objects differ |
| STARTUP-C0-REASSEMBLY | confirmed | TASM 1.0 reassembles `STARTUP\C0.ASM` (`/D__LARGE__ /MX`) to C0L.OBJ's bytes, fixups and publics |
| RUNTIME-CL-LIB | confirmed | 64 CL.LIB code segments, 12,845 bytes, each found exactly once per episode |
| FLAG-O | confirmed | without `-O`: jump chains, `g1_e92e`/`g1_1053`/`g2_276f` stop matching |
| FLAG-K | confirmed | without `-K`: `cbw` on char loads, `g2_276f`/`g2_01d5` stop matching |
| FLAG-G | confirmed | without `-G`: `pop cx` replaces `inc sp; inc sp` in `g2_01d5` |
| CPU-8086 | confirmed | with `-1`: `push imm` appears, `g1_006f` stops matching |
| FLAG-Z | consistent, not discriminated | removing `-Z` changes none of the accepted functions yet |
| Z-EFFECT | confirmed (object level) | with `-Z`, `a=b; c=b;` stores AX twice without reloading |
| CALL-FORMS | confirmed (object level) | extern → far call (EXTDEF); earlier-defined or `static` (even forward-declared) → `push cs; call near` (no fixup); later-defined public → far call (own-segment fixup) |
| PASCAL-CALLEE | confirmed | `g1_e92e` matches only as `pascal` |

Consequences used by the tooling:

* In the originals there are **0 backward far calls** inside G1/G2 and all
  backward intra-segment calls are `push cs; call near`: consistent with one
  translation unit per segment. The **197 forward `push cs; call near`** in G1 are
  evidence of `static` functions.
* G1 is 65,393 bytes, at the 64 KB per-segment limit, and identical in shape in
  all three episodes; G2 carries most episode differences.
* `-f-` (no floating point) and `-a` (alignment) are not yet discriminated;
  they matter at the data/link level.

Not yet established: per-unit flag differences, string merging (`-d`), the
compile path of the assembly region, the exact order of translation units in the
link (assumed C0, G1, G2, library from segment order).
