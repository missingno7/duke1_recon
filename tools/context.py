"""Everything a worker needs about one logical function, compactly.

    python tools/context.py g1_0acc                 summary + annotated dn1 listing
    python tools/context.py g1_0acc --episode dn3   listing of another episode
    python tools/context.py g1_0acc --skeleton      candidate skeleton (declarations + stubs)
    python tools/context.py g1_0acc --json
    python tools/context.py --list [--unit G2_TEXT] [--class SHARED_SHAPE] [--max-size 80] [--open]

Signature hints (pascal, parameter bytes, register variables, locals) are
heuristics read from the original code and are labelled as such.
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, RECIPES, ROOT, load_json  # noqa: E402
import datamap  # noqa: E402
import disasm  # noqa: E402
import oracle  # noqa: E402
import symbols  # noqa: E402


def census_fn(ep: str, start: int) -> dict:
    for f in symbols.census(ep)["functions"]:
        if f["start"] == start:
            return f
    raise KeyError(start)


def sig_hints(img: bytes, f: dict) -> dict:
    body = img[f["start"]:f["end"]]
    h = {"frame": body[:3] == b"\x55\x8b\xec"}
    last = None
    a = f["start"]
    params = 0
    regs = []
    locals_ = 0
    while a < f["end"]:
        tab = next((t for t in f["tables"] if t[0] <= a < t[1]), None)
        if tab:
            a = tab[1]
            continue
        i = disasm.decode(img, a, 0)
        if i is None:
            break
        if "[bp + " in i.ops:
            try:
                off = int(i.ops.split("[bp + ")[1].split("]")[0], 0)
                params = max(params, off - 4 + (2 if "word" in i.ops or "les" in i.mnem or "lds" in i.mnem else 1))
            except ValueError:
                pass
        if a - f["start"] < 12:
            if i.mnem == "sub" and i.ops.startswith("sp, "):
                locals_ = int(i.ops.split(", ")[1], 0)
            if i.mnem == "push" and i.ops in ("si", "di"):
                regs.append(i.ops)
        last = i
        a += i.size
    if last is not None and last.mnem == "retf" and last.ops:
        h["pascal"] = True
        h["param_bytes"] = int(last.ops, 0)
    else:
        h["pascal"] = False
        h["param_bytes_seen"] = params
    h["register_vars"] = regs
    h["locals_bytes"] = locals_
    h["interrupt_handler"] = f.get("interrupt_handler", False)
    return h


def data_name(off: int) -> str:
    return f"d_{off:04x}"


def listing(ep: str, f: dict, img: bytes, relocset: set, dn1_names: dict) -> list:
    """Annotated listing; DGROUP offsets are shown as dn1-named symbols."""
    out = []
    a = f["start"]
    base = f["frame"] << 4
    inv = dn1_names
    while a < f["end"]:
        tab = next((t for t in f["tables"] if t[0] <= a < t[1]), None)
        if tab:
            words = [struct.unpack_from("<H", img, x)[0] for x in range(tab[0], tab[1], 2)]
            out.append(f"  {a - base:04x}  .table {', '.join(f'{w:04x}' for w in words)}")
            a = tab[1]
            continue
        i = disasm.decode(img, a, 0)
        if i is None:
            out.append(f"  {a - base:04x}  db {img[a]:02x}")
            a += 1
            continue
        note = []
        if i.far:
            s, o = i.far
            n = symbols.function_at(ep, (s << 4) + o) if (a + 3) in relocset else None
            note.append(f"-> {n or '?'}")
        elif i.target is not None and i.mnem == "call":
            t = base + ((a - base + ((i.target - a) & 0xFFFF)) & 0xFFFF)
            note.append(f"-> {symbols.function_at(ep, t) or '?'}")
        if i.raw[0] in (0xB8, 0xBB) and a >= 1 and img[a - 1] == 0x0E and i.size == 3:
            v = struct.unpack_from("<H", i.raw, 1)[0]
            note.append(f"&{symbols.function_at(ep, base + v) or '?'}")
        for o, n in ((i.disp_off, i.disp_size), (i.imm_off, i.imm_size)):
            if n == 2 and not i.far and i.target is None:
                v = struct.unpack_from("<H", i.raw, o)[0]
                nm = inv.get(v)
                if nm and (o == i.disp_off or v >= 0x100):
                    note.append(nm)
        if any(k in relocset for k in range(a, a + i.size)):
            note.append("RELOC")
        out.append(f"  {a - base:04x}  {i.raw.hex():<14} {i.mnem} {i.ops}" + (f"   ; {' '.join(note)}" if note else ""))
        a += i.size
    return out


def names_for(ep: str) -> dict:
    """episode DGROUP value -> dn1 symbol name, for every anchored/mapped value."""
    if ep == "dn1":
        return {}
    inv = {}
    for x, y in datamap.anchors(ep).items():
        inv[y] = data_name(x)
    return inv


def gather(fid: str, ep: str = "dn1") -> dict:
    entry = symbols.atlas()[fid]
    if ep not in entry["locations"]:
        ep = sorted(entry["locations"])[0]
    loc = entry["locations"][ep]
    img, relocs = oracle.load_image(ep)
    relocset = {(s << 4) + o for s, o in relocs}
    f = census_fn(ep, loc["start"])
    calls = []
    for c in f["calls"]:
        t = c.get("target")
        callee = symbols.function_at(ep, t) if t is not None else None
        cinfo = {"kind": c["kind"], "callee": callee}
        if callee and callee in symbols.atlas():
            cl = symbols.atlas()[callee]["locations"][ep]
            cinfo["hints"] = sig_hints(img, census_fn(ep, cl["start"]))
            rp = RECIPES / f"{callee}.json"
            cinfo["accepted"] = rp.exists()
        calls.append(cinfo)
    callers = []
    for g in symbols.census(ep)["functions"]:
        for c in g["calls"]:
            if c.get("target") == loc["start"]:
                callers.append({"caller": symbols.function_at(ep, g["start"]), "kind": c["kind"]})
    data = {}
    ref_names = names_for(ep)
    for d in f["datarefs"]:
        ref = d["disp"] if ep == "dn1" else next((k for k, v in datamap.anchors(ep).items() if v == d["disp"]), None)
        if ref is None:
            continue
        nm = data_name(ref)
        data.setdefault(nm, {"region": datamap.region(ref), "addresses": {}, "widths": set(), "indexed": False})
        data[nm]["widths"].add(d.get("width", 2))
        data[nm]["indexed"] |= bool(d.get("based"))
        for e in EPISODES:
            data[nm]["addresses"][e] = datamap.to_episode(e, ref)
    recipe = RECIPES / f"{fid}.json"
    exps = []
    try:
        import db
        con = db.connect()
        for r in con.execute("SELECT best_status, COUNT(*) n, MIN(diff_bytes) best FROM experiments "
                             "WHERE function_id=? GROUP BY best_status", (fid,)):
            exps.append(dict(r))
        blockers = [dict(r) for r in con.execute("SELECT id, category, mechanism, next_experiment FROM blockers "
                                                 "WHERE scope=? AND status='OPEN'", (fid,))]
    except Exception:
        blockers = []
    dn1_inv = ref_names if ep != "dn1" else {}
    if ep == "dn1":
        dn1_inv = {d["disp"]: data_name(d["disp"]) for d in f["datarefs"]}
        for x in datamap.anchors("dn2"):
            dn1_inv.setdefault(x, data_name(x))
    return {
        "id": fid, "unit": entry["segment"], "class": entry["class"], "confidence": entry["confidence"],
        "locations": {e: {"start": hex(v["start"]), "frame_offset": f"{v['frame']:04X}:{v['offset']:04X}",
                          "size": v["size"], "boundary": v["boundary"]} for e, v in entry["locations"].items()},
        "mapping_evidence": entry["evidence"], "accepted": json.loads(recipe.read_text())["episodes"] if recipe.exists() else None,
        "signature_hints": sig_hints(img, f), "calls": calls, "callers": callers, "data": data,
        "experiments": exps, "open_blockers": blockers, "episode_shown": ep,
        "listing": listing(ep, f, img, relocset, dn1_inv),
    }


def c_type(region_width: int) -> str:
    return {1: "char", 2: "int", 4: "long"}.get(region_width, "int")


def accepted_views(unit: str | None = None) -> tuple:
    """Declarations already used by accepted sources (tools/decls.py):
    {function: (ret, conv, params)}, {global: (type, array)}.

    G1 and G2 are separate translation units and the original declares some
    objects differently in each (d_9682 is int in G1, char in G2), so only
    views from the same unit (src/<unit>/) are binding.  A function's view is
    the same unit's own definition/stub/declaration if there is one, else its
    definition in the other unit."""
    try:
        import decls
        views = decls.collect()
    except Exception:
        return {}, {}
    rank = {"definition": 0, "stub": 1, "declaration": 2}
    same = (lambda v: unit is None or v["file"].startswith(f"src/{unit}/"))
    fns = {}
    for name, vs in views["functions"].items():
        own = [v for v in vs if same(v)]
        pool = own or [v for v in vs if v["kind"] == "definition"]
        if not pool:
            continue
        best = sorted(pool, key=lambda v: rank[v["kind"]])[0]
        fns[name] = (best["ret"], best["conv"], best["params"])
    data = {}
    for name, vs in views["data"].items():
        types = sorted({(v["type"], v["array"]) for v in vs if same(v)})
        if len(types) == 1:
            data[name] = types[0]
    return fns, data


def _proto(name: str, view: tuple, stub: bool) -> str:
    ret, conv, params = view
    conv = "" if conv == "cdecl" else conv + " "
    if params == "void":
        plist = "void"
    else:
        plist = ", ".join(f"{t} a{k}" for k, t in enumerate(params.split(", ")))
    if stub:
        body = "{}" if ret == "void" else "{ return 0; }"
        return f"{ret} {conv}{name}({plist}) {body}    /* accepted signature; stub for push cs; call near */"
    return f"{ret} {conv}{name}({plist});    /* accepted signature */"


LIB_HEADERS = {
    "stdio.h": "fopen fclose fread fwrite fprintf printf fscanf scanf fseek ftell getc putc getw putw ungetc fflush "
               "setvbuf tmpnam unlink sprintf fgetc fputc fgets fputs gets puts rewind feof".split(),
    "string.h": "strcpy strcat strlen strcmp strncpy strncmp memcpy memset memcmp memmove".split(),
    "dos.h": "outport inport outportb inportb delay getvect setvect disable enable geninterrupt int86 intdos "
             "sound nosound".split(),
    "conio.h": "textmode clrscr gotoxy getch kbhit cprintf".split(),
    # abs deliberately absent: <stdlib.h> makes it the inline __abs__ intrinsic, while the
    # original calls CL.LIB abs() (rule ABS-IS-A-CALL); declare `int abs(int);` instead
    "stdlib.h": "exit atexit malloc free ltoa itoa atoi rand srand random".split(),
    "io.h": "open close read write lseek access chmod eof".split(),
    "alloc.h": "farmalloc farfree coreleft farcoreleft".split(),
}


def skeleton(ctx: dict) -> str:
    fns, data = accepted_views(ctx["id"].split("_")[0] if ctx["id"].startswith(("g1_", "g2_")) else None)
    lines = [f"/* {ctx['id']}: candidate skeleton generated by tools/context.py.",
             "   Lines marked 'accepted' repeat declarations already proven elsewhere; keep them",
             "   consistent.  Everything else is a guess from the original code. */"]
    # library callees come from the pinned Turbo C headers
    headers = set()
    for c in ctx["calls"]:
        n = c["callee"]
        if n and not n.startswith(("g1_", "g2_", "asm_")):
            h = next((h for h, names in LIB_HEADERS.items() if n.lstrip("_") in names), None)
            if h:
                headers.add(h)
    lines += [f"#include <{h}>" for h in sorted(headers)]
    sizes = {"char": 1, "int": 2, "unsigned int": 2, "long": 4, "unsigned long": 4}
    wide = {int(n[2:], 16): (n, sizes.get(t, 4 if "far*" in t else 2)) for n, (t, arr) in data.items()
            if not arr and n.startswith("d_") and len(n) == 6}
    for nm, d in sorted(ctx["data"].items()):
        off = int(nm[2:], 16) if len(nm) == 6 else None
        inside = next(((b, w) for b, w in wide.items() if off is not None and b < off < b + w[1]), None)
        if inside:
            base, (bname, bsize) = inside
            lines.append(f"/* {nm} is byte {off - base} of accepted {bname} ({data[bname][0]}): use {bname} */")
            continue
        if nm in data:
            t, arr = data[nm]
            lines.append(f"extern {t} {nm}{'[]' if arr else ''};      /* accepted type */")
            continue
        w = sorted(d.get("widths", [2]))
        t = c_type(w[0]) if len(w) == 1 else "int"
        arr = "[]" if d.get("indexed") else ""
        lines.append(f"extern {t} {nm}{arr};      /* {d['region']}, accessed as {w} byte(s){', indexed' if arr else ''} */")
    seen = set()
    near = []
    for c in ctx["calls"]:
        n = c["callee"]
        if not n or n in seen:
            continue
        seen.add(n)
        stub = c["kind"] == "pushcs_near"
        if not n.startswith(("g1_", "g2_", "asm_")) and any(n.lstrip("_") in v for v in LIB_HEADERS.values()):
            continue          # declared by the included header
        if n in fns:
            (near if stub else lines).append(_proto(n, fns[n], stub))
            continue
        h = c.get("hints", {})
        conv = "pascal " if h.get("pascal") else ""
        nparams = (h.get("param_bytes") or h.get("param_bytes_seen") or 0) // 2
        params = ", ".join(f"int a{k}" for k in range(nparams)) or "void"
        if stub:
            near.append(f"void {conv}{n}({params}) {{}}    /* stub: called via push cs; call near */")
        else:
            lines.append(f"void {conv}{n}({params});")
    lines += near
    h = ctx["signature_hints"]
    conv = "pascal " if h.get("pascal") else ""
    nparams = (h.get("param_bytes") or h.get("param_bytes_seen") or 0) // 2
    params = ", ".join(f"int a{k}" for k in range(nparams)) or "void"
    lines += ["/*@body*/", f"void {conv}{ctx['id']}({params})", "{", "}"]
    return "\n".join(lines) + "\n"


def list_functions(a) -> None:
    rows = []
    for fid, f in symbols.atlas().items():
        if a.unit and f["segment"] != a.unit:
            continue
        if a.cls and f["class"] != a.cls:
            continue
        size = max(v["size"] for v in f["locations"].values())
        if a.max_size and size > a.max_size:
            continue
        acc = (RECIPES / f"{fid}.json").exists()
        if a.open and acc:
            continue
        rows.append((fid, f["segment"], f["class"], size, "accepted" if acc else ""))
    for r in sorted(rows, key=lambda r: (r[1], r[0])):
        print(f"{r[0]:14s} {r[1]:9s} {r[2]:17s} {r[3]:6d} {r[4]}")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("function", nargs="?")
    ap.add_argument("--episode", default="dn1", choices=EPISODES)
    ap.add_argument("--skeleton", action="store_true")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--unit")
    ap.add_argument("--class", dest="cls")
    ap.add_argument("--max-size", type=int)
    ap.add_argument("--open", action="store_true")
    a = ap.parse_args()
    if a.list:
        list_functions(a)
        return 0
    if not a.function:
        ap.error("function required")
    ctx = gather(a.function, a.episode)
    if a.json:
        print(json.dumps(ctx, indent=1, default=sorted))
        return 0
    if a.skeleton:
        print(skeleton(ctx), end="")
        return 0
    print(render(ctx), end="")
    return 0


def render(ctx: dict) -> str:
    """The human-readable context report (also written into task packets)."""
    out = [f"{ctx['id']}  {ctx['unit']}  {ctx['class']} ({ctx['confidence']})"]
    for e, v in ctx["locations"].items():
        out.append(f"  {e}: {v['frame_offset']} linear {v['start']} size {v['size']} boundary {v['boundary']}")
    ev = {k: v for k, v in ctx["mapping_evidence"].items() if k != "present"}
    out.append(f"  mapping evidence: {ev}")
    if ctx["accepted"]:
        out.append(f"  ACCEPTED: { {e: v['status'] for e, v in ctx['accepted'].items()} }")
    out.append(f"  signature hints (heuristic): {ctx['signature_hints']}")
    out.append("  calls:")
    for c in ctx["calls"]:
        h = c.get("hints")
        hs = ""
        if h:
            hs = f" pascal={h['pascal']} params~{h.get('param_bytes', h.get('param_bytes_seen'))}B"
        out.append(f"    {c['kind']:12s} {c['callee']}{hs}{' [accepted]' if c.get('accepted') else ''}")
    out.append(f"  callers: {[(c['caller'], c['kind']) for c in ctx['callers']][:12]}")
    if ctx["data"]:
        out.append("  data (dn1-named; per-episode DGROUP offsets):")
        for nm, d in sorted(ctx["data"].items()):
            addrs = " ".join(f"{e}={v:04x}" if v is not None else f"{e}=?" for e, v in d["addresses"].items())
            out.append(f"    {nm} {d['region']:4s} {addrs}  width {sorted(d['widths'])}"
                       f"{' indexed' if d['indexed'] else ''}")
    if ctx["experiments"]:
        out.append(f"  experiments: {ctx['experiments']}")
    if ctx["open_blockers"]:
        out.append(f"  OPEN BLOCKERS: {ctx['open_blockers']}")
    out.append(f"  listing ({ctx['episode_shown']}, frame offsets):")
    out.extend(ctx["listing"])
    return "\n".join(out) + "\n"


if __name__ == "__main__":
    sys.exit(main())
