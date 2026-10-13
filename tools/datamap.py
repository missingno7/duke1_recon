"""Per-episode DGROUP offset maps (reference episode dn1 -> dn2/dn3).

Two independent sources, required to agree:
  1. content alignment of the initialised DGROUP bytes (relocated words
     masked); equal-length replaced runs map positionally;
  2. BSS: the startup's bdata@/edata@ bounds give identical BSS sizes in all
     three episodes, so BSS maps by the constant initialised-data delta;
cross-validated against every displacement/immediate pair that differs
between shape-identical functions (tools/atlas.py records them).

Used to bind logical data symbols (named by their dn1 offset, d_XXXX) to the
address each episode's code must contain.
"""
from __future__ import annotations

import bisect
import difflib
import sys
from functools import lru_cache
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, load_json  # noqa: E402
import oracle  # noqa: E402

REF = "dn1"


def _dgroup(ep: str) -> tuple:
    img, relocs = oracle.load_image(ep)
    c = load_json(BUILD / "census" / f"{ep}.json")
    base = c["dgroup_frame"] << 4
    data = bytearray(img[base:])
    for s, o in relocs:
        a = (s << 4) + o
        if a >= base:
            data[a - base:a - base + 2] = b"\xffR"
    return bytes(data), c["startup"]["bss_start"], c["startup"]["bss_end"]


@lru_cache(maxsize=None)
def segments(ep: str) -> tuple:
    """Sorted ((ref_start, ref_end, delta), ...) such that a dn1 DGROUP offset
    x in [ref_start, ref_end) maps to x + delta in `ep`."""
    if ep == REF:
        d, bs, be = _dgroup(REF)
        return ((0, be, 0),)
    a, abs_, abe = _dgroup(REF)
    b, bbs, bbe = _dgroup(ep)
    if abe - abs_ != bbe - bbs:
        raise RuntimeError(f"BSS sizes differ between {REF} and {ep}; constant BSS map invalid")
    sm = difflib.SequenceMatcher(None, a[:abs_], b[:bbs], autojunk=False)
    segs = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal" or (tag == "replace" and i2 - i1 == j2 - j1):
            segs.append([i1, i2, j1 - i1])
    segs.append([abs_, abe, bbs - abs_])
    merged = []
    for s in segs:
        if merged and merged[-1][1] == s[0] and merged[-1][2] == s[2]:
            merged[-1][1] = s[1]
        else:
            merged.append(s)
    return tuple(tuple(s) for s in merged)


@lru_cache(maxsize=None)
def anchors(ep: str) -> dict:
    """Code-derived (ref value -> episode value) pairs with a unique image
    (written by tools/atlas.py).  They take precedence over the content
    alignment, which is unreliable inside runs of similar text."""
    path = BUILD / "census" / "anchors.json"
    if ep == REF or not path.exists():
        return {}
    out = {}
    for x, ys in load_json(path).get(ep, {}).items():
        if len(ys) == 1:
            out[int(x)] = int(next(iter(ys)))
    return out


def reset() -> None:
    anchors.cache_clear()


def content_map(ep: str, ref_offset: int) -> int | None:
    segs = segments(ep)
    starts = [s[0] for s in segs]
    k = bisect.bisect_right(starts, ref_offset) - 1
    if k >= 0 and segs[k][0] <= ref_offset < segs[k][1]:
        return ref_offset + segs[k][2]
    # one-past-the-end of a mapped run (e.g. &array[N]) maps by that run
    if k >= 0 and ref_offset == segs[k][1]:
        return ref_offset + segs[k][2]
    return None


def to_episode(ep: str, ref_offset: int) -> int | None:
    a = anchors(ep).get(ref_offset)
    return a if a is not None else content_map(ep, ref_offset)


def provenance(ep: str, ref_offset: int) -> str:
    if ep == REF:
        return "reference"
    if ref_offset in anchors(ep):
        return "code-anchor"
    return "content-alignment" if content_map(ep, ref_offset) is not None else "unmapped"


def region(ref_offset: int) -> str:
    _, bs, be = _dgroup(REF)
    if ref_offset < bs:
        return "DATA"
    if ref_offset < be:
        return "BSS"
    return "OUTSIDE"


def validate(pairs: dict) -> dict:
    """pairs: {ep: {(ref_value, ep_value): count}} from shape-identical code.
    Agreement statistics of the content alignment against code evidence.
    A disagreement means either an alignment error (the code anchor wins in
    to_episode) or an episode-specific constant; both are reported."""
    out = {}
    for ep, pp in pairs.items():
        agree, conflict, unmapped = 0, [], 0
        for (x, y), n in pp.items():
            m = content_map(ep, x)
            if m is None:
                unmapped += 1
            elif m == y:
                agree += 1
            else:
                conflict.append([x, y, m])
        out[ep] = {"agree": agree, "conflicts": sorted(conflict), "unmapped": unmapped,
                   "segments": len(segments(ep))}
    return out


if __name__ == "__main__":
    for ep in EPISODES:
        segs = segments(ep)
        print(ep, len(segs), "segments; first", segs[:3], "last", segs[-1])
