"""Generator v2 for the standalone tree: one shared header plus one file per unit.

Used by `python tools/standalone.py generate`.  From the canonical per-function
sources it builds:

  DUKE.H     includes, struct types, one prototype per function (from its
             definition), and every extern global whose declaration agrees in
             both units, ordered by DN1 address (BSS names therefore first appear
             in address order: rule BSS-ORDER ties);
  GAME1.C    #include "duke.h", the unit's own macros, conditional blocks and the
  GAME2.C    few globals the two units declare differently, its BSS definitions,
             then initialised data and functions in original order (rule
             DATA-LAYOUT), each function preceded by its notes.

Nothing here decides code generation by itself: the result is proven by
building it (standalone.py build).
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import EPISODES, RECIPES, ROOT, load_json  # noqa: E402
import decls  # noqa: E402
import symbols  # noqa: E402
import tubuild  # noqa: E402

FUN = re.compile(r"\b((?:g[12]|asm)_[0-9a-f]{4})\s*\(")
GNAME = re.compile(r"\b(d_(?:dn[123]_)?[0-9a-f]{4}_?|c_[0-9a-f]{4})\b")
BOILER = ("candidate skeleton generated", "keep them\n   consistent", "Everything else is a guess")


def ws(s: str) -> str:
    """Whitespace- and pointer-spacing-insensitive form for comparing declarations."""
    s = re.sub(r"\s*\*\s*", " *", s)
    s = re.sub(r"\s*([,;()\[\]])\s*", r"\1", s)
    return re.sub(r"\s+", " ", s).strip()


def strip_trailing_comment(line: str) -> str:
    return re.sub(r"\s*/\*.*?\*/\s*$", "", line).rstrip()


def parse_prelude(text: str) -> dict:
    """Classify a function file's prelude into items."""
    items = {"include": [], "pre": [], "cond": [], "struct": {}, "extern": {}, "libproto": {},
             "comment": [], "other": []}
    lines = text.split("\n")
    i = 0
    while i < len(lines):
        line = lines[i]
        s = line.strip()
        if not s:
            i += 1
            continue
        if s.startswith("/*"):
            buf = [line]
            while "*/" not in lines[i] and i + 1 < len(lines):
                i += 1
                buf.append(lines[i])
            txt = "\n".join(buf).strip()
            if not any(b in txt for b in BOILER):
                items["comment"].append(txt)
            i += 1
            continue
        if re.match(r"#\s*if", s):
            depth, buf = 0, []
            while i < len(lines):
                t = lines[i].strip()
                if re.match(r"#\s*if", t):
                    depth += 1
                elif re.match(r"#\s*endif", t):
                    depth -= 1
                buf.append(strip_trailing_comment(lines[i]))
                i += 1
                if depth == 0:
                    break
            items["cond"].append("\n".join(buf))
            continue
        if s.startswith("#include"):
            items["include"].append(s)
            i += 1
            continue
        if s.startswith("#"):
            items["pre"].append(strip_trailing_comment(s))
            i += 1
            continue
        if re.match(r"(typedef\s+)?struct\s+\w+\s*\{", s) or re.match(r"(typedef\s+)?union\s+\w+\s*\{", s):
            buf = [line]
            depth = line.count("{") - line.count("}")
            while (depth > 0 or not buf[-1].rstrip().endswith(";")) and i + 1 < len(lines):
                i += 1
                buf.append(lines[i])
                depth += lines[i].count("{") - lines[i].count("}")
            txt = "\n".join(strip_trailing_comment(b) for b in buf).strip()
            tag = re.match(r"(?:typedef\s+)?(?:struct|union)\s+(\w+)", txt).group(1)
            items["struct"][tag] = txt
            i += 1
            continue
        # a stub definition `T f(...) {...}` of one of our functions: skipped (prototypes are generated)
        if FUN.search(s) and re.search(r"\)\s*\{", s):
            depth = s.count("{") - s.count("}")
            while depth > 0 and i + 1 < len(lines):
                i += 1
                depth += lines[i].count("{") - lines[i].count("}")
            i += 1
            continue
        decl = strip_trailing_comment(s)
        if FUN.search(decl) and decl.endswith(";") and "(" in decl and not GNAME.search(decl):
            i += 1                                   # prototype of one of our functions: generated
            continue
        m = GNAME.search(decl)
        if decl.startswith("extern") and m and "(" not in decl.split(m.group(1))[0][-1:]:
            items["extern"][m.group(1)] = decl
        elif m and decl.startswith("extern"):
            items["extern"][m.group(1)] = decl
        elif re.search(r"\b(\w+)\s*\([^;]*\)\s*;$", decl):
            name = re.search(r"\b(\w+)\s*\(", decl).group(1)
            items["libproto"][name] = decl
        else:
            items["other"].append(decl)
        i += 1
    return items


def source_file(fid: str) -> Path:
    return ROOT / load_json(RECIPES / f"{fid}.json")["source"]


def definition_header(fid: str, body: str) -> str:
    """`RET CONV NAME(PARAMS)` of the function's definition, as a prototype."""
    cname = load_json(RECIPES / f"{fid}.json").get("name") or fid
    m = re.search(r"(?ms)^([^\n;{}#]*\b" + re.escape(cname) + r"\s*\((?:[^()]|\([^()]*\))*\))\s*\{", body)
    head = ws(m.group(1))
    head = re.sub(r"\bregister\s+", "", head)
    return head + ";"


def addr_key(name: str) -> int:
    m = re.match(r"d_(?:dn[123]_)?([0-9a-f]{4})_?$", name)
    return int(m.group(1), 16) if m else 1 << 20


def collect(unit: str) -> dict:
    from standalone import merged_order          # noqa: E402  (shared helper)
    order = merged_order(unit)
    agg = {"include": [], "pre": [], "cond": [], "struct": {}, "extern": {}, "libproto": {}, "other": [],
           "notes": {}, "bodies": {}, "protos": {}, "order": order}
    for fid in dict.fromkeys(f for f, _ in order):
        pre, body = tubuild.split(source_file(fid))
        it = parse_prelude(pre)
        for k in ("include", "pre", "other"):
            for x in it[k]:
                if x not in agg[k]:
                    agg[k].append(x)
        for c in it["cond"]:
            if ws(c) not in [ws(x) for x in agg["cond"]]:
                agg["cond"].append(c)
        for k in ("struct", "extern", "libproto"):
            for name, txt in it[k].items():
                if name in agg[k] and ws(agg[k][name]) != ws(txt):
                    raise ValueError(f"{unit}: conflicting {k} for {name}: {agg[k][name]!r} vs {txt!r} ({fid})")
                agg[k].setdefault(name, txt)
        agg["notes"][fid] = it["comment"]
        agg["bodies"][fid] = body.strip("\n")
        if (load_json(RECIPES / f"{fid}.json").get("name") or fid) != "main":
            agg["protos"][fid] = definition_header(fid, body)
    return agg


def asm_prototypes() -> dict:
    views = decls.collect()["functions"]
    out = {}
    for fid in tubuild.unit_functions("ASM_TEXT", "dn1"):
        vs = views.get(fid)
        if not vs:
            continue
        v = vs[0]
        conv = "" if v["conv"] == "cdecl" else v["conv"] + " "
        out[fid] = f"{v['ret']} {conv}{fid}({v['params']});"
    return out


def generate_texts() -> dict:
    units = {u: collect(u) for u, _ in (("G1_TEXT", None), ("G2_TEXT", None))}
    g1, g2 = units["G1_TEXT"], units["G2_TEXT"]
    # shared declarations
    includes = list(dict.fromkeys(g1["include"] + g2["include"]))
    structs, local_structs = {}, {"G1_TEXT": {}, "G2_TEXT": {}}
    for u, a in units.items():
        for tag, txt in a["struct"].items():
            other = units["G2_TEXT" if u == "G1_TEXT" else "G1_TEXT"]["struct"].get(tag)
            if other is not None and ws(other) != ws(txt):
                local_structs[u][tag] = txt
            else:
                structs.setdefault(tag, txt)
    # every BSS object must first appear in address order (rule BSS-ORDER ties), including
    # objects no code references: declare all of them from the BSS definitions
    for u in units:
        for fr in (tubuild.data_plan(u) or {}).get("fragments", []):
            if fr["before"] != "header":
                continue
            for line in (ROOT / fr["file"]).read_text("latin-1").splitlines():
                m = re.match(r"^\s*(?!extern|static|typedef|struct\s+\w+\s*\{)(.*\b(d_[0-9a-f]{4}_)\b.*;)\s*(/\*.*)?$", line)
                if m and m.group(2) not in units["G1_TEXT"]["extern"] and m.group(2) not in units["G2_TEXT"]["extern"]:
                    units[u]["extern"][m.group(2)] = "extern " + m.group(1).strip()
    externs, local_externs = {}, {"G1_TEXT": {}, "G2_TEXT": {}}
    for u, a in units.items():
        for name, txt in a["extern"].items():
            other = units["G2_TEXT" if u == "G1_TEXT" else "G1_TEXT"]["extern"].get(name)
            if other is not None and ws(other) != ws(txt):
                local_externs[u][name] = txt
            else:
                externs.setdefault(name, txt)
    libprotos, local_lib = {}, {"G1_TEXT": {}, "G2_TEXT": {}}
    for u, a in units.items():
        for name, txt in a["libproto"].items():
            other = units["G2_TEXT" if u == "G1_TEXT" else "G1_TEXT"]["libproto"].get(name)
            if other is not None and ws(other) != ws(txt):
                local_lib[u][name] = txt
            else:
                libprotos.setdefault(name, txt)

    h = ["/* DUKE.H - declarations shared by both translation units of Duke Nukum v2.0.",
         "",
         "   Names are logical ids: g1_XXXX / g2_XXXX / asm_XXXX are functions at frame",
         "   offset XXXX in DN1; d_XXXX is the global at DN1 DGROUP offset XXXX, d_XXXX_ an",
         "   uninitialised (BSS) one.  Turbo C orders a unit's BSS by a hash of the name,",
         "   ties by first appearance (docs: rule BSS-ORDER): the BSS declarations below",
         "   are therefore kept in address order. */", "",
         "#ifndef DUKE_H", "#define DUKE_H", ""]
    h += includes + [""]
    if structs:
        h += ["/* ---- data structures ---- */", ""]
        h += [structs[t] for t in structs] + [""]
    # functions the other unit declares differently from their definition (legal across
    # separately compiled units, and the code depends on it: e.g. g2_3d1e is defined void
    # but G1 tests its AX) get a prototype in each unit file instead of the header
    views = decls.collect()["functions"]
    unit_of = lambda f: "G1_TEXT" if "/g1/" in f else ("G2_TEXT" if "/g2/" in f else None)
    vkey = lambda v: (v["ret"], v["conv"], v["params"])
    per_unit_protos = {}
    shared = set()
    for u, a in units.items():
        for fid in a["protos"]:
            vs = views.get(fid, [])
            dv = next((v for v in vs if v["kind"] == "definition"), None)
            other = "G2_TEXT" if u == "G1_TEXT" else "G1_TEXT"
            ov = [v for v in vs if unit_of(v["file"]) == other and dv and vkey(v) != vkey(dv)]
            if ov:
                v = ov[0]
                conv = "" if v["conv"] == "cdecl" else v["conv"] + " "
                per_unit_protos[fid] = {u: a["protos"][fid], other: f"{v['ret']} {conv}{fid}({v['params']});"}
            else:
                shared.add(fid)

    def per_unit(texts: dict) -> list:
        """A declaration the two units make differently: both, chosen by UNIT."""
        return ["#if UNIT == 1", texts["G1_TEXT"], "#else", texts["G2_TEXT"], "#endif"]
    for a, title in ((g1, "first unit (GAME1.C)"), (g2, "second unit (GAME2.C)")):
        h += [f"/* ---- functions of the {title} ---- */", ""]
        for f in dict.fromkeys(f for f, _ in a["order"]):
            if f in per_unit_protos:
                h += per_unit(per_unit_protos[f])
            elif f in a["protos"] and f in shared:
                h.append(a["protos"][f])
        h.append("")
    h += ["/* ---- ProGraphx EGA/VGA Toolbox (TOOLBOX.ASM) ---- */", ""]
    h += list(asm_prototypes().values()) + [""]
    if libprotos:
        h += ["/* ---- runtime library functions declared without their header ---- */", ""]
        h += list(libprotos.values()) + [""]
    h += ["/* ---- global data (by DN1 DGROUP offset) ---- */", ""]
    names = set(externs) | set(local_externs["G1_TEXT"]) | set(local_externs["G2_TEXT"])
    for n in sorted(names, key=addr_key):
        if n in externs:
            h.append(externs[n])
        else:
            h += per_unit({u: local_externs[u].get(n, "/* not declared in this unit */") for u in units})
    h += ["", "#endif", ""]
    header = "\n".join(h)

    files = {"DUKE.H": header}

    def frag_text(fr: Path) -> str:
        """A data fragment without struct definitions the header already provides."""
        t = fr.read_text("latin-1")
        for m in list(re.finditer(r"(?ms)^(?:typedef\s+)?struct\s+(\w+)\s*\{.*?\}\s*\w*\s*;[ \t]*\n?", t)):
            if m.group(1) in structs:
                if ws(structs[m.group(1)]) != ws(m.group(0).strip()):
                    raise ValueError(f"{fr}: struct {m.group(1)} differs from the header")
                t = t.replace(m.group(0), "")
        return re.sub(r"(?m)^/\* Accepted G1 struct definitions required by G2 BSS arrays\. \*/\n", "", t).strip()
    for u, fname, title in (("G1_TEXT", "GAME1.C", "first translation unit (startup, main loop, levels, actors, files)"),
                            ("G2_TEXT", "GAME2.C", "second translation unit (menus, text screens, high scores, timer and sound)")):
        a = units[u]
        plan = tubuild.data_plan(u)
        frags = {}
        for fr in (plan or {}).get("fragments", []):
            frags.setdefault(fr["before"], []).append(ROOT / fr["file"])
        out = [f"/* {fname} - {title} of Duke Nukum v2.0. */", "",
               f"#define UNIT {fname[4]}      /* selects this unit's declarations in duke.h */",
               '#include "duke.h"', ""]
        if a["pre"]:
            out += a["pre"] + [""]
        for c in a["cond"]:
            out += [c, ""]
        if a["other"]:
            out += a["other"] + [""]
        loc = list(local_structs[u].values()) + list(local_lib[u].values())
        if loc:
            out += loc + [""]
        body = "\n".join(out) + "\n"
        for fr in frags.get("header", []):
            body += "/* ---- uninitialised data (BSS) ---- */\n\n" + frag_text(fr) + "\n\n"
        for fr in frags.get("start", []):
            body += "/* ---- initialised data ---- */\n\n" + frag_text(fr) + "\n\n"
        from standalone import _episode_cond      # noqa: E402
        for fid, eps in a["order"]:
            for fr in frags.get(fid, []):
                body += "/* ---- initialised data, placed here for the literal pool ---- */\n\n" \
                        + frag_text(fr) + "\n\n"
            guarded = eps != set(EPISODES)
            if guarded:
                body += f"#if {_episode_cond(eps)}\n/* {fid}: at this place in the " \
                        f"{', '.join(sorted(e.upper() for e in eps))} source */\n"
            notes = "\n".join(a["notes"][fid])
            body += (notes + "\n" if notes else "") + a["bodies"][fid] + "\n"
            body += "#endif\n\n" if guarded else "\n"
        for fr in frags.get("end", []):
            body += frag_text(fr) + "\n\n"
        files[fname] = body
    return files
