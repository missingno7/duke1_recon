"""Translation-unit evidence and the production object plan.

    python tools/tu.py            write evidence/tu-structure.json and layout/production-plan.json
    python tools/tu.py --check    fail if either is out of date

Uses rule CALL-FORMS: inside one Turbo C unit, a call to an earlier-defined
function is 'push cs; call near'; a forward call is a relocated far call to a
public function, or 'push cs; call near' to a static one.  Hence per callee:
  forward far call seen        -> PUBLIC (not static)
  forward push-cs near seen    -> STATIC
  both                         -> CONTRADICTION (would mean the segment is not one unit)
  backward far call seen       -> CONTRADICTION
and per segment a check that the call-form evidence is consistent with one
translation unit.
"""
from __future__ import annotations

import argparse
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import EPISODES, EVIDENCE, LAYOUT, atomic_json, canonical_json, load_json  # noqa: E402
import symbols  # noqa: E402

OUT = EVIDENCE / "tu-structure.json"
PLAN = LAYOUT / "production-plan.json"


def build() -> dict:
    units = {}
    storage = {}
    for ep in EPISODES:
        c = symbols.census(ep)
        segs = {s["name"]: s for s in c["segments"] if s["kind"] == "game"}
        fns = {f["start"]: f for f in c["functions"] if f["segment"] in segs}
        for sname, s in segs.items():
            u = units.setdefault(sname, {"episodes": {}})
            stats = defaultdict(int)
            for f in fns.values():
                if f["segment"] != sname:
                    continue
                for cl in f["calls"]:
                    t = cl.get("target")
                    if t is None or t not in fns or fns[t]["segment"] != sname:
                        continue
                    fwd = t > f["start"]
                    kind = cl["kind"]
                    if kind == "far":
                        stats["forward_far" if fwd else "backward_far"] += 1
                    elif kind == "pushcs_near":
                        stats["forward_pushcs" if fwd else "backward_pushcs"] += 1
                    elif kind == "fnptr_cs":
                        stats["fnptr_cs"] += 1
                    callee = symbols.function_at(ep, t)
                    ev = storage.setdefault(callee, defaultdict(set))
                    if fwd and kind == "far":
                        ev["forward_far"].add(ep)
                    elif fwd and kind == "pushcs_near":
                        ev["forward_pushcs"].add(ep)
                    elif not fwd and kind == "far":
                        ev["backward_far"].add(ep)
            stats = dict(stats)
            stats["one_unit_consistent"] = stats.get("backward_far", 0) == 0
            u["episodes"][ep] = {"start": s["start"], "size": s["size"], "frame": s["frame"],
                                 "functions": sum(1 for f in fns.values() if f["segment"] == sname),
                                 "call_forms": stats}
    fn_class = {}
    for fid in sorted(storage):
        ev = storage[fid]
        far, near, back = ev.get("forward_far", set()), ev.get("forward_pushcs", set()), ev.get("backward_far", set())
        if back or (far and near):
            cls = "CONTRADICTION"
        elif near:
            cls = "STATIC"
        elif far:
            cls = "PUBLIC"
        else:
            cls = "UNDETERMINED"
        fn_class[fid] = {"storage": cls, "episodes": sorted(far | near | back)}
    counts = defaultdict(int)
    for v in fn_class.values():
        counts[v["storage"]] += 1
    return {"generated_by": "tools/tu.py (rule CALL-FORMS)", "units": units,
            "storage_class_evidence": fn_class, "storage_counts": dict(counts),
            "note": "Functions only ever called backward (or not at all) are UNDETERMINED: both storage classes "
                    "compile identically for them."}


def production_plan() -> dict:
    """The explicit object plan for the natural historical link.  Structure
    only (no acceptance counts; those live in docs/progress.md)."""
    atlas = load_json(EVIDENCE / "atlas.json")["functions"]
    c = symbols.census("dn1")
    order = {}
    for f in atlas:
        order.setdefault(f["segment"], []).append(f["id"])
    lib = [h["module"] for h in c["library_modules"]]
    return {
        "status": "PLAN: no object below has been linked yet",
        "linker": {"tool": "BIN/TLINK.EXE (2.0)", "options": ["/c", "/d", "/s"], "library": "LIB/CL.LIB",
                   "options_status": "HYPOTHESIS (external Duke1Decomp BUILD.BAT); untested"},
        "objects": [
            {"id": "C0", "kind": "asm", "assembler": "BIN/TASM.EXE (1.0)", "flags": ["/D__LARGE__", "/MX"],
             "source_plan": "STARTUP\C0.ASM with the ASM_TEXT routines appended to its _TEXT segment",
             "contributes": ["C0_TEXT (457 B, matches C0L.OBJ)", "ASM_TEXT (1,082 B, unresolved)",
                             "C0 DGROUP segments (_DATA 147 B ...)"],
             "functions": order.get("ASM_TEXT", [])},
            {"id": "G1", "kind": "c", "compiler": "BIN/TCC.EXE (2.0)", "profile": "tc20-l-gzo",
             "segment": "G1_TEXT (frame 0097, 65,393 B, 64 KB limit)", "functions": order.get("G1_TEXT", []),
             "note": "function order = original order; one unit (rule CALL-FORMS, evidence/tu-structure.json)"},
            {"id": "G2", "kind": "c", "compiler": "BIN/TCC.EXE (2.0)", "profile": "tc20-l-gzo",
             "segment": "G2_TEXT (frame 108E)", "functions": order.get("G2_TEXT", []),
             "note": "order follows dn1 with episode-only functions inserted after their predecessor"},
            {"id": "CL.LIB", "kind": "library", "modules_in_image_order": lib,
             "note": "pulled in by TLINK; module order in the image is the resolution order"},
        ],
        "data": {"DGROUP": "initialised _DATA and BSS ownership per unit: UNRESOLVED",
                 "episode_builds": "EPISODE=1,2,3 via -DEPISODE=n; G1 shape-identical in all episodes"},
        "packing": {"tool": "LZEXE 0.91", "status": "NOT ACQUIRED (only 0.90 present in C:/tools/lzexe90)"},
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    doc = build()
    plan = production_plan()
    if a.check:
        ok = OUT.exists() and OUT.read_text() == canonical_json(doc)
        ok2 = PLAN.exists() and PLAN.read_text() == canonical_json(plan)
        print("tu-structure/production-plan up to date" if ok and ok2 else
              "evidence/tu-structure.json or layout/production-plan.json is stale")
        return 0 if ok and ok2 else 1
    atomic_json(OUT, doc)
    atomic_json(PLAN, plan)
    for u, v in doc["units"].items():
        for e, x in v["episodes"].items():
            print(u, e, x["functions"], x["call_forms"])
    print(doc["storage_counts"])
    return 0


if __name__ == "__main__":
    sys.exit(main())
