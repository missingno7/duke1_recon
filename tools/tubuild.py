"""Translation-unit build: compile a whole unit from accepted function sources.

    python tools/tubuild.py G2_TEXT [--episode dn1] [--write build/tu/G2-{ep}.C] [--override DIR]

--override DIR uses DIR/FUNCTION.c instead of the accepted source where present
(workers test consolidated declarations without touching canonical files).

The unit source is assembled in original function order (per episode):
declarations from every accepted file's prelude (stub definitions become
prototypes, identical declarations and struct definitions are emitted once,
conflicting ones are reported), then every body.  The result is compiled once
and checked:

  * every function is EQUAL when compared out of the unit object;
  * every function's offset inside the unit's code segment equals its
    original offset relative to the segment start;
  * the code segment length equals the original segment length.

Together this proves function order, intra-unit call forms and code layout
of the whole unit.  Data (_DATA contents and placement) is NOT proven here.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, LAYOUT, RECIPES, ROOT, atomic_json, load_json  # noqa: E402
import compare  # noqa: E402
import omf  # noqa: E402
import symbols  # noqa: E402
import tcc  # noqa: E402

STUB = re.compile(r"(?ms)^([^\n;{}#]*\b(?:g[12]|asm)_[0-9a-f]{4}\s*\([^)]*\))\s*\{[^{}]*\}")
STRUCT = re.compile(r"(?ms)^\s*(?:typedef\s+)?struct\s+(\w+)\s*\{.*?\}\s*\w*\s*;")


def unit_functions(unit: str, ep: str) -> list:
    fs = [(f["locations"][ep]["start"], fid) for fid, f in symbols.atlas().items()
          if f["segment"] == unit and ep in f["locations"]]
    return [fid for _, fid in sorted(fs)]


def split(path: Path) -> tuple:
    text = path.read_text("latin-1")
    if "/*@body*/" not in text:
        raise ValueError(f"{path} has no /*@body*/ marker")
    pre, body = text.split("/*@body*/", 1)
    return pre, body


def assemble(unit: str, ep: str, override: Path | None = None) -> dict:
    order = unit_functions(unit, ep)
    def source_of(f):
        if override and (override / f"{f}.c").exists():
            return override / f"{f}.c"
        if (RECIPES / f"{f}.json").exists():
            return ROOT / load_json(RECIPES / f"{f}.json")["source"]
        return None
    missing = [f for f in order if source_of(f) is None]
    decls, seen_lines, structs, conflicts = [], set(), {}, []
    bodies = []
    episode_dependent = False
    for fid in order:
        if fid in missing:
            continue
        pre, body = split(source_of(fid))
        episode_dependent |= "EPISODE" in pre + body
        pre = re.sub(r"/\*.*?\*/", "", pre, flags=re.S)
        for m in STRUCT.finditer(pre):
            tag, txt = m.group(1), re.sub(r"\s+", " ", m.group(0)).strip()
            if tag in structs and structs[tag] != txt:
                conflicts.append(f"struct {tag}: {structs[tag]}  vs  {txt}  ({fid})")
            structs.setdefault(tag, txt)
        pre = STRUCT.sub("", pre)
        pre = STUB.sub(lambda m: m.group(1).strip() + ";", pre)
        for line in pre.splitlines():
            key = re.sub(r"\s+", " ", line).strip()
            if key and key not in seen_lines:
                seen_lines.add(key)
                decls.append(line.rstrip())
        bodies.append((fid, body.strip("\n")))
    includes = [d for d in decls if d.lstrip().startswith("#")]
    others = [d for d in decls if not d.lstrip().startswith("#")]
    text = "\n".join(includes + list(structs.values()) + others) + "\n\n"
    for fid, body in bodies:
        text += f"/* {fid} */\n{body}\n\n"
    return {"order": order, "missing": missing, "source": text, "conflicts": conflicts,
            "episode_dependent": episode_dependent}


def check(unit: str, ep: str, write: Path | None = None, override: Path | None = None) -> dict:
    a = assemble(unit, ep, override)
    out = {"unit": unit, "episode": ep, "functions": len(a["order"]), "missing": a["missing"],
           "declaration_conflicts": a["conflicts"]}
    if write:
        write.parent.mkdir(parents=True, exist_ok=True)
        write.write_text(a["source"], encoding="latin-1")
    if a["missing"]:
        out["status"] = "INCOMPLETE"
        return out
    profile = load_json(LAYOUT / "profiles.json")["default"]
    flags = tcc.profile_flags(profile) + ([f"-DEPISODE={ep[-1]}"] if a["episode_dependent"] else [])
    rec = tcc.compile_c(a["source"], flags)
    if not rec.ok:
        out["status"] = "COMPILE_ERROR"
        out["log"] = rec.log.strip().splitlines()[-12:]
        return out
    module = omf.OmfReader().read(rec.obj)
    seg = next(s["name"] for s in module.segment_defs if s["class"] == "CODE")
    seg_len = module.segment_lengths[seg]
    census = symbols.census(ep)
    useg = next(s for s in census["segments"] if s["name"] == unit)
    pubs = {symbols.norm(p["name"]): p["offset"] for p in module.publics if p["segment"] == seg}
    bad, layout = [], []
    static_bases = {}      # unit-local statics (unit_static bindings) must share one base per segment
    for fid in a["order"]:
        loc = symbols.atlas()[fid]["locations"][ep]
        rel = loc["start"] - useg["start"]
        if pubs.get(fid) != rel:
            layout.append(f"{fid}: unit offset {pubs.get(fid)} vs original {rel}")
            continue
        res = compare.compare_object(rec.obj, fid, ep)
        if res.status != "EQUAL":
            bad.append(f"{fid}: {res.status} {res.detail[:2]}")
        for b in res.bound:
            if b["kind"] == "unit_static":
                static_bases.setdefault(b["segment"], set()).add((b["dgroup_offset"] - b["offset"]) & 0xFFFF)
    for segname, bases in static_bases.items():
        if len(bases) > 1:
            bad.append(f"unit statics in {segname} bind with inconsistent bases {sorted(map(hex, bases))}")
    out.update({"segment_length": [seg_len, useg["size"]], "layout_mismatches": layout, "function_failures": bad,
                "unit_static_bases": {k: sorted(v) for k, v in static_bases.items()}})
    out["status"] = "EQUAL" if not bad and not layout and seg_len == useg["size"] else "DIFFER"
    out["literal_pool"] = literal_pool(module, ep)
    return out


def literal_pool(module, ep: str) -> dict:
    """With every global still extern, the unit's _DATA is exactly its string
    literal pool (rule DATA-LAYOUT: literals follow the initialised globals
    at the end of the unit's _DATA).  Locate it in the original DGROUP: it
    must occur, byte for byte, exactly once."""
    import oracle
    data = module.segments.get("_DATA", b"")
    if not data:
        return {"status": "EMPTY"}
    img, _ = oracle.load_image(ep)
    c = symbols.census(ep)
    base = c["dgroup_frame"] << 4
    dg = img[base:base + c["startup"]["bss_start"]]
    hits = []
    at = dg.find(data)
    while at != -1:
        hits.append(at)
        at = dg.find(data, at + 1)
    return {"status": "EQUAL" if len(hits) == 1 else ("AMBIGUOUS" if hits else "NOT_FOUND"),
            "bytes": len(data), "dgroup_offset": hits[0] if len(hits) == 1 else None}


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("unit")
    ap.add_argument("--episode", default=None)
    ap.add_argument("--write")
    ap.add_argument("--override", help="directory of FUNCTION.c files that replace accepted sources (read-only use)")
    a = ap.parse_args()
    eps = [a.episode] if a.episode else ["dn1", "dn2", "dn3"]
    rc = 0
    for ep in eps:
        res = check(a.unit, ep, Path(a.write.replace("{ep}", ep)) if a.write else None,
                    Path(a.override) if a.override else None)
        atomic_json(BUILD / "tu" / f"{a.unit}-{ep}.json", res)
        print(f"{a.unit} {ep}: {res['status']}  functions {res['functions']}, missing {len(res['missing'])}")
        if res.get("literal_pool"):
            print(f"   literal pool: {res['literal_pool']}")
        for k in ("declaration_conflicts", "layout_mismatches", "function_failures", "log"):
            for x in res.get(k, [])[:8]:
                print(f"   {k}: {x}")
        rc |= res["status"] != "EQUAL"
    return rc


if __name__ == "__main__":
    sys.exit(main())
