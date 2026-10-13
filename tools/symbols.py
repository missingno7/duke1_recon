"""Per-episode symbol binding for proofs.

A name used by candidate source resolves, for one episode, to the address
that episode's original code must contain:

  g1_XXXX / g2_XXXX / asm_XXXX   logical function (evidence/atlas.json)
  d_XXXX                         logical DGROUP object named by its dn1 offset;
                                 other episodes via tools/datamap.py
  d_dnN_XXXX                     object that exists only in episode N, at that
                                 episode's DGROUP offset (use under #if EPISODE)
  library / startup publics      CL.LIB / C0L.OBJ publics located by the census
  aliases                        layout/symbols.json {"alias": "logical name"}

Names are normalised the way Turbo C decorates them: cdecl adds one leading
underscore, pascal upper-cases; resolution is case-insensitive after
stripping one underscore.  Binding is relative to this table; data layout
itself is only proven by the translation-unit/link build.
"""
from __future__ import annotations

import re
import sys
from functools import lru_cache
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EVIDENCE, LAYOUT, load_json  # noqa: E402
import datamap  # noqa: E402


class SymbolError(KeyError):
    pass


def norm(name: str) -> str:
    n = name[1:] if name.startswith("_") else name
    return n.lower()


@lru_cache(maxsize=None)
def atlas() -> dict:
    return {f["id"]: f for f in load_json(EVIDENCE / "atlas.json")["functions"]}


@lru_cache(maxsize=None)
def aliases() -> dict:
    p = LAYOUT / "symbols.json"
    if not p.exists():
        return {}
    return {norm(k): v for k, v in load_json(p).get("aliases", {}).items()}


@lru_cache(maxsize=None)
def census(ep: str) -> dict:
    return load_json(BUILD / "census" / f"{ep}.json")


@lru_cache(maxsize=None)
def runtime(ep: str) -> dict:
    out = {}
    c = census(ep)
    frames = {}
    for h in c["library_modules"]:
        frames[h["module"]] = 0 if h["segment"] == "_TEXT" else h["start"] >> 4
    for s in c["symbols"]:
        if s["kind"] == "startup":
            frame = 0
        else:
            frame = frames[s["module"]]
        out[norm(s["name"])] = {"kind": s["kind"], "linear": s["linear"], "frame": frame,
                                "offset": s["linear"] - (frame << 4), "name": s["name"]}
    return out


# d_XXXX names a global by its DN1 DGROUP offset.  BSS globals carry a trailing
# underscore (d_XXXX_): Turbo C orders a unit's _BSS by a hash of the name
# (rule BSS-ORDER) and d_XXXX_ names all hash alike, so declaration order decides.
_DATA = re.compile(r"^d_([0-9a-f]{4})_?$")
_EPDATA = re.compile(r"^d_(dn[123])_([0-9a-f]{4})$")   # episode-only object, that episode's offset
_CODEDATA = re.compile(r"^c_([0-9a-f]{4})$")            # data inside the shared startup/asm _TEXT


def resolve(name: str, ep: str) -> dict:
    key = norm(name)
    if key in aliases():            # normalise once only: `__exit` must stay `_exit` (C0), not `exit` (CL.LIB)
        key = norm(aliases()[key])
    if key in atlas():
        f = atlas()[key]
        loc = f["locations"].get(ep)
        if loc is None:
            raise SymbolError(f"{key} has no location in {ep}")
        return {"kind": "function", "logical": key, "linear": loc["start"], "frame": loc["frame"],
                "offset": loc["offset"]}
    m = _DATA.match(key)
    if m:
        ref = int(m.group(1), 16)
        off = datamap.to_episode(ep, ref)
        if off is None:
            raise SymbolError(f"{key} has no mapped DGROUP offset in {ep}")
        return {"kind": "data", "logical": key, "dgroup_offset": off,
                "provenance": datamap.provenance(ep, ref)}
    m = _CODEDATA.match(key)
    if m:
        off = int(m.group(1), 16)
        segs = {s["name"]: s for s in census(ep)["segments"]}
        if not (segs["C0_TEXT"]["start"] <= off < segs["ASM_TEXT"]["start"] + segs["ASM_TEXT"]["size"]):
            raise SymbolError(f"{key} is outside the startup/assembly _TEXT region")
        return {"kind": "code_data", "logical": key, "linear": off, "frame": 0, "offset": off}
    m = _EPDATA.match(key)
    if m:
        if m.group(1) != ep:
            raise SymbolError(f"{key} exists only in {m.group(1)}; guard its use with #if EPISODE")
        return {"kind": "data", "logical": key, "dgroup_offset": int(m.group(2), 16),
                "provenance": "episode-only"}
    rt = runtime(ep)
    if key in rt:
        return {**rt[key], "logical": key}
    raise SymbolError(f"unknown symbol {name!r}")


def function_at(ep: str, linear: int) -> str | None:
    for fid, f in atlas().items():
        loc = f["locations"].get(ep)
        if loc and loc["start"] == linear:
            return fid
    for k, v in runtime(ep).items():
        if v["linear"] == linear:
            return k
    return None
