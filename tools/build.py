"""Build DN1/DN2/DN3.EXE from src/ with the original toolchain and compare them with the originals.

    python tools/build.py [--episode dn1] [--src DIR] [--keep DIR]

Does with the pinned toolchain exactly what src/BUILD.BAT does under DOS:

    tcc -c -ml -Z -G -O -1- -f- -K -DEPISODE=n GAME1.C GAME2.C
    tasm /MX TOOLBOX.ASM
    tlink /c /d /s C0L TOOLBOX GAME1 GAME2, DNn.EXE, DNn.MAP, CL.LIB
    lzexe DNn.EXE

then compares the linked image with the original's unpacked image and the packed file with
the original file's SHA-256 (config/oracle.lock.json).  EQUAL means byte for byte.  On a
difference it names the functions that hold the first differing bytes (from the map).
Every file in the source directory is available to the compiler, so a unit may #include
its modules.
"""
from __future__ import annotations

import argparse
import re
import shutil
import sys
import uuid
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, CONFIG, ROOT, atomic_json, load_json, sha256  # noqa: E402
import mz  # noqa: E402
import oracle  # noqa: E402
import repack  # noqa: E402
import tcc  # noqa: E402
import toolchain  # noqa: E402

SRC_DIR = ROOT / "src"
UNITS = ("GAME1.C", "GAME2.C")


def staged_files(srcdir: Path, exclude: str) -> dict:
    return {p.name: p.read_bytes().decode("latin-1") for p in sorted(srcdir.iterdir())
            if p.is_file() and p.suffix.upper() in (".C", ".H") and p.name.upper() != exclude.upper()}


def differing_symbols(image: bytes, orig: bytes, mapfile: str, limit: int = 8) -> list:
    """The public symbols (functions, data) that hold the first differing bytes."""
    pubs = sorted({(int(s, 16) * 16 + int(o, 16), n) for s, o, n in
                   re.findall(r"(?m)^ ([0-9A-F]{4}):([0-9A-F]{4})\s+(\S+)\s*$", mapfile)})
    out = []
    for i in range(min(len(image), len(orig))):
        if image[i] != orig[i]:
            below = [(a, n) for a, n in pubs if a <= i]
            a, n = below[-1] if below else (0, "?")
            name = n.lstrip("_")
            if not out or not out[-1].startswith(name + "+"):
                out.append(f"{name}+{i - a:#x}")
                if len(out) >= limit:
                    break
    return out


def build(srcdir: Path, ep: str, work: Path) -> dict:
    flags = tcc.profile_flags(load_json(CONFIG / "profiles.json")["default"]) + [f"-DEPISODE={ep[-1]}"]
    objs = {}
    for unit in UNITS:
        r = tcc.compile_c((srcdir / unit).read_text("latin-1"), flags, name=unit,
                          extra_files=staged_files(srcdir, unit))
        if not r.ok:
            return {"status": "COMPILE_ERROR", "file": unit, "log": r.log.strip().splitlines()[-12:]}
        objs[unit.replace(".C", ".OBJ")] = r.obj
    r = tcc.assemble((srcdir / "TOOLBOX.ASM").read_text("latin-1"), ["/MX"])
    if not r.ok:
        return {"status": "ASSEMBLY_ERROR", "log": r.log.strip().splitlines()[-12:]}
    objs["TOOLBOX.OBJ"] = r.obj
    work.mkdir(parents=True, exist_ok=True)
    for name, data in objs.items():
        (work / name).write_bytes(data)
    shutil.copy(toolchain.tool("LIB/C0L.OBJ"), work / "C0L.OBJ")
    shutil.copy(toolchain.tool("LIB/CL.LIB"), work / "CL.LIB")
    exe, mapname = f"DN{ep[-1]}.EXE", f"DN{ep[-1]}.MAP"
    rc, out, _ = toolchain.run_dos("BIN/TLINK.EXE", ["/c", "/d", "/s", "C0L.OBJ", "TOOLBOX.OBJ", "GAME1.OBJ",
                                                    f"GAME2.OBJ,{exe},{mapname},CL.LIB"], work)
    if rc != 0 or not (work / exe).exists():
        return {"status": "LINK_ERROR", "log": out.decode("latin-1")[-600:]}
    unpacked = (work / exe).read_bytes()
    image = mz.parse(unpacked)
    orig_image, orig_relocs = oracle.load_image(ep)
    linear = lambda rs: {(s << 4) + o for s, o in rs}
    same_image = image.image == orig_image and linear(image.relocs) == linear(orig_relocs)
    packed = repack.pack(unpacked)
    want = load_json(CONFIG / "oracle.lock.json")["episodes"][ep]["packed"]["sha256"]
    res = {"status": "EQUAL" if sha256(packed) == want and same_image else "DIFFER",
           "packed_sha256": sha256(packed), "packed_size": len(packed),
           "image": "EQUAL" if same_image else "DIFFER"}
    if not same_image:
        res["differing_functions"] = differing_symbols(image.image, orig_image,
                                                       (work / mapname).read_text("latin-1"))
    return res


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--episode", choices=EPISODES)
    ap.add_argument("--src", default=str(SRC_DIR), help="source directory (default src/)")
    ap.add_argument("--keep", help="keep the build directories here")
    a = ap.parse_args()
    rc = 0
    for ep in ([a.episode] if a.episode else EPISODES):
        work = Path(a.keep) / ep if a.keep else BUILD / "scratch" / "dosbuild" / uuid.uuid4().hex[:8]
        res = build(Path(a.src), ep, work)
        if Path(a.src).resolve() == SRC_DIR.resolve():
            atomic_json(BUILD / "dosbuild" / f"{ep}.json", res)
        print(f"{ep}: {res['status']}  {str({k: v for k, v in res.items() if k != 'status'})[:600]}")
        if not a.keep:
            shutil.rmtree(work, ignore_errors=True)
        rc |= res["status"] != "EQUAL"
    return rc


if __name__ == "__main__":
    sys.exit(main())
