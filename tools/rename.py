"""Rename identifiers in src/ without changing the program.

    python tools/rename.py MAP.json [--dir src] [--dry-run]

MAP.json: {"functions": {old: new}, "globals": {old: new},
           "structs": {old_tag: new_tag or {"name": new_tag, "fields": {old: new}}},
           "fields": {old_tag: {old: new}}, "params": {function: {old: new}}}
(the values may also be objects with a "name" key; "docs": {name: description} replaces descriptions).

* Identifiers are replaced as whole C tokens outside string and character
  literals; in comments too, so notes keep pointing at the right names.
  Struct members (after '.' or '->') are never touched by these renames.
* Fields are renamed in their struct definition and in member accesses whose
  struct is known: the variable the access applies to (local, parameter or
  global declared `struct T ...`, also subscripted) or a cast `((struct T *)x)`.
  A field name that only one struct renames is renamed anywhere; anything
  else that cannot be resolved is reported, never guessed.
* Parameters are renamed inside their function only.
* Uninitialised globals: Turbo C places a unit's BSS objects by a hash of the
  name (rule BSS-ORDER: (first + 4*last + 32*length) mod 1024, ties by first
  appearance), so their storage names d_XXXX_ (all hashing alike) stay and the
  new names become macros in DUKE.H (block "names of the uninitialised globals").
The result is only accepted when `python tools/standalone.py build` is EQUAL.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT  # noqa: E402

TOKEN = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*|\d\w*|[A-Za-z_]\w*|\s+|->|.', re.S)
IDENT = re.compile(r"[A-Za-z_]\w*$")
KEYWORDS = set("""auto break case char const continue default do double else enum extern float for goto if int
long register return short signed sizeof static struct switch typedef union unsigned void volatile while
far near huge pascal cdecl interrupt asm _cs _ds _es _ss main""".split())
CRLF, LF = chr(13) + chr(10), chr(10)
       # the tree has DOS line endings


def flat(m: dict) -> dict:
    return {k: (v["name"] if isinstance(v, dict) else v) for k, v in (m or {}).items()}


def is_member(toks: list, k: int) -> bool:
    """toks[k] follows '.' or '->' (a struct member, not a variable)."""
    j = k - 1
    while j >= 0 and toks[j].isspace():
        j -= 1
    return j >= 0 and toks[j] in (".", "->")


def replace_tokens(text: str, mapping: dict, in_comments: bool = True) -> str:
    toks = TOKEN.findall(text)
    out = []
    for k, tok in enumerate(toks):
        if tok in mapping and not is_member(toks, k):
            out.append(mapping[tok])
        elif in_comments and tok.startswith("/*"):
            out.append(re.sub(r"\b[A-Za-z_]\w*\b", lambda m: mapping.get(m.group(0), m.group(0)), tok))
        else:
            out.append(tok)
    return "".join(out)


DECL = re.compile(r"\bstruct\s+(\w+)\s+(?!\{)([^;{}()=]*(?:\([^;{}()=]*\))?[^;{}()=]*)")
TYPE_WORD = re.compile(r"\b(int|char|unsigned|long|void|struct|short|signed)\b")


def struct_vars(text: str) -> dict:
    """{variable: struct tag} for the declarations `struct T [far] *a, b[n]` in text."""
    out = {}
    for m in DECL.finditer(text):
        for piece in m.group(2).split(","):
            piece = re.sub(r"\[[^\]]*\]", "", piece).strip()
            if TYPE_WORD.search(piece):
                break                                  # the next parameter, of another type
            n = re.search(r"(\w+)\s*\)?\s*$", piece)
            if n and n.group(1) not in KEYWORDS:
                out[n.group(1)] = m.group(1)
    return out


def top_blocks(toks: list):
    """(start, open, close) token indexes of each top-level {...} block; start is
    the first token after the previous top-level ';' or '}'."""
    depth, start, opened = 0, 0, None
    for k, tok in enumerate(toks):
        if tok == "{":
            if depth == 0:
                opened = k
            depth += 1
        elif tok == "}":
            depth -= 1
            if depth == 0:
                yield start, opened, k
                start = k + 1
        elif tok == ";" and depth == 0:
            start = k + 1


def top_level_text(text: str) -> str:
    toks, depth, out = TOKEN.findall(text), 0, []
    for tok in toks:
        depth += tok == "{"
        if depth == 0 and not tok.startswith(("/*", "//")):
            out.append(tok)
        depth -= tok == "}"
    return "".join(out)


def rename_fields(text: str, fields: dict, globals_: dict, unresolved: list, fname: str) -> str:
    """fields = {tag: {old: new}}; see the module docstring."""
    toks = TOKEN.findall(text)
    wanted = {f for fm in fields.values() for f in fm}
    scopes = []                                       # (lo, hi, {variable: tag})
    for start, op, cl in top_blocks(toks):
        head = "".join(toks[start:op])
        m = re.search(r"\bstruct\s+(\w+)\s*$", head)
        if m:                                         # struct T { ... }: rename the fields themselves
            fm = fields.get(m.group(1), {})
            for k in range(op, cl):
                if toks[k] in fm and not is_member(toks, k):
                    toks[k] = fm[toks[k]]
            continue
        scopes.append((start, cl, {**globals_, **struct_vars("".join(toks[start:cl]))}))

    def scope_vars(k):
        for lo, hi, v in scopes:
            if lo <= k <= hi:
                return v
        return globals_

    def back(j):
        while j >= 0 and toks[j].isspace():
            j -= 1
        return j

    def matching(j, close, open_):
        depth = 0
        while j >= 0:
            depth += toks[j] == close
            depth -= toks[j] == open_
            if depth == 0:
                return j
            j -= 1
        return j

    def base_tag(k):
        j = back(back(k - 1) - 1)                     # before the '.' / '->'
        while j >= 0 and toks[j] == "]":              # a[i][j]  ->  a
            j = back(matching(j, "]", "[") - 1)
        if j >= 0 and IDENT.match(toks[j]):
            return scope_vars(j).get(toks[j])
        if j >= 0 and toks[j] == ")":                 # ((struct T far *)x)
            i = matching(j, ")", "(")
            m = re.match(r"\(\s*\(\s*struct\s+(\w+)", "".join(toks[i:j + 1]))
            if m:
                return m.group(1)
            h = back(i - 1)                           # VIEW(i).f with #define VIEW(i) (*(struct T *)...)
            return MACRO_TAGS.get(toks[h]) if h >= 0 else None
        return None

    for k, tok in enumerate(toks):
        if tok in wanted and is_member(toks, k):
            tag = base_tag(k)
            if tag in fields and tok in fields[tag]:
                toks[k] = fields[tag][tok]
                continue
            owners = {fm[tok] for t, fm in fields.items() if tok in fm}
            if tag is None and len(owners) == 1 and all(tok not in struct_fields
                                                        for t, struct_fields in STRUCT_FIELDS.items() if t not in fields):
                toks[k] = owners.pop()
            elif tag is None:
                line = "".join(toks[:k]).count(LF) + 1
                unresolved.append(f"{fname}:{line}: .{tok} (struct {tag or 'unknown'})")
    return "".join(toks)


STRUCT_FIELDS: dict = {}                              # tag -> field names, from the struct definitions
MACRO_TAGS: dict = {}                                 # function-like macro -> the struct it casts to


def collect_struct_fields(texts) -> dict:
    out = {}
    for text in texts:
        for m in re.finditer(r"\bstruct\s+(\w+)\s*\{([^{}]*)\}", text):
            body = re.sub(r"/\*.*?\*/", "", m.group(2), flags=re.S)
            names = set()
            for decl in body.split(";"):
                for piece in decl.split(","):
                    n = re.search(r"(\w+)\s*(\[[^\]]*\])*\s*$", piece.strip())
                    if n and n.group(1) not in KEYWORDS:
                        names.add(n.group(1))
            out[m.group(1)] = names
    return out


def rename_params(text: str, func: str, mapping: dict) -> str:
    """Rename inside every definition of func (one per #if EPISODE placement)."""
    defs = list(re.finditer(r"(?m)^[A-Za-z_][^\n;{}#=()]*\b" + re.escape(func) + r"\s*\([^;{]*\)\s*\{", text))
    for m in reversed(defs):
        depth, i = 0, m.end() - 1
        while i < len(text):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        span = text[m.start():i + 1]
        text = text[:m.start()] + replace_tokens(span, mapping, in_comments=False) + text[i + 1:]
    return text


def paren_columns(text: str) -> list:
    """For each line: the column of the innermost '(' still open at its start (or None)."""
    out, stack, col = [None], [], 0
    for tok in TOKEN.findall(text):
        if tok == "(":
            stack.append(col)
        elif tok == ")" and stack:
            stack.pop()
        for ch in tok:
            if ch == LF:
                out.append(stack[-1] if stack else None)
                col = 0
            else:
                col += 1
    return out


def realign(old: str, new: str) -> str:
    """Continuation lines that were aligned one column after an open '(' are
    re-aligned after a rename changed the length of the text before it."""
    po, pn = paren_columns(old), paren_columns(new)
    lines_o, lines_n = old.split(LF), new.split(LF)
    if len(lines_o) != len(lines_n):
        return new
    for i, (lo, ln) in enumerate(zip(lines_o, lines_n)):
        ind = len(lo) - len(lo.lstrip(" "))
        if po[i] is not None and pn[i] is not None and lo.strip() and ind == po[i] + 1:
            lines_n[i] = " " * (pn[i] + 1) + ln.lstrip(" ")
    return LF.join(lines_n)


def wrap_comment(text: str, indent: str = "", width: int = 100) -> list:
    words, lines, cur = text.replace("*/", "* /").split(), [], ""
    for w in words:
        if cur and len(indent) + 3 + len(cur) + 1 + len(w) > width - 3:
            lines.append(cur)
            cur = w
        else:
            cur = f"{cur} {w}".strip()
    lines.append(cur)
    if len(lines) == 1:
        return [f"{indent}/* {lines[0]} */"]
    return [f"{indent}/* {lines[0]}"] + [f"{indent}   {ln}" for ln in lines[1:-1]] + [f"{indent}   {lines[-1]} */"]


def add_docs(text: str, docs: dict, header: bool) -> str:
    """Put each description above its function definition or struct definition;
    in the header, beside (or above) the global's declaration.  The comment block
    directly above (the previous description) is replaced, not stacked."""
    out = []
    lines = text.split(LF)

    def drop_above(name):
        """Remove a standalone comment block (lines '/* ...' and '   ...') ending right above."""
        if not out or not out[-1].rstrip().endswith("*/") or not out[-1].startswith(("/*", "   ")):
            return
        k = len(out) - 1
        while k > 0 and not out[k].startswith("/*") and out[k].startswith("   "):
            k -= 1
        if out[k].startswith("/*"):
            del out[k:]

    for i, ln in enumerate(lines):
        doc = key = None
        m = re.match(r"^[A-Za-z_][^;=()]*?\b(\w+)\s*\([^;]*$", ln)
        if m and not header and m.group(1) in docs and not ln.startswith(("#", "extern")):
            key = m.group(1)
        m = re.match(r"^struct\s+(\w+)\s*\{", ln)
        if m and f"struct {m.group(1)}" in docs:
            key = f"struct {m.group(1)}"
        if key:
            doc = docs[key]
            drop_above(key)
            if not (out and out[-1].startswith("/*") and doc[:30] in out[-1]):
                out += wrap_comment(doc)
        if header:
            g = re.match(r"^extern\b[^(]*?\b(\w+)\s*(\[[^\]]*\])*\s*;", ln) or                 re.match(r"^extern\b.*\(\s*(?:far\s*)?\*\s*(\w+)\s*\).*;", ln)
            if g and g.group(1) in docs:
                name = g.group(1)
                ln = re.sub(r"\s*/\*.*\*/\s*$", "", ln)            # the old trailing description
                drop_above(name)
                d = docs[name].replace("*/", "* /")
                if len(ln) + len(d) + 7 <= 120:
                    ln = f"{ln:<44} /* {d} */" if len(ln) < 44 and 44 + len(d) + 7 <= 120 else f"{ln}  /* {d} */"
                else:
                    out += wrap_comment(d)
        out.append(ln)
    return LF.join(out)


BSS_NAME = re.compile(r"^d_[0-9a-f]{4}_$")
ALIAS_MARK = "/* ---- global data"
ALIAS_HEAD = """/* ---- names of the uninitialised globals ----
   Turbo C 2.0 lays out a unit's uninitialised data by a hash of each name
   (first character + 4 * last character + 32 * length, mod 1024; equal hashes
   in order of first appearance).  The original names are lost, so the objects
   keep storage names that all hash alike (d_ + DN1 address + _) and therefore
   lie in declaration order; the program refers to them by these names. */
"""


def alias_block(aliases: dict) -> str:
    w = max(len(n) for n in aliases.values())
    return ALIAS_HEAD + "".join(f"#define {new:<{w}} {old}{LF}" for old, new in sorted(aliases.items())) + LF


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("map")
    ap.add_argument("--dir", default=str(ROOT / "src"))
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    m = json.loads(Path(a.map).read_text(encoding="utf-8-sig"))
    d = Path(a.dir)
    files = {p.name: p.read_bytes().decode("latin-1").replace(CRLF, LF)
             for p in d.iterdir() if p.suffix.upper() in (".C", ".H", ".ASM")}
    csrc = [n for n in files if not n.upper().endswith(".ASM")]
    original = dict(files)
    glob = {k: v for k, v in {**flat(m.get("functions")), **flat(m.get("globals"))}.items() if k != v}
    tags = {k: v for k, v in flat(m.get("structs")).items() if k != v}
    # uninitialised globals keep their storage names; the new names are macros (see ALIAS_HEAD)
    present = set(TOKEN.findall("".join(files.values())))
    aliases = {o: n for o, n in glob.items() if BSS_NAME.match(o) and o in present}
    news = list(glob.values()) + list(tags.values())
    dup = {n for n in news if news.count(n) > 1}
    dup |= {n for n in news if n in present and n not in glob and n not in tags}      # an existing name
    if dup:
        print("name collisions:", sorted(dup)[:20])
        return 1
    fmaps = {tag: dict(flat(fm)) for tag, fm in (m.get("fields") or {}).items()}
    for tag, sd in (m.get("structs") or {}).items():
        if isinstance(sd, dict) and sd.get("fields"):
            fmaps.setdefault(tag, {}).update(flat(sd["fields"]))
    fmaps = {tag: {o: n for o, n in fm.items() if o != n} for tag, fm in fmaps.items()}
    fmaps = {tag: fm for tag, fm in fmaps.items() if fm}
    member_names = {n for fm in fmaps.values() for n in fm.values()}
    member_names |= {n for pm in (m.get("params") or {}).values() for n in flat(pm).values()}
    clash = sorted(set(aliases.values()) & member_names)
    if clash:
        print("uninitialised-global names that are also field or parameter names (the macro would rename those):", clash)
        return 1
    # 1. fields (while tags and globals still have their old names)
    if fmaps:
        STRUCT_FIELDS.update(collect_struct_fields(files[n] for n in csrc))
        for n in csrc:
            MACRO_TAGS.update(re.findall(r"(?m)^#define\s+(\w+)\([^)]*\).*?\bstruct\s+(\w+)", files[n]))
        gvars = {}
        for n in csrc:
            gvars.update(struct_vars(top_level_text(files[n])))
        unresolved = []
        for n in csrc:
            files[n] = rename_fields(files[n], fmaps, gvars, unresolved, n)
        if unresolved:
            print(f"{len(unresolved)} member accesses not renamed:")
            print(LF.join("  " + u for u in unresolved[:60]))
    # 2. functions, globals, struct tags
    mapping = {**glob, **tags}
    for name, text in files.items():
        if name.upper().endswith(".ASM"):
            amap = {f"_{k}": f"_{v}" for k, v in glob.items() if k.startswith("asm_")}
            amap.update({k: v for k, v in glob.items() if k.startswith("c_")})
            files[name] = replace_tokens(text, amap)
        else:
            files[name] = replace_tokens(text, mapping)
    # 3. parameters
    for func, pm in (m.get("params") or {}).items():
        fname = glob.get(func, func)
        for n in csrc:
            files[n] = rename_params(files[n], fname, flat(pm))
        # the prototypes (header, per-unit copies) name the parameters too
        proto = re.compile(r"(?m)^([A-Za-z_][^\n;{}#=()]*\b" + re.escape(fname) + r"\s*)(\([^;{]*\))(\s*;)")
        for n in csrc:
            files[n] = proto.sub(lambda mm: mm.group(1) + replace_tokens(mm.group(2), flat(pm), in_comments=False)
                                 + mm.group(3), files[n])
    # 4. macro names of the uninitialised globals
    if aliases:
        h = files["DUKE.H"]
        old_block = re.search(r"/\* ---- names of the uninitialised globals.*?\n\n(?=/\* ---- )", h, re.S)
        known = dict(re.findall(r"(?m)^#define (\w+)\s+(d_[0-9a-f]{4}_)$", old_block.group(0))) if old_block else {}
        merged = {v: k2 for k2, v in known.items()}
        merged.update(aliases)
        if old_block:
            h = h[:old_block.start()] + h[old_block.end():]
        k = h.index(ALIAS_MARK)
        files["DUKE.H"] = h[:k] + alias_block(merged) + h[k:]
        print(f"{len(aliases)} uninitialised globals named by macro")
    for n in csrc:
        files[n] = realign(original[n], files[n]) if n != "DUKE.H" else files[n]
    # 5. one-line descriptions
    if m.get("docs"):
        new_name = {**glob, **{f"struct {k}": f"struct {v}" for k, v in tags.items()}}
        docs = {new_name.get(k, k): v for k, v in m["docs"].items() if v}
        for n in csrc:
            files[n] = add_docs(files[n], docs, n == "DUKE.H")
    if a.dry_run:
        return 0
    for name, text in files.items():
        (d / name).write_bytes(text.replace(LF, CRLF).encode("latin-1"))      # DOS line endings
    print(f"renamed {len(mapping)} identifiers in {len(files)} files")
    return 0


if __name__ == "__main__":
    sys.exit(main())
