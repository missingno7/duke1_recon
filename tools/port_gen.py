#!/usr/bin/env python3
"""Generate isolated SDL port translation units from the canonical DOS sources.

The generator deliberately operates on C tokens rather than broad text substitutions:
comments, string literals and character literals keep their original contents.
Generated files belong in the build tree and are never canonical game sources.
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path


DROP_WORDS = {"far", "near", "huge", "pascal", "cdecl", "interrupt"}
RUNTIME_NAMES = {
    "outport": "pc_outport",
    "outportb": "pc_outportb",
    "inport": "pc_inport",
    "inportb": "pc_inportb",
    "MK_FP": "pc_mk_fp",
    "setvect": "pc_setvect",
    "getvect": "pc_getvect",
    "disable": "pc_disable",
    "enable": "pc_enable",
    "delay": "pc_delay",
    "coreleft": "pc_coreleft",
    "textmode": "pc_textmode",
    "exit": "pc_exit",
    "_exit": "pc_exit",
    "fopen": "pc_fopen",
    "getw": "pc_getw",
    "putw": "pc_putw",
    "ltoa": "pc_ltoa",
    "ultoa": "pc_ultoa",
    "malloc": "pc_malloc",
    "free": "pc_free",
}
TOOLBOX_NAMES = {
    "set_video_mode",
    "set_vga_mode_with_parameters",
    "blit_bitmap_to_video_page",
    "copy_planar_video_region",
    "blit_planar_sprite_rows",
    "draw_ega_glyph",
    "blit_planar_masked_glyph",
    "select_draw_page",
    "show_video_page",
}

# These conditions are waits on state changed by asynchronous hardware: they must yield even
# when their source body also polls the keyboard controller or game port. Empty loop bodies
# are instrumented generically; the two title-menu counter sites are named below because the
# number of iterations is itself the original game's delay mechanism.
SPIN_CONDITION_NAMES = {
    "last_keyboard_scan_code",
    "timer_tick_counter",
    "joystick_button_1_state",
    "joystick_button_2_state",
    "joystick_button_1",
    "joystick_button_2",
    "button_1_state",
    "button_2_state",
    "x_axis_pressed",
    "y_axis_pressed",
}
SPIN_LABELS = {
    "title_screen_and_menu": {"L_0652"},
}

TOKEN_RE = re.compile(
    r"(?P<space>\s+)"
    r"|(?P<line>//[^\r\n]*)"
    r"|(?P<block>/\*[\s\S]*?\*/)"
    r"|(?P<string>\"(?:\\.|[^\"\\])*\")"
    r"|(?P<char>'(?:\\.|[^'\\])*')"
    r"|(?P<ident>[A-Za-z_][A-Za-z_0-9]*)"
    r"|(?P<number>(?:0[xX][0-9A-Fa-f]+|(?:[0-9]+))(?:[uUlL]+)?)"
    r"|(?P<punct>##|->|\+\+|--|&&|\|\||==|!=|<=|>=|<<|>>|\.\.\.|[^\s])"
)


@dataclass
class Token:
    kind: str
    text: str
    start: int
    end: int


def lex(text: str) -> list[Token]:
    tokens: list[Token] = []
    pos = 0
    while pos < len(text):
        match = TOKEN_RE.match(text, pos)
        if not match:
            raise ValueError(f"cannot tokenize source at offset {pos}: {text[pos:pos + 40]!r}")
        kind = match.lastgroup or "punct"
        tokens.append(Token(kind, match.group(), pos, match.end()))
        pos = match.end()
    return tokens


def uncomment(text: str) -> str:
    return "".join(t.text if t.kind not in {"line", "block"} else " " for t in lex(text))


def significant(tokens: list[Token], index: int) -> int | None:
    while index < len(tokens):
        if tokens[index].kind not in {"space", "line", "block"}:
            return index
        index += 1
    return None


def header_symbols(header: str) -> tuple[set[str], set[str]]:
    """Collect declared game functions and globals from DUKE.H."""
    clean = uncomment(header)
    functions: set[str] = set()
    globals_: set[str] = set()

    for line in clean.splitlines():
        stmt = line.strip()
        if not stmt or stmt.startswith("#"):
            continue
        if re.match(r"^extern\b", stmt):
            # Runtime-only declarations are removed.  The game header currently has
            # only abs(), which is already declared by stdlib.h.
            if re.search(r"\babs\s*\(", stmt):
                continue
            # Function-pointer variables have a parenthesized declarator, but the
            # object name after '*' is a global rather than a function prototype.
            pointer_name = re.search(r"\(\s*(?:(?:far|near|huge|pascal|cdecl|interrupt)\s+)*\*\s*([A-Za-z_]\w*)", stmt)
            if pointer_name:
                globals_.add(pointer_name.group(1))
                continue
            if "(" in stmt:
                name_matches = re.findall(r"\b([A-Za-z_]\w*)\s*\(", stmt)
                if name_matches and name_matches[0] not in {"far", "near", "huge", "void"}:
                    functions.add(name_matches[0])
            else:
                prefix = stmt.split("[", 1)[0]
                names = re.findall(r"[A-Za-z_]\w*", prefix)
                if names:
                    globals_.add(names[-1])
            continue
        # Prototypes in the header are declarations at top-level, separated by
        # semicolons.  The first identifier followed by '(' is the declared name.
        if ";" in stmt and "(" in stmt and not stmt.startswith(("typedef", "struct ")):
            names = re.findall(r"\b([A-Za-z_]\w*)\s*\(", stmt)
            if names:
                functions.add(names[0])

    # Global-name aliases map readable names to hash-neutral storage names.
    for macro, storage in re.findall(
        r"(?m)^\s*#\s*define\s+([A-Za-z_]\w*)\s+(d_[0-9A-Fa-f]+_)\b", clean
    ):
        globals_.update((macro, storage))

    # Drop the lone runtime prototype that has no header and let stdlib.h declare it.
    c_keywords = {
        "void", "char", "short", "int", "long", "float", "double", "signed", "unsigned",
        "const", "volatile", "struct", "union", "enum", "register", "static", "extern",
        "far", "near", "huge", "pascal", "cdecl", "interrupt", "if", "else", "while",
        "for", "switch", "case", "return", "sizeof", "typedef",
    }
    return functions - {"abs"} - c_keywords, globals_


def defined_objects(text: str) -> set[str]:
    """Names of the variables a unit defines at file level (outside functions): every one
    must get the episode prefix, whether DUKE.H declares it or not."""
    text = re.sub(r"(?m)^[ 	]*#.*$", "", text)          # preprocessor lines
    names: set[str] = set()
    depth = 0
    statement: list[str] = []
    skip_to_semicolon = False

    def declarators(words: list[str]) -> None:
        if not words or words[0] in {"typedef", "extern"}:
            return
        fp = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", " ".join(words))
        if fp:                                             # function pointer variable
            names.add(fp.group(1))
            return
        if "(" in words:
            return                                         # a prototype
        for i, w in enumerate(words):
            nxt = words[i + 1] if i + 1 < len(words) else ";"
            if re.match(r"[A-Za-z_]\w*$", w) and nxt in {"=", "[", ",", ";"}:
                names.add(w)

    for tok in lex(text):
        if tok.kind in {"space", "line", "block"}:
            continue
        if tok.text == "{":
            if depth == 0:
                if "=" in statement:                       # an initialiser: names come before it
                    declarators(statement[:statement.index("=")] + [";"])
                    skip_to_semicolon = True
                statement = []
            depth += 1
            continue
        if tok.text == "}":
            depth -= 1
            continue
        if depth:
            continue
        if tok.text == ";":
            if not skip_to_semicolon:
                declarators(statement)
            statement = []
            skip_to_semicolon = False
        elif not skip_to_semicolon:
            statement.append(tok.text)
    keywords = {"void", "char", "short", "int", "long", "unsigned", "signed", "struct", "far",
                "near", "huge", "static", "const", "volatile", "register", "interrupt"}
    return names - keywords


def function_definitions(text: str) -> list[tuple[str, int, int]]:
    """Find top-level function definition spans using balanced C tokens."""
    tokens = lex(text)
    depth = 0
    result: list[tuple[str, int, int]] = []
    for idx, tok in enumerate(tokens):
        if tok.kind in {"string", "char", "line", "block", "space"}:
            continue
        if tok.text == "{" and depth == 0:
            close_paren = idx - 1
            while close_paren >= 0 and tokens[close_paren].kind in {"space", "line", "block"}:
                close_paren -= 1
            if close_paren >= 0 and tokens[close_paren].text == ")":
                paren_depth = 1
                open_paren = close_paren - 1
                while open_paren >= 0 and paren_depth:
                    if tokens[open_paren].kind not in {"space", "line", "block"}:
                        if tokens[open_paren].text == ")":
                            paren_depth += 1
                        elif tokens[open_paren].text == "(":
                            paren_depth -= 1
                    open_paren -= 1
                open_paren += 1
                name_index = open_paren - 1
                while name_index >= 0 and tokens[name_index].kind in {"space", "line", "block"}:
                    name_index -= 1
                if name_index >= 0 and tokens[name_index].kind == "ident":
                    # Exclude control-flow and compound literal constructs.
                    name = tokens[name_index].text
                    if name not in {"if", "while", "switch", "for", "sizeof"}:
                        body_depth = 1
                        end_idx = idx + 1
                        while end_idx < len(tokens) and body_depth:
                            t = tokens[end_idx]
                            if t.kind not in {"string", "char", "line", "block"}:
                                if t.text == "{":
                                    body_depth += 1
                                elif t.text == "}":
                                    body_depth -= 1
                            end_idx += 1
                        if body_depth == 0:
                            signature_start = text.rfind("\n", 0, tokens[name_index].start) + 1
                            result.append((name, signature_start, tokens[end_idx - 1].end))
                            depth = 0
                            # Skip the body as a whole so nested braces are not
                            # mistaken for additional definitions.
                            while idx + 1 < end_idx:
                                idx += 1
                            continue
            depth = 1
        elif tok.text == "{" and depth:
            depth += 1
        elif tok.text == "}" and depth:
            depth -= 1
    # The in-place loop above cannot safely advance its index in Python's for loop;
    # retain only spans whose opening brace was at file scope (already tracked by the
    # depth logic) and de-duplicate by source position.
    unique: dict[int, tuple[str, int, int]] = {start: (name, start, end) for name, start, end in result}
    return [unique[k] for k in sorted(unique)]


def translate(text: str, episode: int, prefixes: set[str], *, remove_abs: bool = False) -> str:
    if remove_abs:
        text = re.sub(
            r"(?m)^\s*extern\s+int\s+abs\s*\(\s*int\s*\)\s*;\s*",
            "",
            text,
        )
    tokens = lex(text)
    # Rewrite integral types from the DOS 16-bit data model.  Whitespace/comments
    # between type words are preserved, while consumed words are blanked.
    idx = 0
    while idx < len(tokens):
        tok = tokens[idx]
        if tok.kind != "ident":
            idx += 1
            continue
        if tok.text in {"unsigned", "long"}:
            next_idx = significant(tokens, idx + 1)
            next_text = tokens[next_idx].text if next_idx is not None else ""
            after_next = significant(tokens, next_idx + 1) if next_idx is not None else None
            after_text = tokens[after_next].text if after_next is not None else ""
            if tok.text == "unsigned" and next_text == "long":
                tok.text = "uint32_t"
                tokens[next_idx].text = ""
                if after_text == "int":
                    tokens[after_next].text = ""
                    idx = after_next + 1
                    continue
            elif tok.text == "long" and next_text == "int":
                tok.text = "int32_t"
                tokens[next_idx].text = ""
            elif tok.text == "unsigned" and next_text == "int":
                tok.text = "uint16_t"
                tokens[next_idx].text = ""
            elif tok.text == "unsigned" and next_text not in {"char", "short", "long"}:
                tok.text = "uint16_t"
            elif tok.text == "long":
                tok.text = "int32_t"
        elif tok.text == "int":
            tok.text = "int16_t"
        idx += 1

    for tok in tokens:
        if tok.kind != "ident":
            continue
        if tok.text in DROP_WORDS:
            tok.text = ""
        elif tok.text in RUNTIME_NAMES:
            tok.text = RUNTIME_NAMES[tok.text]
        elif tok.text in prefixes and tok.text not in TOOLBOX_NAMES:
            tok.text = f"ep{episode}_{tok.text}"

    out = "".join(tok.text for tok in tokens)
    # Keep generated include casing stable on case-sensitive hosts too.
    out = re.sub(r'(?i)(#\s*include\s*)"duke\.h"', r'\1"DUKE.H"', out)
    return out


def replace_overrides(source: str, source_path: Path, override_dir: Path) -> str:
    overrides = {p.stem: p for p in sorted(override_dir.glob("*.c"))} if override_dir.exists() else {}
    if not overrides:
        return source
    spans = function_definitions(source)
    replacements: list[tuple[int, int, str]] = []
    for name, path in overrides.items():
        matches = [(start, end) for found, start, end in spans if found == name]
        if not matches:
            # An override can target either translation unit; the other unit simply
            # keeps its original source. The union is checked by generate().
            continue
        if len(matches) != 1:
            raise ValueError(f"override {path} expects one definition of {name} in {source_path}, found {len(matches)}")
        start, end = matches[0]
        replacement = path.read_text(encoding="latin1")
        defs = function_definitions(replacement)
        if len(defs) != 1 or defs[0][0] != name:
            raise ValueError(f"override {path} must contain exactly the game-style definition {name}(...) {{...}}")
        replacements.append((start, end, replacement))
    for start, end, replacement in sorted(replacements, reverse=True):
        source = source[:start] + replacement + source[end:]
    return source


def inject_pc_spin(source: str) -> str:
    """Insert a yield into empty loops and loops polling asynchronous input/timer state."""
    tokens = lex(source)
    definitions = function_definitions(source)
    insertions: list[tuple[int, str]] = []
    consumed_do_whiles: set[int] = set()

    def function_at(offset: int) -> str | None:
        return next((name for name, start, end in definitions if start <= offset < end), None)

    def next_sig(index: int) -> int | None:
        return significant(tokens, index)

    def matching(index: int, left: str, right: str) -> int | None:
        if index >= len(tokens) or tokens[index].text != left:
            return None
        depth = 1
        current = index + 1
        while current < len(tokens):
            token = tokens[current]
            if token.kind not in {"string", "char", "line", "block"}:
                if token.text == left:
                    depth += 1
                elif token.text == right:
                    depth -= 1
                    if depth == 0:
                        return current
            current += 1
        return None

    def statement_end(index: int) -> int | None:
        """Return the exclusive token end for a loop body statement."""
        index = next_sig(index) if index is not None else None
        if index is None:
            return None
        if tokens[index].text == "{":
            close = matching(index, "{", "}")
            return close + 1 if close is not None else None
        parens = brackets = braces = 0
        current = index
        while current < len(tokens):
            token = tokens[current]
            if token.kind not in {"string", "char", "line", "block"}:
                if token.text == "(": parens += 1
                elif token.text == ")": parens -= 1
                elif token.text == "[": brackets += 1
                elif token.text == "]": brackets -= 1
                elif token.text == "{": braces += 1
                elif token.text == "}":
                    if braces == 0:
                        return current
                    braces -= 1
                elif token.text == ";" and parens == brackets == braces == 0:
                    return current + 1
            current += 1
        return None

    def loop_parts(keyword_index: int, *, is_do: bool = False):
        if is_do:
            body_start = next_sig(keyword_index + 1)
            body_end = statement_end(body_start) if body_start is not None else None
            if body_end is None:
                return None
            tail = next_sig(body_end)
            if tail is None or tokens[tail].text != "while":
                return None
            open_paren = next_sig(tail + 1)
            close_paren = matching(open_paren, "(", ")") if open_paren is not None else None
            if close_paren is None:
                return None
            semicolon = next_sig(close_paren + 1)
            if semicolon is not None and tokens[semicolon].text == ";":
                consumed_do_whiles.add(tail)
            condition_indexes = range(open_paren + 1, close_paren)
            return body_start, body_end, condition_indexes
        open_paren = next_sig(keyword_index + 1)
        close_paren = matching(open_paren, "(", ")") if open_paren is not None else None
        if close_paren is None:
            return None
        body_start = next_sig(close_paren + 1)
        body_end = statement_end(body_start) if body_start is not None else None
        if body_start is None or body_end is None:
            return None
        return body_start, body_end, range(open_paren + 1, close_paren)

    loop_records: list[tuple[int, int, int, set[str], str | None]] = []
    index = 0
    while index < len(tokens):
        token = tokens[index]
        if token.kind != "ident" or token.text not in {"while", "for", "do"}:
            index += 1
            continue
        if index in consumed_do_whiles:
            index += 1
            continue
        parts = loop_parts(index, is_do=token.text == "do")
        if parts is None:
            index += 1
            continue
        body_start, body_end, cond_indexes = parts
        condition_names = {
            tokens[pos].text for pos in cond_indexes
            if tokens[pos].kind == "ident"
        }
        owner = function_at(token.start)
        body_first = next_sig(body_start + 1) if tokens[body_start].text == "{" else body_start
        empty = False
        if body_first is not None:
            if tokens[body_start].text == "{":
                empty = body_first is not None and body_first < body_end and tokens[body_first].text == "}"
            else:
                empty = tokens[body_start].text == ";"
        loop_records.append((index, body_start, body_end, condition_names, owner))
        is_async_wait = bool(condition_names & SPIN_CONDITION_NAMES)
        if empty or is_async_wait:
            if tokens[body_start].text == "{":
                insert_at = tokens[body_start].end
                if empty:
                    insertions.append((insert_at, "\n            pc_spin();"))
                elif not any(
                    tokens[p].kind == "ident" and tokens[p].text == "pc_spin"
                    for p in range(body_start + 1, body_end - 1)
                ):
                    insertions.append((insert_at, "\n            pc_spin();"))
            elif tokens[body_start].text == ";":
                insertions.append((tokens[body_start].start, "{ pc_spin(); }"))
            else:
                body_text = source[tokens[body_start].start : tokens[body_end - 1].end]
                insertions.append((tokens[body_end - 1].end, " }"))
                insertions.append((tokens[body_start].start, "{ pc_spin(); "))
        index += 1

    # The second title-screen timeout counter advances at a label rather than a loop header.
    for index, token in enumerate(tokens[:-1]):
        if token.kind != "ident" or token.text != "L_0652":
            continue
        colon = next_sig(index + 1)
        if colon is not None and tokens[colon].text == ":" and function_at(token.start) == "title_screen_and_menu":
            insertions.append((tokens[colon].end, " pc_spin();"))

    for position, text in sorted(insertions, reverse=True):
        source = source[:position] + text + source[position:]
    return source


def generate(source_dir: Path, output_dir: Path, override_dir: Path) -> None:
    header_path = source_dir / "DUKE.H"
    game_paths = [source_dir / "GAME1.C", source_dir / "GAME2.C"]
    header = header_path.read_text(encoding="latin1")
    functions, globals_ = header_symbols(header)
    raw_units = {p: p.read_text(encoding="latin1") for p in game_paths}
    for p, raw in raw_units.items():
        functions.update(name for name, _, _ in function_definitions(raw))
        globals_.update(defined_objects(raw))
    # The storage identifiers are intentionally mechanical and never alias library names.
    for raw in [header, *raw_units.values()]:
        globals_.update(re.findall(r"\bd_[0-9A-Fa-f]{4}_?\b", uncomment(raw)))
    prefixes = functions | globals_

    for episode in (1, 2, 3):
        ep_dir = output_dir / f"ep{episode}"
        ep_dir.mkdir(parents=True, exist_ok=True)
        generated_header = translate(header, episode, prefixes, remove_abs=True)
        generated_header = re.sub(
            rf"extern\s+unsigned\s+char\s+ep{episode}_credits_scroll_text\[\];",
            f"extern char ep{episode}_credits_scroll_text[];",
            generated_header,
        )
        generated_header = generated_header.replace(
            "#define DUKE_H\n", "#define DUKE_H\n\n#include <stdint.h>\n#include \"platform.h\"\n", 1
        )
        generated_header = generated_header.replace(
            "/* ---- data structures ---- */", "#pragma pack(push, 1)\n\n/* ---- data structures ---- */", 1
        )
        generated_header = generated_header.replace(
            "/* ---- functions of the first unit (GAME1.C) ---- */",
            "#pragma pack(pop)\n\n/* ---- functions of the first unit (GAME1.C) ---- */",
            1,
        )
        (ep_dir / "DUKE.H").write_text(generated_header, encoding="latin1", newline="\n")
        all_defs = [name for raw in raw_units.values() for name, _, _ in function_definitions(raw)]
        if override_dir.exists():
            for override in sorted(override_dir.glob("*.c")):
                count = all_defs.count(override.stem)
                if count != 1:
                    raise ValueError(f"override {override} expects one game definition named {override.stem}, found {count}")
        for source_path in game_paths:
            raw = replace_overrides(raw_units[source_path], source_path, override_dir)
            raw = inject_pc_spin(raw)
            translated = translate(raw, episode, prefixes)
            (ep_dir / source_path.name).write_text(translated, encoding="latin1", newline="\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=Path(__file__).resolve().parents[1] / "src")
    parser.add_argument("--output", type=Path, default=Path(__file__).resolve().parents[1] / "build" / "port-gen")
    parser.add_argument("--override-dir", type=Path, default=Path(__file__).resolve().parents[1] / "port" / "override")
    args = parser.parse_args()
    try:
        generate(args.source.resolve(), args.output.resolve(), args.override_dir.resolve())
    except (OSError, ValueError) as exc:
        print(f"port_gen.py: {exc}", file=sys.stderr)
        return 2
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
