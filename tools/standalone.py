"""The standalone source tree: generate it and build the original executables from it.

    python tools/standalone.py generate [DIR]     write the tree (default game/)
    python tools/standalone.py build [DIR] [--episode dn1] [--keep WORK]

`generate` writes one C file per original translation unit (GAME1.C = G1,
GAME2.C = G2), the assembly unit (TOOLBOX.ASM) and BUILD.BAT, from the
canonical sources.  Each unit file holds its declarations, then every
function in original order with its initialised data, literals and BSS
definitions at the positions Turbo C needs (rules DATA-LAYOUT, BSS-ORDER).
One file serves all three episodes: episode differences are `#if EPISODE`
blocks; a function the DN3 source kept at another place appears at both
places, each guarded by the episodes that have it there.

`build` does with the pinned toolchain exactly what BUILD.BAT does under DOS:

    tcc -c -ml -Z -G -O -1- -f- -K -DEPISODE=n GAME1.C GAME2.C
    tasm /MX TOOLBOX.ASM
    tlink /c /d /s C0L TOOLBOX GAME1 GAME2, DNn.EXE, DNn.MAP, CL.LIB
    lzexe DNn.EXE

and compares the packed result with the original file's SHA-256
(layout/oracle.lock.json).  C0L.OBJ and CL.LIB are the shipped Turbo C 2.0
files (C0L.OBJ is what STARTUP/C0.ASM reassembles to, rule
STARTUP-C0-REASSEMBLY).
"""
from __future__ import annotations

import argparse
import shutil
import sys
import uuid
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, LAYOUT, RECIPES, ROOT, atomic_json, load_json, sha256  # noqa: E402
import link  # noqa: E402
import repack  # noqa: E402
import tcc  # noqa: E402
import toolchain  # noqa: E402
import tubuild  # noqa: E402

UNITS = (("G1_TEXT", "GAME1.C"), ("G2_TEXT", "GAME2.C"))
DEFAULT_DIR = ROOT / "game"


def _episode_cond(eps: set) -> str:
    nums = sorted(int(e[-1]) for e in eps)
    return " || ".join(f"EPISODE == {n}" for n in nums)


def merged_order(unit: str) -> list:
    """[(fid, episodes)] covering every episode's function order: the DN1 order
    is the spine; a function another episode places elsewhere is emitted again
    at that place for that episode (and removed from the spine for it)."""
    orders = {e: tubuild.unit_functions(unit, e) for e in EPISODES}
    entries = [[f, set(EPISODES)] for f in orders["dn1"]]
    for e in EPISODES[1:]:
        order = orders[e]
        if order == orders["dn1"]:
            continue
        import difflib
        sm = difflib.SequenceMatcher(None, orders["dn1"], order, autojunk=False)
        stable = set()
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == "equal":
                stable.update(orders["dn1"][i1:i2])
        for ent in entries:
            if ent[0] not in stable:
                ent[1].discard(e)
        for k, f in enumerate(order):
            if f in stable:
                continue
            prev = order[k - 1] if k else None
            pos = next((i for i, ent in enumerate(entries) if ent[0] == prev and e in ent[1]), -1) + 1
            entries.insert(pos, [f, {e}])
    return [(f, eps) for f, eps in entries if eps]


def unit_source(unit: str) -> str:
    plan = tubuild.data_plan(unit)
    order = merged_order(unit)
    a = tubuild.assemble(unit, "dn1", plan=plan)
    # split the dn1 assembly into its declaration part and per-function bodies
    text = a["source"]
    bodies = {}
    for f in tubuild.unit_functions(unit, "dn1"):
        src = ROOT / load_json(RECIPES / f"{f}.json")["source"]
        bodies[f] = tubuild.split(src)[1].strip("\n")
    frags = {}
    for fr in (plan or {}).get("fragments", []):
        frags.setdefault(fr["before"], []).append(ROOT / fr["file"])
    # the declaration part ends where the first body (or its 'before' fragments) begins
    first = order[0][0]
    cut = text.find(f"/* {first} */\n")
    for fr in frags.get(first, []):
        mark = f"/* data: {fr.name} */"
        if 0 <= text.find(mark) < cut:
            cut = text.find(mark)
    out = text[:cut].rstrip() + "\n\n"
    for f, eps in order:
        for fr in frags.get(f, []):
            if eps == set(EPISODES):
                out += f"/* data: {fr.name} */\n{fr.read_text('latin-1').strip()}\n\n"
        guarded = eps != set(EPISODES)
        if guarded:
            out += f"#if {_episode_cond(eps)}\n/* {f}: at this place in the {', '.join(sorted(e.upper() for e in eps))} source */\n"
        else:
            out += f"/* {f} */\n"
        out += bodies[f] + "\n"
        out += "#endif\n\n" if guarded else "\n"
    out += "".join(f"/* data: {fr.name} */\n{fr.read_text('latin-1').strip()}\n\n" for fr in frags.get("end", []))
    return out


BUILD_BAT = r"""@echo off
rem Build one episode of Duke Nukum v2.0 with Turbo C 2.0, TASM 1.0, TLINK 2.0 and LZEXE 0.91.
rem usage: BUILD 1|2|3      (expects TCC, TASM, TLINK, LZEXE on the PATH and TC = the Turbo C directory)
if "%1"=="" goto usage
if "%TC%"=="" set TC=C:\TC
tcc -c -ml -Z -G -O -1- -f- -K -I%TC%\INCLUDE -DEPISODE=%1 GAME1.C GAME2.C
if errorlevel 1 goto fail
tasm /MX TOOLBOX.ASM
if errorlevel 1 goto fail
tlink /c /d /s %TC%\LIB\C0L TOOLBOX GAME1 GAME2, DN%1.EXE, DN%1.MAP, %TC%\LIB\CL.LIB
if errorlevel 1 goto fail
lzexe DN%1.EXE
goto end
:usage
echo usage: BUILD 1^|2^|3
goto end
:fail
echo build failed
:end
"""


def dos_text(text: str) -> bytes:
    """CRLF line endings: Turbo C 2.0 mis-reads LF-only headers."""
    return text.replace("\r\n", "\n").replace("\n", "\r\n").encode("latin-1")


def generate(outdir: Path) -> list:
    outdir.mkdir(parents=True, exist_ok=True)
    import gentree
    written = []
    for fname, text in gentree.generate_texts().items():          # DOS line endings for the DOS tools
        (outdir / fname).write_bytes(dos_text(text))
        written.append(fname)
    asm = load_json(LAYOUT / "asm-unit.json")["source"]
    (outdir / "TOOLBOX.ASM").write_bytes(dos_text((ROOT / asm).read_text("latin-1")))
    (outdir / "BUILD.BAT").write_bytes(BUILD_BAT.replace("\n", "\r\n").encode("ascii"))
    return written + ["TOOLBOX.ASM", "BUILD.BAT"]


def build(srcdir: Path, ep: str, work: Path) -> dict:
    profile = load_json(LAYOUT / "profiles.json")["default"]
    flags = tcc.profile_flags(profile) + [f"-DEPISODE={ep[-1]}"]
    objs = {}
    for unit, fname in UNITS:
        extra = {"DUKE.H": (srcdir / "DUKE.H").read_text("latin-1")} if (srcdir / "DUKE.H").exists() else None
        r = tcc.compile_c((srcdir / fname).read_text("latin-1"), flags, name=fname, extra_files=extra)
        if not r.ok:
            return {"status": "COMPILE_ERROR", "file": fname, "log": r.log.strip().splitlines()[-12:]}
        objs[fname.replace(".C", ".OBJ")] = r.obj
    r = tcc.assemble((srcdir / "TOOLBOX.ASM").read_text("latin-1"), ["/MX"])
    if not r.ok:
        return {"status": "ASSEMBLY_ERROR", "log": r.log.strip().splitlines()[-12:]}
    objs["TOOLBOX.OBJ"] = r.obj
    work.mkdir(parents=True, exist_ok=True)
    for name, data in objs.items():
        (work / name).write_bytes(data)
    shutil.copy(toolchain.tool("LIB/C0L.OBJ"), work / "C0L.OBJ")
    shutil.copy(toolchain.tool("LIB/CL.LIB"), work / "CL.LIB")
    exe = f"DN{ep[-1]}.EXE"
    rc, out, _ = toolchain.run_dos("BIN/TLINK.EXE", ["/c", "/d", "/s", "C0L.OBJ", "TOOLBOX.OBJ", "GAME1.OBJ",
                                                    f"GAME2.OBJ,{exe},DN{ep[-1]}.MAP,CL.LIB"], work)
    if rc != 0 or not (work / exe).exists():
        return {"status": "LINK_ERROR", "log": out.decode("latin-1")[-600:]}
    unpacked = (work / exe).read_bytes()
    res = link.compare(unpacked, (work / f"DN{ep[-1]}.MAP").read_text("latin-1"), ep)
    packed = repack.pack(unpacked)
    want = load_json(LAYOUT / "oracle.lock.json")["episodes"][ep]["packed"]["sha256"]
    res = {"status": "EQUAL" if sha256(packed) == want else "DIFFER", "packed_sha256": sha256(packed),
           "packed_size": len(packed), "unpacked_status": res["status"],
           "differing_bytes": res["differing_bytes"], "first_diff": res["first_diff"]}
    return res


def main() -> int:
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    g = sub.add_parser("generate")
    g.add_argument("dir", nargs="?", default=str(DEFAULT_DIR))
    g.add_argument("--force", action="store_true", help="overwrite an existing tree (it is edited by hand after generation)")
    b = sub.add_parser("build")
    b.add_argument("dir", nargs="?", default=str(DEFAULT_DIR))
    b.add_argument("--episode")
    b.add_argument("--keep")
    a = ap.parse_args()
    if a.cmd == "generate":
        if (Path(a.dir) / "GAME1.C").exists() and not a.force:
            print(f"{a.dir} exists: it is the canonical, hand-edited tree; use --force to regenerate it")
            return 1
        print("wrote", generate(Path(a.dir)))
        return 0
    rc = 0
    for ep in ([a.episode] if a.episode else EPISODES):
        work = Path(a.keep) / ep if a.keep else BUILD / "scratch" / "standalone" / uuid.uuid4().hex[:8]
        res = build(Path(a.dir), ep, work)
        atomic_json(BUILD / "standalone" / f"{ep}.json", res)
        print(f"{ep}: {res['status']}  {str({k: v for k, v in res.items() if k != 'status'})[:300]}")
        if not a.keep:
            shutil.rmtree(work, ignore_errors=True)
        rc |= res["status"] != "EQUAL"
    return rc


if __name__ == "__main__":
    sys.exit(main())
