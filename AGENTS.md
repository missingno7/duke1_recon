# Agent rules (supervisor and workers)

## Roles

* **Supervisor** (one interactive session): plans waves, launches workers, runs
  intake, promotes, curates blockers, changes shared headers/tools/profiles,
  commits. Canonical source, recipes, symbol aliases, profiles, the oracle lock
  and acceptance tools have exactly one writer, enforced by the canonical lock in
  `tools/promote.py`.
* **Workers** (independent agents, e.g. GPT-6 Luna xhigh via the codex-workers
  skill): each owns `build/workers/<worker>/<task>/` and nothing else.

## Worker rules

1. Write only inside your task directory. Never modify `src/`, `recipes/`,
   `layout/`, `evidence/`, `include/`, `tools/`, `tests/`, `probes/`, `assets/`.
   Never run `tools/promote.py`, `git commit`, or delete lock files.
2. Every compile goes through `tools/search.py ... --worker NAME --receipt ...`.
   It is isolated, content-addressed and recorded; repeated experiments are
   answered from the database. Do not run the DOS tools by hand.
3. No inline `asm`, `#pragma inline`, byte emission, object editing, or anything
   that manufactures equality. Never alter the oracle or the tool pins.
4. One controlled change per attempt; say what you expect it to change.
5. Stop at EQUAL; or when `search.py` reports *identical emission* for three
   hypotheses in one family; or when you can name the concrete mechanism and the
   next discriminating experiment (that is a blocker, see categories in
   `tools/db.py`). A large function, a first diff or an ugly residual is not a
   blocker.
6. Report steering (dummy locals/fields that only force offsets) in `notes`.
7. Finish with `result.json` (schema in your PROMPT.md) and a reply of at most
   15 lines.

## Naming in candidate source

* Functions: logical ids `g1_XXXX`, `g2_XXXX`, `asm_XXXX` (frame offset in DN1).
* Globals: `d_XXXX`, the DN1 DGROUP offset; the proof binds them per episode.
* Library: real CL.LIB names (`outport`, `fopen`, ...).
* Semantic names come later through `layout/symbols.json` aliases (supervisor).

## Candidate format

Declarations and empty stub definitions, then a line `/*@body*/`, then exactly
the definition of the target. Callees the original reaches with
`push cs; call near` must be defined before the marker (a stub is enough);
far-called callees must only be declared (see rule CALL-FORMS).

## Supervisor loop

```bash
python tools/tasks.py plan
python tools/tasks.py wave 4                    # packets + cx launch commands
# launch each printed command as its own background task
python tools/tasks.py intake                    # re-verifies every claim fresh; never promotes
python tools/promote.py FUNCTION CANDIDATE.c    # one at a time; full re-proof under the lock
python tools/validate.py --write-progress && git commit
```

Grow the wave only when compile throughput and intake keep up. When two workers
report the same mechanism, stop dispatching that family, fix the shared
mechanism (header, profile, tool) once, encode it in `evidence/compiler-rules.json`
or a test, then release the blocked tasks (`tools/db.py resolve`).
