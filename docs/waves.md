# Worker waves (measured)

Workers: GPT-6 Luna, reasoning effort xhigh, launched with the codex-workers
skill (`cx.py`), one task packet each (`tools/tasks.py`). Every claim was
re-verified fresh at intake; promotion re-proved all accepted recipes.

## Wave 1 (4 workers, 2026-10-13)

Targets: the four highest-ranked grindable leaves (G1, 55–83 bytes).

| Function | Outcome | Recorded experiments | Wall time |
|---|---|---:|---:|
| `g1_2a40` | EQUAL ×3 | 2 | 2m33s |
| `g1_2e64` | EQUAL ×3 | 3 | 3m05s |
| `g1_326e` | EQUAL ×3 | 4 | 4m47s |
| `g1_3513` | EQUAL ×3 (after resume) | 2 | 1m44s + 1m35s |

Shared obstacle found: the codex sandbox does not see the user's
site-packages, so `capstone` failed to import; one worker reported it as a
TOOLCHAIN blocker (`MISSING_CAPSTONE_DEPENDENCY`), three installed private
copies. Fixed once by the supervisor (`tools/setup_env.py` vendors the pinned
packages into `build/python`; `tools/common.py` prefers them; the decoder
version is part of the proof context key). The blocked worker was resumed with
its context and finished.

## Wave 2 (8 workers)

Targets: six highest-ranked grindable functions plus two episode-parameterized
ones (to exercise `EPISODE` conditionals and per-episode compiles).

| Function | Outcome | Recorded experiments | Wall time |
|---|---|---:|---:|
| `g2_01a9` | EQUAL ×3 | 1 | 0m42s |
| `g2_3114` | EQUAL ×3 | 1 | 0m50s |
| `g1_0042` | EQUAL ×3 | 1 | 0m55s |
| `g1_3558` | EQUAL ×3 | 2 | 1m16s |
| `g1_3714` | EQUAL ×3 | 2 | 2m10s |
| `g1_2b86` | EQUAL ×3 | 2 | 3m04s |
| `g2_3bd7` (parameterized) | EQUAL ×3 with `#if EPISODE` | 2 | 3m38s |
| `g2_4334` (parameterized) | EQUAL ×3, **rewritten at review** | 3 | 4m03s |

Review finding: `g2_4334` matched by addressing DN3/DN2 text as offsets from an
unrelated DN1 symbol (`(char *)&d_4713 + 0x19`). That is a binding artefact,
not plausible source. The supervisor replaced it with per-episode string
literals (EQUAL ×3) and closed the gap that invited it: episode-only data now has
a name (`d_dnN_XXXX`), and packets state that offsets from unrelated symbols are
rejected.

Throughput: compiles take ~0.3 s and are cached/coalesced; intake re-verifies
in seconds; batch promotion (`promote.py --batch`) re-proves every recipe once
per batch. The supervisor's review is the slowest step.

## Wave 3 (12 workers)

Targets: the eight highest-ranked grindable functions plus four chosen to be
hard: the keyboard interrupt handler (`g1_15f4`, 513 B), two switch-table
functions (`g1_6292`, `g1_314c`) and a 476-byte G2 routine (`g2_3d8c`).

| Function | Outcome | Recorded experiments | Wall time | Review |
|---|---|---:|---:|---|
| `g2_37b6` | EQUAL ×3 | 3 | 2m50s | |
| `g1_12ce` | EQUAL ×3 | 2 | 3m02s | |
| `g1_15f4` (ISR) | EQUAL ×3 | 2 | 4m00s | |
| `g1_367e` | EQUAL ×3 | 5 | 4m06s | |
| `g1_1247` | EQUAL ×3 | 7 | 4m16s | |
| `g1_0b85` | EQUAL ×3 | 7 | 4m22s | `#define` long view → `extern long` |
| `g1_0151` | EQUAL ×3 | 3 | 5m15s | `typedef char FILE` → `<stdio.h>` |
| `g1_1b8a` | EQUAL ×3 | 3 | 5m15s | |
| `g2_2870` | EQUAL ×3 | 6 | 7m35s | `MK_FP` of two ints → `char far *` global |
| `g1_314c` (switch) | BLOCKED → EQUAL ×3 after tool fix | 6 | 7m43s | |
| `g1_6292` (switch) | BLOCKED → EQUAL ×3 after fix + resume | 6 + 2m26s | 7m18s | old-style decl → prototype |
| `g2_3d8c` | EQUAL ×3 | 4 | 11m24s | `goto` loops → `for` (identical emission) |

Shared mechanism found: two workers independently reported that switch jump
tables (own-segment `offset16` fixups to labels *inside* the function) were
rejected by the comparer, which only accepted public targets
(`INTERNAL_SWITCH_TABLE_FIXUPS_UNSUPPORTED`, `PRIVATE_SWITCH_LABEL_FIXUPS`).
Fixed once in `tools/compare.py` (relational binding: same relative offset in
the original function), covered by a regression test, both blockers resolved;
`g1_314c` became EQUAL at intake without further work, `g1_6292` after a
resumed worker fixed `switch (x - 4)` → `switch (x)`. The instruction diff now
masks verified fixup fields, so only genuine differences are shown.

Consolidation: `tools/decls.py` collects every accepted file's view of each
function and global. `g1_3513` had been accepted with a phantom third
parameter; it was re-proven as `(int, int)` (callers push two words) and the
caller's old-style declaration replaced by the prototype.

## Totals after three waves

24 worker tasks, 24 functions EQUAL in all three episodes, median ≈3
recorded experiments per function, 0.7–11 minutes per worker. Supervisor
review changed 7 of 24 sources to more natural, equally proven forms.
Throughput limits observed: none in compiles or intake; review is the
bottleneck. A larger wave (≥16) is justified by these numbers.
