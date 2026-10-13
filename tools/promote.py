"""Canonical promotion: the only writer of src/, recipes/ and the promotion log.

    python tools/promote.py FUNCTION CANDIDATE.c [--profile P] [--name C_NAME]
                            [--receipt R.json] [--verify-only] [--note TEXT]
    python tools/promote.py --batch LIST.txt [--note TEXT]   (lines: FUNCTION CANDIDATE)
    python tools/promote.py --recover

Rules enforced here:
  * the candidate is lint-clean and has a '/*@body*/' marker; everything after
    the marker is the function definition that a translation-unit build
    will use; before it only declarations and stub definitions may appear;
  * verification is fresh (no compile cache, no experiment cache); a supplied
    search receipt must carry the current context key and the candidate's
    hash, otherwise it is stale and refused;
  * at least one episode must be EQUAL; an existing recipe's proven episodes
    may never shrink;
  * under the single-writer lock: the candidate bytes must be unchanged since
    verification, every previously accepted recipe is re-proven fresh in every
    episode it claims, the files are published through the journal, the new
    canonical file is re-proven from its canonical path, and any failure
    rolls the publication back.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import EVIDENCE, LAYOUT, RECIPES, ROOT, canonical_json, load_json, rel, sha256  # noqa: E402
import search  # noqa: E402
import symbols  # noqa: E402
import tcc  # noqa: E402
import transaction  # noqa: E402

MARKER = "/*@body*/"


class PromotionError(RuntimeError):
    pass


def canonical_path(function: str, asm: bool = False) -> str:
    unit = symbols.atlas()[function]["segment"].split("_")[0].lower()
    return f"src/{unit}/{function}.{'asm' if asm else 'c'}"


def check_text(text: str, function: str, name: str | None, asm: bool = False) -> None:
    if asm:
        target = (name or function).lstrip("_")
        if not re.search(r"(?im)^\s*_?" + re.escape(target) + r"\s+proc\b", text):
            raise PromotionError(f"the assembly source does not define a PROC {target}")
        problems = search.lint_asm(text)
        if problems:
            raise PromotionError("lint: " + "; ".join(problems))
        return
    if text.count(MARKER) != 1:
        raise PromotionError(f"candidate needs exactly one {MARKER} marker before the function definition")
    body = text.split(MARKER, 1)[1]
    target = name or function
    if not re.search(r"\b" + re.escape(target.lstrip("_")) + r"\s*\(", body):
        raise PromotionError(f"the body after {MARKER} does not define {target}")
    problems = search.lint(text)
    if problems:
        raise PromotionError("lint: " + "; ".join(problems))


def verify(function: str, text: str, flags: list, profile: str | None, name: str | None,
           asm: bool = False) -> dict:
    out = search.run(text, function, flags=flags, profile=profile, name=name, fresh=True,
                     fresh_compile=True, worker="promote", note="promotion verification", asm=asm)
    equal = [e for e, v in out["results"].items() if v["status"] == "EQUAL"]
    out["equal"] = equal
    return out


def build_recipe(function, path, text, flags, profile, name, out) -> dict:
    entry = symbols.atlas()[function]
    eps = {}
    for e, v in out["results"].items():
        loc = entry["locations"][e]
        eps[e] = {"status": v["status"], "start": loc["start"], "offset": loc["offset"], "size": loc["size"],
                  "original_sha256": loc["sha256"]}
    return {
        "function": function, "unit": entry["segment"], "class": entry["class"], "source": path,
        "source_sha256": sha256(text.encode("latin-1")), "profile": profile, "flags": flags, "name": name,
        "per_episode_compile": bool(re.search(r"\bEPISODE\b", text)),
        "language": "asm" if path.endswith(".asm") else "c",
        "episodes": eps,
        "proven_under": {"context_key": out["context_key"],
                         "oracle_lock_sha256": sha256((LAYOUT / "oracle.lock.json").read_bytes()),
                         "atlas_sha256": sha256((EVIDENCE / "atlas.json").read_bytes()),
                         "emission_key": out.get("emission_key")},
    }


def promote(function: str, candidate: Path, profile: str | None, flags: list | None, name: str | None,
            receipt: Path | None, verify_only: bool, note: str | None) -> dict:
    if function not in symbols.atlas():
        raise PromotionError(f"unknown function {function}")
    raw = candidate.read_bytes()
    text = raw.decode("latin-1")
    asm = search.is_asm(candidate)
    check_text(text, function, name, asm)
    profiles_doc = load_json(LAYOUT / "profiles.json")
    profile = profile or (profiles_doc.get("default_asm", "tasm10-mx") if asm else profiles_doc["default"])
    flags = flags or tcc.profile_flags(profile)
    if receipt:
        rc = load_json(receipt)
        if rc.get("context_key") != search.context_key():
            raise PromotionError("stale receipt: proof context (oracle/atlas/symbols/profiles/tools) changed")
        if rc.get("source_sha256") != sha256(raw):
            raise PromotionError("stale receipt: candidate changed after the receipt was produced")
        if rc.get("function") != function:
            raise PromotionError("receipt is for a different function")
    out = verify(function, text, flags, profile, name, asm)
    if not out["equal"]:
        raise PromotionError(f"no episode is EQUAL: { {e: v['status'] for e, v in out['results'].items()} }")
    rpath = RECIPES / f"{function}.json"
    old = load_json(rpath) if rpath.exists() else None
    if old:
        lost = [e for e, v in old["episodes"].items() if v["status"] == "EQUAL" and e not in out["equal"]]
        if lost:
            raise PromotionError(f"regression: replacement loses proven episodes {lost}")
    summary = {"function": function, "equal": out["equal"],
               "results": {e: v["status"] for e, v in out["results"].items()}}
    if verify_only:
        summary["verify_only"] = True
        return summary
    path = canonical_path(function, asm) if not old else old["source"]
    import validate
    with transaction.exclusive(owner=f"promote {function}"):
        if candidate.read_bytes() != raw:
            raise PromotionError("candidate changed during verification; re-run")
        protected = validate.check_recipes(fresh=True)
        # the function being replaced is exempt: its new source was just verified fresh
        broken = [r for r in protected if not r["ok"] and r["function"] != function]
        if broken:
            raise PromotionError(f"canonical state does not validate; refusing to publish: {broken[:3]}")
        recipe = build_recipe(function, path, text, flags, profile, name, out)
        log_path = EVIDENCE / "promotions.jsonl"
        log = log_path.read_bytes() if log_path.exists() else b""
        entry = {"function": function, "episodes": out["equal"], "source_sha256": recipe["source_sha256"],
                 "recipe_sha256": sha256(canonical_json(recipe).encode()), "replaced": bool(old),
                 "at": time.strftime("%Y-%m-%dT%H:%M:%S"), "note": note}
        changes = {path: raw, rel(rpath): canonical_json(recipe).encode(),
                   "evidence/promotions.jsonl": log + (json.dumps(entry, sort_keys=True) + "\n").encode()}
        journal = transaction.prepare(changes)
        try:
            transaction.apply(journal)
            post = validate.prove_recipe(function, load_json(rpath), fresh=True)
            if not post["ok"]:
                raise PromotionError(f"post-publication proof failed: {post['problems']}")
            unit = symbols.atlas()[function]["segment"]
            broken = {u: eps for u, eps in validate.check_units({unit}).items()
                      if any(s not in ("EQUAL", "INCOMPLETE") for s in eps.values())}
            if broken:
                raise PromotionError(f"publication would break a complete translation unit: {broken}")
            transaction.finish()
        except BaseException:
            transaction.rollback(journal)
            raise
    try:
        import db
        db.rebuild(db.connect())
        _close_blockers([function], note)
    except Exception as exc:  # the database is advisory
        print(f"[db] rebuild skipped: {exc}")
    summary["published"] = [path, rel(rpath)]
    return summary


def _close_blockers(functions, note) -> None:
    """An accepted function has no open blocker: resolve the ones scoped to it."""
    import db
    con = db.connect()
    with db.tx(con):
        for f in functions:
            con.execute("UPDATE blockers SET status='RESOLVED', resolved=?, resolution=? "
                        "WHERE scope=? AND status='OPEN'",
                        (time.time(), f"accepted ({note or 'promotion'})", f))


def promote_batch(items: list, note: str | None, source_path: str | None = None) -> list:
    """items: [(function, candidate Path)].  Each candidate is verified fresh
    on its own; then ONE lock, ONE re-proof of all existing recipes, ONE
    journal for every file, a post-publication proof of each new recipe, and
    a rollback of the whole batch on any failure."""
    staged = []
    for function, candidate in items:
        raw = candidate.read_bytes()
        text = raw.decode("latin-1")
        asm = search.is_asm(candidate)
        rpath = RECIPES / f"{function}.json"
        old = load_json(rpath) if rpath.exists() else None
        cname = old.get("name") if old else None          # e.g. main: kept across replacements
        check_text(text, function, cname, asm)
        profiles_doc = load_json(LAYOUT / "profiles.json")
        profile = profiles_doc.get("default_asm", "tasm10-mx") if asm else profiles_doc["default"]
        flags = tcc.profile_flags(profile)
        out = verify(function, text, flags, profile, cname, asm)
        if not out["equal"]:
            raise PromotionError(f"{function}: no episode is EQUAL")
        if old:
            lost = [e for e, v in old["episodes"].items() if v["status"] == "EQUAL" and e not in out["equal"]]
            if lost:
                raise PromotionError(f"{function}: regression, loses {lost}")
        staged.append((function, candidate, raw, text, flags, profile, out, old))
    if len({f for f, *_ in staged}) != len(staged):
        raise PromotionError("a batch may contain each function once")
    import validate
    with transaction.exclusive(owner=f"promote batch of {len(staged)}"):
        for function, candidate, raw, *_ in staged:
            if candidate.read_bytes() != raw:
                raise PromotionError(f"{function}: candidate changed during verification")
        replaced = {f for f, *_ in staged}       # verified fresh above; their old proofs may not hold
        broken = [r for r in validate.check_recipes(fresh=True) if not r["ok"] and r["function"] not in replaced]
        if broken:
            raise PromotionError(f"canonical state does not validate; refusing to publish: {broken[:3]}")
        log_path = EVIDENCE / "promotions.jsonl"
        log = log_path.read_bytes() if log_path.exists() else b""
        changes = {}
        for function, candidate, raw, text, flags, profile, out, old in staged:
            path = source_path or (canonical_path(function, search.is_asm(candidate)) if not old else old["source"])
            if old and old["source"] != path:
                changes[old["source"]] = None          # the function moved into a shared module source
            recipe = build_recipe(function, path, text, flags, profile, old.get("name") if old else None, out)
            rpath = RECIPES / f"{function}.json"
            changes[path] = raw
            changes[rel(rpath)] = canonical_json(recipe).encode()
            entry = {"function": function, "episodes": out["equal"], "source_sha256": recipe["source_sha256"],
                     "recipe_sha256": sha256(canonical_json(recipe).encode()), "replaced": bool(old),
                     "at": time.strftime("%Y-%m-%dT%H:%M:%S"), "note": note}
            log += (json.dumps(entry, sort_keys=True) + "\n").encode()
        changes["evidence/promotions.jsonl"] = log
        journal = transaction.prepare(changes)
        try:
            transaction.apply(journal)
            post = validate.check_recipes(fresh=True, only={f for f, *_ in staged})
            bad = [r for r in post if not r["ok"]]
            if bad:
                raise PromotionError(f"post-publication proof failed: {bad}")
            touched = {symbols.atlas()[f]["segment"] for f, *_ in staged}
            broken = {u: eps for u, eps in validate.check_units(touched).items()
                      if any(s not in ("EQUAL", "INCOMPLETE") for s in eps.values())}
            if broken:
                raise PromotionError(f"publication would break a complete translation unit: {broken}")
            transaction.finish()
        except BaseException:
            transaction.rollback(journal)
            raise
    try:
        import db
        db.rebuild(db.connect())
        _close_blockers([f for f, *_ in staged], note)
    except Exception as exc:
        print(f"[db] rebuild skipped: {exc}")
    return [{"function": f, "equal": out["equal"]} for f, _, _, _, _, _, out, _ in staged]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("function", nargs="?")
    ap.add_argument("candidate", nargs="?")
    ap.add_argument("--profile")
    ap.add_argument("--flags", nargs="+")
    ap.add_argument("--name")
    ap.add_argument("--receipt")
    ap.add_argument("--verify-only", action="store_true")
    ap.add_argument("--note")
    ap.add_argument("--recover", action="store_true")
    ap.add_argument("--batch", help="file with lines 'FUNCTION CANDIDATE'")
    ap.add_argument("--source-path", help="with --batch: publish every candidate as this one shared source "
                                          "(e.g. a whole assembly module); the functions' old sources are removed")
    a = ap.parse_args()
    if a.recover:
        print("rolled back:", transaction.recover())
        return 0
    if a.batch:
        items = []
        for line in Path(a.batch).read_text().splitlines():
            if line.strip() and not line.startswith("#"):
                fn, cand = line.split()
                items.append((fn, Path(cand)))
        try:
            res = promote_batch(items, a.note, a.source_path)
        except (PromotionError, transaction.Conflict, transaction.LockBusy) as exc:
            print(f"BATCH PROMOTION REFUSED: {exc}")
            return 1
        print(json.dumps(res, indent=1))
        return 0
    if not a.function or not a.candidate:
        ap.error("FUNCTION and CANDIDATE are required")
    try:
        res = promote(a.function, Path(a.candidate), a.profile, a.flags, a.name,
                      Path(a.receipt) if a.receipt else None, a.verify_only, a.note)
    except (PromotionError, transaction.Conflict, transaction.LockBusy) as exc:
        print(f"PROMOTION REFUSED: {exc}")
        return 1
    print(json.dumps(res, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
