# Workflow

## Single function, by hand (no bureaucracy required)

```bash
python tools/context.py g2_37b6                       # annotated original, bindings, callers/callees
python tools/context.py g2_37b6 --skeleton > build/workers/me/g2_37b6.c
python tools/search.py build/workers/me/g2_37b6.c --function g2_37b6 --asm
```

`search.py` works without tasks or leases. It records each experiment in
`state/research.sqlite` (content-addressed: identical source, flags and proof
context are answered from the database), and prints `NOTE: identical
emission` when a different source produced code already seen.

Useful queries:

```bash
python tools/db.py experiments g2_37b6          # every attempt, including failures
python tools/db.py same-emission g2_37b6        # distinct sources, identical object code
python tools/db.py blockers --open
python tools/context.py --list --unit G2_TEXT --max-size 80 --open
```

## Supervised waves

1. `python tools/tasks.py plan` routes every open function:
   `GRINDABLE_C`, `EPISODE_PARAMETERIZED`, `EPISODE_SPECIFIC`,
   `ASM_RECONSTRUCTION`, `STRUCTURAL_EVIDENCE`, `BLOCKED_BY_SHARED_MECHANISM`,
   `NEEDS_REVIEW` (many experiments, few distinct emissions), and ranks
   grindable ones by size, three-episode reuse, unlock value (callers),
   known callees, previous experiments and switch tables.
2. `python tools/tasks.py wave 4` writes immutable packets
   (`build/workers/luna-<fn>/fn-<fn>/`: PROMPT.md, task.json snapshot with
   canonical revision + proof context key, context.txt, skeleton.c, prior
   attempts) and prints one `cx` launch command per worker.
3. Launch each command as its own background task (codex-workers skill;
   model gpt-6-luna, effort xhigh).
4. `python tools/tasks.py intake` validates `result.json`, re-verifies every
   candidate fresh (no cache), records proposed blockers (mechanism token +
   next experiment are mandatory) and prints a promote command for confirmed
   candidates. It never promotes.
5. The supervisor reviews each candidate (natural declarations: real types for
   globals, pinned Turbo C headers, literals for text, no offsets from unrelated
   symbols, no steering), fixes small issues by hand and re-runs `search.py`,
   then promotes with `tools/promote.py --batch LIST.txt` (one lock, one full
   re-proof, one journal, all-or-nothing), checks `tools/decls.py` for
   conflicting views, runs `tools/validate.py --write-progress`, commits.

Start with about four workers. Grow only while compiles (≈0.3 s each, cached
and coalesced in `build/cc-cache`) and intake keep up. If DOS compiles ever
become the bottleneck, the in-flight coalescing in `tools/tcc.py` is the place
to add a central queue.

## Blockers

A blocker is a concrete mechanism plus the next discriminating experiment, in
one of: SOURCE_SHAPE, DECLARATION_VIEW, TU_LAYOUT, DATA_OWNERSHIP,
CALL_BINDING, CFG_BOUNDARY, RUNTIME_LIBRARY, TOOLCHAIN, EPISODE_DIVERGENCE,
ASM_REQUIRED. When two workers report the same mechanism, stop dispatching that
family, fix it once (header, profile, rule, tool), record the rule, resolve the
blockers, and re-plan.

## Recovery

* Crash during promotion: `python tools/promote.py --recover`.
* Lost database: `python tools/db.py rebuild` (research history is lost; proofs
  are not).
* Lost `build/`: `python tools/oracle.py && python tools/census.py && python tools/atlas.py --check`.
