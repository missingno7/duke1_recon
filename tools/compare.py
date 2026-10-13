"""Strict function-level comparison of a compiled candidate against an oracle.

compare_object(obj_bytes, function_id, episode, name=None) -> Result

A candidate is EQUAL for an episode only if all of these hold:
  1. the object passes strict OMF validation (checksums, known records,
     THEADR first, MODEND last, no overlapping LEDATA);
  2. the target public exists in a CODE segment and its extent
     [public, next public or segment end) has the oracle extent's length;
  3. every candidate FIXUPP inside the extent binds, through tools/symbols.py
     for that episode, to exactly the value the original bytes contain
     (far pointers: offset AND frame; data: DGROUP offset + addend; string
     literals of the candidate's own _DATA: content-verified at the address
     the original uses);
  4. the set of original MZ relocation sites in the extent equals the set of
     segment words the candidate's fixups produce (no hard-coded frames, no
     missing relocations);
  5. every 'push cs; call near' / 'push cs; mov reg, offset' inside the
     candidate resolves to a candidate public whose binding is the original
     target (relational check; Turbo C resolves these at compile time);
  6. every other byte is identical.
No byte is masked, patched or trimmed beyond the bound fields above.
"""
from __future__ import annotations

import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import disasm  # noqa: E402
import omf  # noqa: E402
import oracle  # noqa: E402
import symbols  # noqa: E402

ALLOWED = {0x80, 0x88, 0x8A, 0x8C, 0x90, 0x94, 0x96, 0x98, 0x9A, 0x9C, 0xA0, 0xA2}


class ObjectError(ValueError):
    pass


def validate_object(data: bytes) -> None:
    i = 0
    kinds = []
    while i < len(data):
        if i + 3 > len(data):
            raise ObjectError("truncated record header")
        k = data[i]
        n = struct.unpack_from("<H", data, i + 1)[0]
        rec = data[i:i + 3 + n]
        if len(rec) != 3 + n:
            raise ObjectError(f"truncated record 0x{k:02X} at {i}")
        if k not in ALLOWED:
            raise ObjectError(f"record 0x{k:02X} at {i} is not in the reviewed record set")
        if rec[-1] != 0 and sum(rec) % 256 != 0:
            raise ObjectError(f"bad checksum in record 0x{k:02X} at {i}")
        kinds.append(k)
        i += 3 + n
        if k == 0x8A:
            break
    if not kinds or kinds[0] != 0x80 or kinds[-1] != 0x8A:
        raise ObjectError("object must start with THEADR and end with MODEND")
    if any(data[i:].strip(b"\0")):
        raise ObjectError("bytes after MODEND")


def _ledata_spans(data: bytes, module: omf.ObjectModule) -> None:
    """Reject overlapping LEDATA within a segment (an object that writes the
    same byte twice could hide content from a comparison)."""
    seen = {}
    names = [s["name"] for s in module.segment_defs]
    for kind, body in omf.OmfReader.records(data):
        if kind == 0xA0:
            idx, at = omf.OmfReader._index(body, 0)
            off = struct.unpack_from("<H", body, at)[0]
            n = len(body) - at - 2
            seg = names[idx - 1]
            for a, b in seen.get(seg, []):
                if off < b and a < off + n:
                    raise ObjectError(f"overlapping LEDATA in {seg} at {off:#x}")
            seen.setdefault(seg, []).append((off, off + n))


@dataclass
class Result:
    status: str                    # EQUAL | DIFFER | EXTENT_MISMATCH | BINDING_ERROR | OBJECT_ERROR | NO_SYMBOL
    episode: str
    function: str
    detail: list = field(default_factory=list)
    bound: list = field(default_factory=list)
    diff_bytes: int = 0
    cand_size: int | None = None
    orig_size: int | None = None
    first_diff: int | None = None
    cand: bytes = b""
    orig: bytes = b""
    cand_base: int = 0
    orig_base: int = 0
    covered: frozenset = frozenset()   # positions verified by a binding (diagnostics only)

    def summary(self) -> dict:
        return {"status": self.status, "episode": self.episode, "function": self.function,
                "size": [self.cand_size, self.orig_size], "diff_bytes": self.diff_bytes,
                "first_diff": self.first_diff, "detail": self.detail[:12],
                "bindings": len(self.bound)}


def find_public(module, name: str):
    want = symbols.norm(name)
    hits = [p for p in module.publics if symbols.norm(p["name"]) == want]
    if len(hits) != 1:
        return None
    return hits[0]


def candidate_extent(module, pub) -> tuple:
    seg = pub["segment"]
    offs = sorted({p["offset"] for p in module.publics if p["segment"] == seg})
    nxt = [o for o in offs if o > pub["offset"]]
    end = nxt[0] if nxt else module.segment_lengths.get(seg, len(module.segments.get(seg, b"")))
    return seg, pub["offset"], end


def compare_object(obj: bytes, function_id: str, ep: str, name: str | None = None) -> Result:
    res = Result("DIFFER", ep, function_id)
    try:
        validate_object(obj)
        module = omf.OmfReader().read(obj)
        _ledata_spans(obj, module)
    except (ObjectError, omf.MatchError, IndexError, struct.error) as exc:
        res.status = "OBJECT_ERROR"
        res.detail.append(str(exc))
        return res
    entry = symbols.atlas().get(function_id)
    if entry is None or ep not in entry["locations"]:
        res.status = "NO_SYMBOL"
        res.detail.append(f"{function_id} has no {ep} location in evidence/atlas.json")
        return res
    loc = entry["locations"][ep]
    pub = find_public(module, name or function_id)
    if pub is None:
        res.status = "NO_SYMBOL"
        res.detail.append(f"candidate object has no unique public {name or function_id}")
        return res
    seg, cstart, cend = candidate_extent(module, pub)
    segdef = next(s for s in module.segment_defs if s["name"] == seg)
    if segdef["class"] != "CODE":
        res.status = "NO_SYMBOL"
        res.detail.append(f"public {pub['name']} is in non-CODE segment {seg}")
        return res
    body = module.segments.get(seg, b"")
    cand = bytearray(body[cstart:cend])
    img, relocs = oracle.load_image(ep)
    ostart = loc["start"]
    orig = img[ostart:ostart + loc["size"]]
    res.cand_size, res.orig_size = len(cand), len(orig)
    res.cand, res.orig, res.cand_base, res.orig_base = bytes(cand), orig, cstart, loc["offset"]
    if len(cand) != len(orig):
        res.status = "EXTENT_MISMATCH"
        res.detail.append(f"candidate {len(cand)} bytes, original {len(orig)} bytes")
        _first_diff(res)
        return res
    relocset = {(s << 4) + o for s, o in relocs}
    orig_relocs = {a - ostart for a in relocset if ostart <= a < ostart + len(orig)}
    census = symbols.census(ep)
    dgroup_frame = census["dgroup_frame"]
    dgroup_base = dgroup_frame << 4
    pubs_by_off = {}
    for p in module.publics:
        if p["segment"] == seg:
            pubs_by_off.setdefault(p["offset"], []).append(p["name"])
    covered = set()        # byte positions verified by binding
    attempted = set()      # fixup positions whose binding failed (reported as binding errors)
    cand_segwords = set()
    errors = []

    def word(buf, at):
        return struct.unpack_from("<H", buf, at)[0]

    for fx in module.linker_fixups:
        if fx["segment"] != seg or not (cstart <= fx["offset"] < cend):
            continue
        at = fx["offset"] - cstart
        width = fx["width"]
        if at + width > len(cand):
            errors.append(f"fixup at +{at:#x} crosses the extent end")
            continue
        attempted.update(range(at, at + width))
        addend = fx["displacement"] + int.from_bytes(cand[at:at + width], "little")
        tkind, tname = fx["target_kind"], fx["target"]
        loc_name = fx["loc"]
        try:
            if tkind == "external":
                tgt = symbols.resolve(tname, ep)
            elif tkind == "segment" and tname == seg and loc_name == "offset16" and                     cstart <= (addend & 0xFFFF) < cend:
                # a label inside this function (switch jump-table entries and
                # the table address itself): must land at the same relative
                # offset in the original function
                tgt = {"kind": "local_label", "relative": (addend & 0xFFFF) - cstart}
            elif tkind == "segment" and tname == seg:
                names = pubs_by_off.get(addend & 0xFFFF)
                if not names:
                    raise symbols.SymbolError(f"own-segment target +{addend:#x} is not a public")
                tgt = symbols.resolve(names[0], ep)
                addend = 0         # the embedded value was the public's own offset
            elif tkind in ("segment", "group") and tname in ("_DATA", "_BSS", "DGROUP"):
                tgt = {"kind": "own_data", "segment": tname}
            else:
                raise symbols.SymbolError(f"unsupported fixup target {tkind} {tname}")
        except symbols.SymbolError as exc:
            errors.append(f"+{at:#x} {loc_name} -> {tname}: {exc}")
            continue
        ow = orig[at:at + width]
        if loc_name == "pointer32":
            if tgt["kind"] not in ("function", "library", "startup"):
                errors.append(f"+{at:#x} far pointer to non-code {tname}")
                continue
            exp_off = (tgt["offset"] + addend) & 0xFFFF
            got_off, got_seg = word(ow, 0), word(ow, 2)
            if (got_off, got_seg) != (exp_off, tgt["frame"]):
                errors.append(f"+{at:#x} far {tname}: original {got_seg:04X}:{got_off:04X}, "
                              f"binding {tgt['frame']:04X}:{exp_off:04X}")
                continue
            cand_segwords.add(at + 2)
            covered.update(range(at, at + 4))
            res.bound.append({"at": at, "kind": "far", "target": tgt["logical"]})
        elif loc_name == "base16":
            frame = tgt.get("frame") if tgt["kind"] != "own_data" else dgroup_frame
            if tgt["kind"] == "data":
                frame = dgroup_frame
            if word(ow, 0) != frame:
                errors.append(f"+{at:#x} segment of {tname}: original {word(ow, 0):04X}, binding {frame:04X}")
                continue
            cand_segwords.add(at)
            covered.update(range(at, at + 2))
            res.bound.append({"at": at, "kind": "seg", "target": tname})
        elif loc_name == "offset16":
            got = word(ow, 0)
            if tgt["kind"] == "local_label":
                exp = (loc["offset"] + tgt["relative"]) & 0xFFFF
                if got != exp:
                    errors.append(f"+{at:#x} local label +{tgt['relative']:#x}: original {got:#06x}, "
                                  f"expected {exp:#06x}")
                    continue
                res.bound.append({"at": at, "kind": "local_label", "relative": tgt["relative"]})
            elif tgt["kind"] == "data":
                exp = (tgt["dgroup_offset"] + addend) & 0xFFFF
                if got != exp:
                    errors.append(f"+{at:#x} {tname}+{addend:#x}: original {got:#06x}, binding {exp:#06x}")
                    continue
                res.bound.append({"at": at, "kind": "data", "target": tname, "addend": addend,
                                  "provenance": tgt["provenance"]})
            elif tgt["kind"] == "own_data":
                own = module.segments.get("_DATA", b"")
                if tname == "_BSS" or addend >= len(own):
                    errors.append(f"+{at:#x} reference to candidate-local BSS/static at +{addend:#x}: "
                                  "declare it extern d_XXXX for function-level proof")
                    continue
                lit = own[addend:own.index(b"\0", addend) + 1] if b"\0" in own[addend:] else own[addend:]
                if img[dgroup_base + got:dgroup_base + got + len(lit)] != lit:
                    errors.append(f"+{at:#x} literal {lit[:24]!r} not found at original DGROUP:{got:04X}")
                    continue
                res.bound.append({"at": at, "kind": "literal", "dgroup_offset": got, "length": len(lit)})
            elif tgt["kind"] in ("function", "library", "startup", "code_data"):
                exp = (tgt["offset"] + addend) & 0xFFFF
                if got != exp:
                    errors.append(f"+{at:#x} offset of {tname}: original {got:#06x}, binding {exp:#06x}")
                    continue
                res.bound.append({"at": at, "kind": "code_offset", "target": tgt["logical"]})
            covered.update(range(at, at + 2))
        else:
            errors.append(f"+{at:#x} unsupported fixup location {loc_name}")
    # Relational checks for compile-time-resolved same-segment references.
    tables = []
    for f in census["functions"]:
        if f["start"] == ostart:
            tables = [(t0 - ostart, t1 - ostart) for t0, t1 in f["tables"]]
    a = 0
    while a < len(cand):
        tab = next((t for t in tables if t[0] <= a < t[1]), None)
        if tab:
            a = tab[1]
            continue
        if a in covered:
            a += 1
            continue
        ins = disasm.decode(bytes(cand), a, 0)
        if ins is None:
            break
        if a >= 1 and cand[a - 1] == 0x0E and ins.raw[0] in (0xE8, 0xB8, 0xB9, 0xBA, 0xBB, 0xBE, 0xBF) \
                and ins.size == 3 and orig[a - 1] == 0x0E and orig[a] == cand[a]:
            if ins.raw[0] == 0xE8:
                ctgt = (cstart + a + 3 + struct.unpack_from("<h", cand, a + 1)[0]) & 0xFFFF
                otgt_lin = (loc["frame"] << 4) + ((loc["offset"] + a + 3 + struct.unpack_from("<h", orig, a + 1)[0]) & 0xFFFF)
            else:
                ctgt = word(cand, a + 1)
                otgt_lin = (loc["frame"] << 4) + word(orig, a + 1)
            names = pubs_by_off.get(ctgt)
            oname = symbols.function_at(ep, otgt_lin)
            ok = False
            if names and oname:
                try:
                    ok = symbols.resolve(names[0], ep)["linear"] == otgt_lin
                except symbols.SymbolError:
                    ok = False
            if ok:
                covered.update(range(a + 1, a + 3))
                res.bound.append({"at": a, "kind": "near_cs", "target": oname})
            elif names or oname:
                errors.append(f"+{a:#x} push cs/{ins.mnem}: candidate -> {names}, original -> {oname}")
        a += max(ins.size, 1)
    missing = sorted(orig_relocs - cand_segwords)
    extra = sorted(cand_segwords - orig_relocs)
    if missing:
        errors.append(f"original relocations without candidate fixups at {[hex(x) for x in missing]}")
    if extra:
        errors.append(f"candidate segment fixups where original has no relocation: {[hex(x) for x in extra]}")
    res.covered = frozenset(covered)
    diffs = [i for i in range(len(cand)) if i not in covered and i not in attempted and cand[i] != orig[i]]
    res.diff_bytes = len(diffs)
    if diffs:
        res.first_diff = diffs[0]
    res.detail.extend(errors)
    if errors:
        res.status = "BINDING_ERROR" if not diffs else "DIFFER"
    elif diffs:
        res.status = "DIFFER"
    else:
        res.status = "EQUAL"
    return res


def _first_diff(res: Result) -> None:
    n = min(len(res.cand), len(res.orig))
    for i in range(n):
        if res.cand[i] != res.orig[i]:
            res.first_diff = i
            return
    res.first_diff = n


def instruction_diff(res: Result, context: int = 3, limit: int = 40) -> list:
    """Side-by-side instruction listing around differences (diagnostic only)."""
    def listing(buf, base):
        out, a = [], 0
        while a < len(buf):
            ins = disasm.decode(buf, a, 0)
            if ins is None:
                out.append((a, buf[a:a + 1].hex(), "db"))
                a += 1
                continue
            out.append((a, ins.raw.hex(), f"{ins.mnem} {ins.ops}".strip()))
            a += ins.size
        return out
    import difflib
    shown = bytearray(res.cand)
    for i in res.covered:           # verified bindings are not differences
        if i < len(shown) and i < len(res.orig):
            shown[i] = res.orig[i]
    lc, lo = listing(bytes(shown), res.cand_base), listing(res.orig, res.orig_base)
    kc = [x[2] for x in lc]
    ko = [x[2] for x in lo]
    sm = difflib.SequenceMatcher(None, kc, ko, autojunk=False)
    lines = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            if i2 - i1 > 2 * context:
                for k in range(i1, i1 + context):
                    lines.append(f"  {lc[k][0]:04x} {lc[k][2]}")
                lines.append("  ...")
                for k in range(i2 - context, i2):
                    lines.append(f"  {lc[k][0]:04x} {lc[k][2]}")
            else:
                for k in range(i1, i2):
                    lines.append(f"  {lc[k][0]:04x} {lc[k][2]}")
            continue
        for k in range(i1, i2):
            lines.append(f"- {lc[k][0]:04x} {lc[k][1]:<14} {lc[k][2]}")
        for k in range(j1, j2):
            lines.append(f"+ {lo[k][0]:04x} {lo[k][1]:<14} {lo[k][2]}")
        if len(lines) > limit * 3:
            break
    return lines
