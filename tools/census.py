"""Deterministic census of the three unpacked episode images.

    python tools/census.py            write build/census/<ep>.json + summary
    python tools/census.py --summary  print the summary only

Everything here is derived from the locked oracle and the pinned toolchain
library (CL.LIB / C0L.OBJ), so it is regenerable and never committed.  The
committed, reviewed view is evidence/atlas.json (tools/atlas.py).

Segment model (Turbo C 2.0 large model, verified below, not assumed):
  _TEXT    = C0L startup _TEXT | hand-written asm appended to C0 | CL.LIB _TEXT
  G?_TEXT  = first-party C translation units (one frame each)
  LIB      = CL.LIB  <MODULE>_TEXT segments
  DGROUP   = _DATA ... _BSS (frame read from the startup's 'mov dx,DGROUP')
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from functools import lru_cache
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, atomic_json, sha256  # noqa: E402
import disasm  # noqa: E402
import omf  # noqa: E402
import oracle  # noqa: E402
import toolchain  # noqa: E402

OUT = BUILD / "census"


# ----------------------------------------------------------------- library
@lru_cache(maxsize=None)
def library_patterns() -> tuple:
    """(module, segment, regex, size, publics, fixup_offsets) for every CL.LIB
    code segment, with fixup bytes as wildcards."""
    r = omf.OmfReader()
    pats = []
    for name, data in r.split_library(toolchain.tool("LIB/CL.LIB").read_bytes()):
        o = r.read(data)
        for seg, body in o.segments.items():
            if not seg.endswith("TEXT") or len(body) < 6:
                continue
            mask = set()
            for f in o.fixups:
                if f["segment"] == seg:
                    mask.update(range(f["offset"], f["offset"] + f["width"]))
            rx = b"".join(b"." if i in mask else re.escape(bytes([body[i]])) for i in range(len(body)))
            pubs = tuple(sorted((p["offset"], p["name"]) for p in o.publics if p["segment"] == seg))
            pats.append((name, seg, re.compile(rx, re.S), len(body), pubs, tuple(sorted(mask))))
    return tuple(pats)


@lru_cache(maxsize=None)
def startup_text() -> tuple:
    o = omf.OmfReader().read(toolchain.tool("LIB/C0L.OBJ").read_bytes())
    body = o.segments["_TEXT"]
    mask = set()
    for f in o.fixups:
        if f["segment"] == "_TEXT":
            mask.update(range(f["offset"], f["offset"] + f["width"]))
    pubs = tuple(sorted((p["offset"], p["name"]) for p in o.publics if p["segment"] == "_TEXT"))
    # The SEGDEF length includes the trailing uninitialised 'DGROUP@ dw ?'.
    return body, frozenset(mask), pubs, o.segment_lengths["_TEXT"]


def scan_library(img: bytes) -> list:
    hits = []
    for name, seg, rx, size, pubs, _mask in library_patterns():
        found = [m.start() for m in rx.finditer(img)]
        if len(found) == 1:
            hits.append({"module": name, "segment": seg, "start": found[0], "size": size,
                         "publics": [{"name": n, "linear": found[0] + o} for o, n in pubs]})
    # Drop matches contained in a longer match (e.g. GFREEMEM inside FFREE).
    hits.sort(key=lambda h: (h["start"], -h["size"]))
    kept = []
    for h in hits:
        if kept and h["start"] < kept[-1]["start"] + kept[-1]["size"]:
            continue
        kept.append(h)
    return kept


# ------------------------------------------------------------------ helpers
def far_targets(img: bytes, relocs) -> list:
    """(site, seg, off) for every relocated far call/jump (9A/EA ofs seg)."""
    out = []
    for s, o in relocs:
        a = (s << 4) + o
        if a >= 3 and img[a - 3] in (0x9A, 0xEA):
            off, seg = struct.unpack_from("<HH", img, a - 2)
            out.append((a - 3, seg, off))
    return out


class Segment:
    def __init__(self, name, kind, start, end, frame):
        self.name, self.kind, self.start, self.end, self.frame = name, kind, start, end, frame

    def as_dict(self):
        return {"name": self.name, "kind": self.kind, "start": self.start, "end": self.end,
                "frame": self.frame, "size": self.end - self.start}


# --------------------------------------------------------------- explorer
def explore(img: bytes, seg: Segment, entry: int, relocset: set) -> dict:
    """Intra-procedural recursive descent from linear `entry` inside `seg`.

    Returns covered byte ranges (instructions and jump tables), calls,
    data references and anomalies.  Never follows calls."""
    base = seg.frame << 4
    code = img
    seen = {}
    tables = []
    calls = []
    datarefs = []
    reloc_uses = []
    anomalies = []
    work = [entry]
    while work:
        pc = work.pop()
        while True:
            if pc in seen:
                break
            if not (seg.start <= pc < seg.end):
                anomalies.append(f"flow leaves segment at {pc:#x}")
                break
            ins = disasm.decode(code, pc, 0)
            if ins is None:
                anomalies.append(f"undecodable at {pc:#x}")
                break
            # re-express addresses in frame offsets
            ins_off = pc - base
            seen[pc] = ins
            nxt = pc + ins.size
            for k in range(pc, nxt):
                if k in relocset:
                    reloc_uses.append(k)
            if ins.far:
                fs, fo = ins.far
                calls.append({"site": pc, "kind": "far" if ins.mnem == "lcall" else "farjmp",
                              "target": (fs << 4) + fo if (pc + 3) in relocset else None,
                              "seg": fs, "off": fo, "relocated": (pc + 3) in relocset})
                if ins.mnem == "ljmp":
                    break
                pc = nxt
                continue
            if ins.target is not None:
                # capstone computed target relative to address pc (linear);
                # convert to the 16-bit frame offset then back to linear.
                rel = (ins.target - pc) & 0xFFFF
                tgt = base + ((ins_off + rel) & 0xFFFF)
                if ins.mnem == "call":
                    pushcs = pc >= 1 and img[pc - 1] == 0x0E and (pc - 1) in seen
                    calls.append({"site": pc, "kind": "pushcs_near" if pushcs else "near", "target": tgt})
                    pc = nxt
                    continue
                if ins.mnem == "jmp":
                    pc = tgt
                    continue
                work.append(tgt)
                pc = nxt
                continue
            if (ins.mnem == "mov" and ins.imm_size == 2 and 0xB8 <= ins.raw[0] <= 0xBF
                    and pc >= 1 and img[pc - 1] == 0x0E and (pc - 1) in seen):
                # push cs; mov reg, offset  -> far address of a same-segment
                # function (Turbo C builds same-TU function pointers from CS)
                imm = struct.unpack_from("<H", ins.raw, ins.imm_off)[0]
                calls.append({"site": pc, "kind": "fnptr_cs", "target": base + imm})
            if ins.mem_disp is not None and ins.mem_seg in (None, "ds", "es") and not ins.mem_bp and (
                    not ins.mem_base or (ins.disp_size == 2 and ins.mem_disp >= 0x100)):
                datarefs.append({"site": pc, "disp": ins.mem_disp, "seg": ins.mem_seg or "ds",
                                 "based": ins.mem_base, "width": ins.mem_size})
            if ins.raw[:2] == b"\x2e\xff" and (ins.raw[2] & 0x38) == 0x20 and ins.disp_size == 2:
                # jmp word ptr cs:[bx+table]  (Turbo C switch)
                tab = base + struct.unpack_from("<H", ins.raw, ins.disp_off)[0]
                count = _switch_count(seen, pc)
                if count is None:
                    anomalies.append(f"switch at {pc:#x} with unknown entry count")
                    break
                vals_size = 0
                if count[0] == "sparse":
                    vals_size = 2 * count[1]
                    tables.append((tab - vals_size, tab))
                n = count[1]
                tables.append((tab, tab + 2 * n))
                for i in range(n):
                    t = struct.unpack_from("<H", img, tab + 2 * i)[0]
                    work.append(base + t)
                break
            if ins.mnem == "jmp":   # other indirect jump
                anomalies.append(f"indirect jump at {pc:#x}: {ins.mnem} {ins.ops}")
                break
            if disasm.is_end(ins):
                break
            pc = nxt
    ranges = sorted([(a, a + i.size) for a, i in seen.items()] + tables)
    merged = []
    for a, b in ranges:
        if merged and a <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], b)
        else:
            merged.append([a, b])
    return {"insns": seen, "ranges": merged, "calls": calls, "datarefs": datarefs,
            "relocs": sorted(set(reloc_uses)), "anomalies": anomalies, "tables": tables}


def _switch_count(seen: dict, pc: int):
    """Find the case count for the switch jump at pc by looking back for
    'cmp reg, N' (dense: N+1 entries) or 'mov cx, N' (sparse: N values then
    N targets)."""
    back = sorted(a for a in seen if a < pc)[-12:]
    for a in reversed(back):
        ins = seen[a]
        if ins.mnem == "mov" and ins.ops.startswith("cx, ") and ins.imm_size:
            return ("sparse", int(ins.ops.split(", ")[1], 0))
        if ins.mnem == "cmp" and ins.imm_size and ins.ops.split(",")[0] in ("ax", "bx", "cx", "dx", "si", "di"):
            return ("dense", int(ins.ops.split(", ")[1], 0) + 1)
    return None


# ------------------------------------------------------------------ census
def census(ep: str) -> dict:
    img, relocs = oracle.load_image(ep)
    relocset = {(s << 4) + o for s, o in relocs}
    # Startup: C0L _TEXT must match at 0 outside its own fixups.
    st, stmask, stpubs, st_len = startup_text()
    st_diff = [i for i in range(len(st)) if i not in stmask and st[i] != img[i]]
    if st_diff:
        raise RuntimeError(f"{ep}: C0L.OBJ _TEXT differs at {st_diff[:8]}")
    dgroup = struct.unpack_from("<H", img, 1)[0]
    if 1 not in relocset:
        raise RuntimeError("startup 'mov dx, DGROUP' is not relocated")
    lib = scan_library(img)
    lib_seg0 = [h for h in lib if h["segment"] == "_TEXT"]
    lib_far = [h for h in lib if h["segment"] != "_TEXT"]
    asm_start = st_len
    asm_end = min(h["start"] for h in lib_seg0)
    seg0_end = max(h["start"] + h["size"] for h in lib_seg0)
    lib_far_start = min(h["start"] for h in lib_far)
    segs = [Segment("C0_TEXT", "startup", 0, asm_start, 0),
            Segment("ASM_TEXT", "asm", asm_start, asm_end, 0)]
    for h in lib_seg0:
        segs.append(Segment(h["module"], "lib", h["start"], h["start"] + h["size"], 0))
    fts = far_targets(img, relocs)
    lib_frames = set()
    for h in lib_far:
        lib_frames.add(h["start"] >> 4)
    game_frames = sorted({s for _, s, _ in fts if s != 0 and (s << 4) < lib_far_start - 0x10
                          and s not in lib_frames})
    # Game segments: consecutive frames; segment i spans [start_i, start_{i+1}).
    starts = [seg0_end]
    for f in game_frames[1:]:
        tg = [(s << 4) + o for _, s, o in fts if s == f]
        starts.append(min(tg))   # refined below once functions are known
    bounds = starts + [lib_far_start]
    for i, f in enumerate(game_frames):
        segs.append(Segment(f"G{i + 1}_TEXT", "game", bounds[i], bounds[i + 1], f))
    for h in lib_far:
        segs.append(Segment(h["module"], "lib", h["start"], h["start"] + h["size"], h["start"] >> 4))
    segs.append(Segment("DGROUP", "data", dgroup << 4, len(img), dgroup))
    segs.sort(key=lambda s: s.start)

    # Function discovery in game and asm segments.
    functions = {}
    gsegs = [s for s in segs if s.kind in ("game", "asm")]

    def seg_of(a):
        for s in gsegs:
            if s.start <= a < s.end:
                return s
        return None

    entries = set()
    for site, s, o in fts:
        a = (s << 4) + o
        sg = seg_of(a)
        if sg and (s == sg.frame):
            entries.add(a)
    # main from startup: lcall at 0x102 is part of startup; far_targets saw it.
    pending = sorted(entries)
    explored = {}
    while pending:
        e = pending.pop()
        if e in explored:
            continue
        sg = seg_of(e)
        if sg is None:
            continue
        r = explore(img, sg, e, relocset)
        explored[e] = r
        for c in r["calls"]:
            t = c.get("target")
            if t is not None and seg_of(t) and t not in explored:
                if c["kind"] in ("pushcs_near", "near", "fnptr_cs") or c.get("relocated"):
                    pending.append(t)
    # Gap filling: unexplored bytes inside game segments become candidate
    # entries (dead or pointer-only functions); repeat until stable.
    for _ in range(50):
        added = False
        for sg in gsegs:
            if sg.kind != "game":
                continue
            covered = []
            for e, r in explored.items():
                if sg.start <= e < sg.end:
                    covered.extend(r["ranges"])
            covered.sort()
            pos = sg.start
            gaps = []
            for a, b in covered:
                if a > pos:
                    gaps.append((pos, a))
                pos = max(pos, b)
            if pos < sg.end:
                gaps.append((pos, sg.end))
            for a, b in gaps:
                if a in explored:
                    continue
                r = explore(img, sg, a, relocset)
                if r["anomalies"] and not r["insns"]:
                    continue
                explored[a] = r
                r["gap_seed"] = True
                added = True
        if not added:
            break

    # Turbo C emits the epilogue even after an infinite loop; a caller-less
    # gap consisting only of epilogue instructions belongs to the function
    # before it (recorded as an unreachable tail, not a function).
    tails = {}
    for e, r in list(explored.items()):
        if not r.get("gap_seed"):
            continue
        ins = [r["insns"][a] for a in sorted(r["insns"])]
        if ins and all(i.mnem in ("pop", "retf", "ret") or (i.mnem == "mov" and i.ops == "sp, bp")
                       for i in ins):
            prev = max((x for x in explored if x < e and seg_of(x) is seg_of(e)), default=None)
            if prev is not None:
                tails[prev] = (e, max(b for a, b in r["ranges"]))
                del explored[e]
    for prev, (a, b) in tails.items():
        explored[prev]["ranges"].append([a, b])
        explored[prev]["ranges"].sort()
        explored[prev].setdefault("tail", []).append([a, b])

    # Build function records: extent = [entry, next entry in same segment).
    funcs = []
    for sg in gsegs:
        es = sorted(e for e in explored if sg.start <= e < sg.end)
        for k, e in enumerate(es):
            end = es[k + 1] if k + 1 < len(es) else sg.end
            r = explored[e]
            merged = []
            for a, b in sorted(r["ranges"]):
                if merged and a <= merged[-1][1]:
                    merged[-1][1] = max(merged[-1][1], b)
                else:
                    merged.append([a, b])
            r["ranges"] = merged
            cov = sum(min(b, end) - max(a, e) for a, b in r["ranges"] if b > e and a < end)
            outside = [(a, b) for a, b in r["ranges"] if a < e or b > end]
            last_end = max(b for a, b in r["ranges"])
            status = "VERIFIED"
            notes = list(r["anomalies"])
            if outside:
                status = "OVERLAP"
                notes.append(f"flow outside extent: {[(hex(a), hex(b)) for a, b in outside][:4]}")
            elif cov != end - e:
                status = "GAP"
                notes.append(f"covers {cov} of {end - e} bytes")
            if sg.kind == "asm" and status == "VERIFIED":
                status = "ASM_VERIFIED"
            if r.get("gap_seed"):
                notes.append("entry inferred from coverage gap (no reference found)")
            if r.get("tail"):
                notes.append(f"unreachable epilogue tail {[(hex(a), hex(b)) for a, b in r['tail']]}")
            body = img[e:end]
            masked = bytearray(body)
            for a in r["relocs"]:
                if e <= a < end:
                    masked[a - e:a - e + 2] = b"\0\0"
            funcs.append({
                "start": e, "end": end, "size": end - e, "segment": sg.name, "frame": sg.frame,
                "offset": e - (sg.frame << 4), "status": status, "notes": notes,
                "sha256": sha256(body), "reloc_masked_sha256": sha256(bytes(masked)),
                "relocs": [a for a in r["relocs"] if e <= a < end],
                "calls": [{**c} for c in r["calls"]],
                "datarefs": r["datarefs"],
                "tables": [list(t) for t in r["tables"]],
                "insn_count": len(r["insns"]),
                "shape": sha256(b"".join(disasm.shape(r["insns"][a]) for a in sorted(r["insns"]))),
                "gap_seed": bool(r.get("gap_seed")),
                "interrupt_handler": img[e:e + 9] == bytes.fromhex("505351520 61e565755".replace(" ", "")),
                "has_frame": img[e:e + 3] == b"\x55\x8b\xec",
            })
    # Library and startup symbols.
    symbols = [{"name": n, "linear": o, "kind": "startup"} for o, n in stpubs]
    for h in lib:
        for p in h["publics"]:
            symbols.append({"name": p["name"], "linear": p["linear"], "kind": "library",
                            "module": h["module"]})
    # Reloc classification.
    rclass = {}
    for a in sorted(relocset):
        v = struct.unpack_from("<H", img, a)[0]
        if a >= 3 and img[a - 3] in (0x9A, 0xEA):
            k = "far_call_seg"
        elif a >= (dgroup << 4):
            k = "data_far_pointer_seg"
        else:
            k = "code_seg_immediate"
        target_kind = "DGROUP" if v == dgroup else ("code" if v < dgroup else "other")
        rclass.setdefault(f"{k}->{target_kind}", 0)
        rclass[f"{k}->{target_kind}"] += 1
    startup_regs = {"bss_start": struct.unpack_from("<H", img, 0xC5)[0],
                    "bss_end": struct.unpack_from("<H", img, 0xC8)[0]}
    return {
        "episode": ep, "image_size": len(img), "dgroup_frame": dgroup,
        "segments": [s.as_dict() for s in segs],
        "library_modules": lib, "symbols": symbols,
        "functions": funcs, "reloc_classes": rclass, "startup": startup_regs,
        "main": {"seg": struct.unpack_from("<H", img, 0x105)[0], "off": struct.unpack_from("<H", img, 0x103)[0]},
    }


def summary(c: dict) -> dict:
    fs = c["functions"]
    by = {}
    for f in fs:
        k = (f["segment"], f["status"])
        by.setdefault(k, [0, 0])
        by[k][0] += 1
        by[k][1] += f["size"]
    return {
        "episode": c["episode"],
        "segments": [(s["name"], s["kind"], hex(s["start"]), s["size"]) for s in c["segments"]
                     if s["kind"] != "lib"],
        "library_modules": len(c["library_modules"]),
        "library_bytes": sum(h["size"] for h in c["library_modules"]),
        "functions": {f"{a}/{b}": v for (a, b), v in sorted(by.items())},
        "reloc_classes": c["reloc_classes"],
        "main": f"{c['main']['seg']:04X}:{c['main']['off']:04X}",
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--episode", choices=EPISODES)
    a = ap.parse_args()
    eps = [a.episode] if a.episode else EPISODES
    for ep in eps:
        c = census(ep)
        atomic_json(OUT / f"{ep}.json", c)
        s = summary(c)
        atomic_json(OUT / f"{ep}.summary.json", s)
        print(ep, s["main"], "lib modules", s["library_modules"], "lib bytes", s["library_bytes"])
        for seg in s["segments"]:
            print("   ", seg)
        for k, v in s["functions"].items():
            print("   ", k, v)
        print("   ", s["reloc_classes"])
    return 0


if __name__ == "__main__":
    sys.exit(main())
