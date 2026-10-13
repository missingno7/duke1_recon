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
of the whole unit.

    python tools/tubuild.py G2_TEXT --data [--data-plan PLAN.json]

--data additionally checks the unit's initialised data.  Data fragments
(definitions of initialised globals, src/<unit>/data/*.c) are inserted between
function bodies at the positions recorded in layout/unit-data.json, because
Turbo C places a unit's initialised globals first in its _DATA (definition
order) and then every string literal in order of appearance (rule
DATA-LAYOUT): where a table is defined decides where its strings land.  The
unit's _DATA must equal the original DGROUP range recorded for the unit byte
for byte; every fixup in it must bind (far pointers to the unit's own data at
the right DGROUP offset, externals through tools/symbols.py) and the set of
segment words must equal the original MZ relocations in that range.  A single
trailing zero byte of the range is accepted as segment alignment padding.
--data-plan replaces the registry entry (workers test placements read-only).
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

# a stub definition `T f(params) {...}`; params may nest one level of
# parentheses (function-pointer parameters: `void (far *fn)(void)`)
STUB = re.compile(r"(?ms)^([^\n;{}#]*\b(?:g[12]|asm)_[0-9a-f]{4}\s*\((?:[^()]|\([^()]*\))*\))\s*\{[^{}]*\}")
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


def c_name(fid: str) -> str:
    """The C name a function is defined under (recipe "name", e.g. main), else its logical id."""
    rp = RECIPES / f"{fid}.json"
    return (load_json(rp).get("name") or fid) if rp.exists() else fid


def data_plan(unit: str, plan=None) -> dict | None:
    """The unit's data plan: a dict, a JSON file, or the layout/unit-data.json entry."""
    if isinstance(plan, dict):
        return plan
    if plan is not None:
        return load_json(Path(plan))
    reg = LAYOUT / "unit-data.json"
    return load_json(reg).get(unit) if reg.exists() else None


def assemble(unit: str, ep: str, override: Path | None = None, plan: dict | None = None) -> dict:
    order = unit_functions(unit, ep)
    frags = {}
    for fr in (plan or {}).get("fragments", []):
        frags.setdefault(fr["before"], []).append(ROOT / fr["file"])
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

    def fragments(key):
        nonlocal episode_dependent
        out = ""
        for f in frags.get(key, []):
            src = f.read_text("latin-1")
            episode_dependent |= "EPISODE" in src
            out += f"/* data: {f.name} */\n{src.strip()}\n\n"
        return out
    text += fragments("start")
    for fid, body in bodies:
        text += fragments(fid)
        text += f"/* {fid} */\n{body}\n\n"
    text += fragments("end")
    return {"order": order, "missing": missing, "source": text, "conflicts": conflicts,
            "episode_dependent": episode_dependent}


def check_asm_unit(ep: str, source: Path | None = None) -> dict:
    """The assembly unit (ASM_TEXT) is ONE module (layout/asm-unit.json): its
    code segment, data tables in it included, must equal the original range
    byte for byte; own-segment offsets bind relative to the unit's position in
    _TEXT, externals through tools/symbols.py, segment words to the original
    MZ relocations; and every procedure must be EQUAL on its own."""
    import struct
    import oracle
    reg = load_json(LAYOUT / "asm-unit.json") if (LAYOUT / "asm-unit.json").exists() else {}
    src = Path(source) if source else (ROOT / reg["source"] if reg.get("source") else None)
    out = {"unit": "ASM_TEXT", "episode": ep}
    if src is None or not src.exists():
        out["status"] = "INCOMPLETE"
        return out
    rec = tcc.assemble(src.read_text("latin-1"), ["/MX"])
    if not rec.ok:
        out["status"] = "ASSEMBLY_ERROR"
        out["log"] = rec.log.strip().splitlines()[-12:]
        return out
    module = omf.OmfReader().read(rec.obj)
    seg = next(s["name"] for s in module.segment_defs if s["class"] == "CODE")
    code = module.segments[seg]
    census = symbols.census(ep)
    useg = next(s for s in census["segments"] if s["name"] == "ASM_TEXT")
    frame = 0                                  # the unit's _TEXT combines with C0's: frame 0
    base = useg["start"] - (frame << 4)        # offset of the unit inside that frame
    img, relocs = oracle.load_image(ep)
    orig = img[useg["start"]:useg["start"] + useg["size"]]
    out["bytes"] = [len(code), len(orig)]
    if len(code) != len(orig):
        out["status"] = "LENGTH_MISMATCH"
        return out
    errors, covered, segwords = [], set(), set()
    for fx in module.linker_fixups:
        if fx["segment"] != seg:
            continue
        at, loc = fx["offset"], fx["loc"]
        addend = (fx["displacement"] + int.from_bytes(code[at:at + 2], "little")) & 0xFFFF
        got = struct.unpack_from("<H", orig, at)[0]
        try:
            if fx["target_kind"] == "segment" and fx["target"] == seg:
                exp_off, exp_seg = (base + addend) & 0xFFFF, frame
            elif fx["target_kind"] == "external":
                t = symbols.resolve(fx["target"], ep)
                if t["kind"] == "data":
                    exp_off, exp_seg = (t["dgroup_offset"] + addend) & 0xFFFF, census["dgroup_frame"]
                else:
                    exp_off, exp_seg = (t["offset"] + addend) & 0xFFFF, t["frame"]
            elif fx["target_kind"] in ("segment", "group") and fx["target"] in ("_DATA", "DGROUP", "_BSS"):
                exp_off, exp_seg = None, census["dgroup_frame"]
            else:
                raise symbols.SymbolError(f"unsupported target {fx['target_kind']} {fx['target']}")
        except symbols.SymbolError as exc:
            errors.append(f"+{at:#x} {fx['target']}: {exc}")
            continue
        if loc == "offset16":
            if exp_off is None or got != exp_off:
                errors.append(f"+{at:#x} offset {fx['target']}+{addend:#x}: original {got:#06x}, binding {exp_off}")
                continue
            covered.update(range(at, at + 2))
        elif loc == "base16":
            if got != exp_seg:
                errors.append(f"+{at:#x} segment {fx['target']}: original {got:#06x}, binding {exp_seg:#06x}")
                continue
            covered.update(range(at, at + 2))
            segwords.add(at)
        elif loc == "pointer32":
            gs = struct.unpack_from("<H", orig, at + 2)[0]
            if (got, gs) != (exp_off, exp_seg):
                errors.append(f"+{at:#x} far {fx['target']}: original {gs:04X}:{got:04X}")
                continue
            covered.update(range(at, at + 4))
            segwords.add(at + 2)
        else:
            errors.append(f"+{at:#x} unsupported fixup location {loc}")
    diffs = [i for i in range(len(code)) if i not in covered and code[i] != orig[i]]
    orig_relocs = {(s << 4) + o - useg["start"] for s, o in relocs}
    orig_relocs = {r for r in orig_relocs if 0 <= r < len(orig)}
    if orig_relocs != segwords:
        errors.append(f"relocation set differs: missing {sorted(orig_relocs - segwords)[:6]}, extra {sorted(segwords - orig_relocs)[:6]}")
    fails = []
    for fid in unit_functions("ASM_TEXT", ep):
        res = compare.compare_object(rec.obj, fid, ep)
        if res.status != "EQUAL":
            fails.append(f"{fid}: {res.status} {res.detail[:2]}")
    out.update({"binding_errors": errors[:12], "differing_bytes": len(diffs),
                "first_diff": hex(diffs[0]) if diffs else None, "function_failures": fails})
    out["status"] = "EQUAL" if not errors and not diffs and not fails else "DIFFER"
    return out


def check(unit: str, ep: str, write: Path | None = None, override: Path | None = None,
          plan=None, data: bool = False, allow_incomplete: bool = False) -> dict:
    if unit == "ASM_TEXT":
        return check_asm_unit(ep, override)
    plan = data_plan(unit, plan)
    a = assemble(unit, ep, override, plan)
    out = {"unit": unit, "episode": ep, "functions": len(a["order"]), "missing": a["missing"],
           "declaration_conflicts": a["conflicts"]}
    if write:
        write.parent.mkdir(parents=True, exist_ok=True)
        write.write_text(a["source"], encoding="latin-1")
    if a["missing"] and not (allow_incomplete and data):
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
    own_base = None
    if data:
        out["data"] = check_data(module, ep, plan) if plan else {"status": "NO_PLAN"}
        if out["data"]["status"] == "EQUAL":
            # the unit's _DATA is the original range: own-data references bind to it
            own_base = {"_DATA": int(plan["data_segment_range"][ep][0], 16)}
        if plan and plan.get("bss_range"):
            out["bss"] = check_bss(module, ep, plan)
            if out["bss"]["status"] == "EQUAL":
                own_base = dict(own_base or {}, _BSS=int(plan["bss_range"][ep][0], 16))
    if a["missing"]:
        # diagnostic only: the data of an incomplete unit (its missing functions'
        # literals are absent), no code verdict
        out["status"] = "INCOMPLETE_DATA_DIAGNOSTIC"
        return out
    for fid in a["order"]:
        loc = symbols.atlas()[fid]["locations"][ep]
        rel = loc["start"] - useg["start"]
        cname = c_name(fid)
        if pubs.get(cname) != rel:
            layout.append(f"{fid}: unit offset {pubs.get(cname)} vs original {rel}")
            continue
        res = compare.compare_object(rec.obj, fid, ep, name=cname if cname != fid else None,
                                     own_data_base=own_base)
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


def check_data(module, ep: str, plan: dict) -> dict:
    """The unit's _DATA against the original DGROUP range [start, end) of the
    plan: identical bytes outside fixups, every fixup bound, relocation set
    equal.  One trailing zero byte of the range may be alignment padding."""
    import struct
    import oracle
    start, end = (int(x, 16) for x in plan["data_segment_range"][ep])
    data = module.segments.get("_DATA", b"")
    img, relocs = oracle.load_image(ep)
    c = symbols.census(ep)
    frame = c["dgroup_frame"]
    base = frame << 4
    orig = img[base + start:base + end]
    out = {"range": [hex(start), hex(end)], "bytes": [len(data), len(orig)]}
    pad = 0
    if len(data) == len(orig) - 1 and orig[-1] == 0 and end % 2 == 0:
        pad = 1
    elif len(data) != len(orig):
        out["status"] = "LENGTH_MISMATCH"
        n = min(len(data), len(orig))
        out["first_diff"] = next((hex(start + i) for i in range(n) if data[i] != orig[i]), hex(start + n))
        return out
    errors, covered, segwords = [], set(), set()
    for fx in module.linker_fixups:
        if fx["segment"] != "_DATA":
            continue
        at, width, loc = fx["offset"], fx["width"], fx["loc"]
        emb = int.from_bytes(data[at:at + 2], "little")
        addend = (fx["displacement"] + emb) & 0xFFFF
        tkind, tname = fx["target_kind"], fx["target"]
        got_off = struct.unpack_from("<H", orig, at)[0]
        try:
            if tkind == "segment" and tname in ("_DATA", "DGROUP"):
                exp_off, exp_seg = (start + addend) & 0xFFFF, frame
            elif tkind == "external":
                tgt = symbols.resolve(tname, ep)
                if tgt["kind"] == "data":
                    exp_off, exp_seg = (tgt["dgroup_offset"] + addend) & 0xFFFF, frame
                elif tgt["kind"] in ("function", "library", "startup"):
                    exp_off, exp_seg = (tgt["offset"] + addend) & 0xFFFF, tgt["frame"]
                else:
                    raise symbols.SymbolError(f"unsupported external kind {tgt['kind']}")
            else:
                raise symbols.SymbolError(f"unsupported target {tkind} {tname}")
        except symbols.SymbolError as exc:
            errors.append(f"{hex(start + at)} {loc} -> {tname}: {exc}")
            continue
        if loc == "pointer32":
            got_seg = struct.unpack_from("<H", orig, at + 2)[0]
            if (got_off, got_seg) != (exp_off, exp_seg):
                errors.append(f"{hex(start + at)} far {tname}+{addend:#x}: original {got_seg:04X}:{got_off:04X}, "
                              f"binding {exp_seg:04X}:{exp_off:04X}")
                continue
            segwords.add(at + 2)
        elif loc == "offset16":
            if got_off != exp_off:
                errors.append(f"{hex(start + at)} near {tname}+{addend:#x}: original {got_off:04X}, binding {exp_off:04X}")
                continue
        elif loc == "base16":
            if got_off != exp_seg:
                errors.append(f"{hex(start + at)} segment {tname}: original {got_off:04X}, binding {exp_seg:04X}")
                continue
            segwords.add(at)
        else:
            errors.append(f"{hex(start + at)} unsupported fixup location {loc}")
            continue
        covered.update(range(at, at + width))
    diffs = [i for i in range(len(data)) if i not in covered and data[i] != orig[i]]
    orig_relocs = {(s << 4) + o - base - start for s, o in relocs}
    orig_relocs = {r for r in orig_relocs if 0 <= r < len(orig)}
    if orig_relocs != segwords:
        errors.append(f"relocation set differs: missing {sorted(hex(start + r) for r in orig_relocs - segwords)[:6]}, "
                      f"extra {sorted(hex(start + r) for r in segwords - orig_relocs)[:6]}")
    out.update({"fixups_bound": len(covered) // 2, "binding_errors": errors[:12], "differing_bytes": len(diffs),
                "first_diff": hex(start + diffs[0]) if diffs else None, "alignment_pad": pad})
    out["status"] = "EQUAL" if not errors and not diffs else "DIFFER"
    return out


def check_bss(module, ep: str, plan: dict) -> dict:
    """The unit's _BSS against the original range [start, end) of the plan:
    its length (one trailing alignment byte allowed) and the offset of every
    global it defines (PUBDEF in _BSS) must put that global exactly at the
    DGROUP offset its name is bound to in this episode.  BSS holds no bytes, so
    length plus symbol placement is the whole layout."""
    start, end = (int(x, 16) for x in plan["bss_range"][ep])
    length = module.segment_lengths.get("_BSS", 0)
    out = {"range": [hex(start), hex(end)], "bytes": [length, end - start]}
    pad = 1 if length == end - start - 1 else 0
    errors, defined = [], 0
    for p in module.publics:
        if p["segment"] != "_BSS":
            continue
        name = symbols.norm(p["name"])
        try:
            t = symbols.resolve(name, ep)
        except symbols.SymbolError as exc:
            errors.append(f"{name}: {exc}")
            continue
        defined += 1
        if t["kind"] != "data" or t["dgroup_offset"] != start + p["offset"]:
            errors.append(f"{name} at _BSS+{p['offset']:#x} = {start + p['offset']:#06x}, "
                          f"bound to {t.get('dgroup_offset', 0):#06x}")
    if length != end - start and not pad:
        errors.insert(0, f"_BSS is {length} bytes, the range {end - start}")
    out.update({"defined_globals": defined, "errors": errors[:12], "alignment_pad": pad,
                "status": "EQUAL" if not errors and defined else ("NO_DEFINITIONS" if not defined else "DIFFER")})
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
    ap.add_argument("--data", action="store_true", help="also check the unit's initialised data")
    ap.add_argument("--data-plan", help="JSON data plan replacing the layout/unit-data.json entry")
    ap.add_argument("--allow-incomplete", action="store_true",
                    help="with --data: check the data of a unit with missing functions (diagnostic, never a proof)")
    a = ap.parse_args()
    eps = [a.episode] if a.episode else ["dn1", "dn2", "dn3"]
    rc = 0
    for ep in eps:
        res = check(a.unit, ep, Path(a.write.replace("{ep}", ep)) if a.write else None,
                    Path(a.override) if a.override else None, plan=a.data_plan, data=a.data,
                    allow_incomplete=a.allow_incomplete)
        atomic_json(BUILD / "tu" / f"{a.unit}-{ep}.json", res)
        if a.unit == "ASM_TEXT":
            print(f"{a.unit} {ep}: {res['status']}  " + str({k: v for k, v in res.items() if k not in ('unit', 'episode', 'status')}))
            rc |= res["status"] != "EQUAL"
            continue
        print(f"{a.unit} {ep}: {res['status']}  functions {res['functions']}, missing {len(res['missing'])}")
        if res.get("literal_pool"):
            print(f"   literal pool: {res['literal_pool']}")
        if "data" in res:
            print(f"   data: {res['data']}")
        if "bss" in res:
            print(f"   bss: {res['bss']}")
        for k in ("declaration_conflicts", "layout_mismatches", "function_failures", "log"):
            for x in res.get(k, [])[:8]:
                print(f"   {k}: {x}")
        rc |= res["status"] != "EQUAL" or (a.data and res.get("data", {}).get("status") != "EQUAL")
    return rc


if __name__ == "__main__":
    sys.exit(main())
