"""Declaration consistency across accepted sources.

    python tools/decls.py            report conflicting views of functions and globals
    python tools/decls.py --json     machine-readable (written to build/decls.json too)

Workers declare callees and globals locally (before /*@body*/).  A
translation-unit build needs exactly one prototype per function and one type
per global, so every accepted file's view is collected and compared:
function views come from definitions (the body) and from declarations/stubs
in other files; global views from `extern` declarations.  Parameter names are
ignored; return type, calling convention and parameter types are compared.
This is a light regex parser for the declaration forms the project uses.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, RECIPES, ROOT, atomic_json, load_json  # noqa: E402

FN = re.compile(r"(?m)^\s*(?:extern\s+)?(?P<ret>[A-Za-z_][\w \t\*]*?)\s*\b(?P<conv>pascal\s+|cdecl\s+|interrupt\s+)?"
                r"(?P<name>(?:g[12]|asm)_[0-9a-f]{4})\s*\((?P<params>[^)]*)\)\s*(?P<tail>;|\{)")
DATA = re.compile(r"(?m)^\s*extern\s+(?P<type>[\w \t\*]+?)\s*\b(?P<name>d_(?:dn[123]_)?[0-9a-f]{4})\s*(?P<arr>\[[^\]]*\])?\s*;")


def norm_type(t: str) -> str:
    t = re.sub(r"\s+", " ", t.replace("*", " * ")).strip()
    return re.sub(r"\s*\*\s*", "*", t)


def norm_params(p: str) -> str:
    p = p.strip()
    if p in ("", "void"):
        return "void"
    out = []
    for part in p.split(","):
        part = re.sub(r"\bregister\b", "", part).strip()
        part = re.sub(r"\s*\b[A-Za-z_]\w*\s*$", "", part) if re.search(r"[\w\*]\s+[A-Za-z_]\w*\s*$", part) \
            or re.search(r"\*\s*[A-Za-z_]\w*\s*$", part) else part
        out.append(norm_type(part))
    return ", ".join(out)


def collect() -> dict:
    fviews = defaultdict(list)
    dviews = defaultdict(list)
    for rp in sorted(RECIPES.glob("*.json")):
        r = load_json(rp)
        if r.get("language") == "asm":
            continue
        raw = (ROOT / r["source"]).read_text("latin-1")
        prelude, body = raw.split("/*@body*/", 1)
        prelude = re.sub(r"/\*.*?\*/", "", prelude, flags=re.S)
        body = re.sub(r"/\*.*?\*/", "", body, flags=re.S)
        # declarations and stubs only before the marker; from the body only
        # the target's own definition header (statements are not declarations)
        defn = [m for m in FN.finditer(body) if m.group("name") == r["function"] and m.group("tail") == "{"][:1]
        for m in list(FN.finditer(prelude)) + defn:
            ret = norm_type(re.sub(r"\b(static|far|extern)\b", "", m.group("ret")))
            kind = "definition" if m in defn else ("stub" if m.group("tail") == "{" else "declaration")
            fviews[m.group("name")].append({"file": r["source"], "kind": kind, "ret": ret,
                                            "conv": (m.group("conv") or "").strip() or "cdecl",
                                            "params": norm_params(m.group("params"))})
        for m in DATA.finditer(prelude):
            dviews[m.group("name")].append({"file": r["source"], "type": norm_type(m.group("type")),
                                            "array": bool(m.group("arr"))})
    return {"functions": fviews, "data": dviews}


def _unit(v: dict) -> str:
    return v["file"].split("/")[1] if v["file"].startswith("src/") else "?"


def conflicts(views: dict) -> dict:
    """Conflicting views inside one translation unit (a unit has one declaration
    per name).  Differences between G1 and G2 are legal C and occur in the
    original (d_9682: int in G1, char in G2); they are listed under cross_unit."""
    out = {"functions": {}, "data": {}, "cross_unit": {}}
    for kind, key in (("functions", lambda v: (v["ret"], v["conv"], v["params"])),
                      ("data", lambda v: (v["type"], v["array"]))):
        for name, vs in views[kind].items():
            units = defaultdict(set)
            for v in vs:
                units[_unit(v)].add(key(v))
            bad = [v for v in vs if len(units[_unit(v)]) > 1]
            if bad:
                out[kind][name] = bad
            elif len(set().union(*units.values())) > 1:
                out["cross_unit"][name] = vs
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    views = collect()
    c = conflicts(views)
    doc = {"functions_seen": len(views["functions"]), "globals_seen": len(views["data"]), "conflicts": c}
    atomic_json(BUILD / "decls.json", doc)
    if a.json:
        print(json.dumps(doc, indent=1))
        return 0
    print(f"{doc['functions_seen']} functions and {doc['globals_seen']} globals declared across accepted sources")
    for name, vs in sorted(c["functions"].items()):
        print(f"  CONFLICT {name}:")
        for v in vs:
            print(f"     {v['kind']:11s} {v['conv']:6s} {v['ret']} ({v['params']})   {v['file']}")
    for name, vs in sorted(c["data"].items()):
        print(f"  CONFLICT {name}: " + "; ".join(f"{v['type']}{'[]' if v['array'] else ''} in {v['file']}" for v in vs))
    if not c["functions"] and not c["data"]:
        print("  no conflicting views inside a unit")
    for name, vs in sorted(c["cross_unit"].items()):
        print(f"  cross-unit {name}: " + "; ".join(sorted({f"{v.get('type') or v.get('params')} in {_unit(v)}" for v in vs})))
    return 0


if __name__ == "__main__":
    sys.exit(main())
