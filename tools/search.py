"""Isolated compiler experiment for one logical function.

    python tools/search.py CANDIDATE.c --function g1_e92e [--profile P | --flags F ...]
                           [--episodes dn1,dn2] [--name C_NAME] [--asm] [--fresh]
                           [--worker NAME] [--note TEXT] [--receipt OUT.json] [--json]

* Never touches canonical state (src/, recipes/, layout/, evidence/).
* Compiles in a unique scratch directory through tools/tcc.py (content-
  addressed; identical requests are served from cache or coalesced).
* Compares against every episode the function exists in (or --episodes),
  strictly (tools/compare.py), and prints compact feedback first.  --asm adds
  the instruction-level diff.
* A source that mentions EPISODE is compiled once per episode with
  -DEPISODE=n; otherwise one object is compared against all episodes.
* Records the experiment in state/research.sqlite keyed by its content
  address; an identical experiment is answered from the database (marked
  CACHED) unless --fresh.
* The receipt carries the context key (oracle lock, atlas, symbol table,
  profiles, proof-tool identity).  A receipt whose context key differs from
  the current one is stale and is rejected by tools/promote.py.

Exit status: 0 = EQUAL in every compared episode, 1 = otherwise.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, EVIDENCE, LAYOUT, TOOLS, atomic_json, content_key, sha256, tree_hash  # noqa: E402
import compare  # noqa: E402
import symbols  # noqa: E402
import tcc  # noqa: E402

FORBIDDEN = [
    (re.compile(r"\basm\b"), "inline asm (changes the compile path; justify and route to the supervisor)"),
    (re.compile(r"#\s*pragma\s+inline", re.I), "#pragma inline"),
    (re.compile(r"__emit__|_emit\b"), "byte emission"),
]
PROOF_TOOLS = ("common.py", "compare.py", "symbols.py", "datamap.py", "omf.py", "disasm.py", "tcc.py",
               "toolchain.py", "oracle.py", "lz91.py", "mz.py")


def context_key() -> str:
    files = [LAYOUT / "oracle.lock.json", LAYOUT / "toolchain.json", LAYOUT / "profiles.json",
             EVIDENCE / "atlas.json", BUILD / "census" / "anchors.json"]
    if (LAYOUT / "symbols.json").exists():
        files.append(LAYOUT / "symbols.json")
    files += [TOOLS / n for n in PROOF_TOOLS]
    import capstone
    return sha256((tree_hash(files) + f"|capstone {capstone.__version__}").encode())


def lint(text: str) -> list:
    stripped = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    stripped = re.sub(r"//[^\n]*", "", stripped)
    return [msg for rx, msg in FORBIDDEN if rx.search(stripped)]


def emission_key(res: compare.Result, obj: bytes) -> str | None:
    """Identity of what the compiler emitted for the target: extent bytes plus
    the ordered fixup list (relative positions, kinds, targets)."""
    if not res.cand:
        return None
    import omf
    m = omf.OmfReader().read(obj)
    fx = [(f["offset"] - res.cand_base, f["loc"], f["target_kind"], f["target"], f["displacement"])
          for f in m.linker_fixups if res.cand_base <= f["offset"] < res.cand_base + len(res.cand)]
    return content_key({"bytes": res.cand.hex(), "fixups": fx})


def run(source_text: str, function: str, *, flags: list, profile: str | None, episodes: list | None = None,
        name: str | None = None, fresh: bool = False, worker: str | None = None, note: str | None = None,
        record: bool = True, fresh_compile: bool = False) -> dict:
    entry = symbols.atlas().get(function)
    if entry is None:
        raise SystemExit(f"unknown function {function}; see evidence/atlas.json")
    eps = [e for e in (episodes or EPISODES) if e in entry["locations"]]
    problems = lint(source_text)
    per_episode = bool(re.search(r"\bEPISODE\b", source_text))
    ctx = context_key()
    compiles = {}
    for e in eps:
        fl = list(flags) + ([f"-DEPISODE={e[-1]}"] if per_episode else [])
        compiles[e] = fl
    req = {"function": function, "name": name, "flags": compiles, "source": sha256(source_text.encode("latin-1")),
           "context": ctx}
    key = content_key(req)
    con = None
    if record:
        import db
        con = db.connect()
        if not fresh:
            hit = db.lookup_experiment(con, key)
            if hit:
                out = {"key": key, "cached": True, "context_key": ctx, "function": function,
                       "results": json.loads(hit["results"]), "best_status": hit["best_status"],
                       "lint": problems, "emission_key": hit["emission_key"]}
                return out
    results = {}
    receipts = {}
    emis = None
    diffs = {}
    objects = {}
    for e in eps:
        fk = tuple(compiles[e])
        if fk not in objects:      # one compile per distinct flag set
            objects[fk] = tcc.compile_c(source_text, compiles[e], fresh=fresh_compile)
        r = objects[fk]
        receipts[e] = r.key
        if not r.ok:
            results[e] = {"status": "COMPILE_ERROR", "detail": r.log.strip().splitlines()[-6:]}
            continue
        res = compare.compare_object(r.obj, function, e, name=name)
        results[e] = res.summary()
        if res.status != "EQUAL" and res.cand:
            diffs[e] = compare.instruction_diff(res)
        if emis is None and res.cand:
            emis = emission_key(res, r.obj)
    order = ["EQUAL", "BINDING_ERROR", "DIFFER", "EXTENT_MISMATCH", "NO_SYMBOL", "OBJECT_ERROR", "COMPILE_ERROR"]
    statuses = [v["status"] for v in results.values()]
    best = min(statuses, key=order.index) if statuses else "NO_EPISODE"
    if statuses and all(s == "EQUAL" for s in statuses):
        best = "EQUAL"
    elif best == "EQUAL":
        best = "PARTIAL_EQUAL"
    repeats = []
    if con is not None and emis:
        repeats = [dict(r) for r in con.execute(
            "SELECT key, source_sha256, best_status, note FROM experiments WHERE function_id=? AND emission_key=? "
            "AND source_sha256 != ?", (function, emis, req["source"]))]
    out = {"key": key, "cached": False, "context_key": ctx, "function": function, "results": results,
           "repeat_emission": repeats,
           "best_status": best, "compile_keys": receipts, "lint": problems, "emission_key": emis,
           "source_sha256": req["source"], "flags": compiles, "diffs": diffs}
    if con is not None:
        import db
        db.record_experiment(con, {"key": key, "function": function, "source_text": source_text,
                                   "source_sha256": req["source"], "profile": profile, "flags": compiles,
                                   "compile_key": content_key(receipts), "context_key": ctx,
                                   "ok": all(v["status"] != "COMPILE_ERROR" for v in results.values()),
                                   "emission_key": emis, "results": results, "best_status": best,
                                   "diff_bytes": max((v.get("diff_bytes") or 0) for v in results.values()) if results else None,
                                   "worker": worker, "note": note})
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source")
    ap.add_argument("--function", required=True)
    ap.add_argument("--profile")
    ap.add_argument("--flags", nargs="+")
    ap.add_argument("--episodes")
    ap.add_argument("--name")
    ap.add_argument("--asm", action="store_true", help="show instruction-level differences")
    ap.add_argument("--fresh", action="store_true")
    ap.add_argument("--worker")
    ap.add_argument("--note")
    ap.add_argument("--receipt")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--no-record", action="store_true")
    a = ap.parse_args()
    text = Path(a.source).read_text("latin-1")
    profile = a.profile or json.loads((LAYOUT / "profiles.json").read_text())["default"]
    flags = a.flags if a.flags else tcc.profile_flags(profile)
    out = run(text, a.function, flags=flags, profile=None if a.flags else profile,
              episodes=a.episodes.split(",") if a.episodes else None, name=a.name, fresh=a.fresh,
              worker=a.worker, note=a.note, record=not a.no_record)
    if a.receipt:
        atomic_json(Path(a.receipt), {k: v for k, v in out.items() if k != "diffs"})
    if a.json:
        print(json.dumps(out, indent=1, default=str))
    else:
        tag = " (CACHED)" if out["cached"] else ""
        print(f"{a.function}: {out['best_status']}{tag}  key {out['key'][:16]}")
        for e, v in out["results"].items():
            extra = ""
            if v.get("size"):
                extra = f" size {v['size'][0]}/{v['size'][1]} diff_bytes {v.get('diff_bytes')} first_diff {v.get('first_diff')}"
            print(f"  {e}: {v['status']}{extra}")
            for d in v.get("detail", [])[:6]:
                print(f"      {d}")
        if out["lint"]:
            print("  LINT:", "; ".join(out["lint"]))
        if out.get("repeat_emission"):
            print(f"  NOTE: identical emission already produced by {len(out['repeat_emission'])} other source(s) "
                  f"(e.g. experiment {out['repeat_emission'][0]['key'][:16]}); this change did not alter codegen")
        if out.get("diffs") and (a.asm or len(out["diffs"]) and not out["cached"]):
            e, lines = next(iter(out["diffs"].items()))
            shown = lines if a.asm else lines[:24]
            print(f"  instruction diff ({e}; '-' candidate, '+' original):")
            for ln in shown:
                print("   ", ln)
            if not a.asm and len(lines) > 24:
                print(f"    ... {len(lines) - 24} more lines (--asm)")
    return 0 if out["best_status"] == "EQUAL" else 1


if __name__ == "__main__":
    sys.exit(main())
