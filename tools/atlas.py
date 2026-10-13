"""Tri-episode function atlas: one logical function -> up to three locations.

    python tools/atlas.py            rebuild evidence/atlas.json from build/census
    python tools/atlas.py --check    fail if evidence/atlas.json is out of date

Signals (each recorded separately; none alone is treated as identity):
  bytes      relocation-masked bytes identical
  shape      instruction shapes identical (displacements/immediates blanked)
  size       extent sizes identical
  calls      every resolved callee maps to the aligned callee in the other episode
  data       every absolute data displacement agrees with the global DGROUP
             offset map inferred from shape-identical functions
  order      position in the alignment of the translation unit's function order

Classification:
  SHARED_EXACT       bytes equal in all present episodes
  SHARED_SHAPE       shapes equal, calls+data consistent: same C, different data layout
  PARAMETERIZED      aligned, shapes differ (constants or small code differences)
  EPISODE_SPECIFIC   present in only some episodes
  UNRESOLVED         aligned only weakly (needs review)
"""
from __future__ import annotations

import argparse
import difflib
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, EVIDENCE, atomic_json, canonical_json, load_json  # noqa: E402
import datamap  # noqa: E402
import disasm  # noqa: E402
import oracle  # noqa: E402

ATLAS = EVIDENCE / "atlas.json"
REF = "dn1"


def shapes(img: bytes, f: dict) -> list:
    out, a = [], f["start"]
    while a < f["end"]:
        # tables are data: compare them raw
        tab = next((t for t in f["tables"] if t[0] <= a < t[1]), None)
        if tab:
            out.append(b"T" + img[a:tab[1]])
            a = tab[1]
            continue
        ins = disasm.decode(img, a, 0)
        if ins is None:
            out.append(b"?")
            a += 1
            continue
        out.append(disasm.shape(ins))
        a += ins.size
    return out


def field_pairs(ia: bytes, fa: dict, ib: bytes, fb: dict, ra: set = frozenset(), rb: set = frozenset()) -> Counter:
    """(ref value, other value) for every disp/imm field that differs between
    two shape-identical functions (instruction boundaries coincide)."""
    out = Counter()
    a, b = fa["start"], fb["start"]
    tabs = [(t[0] - fa["start"], t[1] - fa["start"]) for t in fa["tables"]]
    while a < fa["end"]:
        rel = a - fa["start"]
        t = next((t for t in tabs if t[0] <= rel < t[1]), None)
        if t:
            b += t[1] - rel
            a = fa["start"] + t[1]
            continue
        x, y = disasm.decode(ia, a, 0), disasm.decode(ib, b, 0)
        if x is None or y is None or x.size != y.size:
            break
        if not x.far:
            for o, n in ((x.disp_off, x.disp_size), (x.imm_off, x.imm_size)):
                if n == 2 and x.target is None and (a + o) not in ra and (b + o) not in rb:
                    va = int.from_bytes(x.raw[o:o + 2], "little")
                    vb = int.from_bytes(y.raw[o:o + 2], "little")
                    if va != vb:
                        out[(va, vb)] += 1
        a += x.size
        b += y.size
    return out


def similarity(sa: list, sb: list) -> float:
    if sa == sb:
        return 1.0
    return difflib.SequenceMatcher(None, sa, sb, autojunk=False).ratio()


def align(A: list, B: list, score) -> list:
    """Needleman-Wunsch over function lists; returns [(i or None, j or None)]."""
    n, m = len(A), len(B)
    gap = -0.4
    S = [[0.0] * (m + 1) for _ in range(n + 1)]
    P = [[None] * (m + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        S[i][0], P[i][0] = S[i - 1][0] + gap, "u"
    for j in range(1, m + 1):
        S[0][j], P[0][j] = S[0][j - 1] + gap, "l"
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            d = S[i - 1][j - 1] + score(i - 1, j - 1)
            u = S[i - 1][j] + gap
            l_ = S[i][j - 1] + gap
            S[i][j], P[i][j] = max((d, "d"), (u, "u"), (l_, "l"))
    out, i, j = [], n, m
    while i or j:
        p = P[i][j]
        if p == "d":
            out.append((i - 1, j - 1))
            i, j = i - 1, j - 1
        elif p == "u":
            out.append((i - 1, None))
            i -= 1
        else:
            out.append((None, j - 1))
            j -= 1
    return out[::-1]


def build() -> dict:
    C = {e: load_json(BUILD / "census" / f"{e}.json") for e in EPISODES}
    imgs = {e: oracle.load_image(e)[0] for e in EPISODES}
    rsets = {e: {(sg << 4) + o for sg, o in oracle.load_image(e)[1]} for e in EPISODES}
    segnames = [s["name"] for s in C[REF]["segments"] if s["kind"] in ("game", "asm")]
    F = {e: {s: [f for f in C[e]["functions"] if f["segment"] == s] for s in segnames} for e in EPISODES}
    SH = {e: {s: [shapes(imgs[e], f) for f in F[e][s]] for s in segnames} for e in EPISODES}

    # 1. alignment per segment, every other episode against the reference
    rows = {s: [] for s in segnames}     # list of {ep: index}
    for s in segnames:
        maps = {}
        for e in EPISODES:
            if e == REF:
                continue
            A, B = F[REF][s], F[e][s]

            def score(i, j, s=s, e=e, A=A, B=B):
                if A[i]["shape"] == B[j]["shape"]:
                    return 2.0
                sim = similarity(SH[REF][s][i], SH[e][s][j])
                return 2.0 * sim - 1.0 if sim > 0.6 else -1.0
            maps[e] = align(A, B, score)
        # merge: rows keyed by reference index; unmatched other-episode
        # functions become their own rows, placed after their predecessor.
        by_ref = {i: {REF: i} for i in range(len(F[REF][s]))}
        extra = []
        for e, al in maps.items():
            last_ref = -1
            for i, j in al:
                if i is not None and j is not None:
                    by_ref[i][e] = j
                    last_ref = i
                elif i is None:
                    extra.append((last_ref, e, j))
        # pair extras of different episodes that align with each other
        ordered = []
        for i in range(len(F[REF][s])):
            ordered.append(by_ref[i])
            here = [x for x in extra if x[0] == i]
            used = set()
            for k, (_, e1, j1) in enumerate(here):
                if k in used:
                    continue
                row = {e1: j1}
                for k2, (_, e2, j2) in enumerate(here):
                    if k2 != k and k2 not in used and e2 not in row and \
                            F[e1][s][j1]["shape"] == F[e2][s][j2]["shape"]:
                        row[e2] = j2
                        used.add(k2)
                used.add(k)
                ordered.append(row)
        head = [x for x in extra if x[0] == -1]
        rows[s] = [{e: j} for _, e, j in head] + ordered

    # 2. index: (ep, linear start) -> logical id
    ids = {}
    logical = []
    for s in segnames:
        prefix = s.split("_")[0].lower()
        for row in rows[s]:
            if REF in row:
                lid = f"{prefix}_{F[REF][s][row[REF]]['offset']:04x}"
            else:
                e0 = sorted(row)[0]
                lid = f"{prefix}_{e0}_{F[e0][s][row[e0]]['offset']:04x}"
            for e, j in row.items():
                ids[(e, F[e][s][j]["start"])] = lid
            logical.append((lid, s, row))

    # 3. displacement/immediate pairs that differ between shape-identical
    #    functions; validated against the independent DGROUP map.
    pairs = {e: Counter() for e in EPISODES if e != REF}
    fn_pairs = {}
    for lid, s, row in logical:
        if REF not in row:
            continue
        fa = F[REF][s][row[REF]]
        for e in pairs:
            if e in row and F[e][s][row[e]]["shape"] == fa["shape"]:
                pp = field_pairs(imgs[REF], fa, imgs[e], F[e][s][row[e]], rsets[REF], rsets[e])
                fn_pairs[(lid, e)] = pp
                pairs[e].update(pp)
    anchors = {e: {} for e in pairs}
    for e, pp in pairs.items():
        for (x, y), n in pp.items():
            anchors[e].setdefault(x, {})[y] = anchors[e].get(x, {}).get(y, 0) + n
    atomic_json(BUILD / "census" / "anchors.json",
                {e: {str(x): ys for x, ys in sorted(m.items())} for e, m in anchors.items()})
    datamap.reset()
    dm_report = datamap.validate(pairs)
    bad = {e: {tuple(c[:2]) for c in dm_report[e]["conflicts"]} for e in pairs}

    # 4. per logical function evidence
    out = []
    for lid, s, row in logical:
        locs = {}
        for e, j in sorted(row.items()):
            f = F[e][s][j]
            locs[e] = {"start": f["start"], "offset": f["offset"], "frame": f["frame"], "size": f["size"],
                       "sha256": f["sha256"], "reloc_masked_sha256": f["reloc_masked_sha256"],
                       "shape": f["shape"], "boundary": f["status"]}
        present = sorted(row)
        ev = {"present": present}
        if len(present) > 1:
            fs = {e: F[e][s][row[e]] for e in present}
            base = present[0]
            ev["bytes"] = len({fs[e]["reloc_masked_sha256"] for e in present}) == 1
            ev["shape"] = len({fs[e]["shape"] for e in present}) == 1
            ev["size"] = len({fs[e]["size"] for e in present}) == 1
            # call consistency: callee logical ids equal across episodes
            callee_sets = {}
            for e in present:
                seq = []
                for c in fs[e]["calls"]:
                    t = c.get("target")
                    seq.append((c["kind"], ids.get((e, t), f"ext:{t}" if t is None else "lib")))
                callee_sets[e] = seq
            ev["calls"] = len({tuple(v) for v in callee_sets.values()}) == 1
            # every differing displacement/immediate agrees with the DGROUP map
            if REF in present and ev["shape"]:
                ev["data"] = all(not (set(fn_pairs.get((lid, e), {})) & bad[e])
                                 and all(datamap.to_episode(e, x) == y for x, y in fn_pairs.get((lid, e), {}))
                                 for e in present if e != REF)
            if not ev["shape"]:
                ev["similarity"] = round(min(similarity(SH[base][s][row[base]], SH[e][s][row[e]])
                                             for e in present[1:]), 3)
        if len(present) < 3:
            cls = "EPISODE_SPECIFIC"
        elif ev.get("bytes"):
            cls = "SHARED_EXACT"
        elif ev.get("shape") and ev.get("calls") and ev.get("data", False):
            cls = "SHARED_SHAPE"
        elif ev.get("similarity", 0) >= 0.8 or ev.get("shape"):
            cls = "PARAMETERIZED"
        else:
            cls = "UNRESOLVED"
        conf = {"SHARED_EXACT": "high", "SHARED_SHAPE": "high", "PARAMETERIZED": "medium",
                "EPISODE_SPECIFIC": "medium", "UNRESOLVED": "low"}[cls]
        if any(v["boundary"] not in ("VERIFIED", "ASM_VERIFIED") for v in locs.values()):
            conf = "low"
        out.append({"id": lid, "segment": s, "class": cls, "confidence": conf,
                    "locations": locs, "evidence": ev})
    stats = Counter((x["segment"], x["class"]) for x in out)
    return {
        "generated_by": "tools/atlas.py from build/census (regenerable; committed for review/diff)",
        "reference_episode": REF,
        "functions": out,
        "data_map_validation": {e: {"agree": v["agree"], "unmapped": v["unmapped"],
                                    "conflicts": [[hex(x) for x in c] for c in v["conflicts"]],
                                    "segments": v["segments"]} for e, v in dm_report.items()},
        "stats": {f"{a}/{b}": n for (a, b), n in sorted(stats.items())},
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    doc = build()
    if a.check:
        if not ATLAS.exists() or ATLAS.read_text() != canonical_json(doc):
            print("evidence/atlas.json is stale; run tools/atlas.py")
            return 1
        print("atlas up to date")
        return 0
    atomic_json(ATLAS, doc)
    for k, v in doc["stats"].items():
        print(f"  {k:32s} {v}")
    for e, v in doc["data_map_validation"].items():
        print(f"  datamap {e}: {v['agree']} code pairs agree, {len(v['conflicts'])} conflicts, "
              f"{v['unmapped']} unmapped, {v['segments']} segments")
    return 0


if __name__ == "__main__":
    sys.exit(main())
