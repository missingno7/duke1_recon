"""Natural link of the reconstruction with the pinned TLINK 2.0.

    python tools/link.py [--episode dn1] [--keep DIR]

Objects, all built from canonical sources:
  C0L.OBJ      STARTUP/C0.ASM reassembled with TASM 1.0 /D__LARGE__ /MX
               (rule STARTUP-C0-REASSEMBLY: identical to the shipped C0L.OBJ)
  TOOLBOX.OBJ  the assembly unit (layout/asm-unit.json), TASM 1.0 /MX
  G1.OBJ       G1 as one unit (tools/tubuild.py assemble, data fragments included)
  G2.OBJ       G2 likewise
linked as  TLINK /c /d /s C0L TOOLBOX G1 G2, OUT.EXE, OUT.MAP, CL.LIB  (rule LINK-PATH).

The linked image is compared with the episode's unpacked oracle image: load
module bytes, MZ relocation SET (order is unobservable, rule
RELOCATION-ORDER-UNOBSERVABLE) and the header fields that matter at run time
(CS:IP, SS:SP, minimum allocation).  The report attributes every differing
range to a segment of the map.  Nothing is patched: a difference is reported,
never repaired.
"""
from __future__ import annotations

import argparse
import shutil
import sys
import uuid
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, LAYOUT, ROOT, atomic_json, load_json  # noqa: E402
import mz  # noqa: E402
import oracle  # noqa: E402
import tcc  # noqa: E402
import toolchain  # noqa: E402
import tubuild  # noqa: E402


class LinkError(RuntimeError):
    pass


def build_objects(ep: str) -> dict:
    objs = {}
    extra = {n: toolchain.tool(f"STARTUP/{n}").read_bytes() for n in ("RULES.ASI", "EMUVARS.ASI")}
    r = tcc.assemble(toolchain.tool("STARTUP/C0.ASM").read_text("latin-1"), ["/D__LARGE__", "/MX"],
                     extra_files=extra)
    if not r.ok:
        raise LinkError("C0.ASM does not assemble: " + r.log[-400:])
    objs["C0L.OBJ"] = r.obj
    asm = load_json(LAYOUT / "asm-unit.json")
    r = tcc.assemble((ROOT / asm["source"]).read_text("latin-1"), ["/MX"])
    if not r.ok:
        raise LinkError("assembly unit does not assemble: " + r.log[-400:])
    objs["TOOLBOX.OBJ"] = r.obj
    profile = load_json(LAYOUT / "profiles.json")["default"]
    for unit, fname in (("G1_TEXT", "G1.C"), ("G2_TEXT", "G2.C")):
        a = tubuild.assemble(unit, ep, plan=tubuild.data_plan(unit))
        if a["missing"]:
            raise LinkError(f"{unit} incomplete: {len(a['missing'])} functions missing ({a['missing'][:5]})")
        flags = tcc.profile_flags(profile) + ([f"-DEPISODE={ep[-1]}"] if a["episode_dependent"] else [])
        r = tcc.compile_c(a["source"], flags, name=fname)
        if not r.ok:
            raise LinkError(f"{unit} does not compile: " + r.log[-600:])
        objs[fname[:-2] + ".OBJ"] = r.obj
    return objs


def link(objs: dict, work: Path) -> tuple:
    work.mkdir(parents=True, exist_ok=True)
    for name, data in objs.items():
        (work / name).write_bytes(data)
    shutil.copy(toolchain.tool("LIB/CL.LIB"), work / "CL.LIB")
    args = ["/c", "/d", "/s", "C0L.OBJ", "TOOLBOX.OBJ", "G1.OBJ", "G2.OBJ,OUT.EXE,OUT.MAP,CL.LIB"]
    rc, out, _ = toolchain.run_dos("BIN/TLINK.EXE", args, work)
    if rc != 0 or not (work / "OUT.EXE").exists():
        raise LinkError("TLINK failed: " + out.decode("latin-1")[-800:])
    return (work / "OUT.EXE").read_bytes(), (work / "OUT.MAP").read_text("latin-1"), out.decode("latin-1")


def segments_from_map(text: str) -> list:
    segs = []
    for ln in text.splitlines():
        p = ln.split()
        if len(p) >= 5 and p[0].endswith("H") and p[1].endswith("H") and len(p[0]) == 6:
            try:
                segs.append((int(p[0][:-1], 16), int(p[1][:-1], 16) + 1, p[3]))
            except ValueError:
                pass
    return segs


def compare(exe: bytes, mapfile: str, ep: str) -> dict:
    m = mz.parse(exe)
    img, relocs = oracle.load_image(ep)
    out = {"image_bytes": [len(m.image), len(img)]}
    n = min(len(m.image), len(img))
    diffs = [i for i in range(n) if m.image[i] != img[i]]
    segs = segments_from_map(mapfile)
    by_seg = {}
    for i in diffs:
        s = next((nm for a, b, nm in segs if a <= i < b), "?")
        by_seg[s] = by_seg.get(s, 0) + 1
    ours = {(s << 4) + o for s, o in m.relocs}
    theirs = {(s << 4) + o for s, o in relocs}
    out.update({"differing_bytes": len(diffs), "first_diff": hex(diffs[0]) if diffs else None,
                "differing_by_segment": by_seg,
                "relocations": [len(ours), len(theirs)],
                "relocations_missing": sorted(hex(x) for x in theirs - ours)[:10],
                "relocations_extra": sorted(hex(x) for x in ours - theirs)[:10]})
    lock = load_json(LAYOUT / "oracle.lock.json")["episodes"][ep]["unpacked"]
    hdr = m.header
    pairs = {"cs": ("cs", "cs"), "ip": ("ip", "ip"), "ss": ("ss", "ss"), "sp": ("sp", "sp"),
             "minalloc": ("minalloc", "min_extra_paras"), "maxalloc": ("maxalloc", "max_extra_paras")}
    out["header"] = {k: [hdr[a], lock[b]] for k, (a, b) in pairs.items()}
    hdr_ok = all(x == y for x, y in out["header"].values())
    out["status"] = ("EQUAL" if not diffs and len(m.image) == len(img) and ours == theirs and hdr_ok
                     else "DIFFER")
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--episode", default=None)
    ap.add_argument("--keep", help="keep the link directory here")
    a = ap.parse_args()
    rc = 0
    for ep in ([a.episode] if a.episode else ["dn1", "dn2", "dn3"]):
        work = Path(a.keep) / ep if a.keep else BUILD / "scratch" / "link" / uuid.uuid4().hex[:8]
        try:
            exe, mapfile, log = link(build_objects(ep), work)
            res = compare(exe, mapfile, ep)
        except LinkError as exc:
            res = {"status": "LINK_ERROR", "error": str(exc)}
        res["episode"] = ep
        atomic_json(BUILD / "link" / f"{ep}.json", res)
        print(f"{ep}: {res['status']}  " + str({k: v for k, v in res.items() if k not in ('status', 'episode')})[:900])
        if not a.keep:
            shutil.rmtree(work, ignore_errors=True)
        rc |= res["status"] != "EQUAL"
    return rc


if __name__ == "__main__":
    sys.exit(main())
