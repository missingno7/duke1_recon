"""Routing, immutable task packets, worker waves and intake.

    python tools/tasks.py plan                     route + rank every open target (writes build/tasks/plan.json)
    python tools/tasks.py show [--route R] [--limit N]
    python tools/tasks.py packet FUNCTION --worker NAME
    python tools/tasks.py wave N [--route GRINDABLE_C] [--dry-run]   packets + launch commands
    python tools/tasks.py intake [WORKER_DIR ...]  validate results, re-verify claims fresh, record
    python tools/tasks.py status

The supervisor owns canonical integration: intake never promotes, it prints
the promote command for each re-verified EQUAL candidate.  Packets are
snapshots: they record the canonical revision and proof context they were
made from, so an outdated packet is detectable.
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, EVIDENCE, LAYOUT, RECIPES, ROOT, atomic_json, load_json, rel, sha256  # noqa: E402
import context as ctxmod  # noqa: E402
import search  # noqa: E402
import symbols  # noqa: E402

PLAN = BUILD / "tasks" / "plan.json"
WORKERS = BUILD / "workers"
ROUTES = ("GRINDABLE_C", "EPISODE_PARAMETERIZED", "EPISODE_SPECIFIC", "ASM_RECONSTRUCTION",
          "STRUCTURAL_EVIDENCE", "BLOCKED_BY_SHARED_MECHANISM", "NEEDS_REVIEW", "ACCEPTED")
RESULT_STATUSES = ("EQUAL_CANDIDATE", "PARTIAL_EQUAL", "NEAR", "BLOCKED", "NEEDS_EVIDENCE")


def revision() -> dict:
    def git(*a):
        r = subprocess.run(["git", *a], cwd=ROOT, capture_output=True, text=True)
        return r.stdout.strip()
    dirty = git("status", "--porcelain", "--", "src", "recipes", "include", "layout", "evidence")
    return {"commit": git("rev-parse", "HEAD"), "canonical_dirty": bool(dirty)}


def _db():
    import db
    return db.connect()


def route_all() -> list:
    con = _db()
    exp = {r["function_id"]: dict(r) for r in con.execute(
        "SELECT function_id, COUNT(*) n, SUM(best_status='EQUAL') eq, MIN(diff_bytes) best, "
        "COUNT(DISTINCT emission_key) emissions FROM experiments GROUP BY function_id")}
    blocked = {r["scope"] for r in con.execute("SELECT scope FROM blockers WHERE status='OPEN'")}
    accepted = {p.stem for p in RECIPES.glob("*.json")}
    callers = {}
    for r in con.execute("SELECT caller, callee FROM deps WHERE episode='dn1'"):
        callers.setdefault(r["callee"], set()).add(r["caller"])
    callees = {}
    for r in con.execute("SELECT caller, callee FROM deps WHERE episode='dn1'"):
        callees.setdefault(r["caller"], set()).add(r["callee"])
    rows = []
    for fid, f in symbols.atlas().items():
        size = max(v["size"] for v in f["locations"].values())
        boundary_ok = all(v["boundary"] in ("VERIFIED", "ASM_VERIFIED") for v in f["locations"].values())
        e = exp.get(fid, {})
        cl = callees.get(fid, set())
        known = [c for c in cl if c in accepted or not c.startswith(("g1_", "g2_", "asm_"))]
        loc = next(iter(f["locations"].values()))
        cf = ctxmod.census_fn(next(iter(f["locations"])), loc["start"])
        if fid in accepted:
            route = "ACCEPTED"
            recipe = load_json(RECIPES / f"{fid}.json")
            if any(v["status"] != "EQUAL" for v in recipe["episodes"].values()):
                route = "EPISODE_PARAMETERIZED"
        elif fid in blocked:
            route = "BLOCKED_BY_SHARED_MECHANISM"
        elif f["segment"] == "ASM_TEXT":
            route = "ASM_RECONSTRUCTION"
        elif not boundary_ok or f["class"] == "UNRESOLVED":
            route = "STRUCTURAL_EVIDENCE"
        elif f["class"] == "EPISODE_SPECIFIC":
            route = "EPISODE_SPECIFIC"
        elif f["class"] == "PARAMETERIZED":
            route = "EPISODE_PARAMETERIZED"
        elif e.get("n", 0) >= 25 and not e.get("eq") and e.get("emissions", 0) <= e.get("n", 0) // 3:
            route = "NEEDS_REVIEW"          # many experiments, few distinct emissions: stagnation
        else:
            route = "GRINDABLE_C"
        score = 100.0 - size / 20.0
        score += 15 if f["class"].startswith("SHARED") else 0
        score += min(3 * len(callers.get(fid, ())), 30)
        score += 10 * (len(known) / len(cl)) if cl else 10
        score -= min(2 * e.get("n", 0), 20)
        score -= 5 * len(cf["tables"])
        score -= 10 if cf.get("interrupt_handler") else 0
        rows.append({"function": fid, "unit": f["segment"], "class": f["class"], "size": size, "route": route,
                     "priority": round(score, 2), "callers": len(callers.get(fid, ())), "callees": len(cl),
                     "callees_known": len(known), "experiments": e.get("n", 0), "switch_tables": len(cf["tables"])})
    rows.sort(key=lambda r: (ROUTES.index(r["route"]), -r["priority"], r["function"]))
    return rows


def plan() -> dict:
    rows = route_all()
    doc = {"made_at": time.strftime("%Y-%m-%dT%H:%M:%S"), "revision": revision(),
           "context_key": search.context_key(), "targets": rows,
           "routes": {r: sum(1 for x in rows if x["route"] == r) for r in ROUTES}}
    atomic_json(PLAN, doc)
    con = _db()
    import db
    with db.tx(con):
        for r in rows:
            tid = f"fn-{r['function']}"
            old = con.execute("SELECT status FROM tasks WHERE id=?", (tid,)).fetchone()
            status = "DONE" if r["route"] == "ACCEPTED" else (old["status"] if old and old["status"] in (
                "LEASED", "RESULT") else "OPEN")
            con.execute("INSERT INTO tasks (id, kind, targets, route, priority, status, created, updated) "
                        "VALUES (?,?,?,?,?,?,?,?) ON CONFLICT(id) DO UPDATE SET route=excluded.route, "
                        "priority=excluded.priority, status=?, updated=excluded.updated",
                        (tid, "function", json.dumps([r["function"]]), r["route"], r["priority"], status,
                         time.time(), time.time(), status))
    return doc


LESSONS = """\
Measured rules for this toolchain (evidence/compiler-rules.json, re-run by tools/probe.py):
- Turbo C 2.0, large model, flags -ml -Z -G -O -1- -f- -K (char is UNSIGNED by default).
- Functions are far.  Calls to functions defined EARLIER in the same file, or to `static`
  functions (even only forward-declared), compile to `push cs; call near`.  Calls to externs
  and to later-defined public functions compile to relocated far calls.  So: a callee the
  original reaches with `push cs; call near` must be DEFINED (an empty stub is fine) BEFORE
  your /*@body*/ marker; a callee reached with a far call must only be DECLARED.
- `retf N` = pascal function (callee pops N bytes; callers do no cleanup).
- No `push bp; mov bp,sp` when a function has no parameters and no locals.
- Register variables: first `register` local -> SI, second -> DI. Parameters can be `register`.
- 2-byte caller cleanup is `inc sp; inc sp` (-G); larger cleanups `add sp,N` or `mov sp,bp`.
- Arrays of structs in DGROUP are addressed through ES:BX built from DS (`mov ax,ds; mov es,ax`)
  even for plain `table[i].field = x` in the large model.
- `inportb/outportb/disable/enable` from <dos.h> are inline intrinsics (IN/OUT/CLI/STI).
- Globals are named by their DN1 DGROUP offset: `extern int d_4ed4;`.  Other functions are
  named by logical id (g1_XXXX, g2_XXXX, asm_XXXX).  Library functions use their real names.
- String literals in your file are verified by content at the address the original uses.
"""

RULES = """\
- Write ONLY inside {dir}.  Never modify src/, recipes/, layout/, evidence/, include/, tools/,
  tests/, probes/ or assets/.  Never run tools/promote.py or git commit.  Never delete lock files.
- No inline asm, no #pragma inline, no byte emission, no edited objects.  Never alter the oracle.
- Every attempt goes through: python tools/search.py CAND.c --function {fid} --worker {worker} --receipt {dir}/receipt.json
  (it records the experiment; identical experiments are answered from the database).
- Make one controlled change per attempt and say what you expect it to change.
- Do not pad with dummy locals/fields to force offsets unless you report it as `steered` in notes.
- Stop when: all present episodes are EQUAL; or the same emitted code repeats (search.py prints
  NOTE: identical emission) for three different hypotheses in one family; or you can name the
  concrete mechanism that blocks you and the next discriminating experiment.
"""

SCHEMA = """\
Write {dir}/result.json:
{{
  "task": "{task}", "function": "{fid}",
  "status": "EQUAL_CANDIDATE | PARTIAL_EQUAL | NEAR | BLOCKED | NEEDS_EVIDENCE",
  "candidate": "<path of your best .c file, inside {dir}>",
  "receipt": "<path of the search.py --receipt for that candidate>",
  "episodes_equal": ["dn1", ...],
  "experiments": <number of search.py runs>,
  "blocker": null | {{"category": "<one of {cats}>", "mechanism": "UPPER_SNAKE_TOKEN",
                     "evidence": "<what you measured>", "next_experiment": "<smallest next test>"}},
  "notes": "<declarations you had to guess (types, signatures), steering, anything shared>"
}}
Then reply with at most 15 lines: TASK <id> <STATUS> <candidate path>, then the key facts.
"""


def packet(fid: str, worker: str) -> Path:
    if fid not in symbols.atlas():
        raise SystemExit(f"unknown function {fid}")
    import db
    task = f"fn-{fid}"
    d = WORKERS / worker / task
    d.mkdir(parents=True, exist_ok=True)
    ctx = ctxmod.gather(fid)
    con = db.connect()
    prior = [dict(r) for r in con.execute(
        "SELECT key, source_sha256, best_status, diff_bytes, worker, note FROM experiments WHERE function_id=? "
        "ORDER BY created DESC LIMIT 12", (fid,))]
    for p in prior:
        src = db.get_source(con, p["source_sha256"])
        if src is not None:
            (d / f"prior-{p['key'][:12]}.c").write_text(src)
    blockers = [dict(r) for r in con.execute("SELECT * FROM blockers WHERE scope=?", (fid,))]
    profiles = load_json(LAYOUT / "profiles.json")
    snap = {
        "task": task, "function": fid, "worker": worker, "made_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
        "revision": revision(), "context_key": search.context_key(),
        "oracle_lock_sha256": sha256((LAYOUT / "oracle.lock.json").read_bytes()),
        "atlas_sha256": sha256((EVIDENCE / "atlas.json").read_bytes()),
        "locations": ctx["locations"], "class": ctx["class"], "mapping_evidence": ctx["mapping_evidence"],
        "signature_hints": ctx["signature_hints"], "calls": ctx["calls"], "callers": ctx["callers"],
        "data": {k: {**v, "widths": sorted(v["widths"])} for k, v in ctx["data"].items()}, "profile_hypotheses": {k: v for k, v in profiles["profiles"].items()},
        "default_profile": profiles["default"], "prior_experiments": prior, "blockers": blockers,
        "verify": f"python tools/search.py {rel(d)}/cand.c --function {fid} --worker {worker} "
                  f"--receipt {rel(d)}/receipt.json",
        "result_schema": "result.json as described in PROMPT.md",
    }
    atomic_json(d / "task.json", snap)
    (d / "context.txt").write_text(subprocess.run([sys.executable, str(ROOT / "tools" / "context.py"), fid],
                                                  capture_output=True, text=True, cwd=ROOT).stdout)
    (d / "skeleton.c").write_text(ctxmod.skeleton(ctx))
    import db as _db_mod
    prompt = f"""# Task {task}: recover `{fid}` as Turbo C 2.0 source

You are an independent worker in the duke1_recon matching-decompilation project (repository root:
{ROOT}).  Goal: C source whose pinned Turbo C 2.0 compilation is byte-for-byte identical to the
original function `{fid}` ({ctx['unit']}, {ctx['class']}) in every episode it exists in
({', '.join(ctx['locations'])}), with all relocations and symbol bindings correct.

Read first: {rel(d)}/context.txt (annotated original code and bindings), {rel(d)}/skeleton.c
(generated declaration guesses), {rel(d)}/task.json (immutable snapshot of this task), and any
{rel(d)}/prior-*.c (earlier attempts; do not repeat them).  Accepted examples: src/g1/*.c, src/g2/*.c.
AGENTS.md explains the project rules.

## Rules
{RULES.format(dir=rel(d), fid=fid, worker=worker)}
## Compiler facts
{LESSONS}
## Candidate format
Declarations and stub definitions first, then a line `/*@body*/`, then exactly the definition of
`{fid}`.  Start from skeleton.c; fix types/signatures from the evidence.

## Result
{SCHEMA.format(dir=rel(d), task=task, fid=fid, cats=', '.join(_db_mod.BLOCKER_CATEGORIES))}
"""
    (d / "PROMPT.md").write_text(prompt)
    with db.tx(con):
        con.execute("UPDATE tasks SET status='LEASED', worker=?, packet=?, updated=? WHERE id=?",
                    (worker, rel(d), time.time(), task))
    return d


def wave(n: int, route: str, dry: bool) -> list:
    doc = plan()
    if doc["revision"]["canonical_dirty"]:
        print("WARNING: canonical files have uncommitted changes; packets record the dirty state")
    con = _db()
    leased = {r["id"] for r in con.execute("SELECT id FROM tasks WHERE status IN ('LEASED','RESULT')")}
    picks = [r for r in doc["targets"] if r["route"] == route and f"fn-{r['function']}" not in leased][:n]
    out = []
    for k, r in enumerate(picks):
        worker = f"luna-{r['function']}"
        if dry:
            out.append({"function": r["function"], "worker": worker, "priority": r["priority"]})
            continue
        d = packet(r["function"], worker)
        cmd = (f"python ~/.codex-dashboard/cx.py run -n {worker} -C {ROOT.as_posix()} -m gpt-6-luna -e xhigh "
               f"< {(d / 'PROMPT.md').as_posix()}")
        out.append({"function": r["function"], "worker": worker, "packet": rel(d), "launch": cmd})
    atomic_json(BUILD / "tasks" / f"wave-{time.strftime('%Y%m%d-%H%M%S')}.json", out)
    return out


def intake(dirs: list) -> list:
    import db
    con = db.connect()
    if not dirs:
        dirs = [Path(r["packet"]) for r in con.execute("SELECT packet FROM tasks WHERE status='LEASED' AND packet IS NOT NULL")]
    outcomes = []
    for d in dirs:
        d = (ROOT / d) if not Path(d).is_absolute() else Path(d)
        rp = d / "result.json"
        if not rp.exists():
            outcomes.append({"dir": rel(d), "outcome": "NO_RESULT"})
            continue
        try:
            res = load_json(rp)
            task = load_json(d / "task.json")
        except ValueError as exc:
            outcomes.append({"dir": rel(d), "outcome": "MALFORMED_RESULT", "error": str(exc)})
            continue
        fid = task["function"]
        o = {"dir": rel(d), "function": fid, "claimed": res.get("status")}
        if res.get("status") not in RESULT_STATUSES or res.get("function") != fid:
            o["outcome"] = "MALFORMED_RESULT"
            outcomes.append(o)
            continue
        cand = res.get("candidate")
        cpath = (ROOT / cand) if cand and not Path(cand).is_absolute() else Path(cand or "")
        if cand and (not cpath.exists() or d.resolve() not in cpath.resolve().parents):
            o["outcome"] = "CANDIDATE_OUTSIDE_TASK_DIR"
            outcomes.append(o)
            continue
        if cand:
            text = cpath.read_text("latin-1")
            r = load_json(RECIPES / f"{fid}.json") if (RECIPES / f"{fid}.json").exists() else None
            fresh = search.run(text, fid, flags=__import__("tcc").profile_flags(task["default_profile"]),
                               profile=task["default_profile"], fresh=True, fresh_compile=True,
                               worker="intake", note=f"intake of {rel(d)}")
            eq = sorted(e for e, v in fresh["results"].items() if v["status"] == "EQUAL")
            o["reverified_equal"] = eq
            o["stale_packet"] = task["context_key"] != fresh["context_key"]
            if res["status"] in ("EQUAL_CANDIDATE", "PARTIAL_EQUAL") and not eq:
                o["outcome"] = "EQUAL_CLAIM_REJECTED"
            elif eq:
                o["outcome"] = "CONFIRMED_EQUAL" if res["status"] in ("EQUAL_CANDIDATE", "PARTIAL_EQUAL") \
                    else "UNCLAIMED_EQUAL_FOUND"
                o["promote"] = f"python tools/promote.py {fid} {rel(cpath)}"
                if r:
                    o["note"] = "function already accepted; promotion only if it adds episodes"
            else:
                o["outcome"] = "NEAR_RECORDED" if res["status"] == "NEAR" else "NOT_EQUAL"
        else:
            o["outcome"] = "NO_CANDIDATE"
        b = res.get("blocker")
        if b:
            try:
                o["blocker_id"] = db.add_blocker(con, fid, b["category"], b["mechanism"], b["evidence"],
                                                 b["next_experiment"], reporter=task["worker"])
            except (ValueError, KeyError) as exc:
                o["blocker_rejected"] = str(exc)
        with db.tx(con):
            con.execute("UPDATE tasks SET status='RESULT', result=?, updated=? WHERE id=?",
                        (json.dumps(o), time.time(), task["task"]))
        outcomes.append(o)
    atomic_json(BUILD / "tasks" / f"intake-{time.strftime('%Y%m%d-%H%M%S')}.json", outcomes)
    return outcomes


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("plan")
    s = sub.add_parser("show")
    s.add_argument("--route")
    s.add_argument("--limit", type=int, default=25)
    p = sub.add_parser("packet")
    p.add_argument("function")
    p.add_argument("--worker", required=True)
    w = sub.add_parser("wave")
    w.add_argument("n", type=int)
    w.add_argument("--route", default="GRINDABLE_C", choices=ROUTES)
    w.add_argument("--dry-run", action="store_true")
    i = sub.add_parser("intake")
    i.add_argument("dirs", nargs="*")
    sub.add_parser("status")
    a = ap.parse_args()
    if a.cmd == "plan":
        doc = plan()
        print(json.dumps(doc["routes"], indent=1))
    elif a.cmd == "show":
        rows = load_json(PLAN)["targets"] if PLAN.exists() else plan()["targets"]
        for r in [r for r in rows if not a.route or r["route"] == a.route][:a.limit]:
            print(f"{r['function']:12s} {r['route']:28s} prio {r['priority']:7.2f} size {r['size']:5d} "
                  f"callers {r['callers']:2d} callees {r['callees_known']}/{r['callees']} exps {r['experiments']}")
    elif a.cmd == "packet":
        print(rel(packet(a.function, a.worker)))
    elif a.cmd == "wave":
        for x in wave(a.n, a.route, a.dry_run):
            print(json.dumps(x))
    elif a.cmd == "intake":
        for o in intake([Path(x) for x in a.dirs]):
            print(json.dumps(o))
    elif a.cmd == "status":
        con = _db()
        for r in con.execute("SELECT route, status, COUNT(*) n FROM tasks GROUP BY route, status ORDER BY route"):
            print(f"{r['route']:28s} {r['status']:8s} {r['n']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
