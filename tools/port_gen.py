#!/usr/bin/env python3
"""Generate isolated SDL port translation units from the canonical DOS sources.

The generator deliberately operates on C tokens rather than broad text substitutions:
comments, string literals and character literals keep their original contents.
Generated files belong in the build tree and are never canonical game sources.
"""

from __future__ import annotations

import argparse
import csv
import json
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
    "keyboard_backspace_pressed",
    "keyboard_interrupt_state",
    "keyboard_key_g_pressed",
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
        fp = re.search(r"\(\s*(?:(?:far|near|huge|pascal|cdecl|interrupt)\s+)*"
                       r"\*\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*\)",
                       " ".join(words))
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


def call_bounds(tokens: list[Token], opening: int) -> int | None:
    """Return the closing parenthesis token for a call beginning at opening."""
    if opening >= len(tokens) or tokens[opening].text != "(":
        return None
    depth = 1
    for pos in range(opening + 1, len(tokens)):
        token = tokens[pos]
        if token.kind in {"string", "char", "line", "block"}:
            continue
        if token.text == "(": depth += 1
        elif token.text == ")":
            depth -= 1
            if depth == 0: return pos
    return None


def split_call_args(source: str, tokens: list[Token], opening: int, closing: int) -> list[str]:
    """Split call arguments at commas outside nested delimiters."""
    args: list[str] = []
    start = tokens[opening].end
    parens = brackets = braces = 0
    for pos in range(opening + 1, closing):
        token = tokens[pos]
        if token.kind in {"string", "char", "line", "block"}:
            continue
        if token.text == "(": parens += 1
        elif token.text == ")": parens -= 1
        elif token.text == "[": brackets += 1
        elif token.text == "]": brackets -= 1
        elif token.text == "{": braces += 1
        elif token.text == "}": braces -= 1
        elif token.text == "," and parens == brackets == braces == 0:
            args.append(source[start:token.start].strip())
            start = token.end
    final = source[start:tokens[closing].start].strip()
    if final or args:
        args.append(final)
    return args


def rewrite_sound_requests(source: str, source_name: str, sound_sites: dict,
                           report: list[dict[str, str]]) -> str:
    """Attach each request to the statically reviewed world-x expression."""
    scan_source = re.sub(r"(?m)^[ \t]*#.*$", lambda m: re.sub(r"[^\r\n]", " ", m.group()), source)
    tokens = lex(scan_source)
    definitions = function_definitions(source)
    occurrences: dict[str, int] = {}
    edits: list[tuple[int, int, str]] = []
    used: set[str] = set()
    for pos, token in enumerate(tokens):
        if token.kind != "ident" or token.text != "request_priority_sound_effect":
            continue
        opening = significant(tokens, pos + 1)
        if opening is None or tokens[opening].text != "(":
            continue
        closing = call_bounds(tokens, opening)
        if closing is None:
            continue
        after = significant(tokens, closing + 1)
        if after is not None and tokens[after].text == "{":
            continue                         # the original definition, replaced later
        owner = next((name for name, start, end in definitions
                      if start <= token.start < end), None)
        if owner is None:
            raise ValueError(f"sound request at {source_name}:{source.count(chr(10), 0, token.start) + 1} has no function")
        occurrence = occurrences.get(owner, 0) + 1
        occurrences[owner] = occurrence
        key = f"{source_name}:{owner}#{occurrence}"
        entry = sound_sites.get(key)
        if not entry:
            raise ValueError(f"missing sound source attribution for {key}")
        source_x = entry["x"]
        if source_x == "player":
            expression = "player_screen_x + level_scroll_x"
        elif source_x == "centre":
            expression = "PC_SOUND_SOURCE_CENTRE"
        else:
            expression = source_x
        args = split_call_args(source, tokens, opening, closing)
        if len(args) != 1:
            raise ValueError(f"expected one sound id in {key}, found {len(args)} arguments")
        replacement = ("request_priority_sound_effect(" + args[0] +
                      ", (int16_t)(" + expression + "))")
        edits.append((token.start, tokens[closing].end, replacement))
        used.add(key)
        line = str(source.count("\n", 0, token.start) + 1)
        report.append({"source": source_name, "line": line, "function": owner,
                       "occurrence": str(occurrence), "x": source_x,
                       "reason": entry["reason"]})
    expected = {key for key in sound_sites if key.startswith(source_name + ":")}
    missing = expected - used
    if missing:
        raise ValueError("sound source table has sites absent from source: " + ", ".join(sorted(missing)))
    for start, end, replacement in sorted(edits, reverse=True):
        source = source[:start] + replacement + source[end:]
    return source


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


def normalized_hook_signature(signature: str, name: str) -> tuple[str, tuple[str, ...]]:
    signature = re.sub(r"/\*[\s\S]*?\*/|//[^\r\n]*", " ", signature)
    match = re.search(rf"([A-Za-z_][\w\s*]*?)\b{name}\s*\((.*?)\)\s*;?\s*$", signature, re.S)
    if not match:
        raise ValueError(f"cannot parse hook signature for {name}: {signature.strip()!r}")
    result = " ".join(match.group(1).split())
    result = re.sub(r"\b(?:extern|static|inline)\b", "", result)
    result = " ".join(result.split())
    params_text = match.group(2).strip()
    if not params_text or params_text == "void":
        params: tuple[str, ...] = ()
    else:
        parts: list[str] = []
        start = 0
        depth = 0
        for pos, char in enumerate(params_text):
            if char in "([": depth += 1
            elif char in ")]": depth -= 1
            elif char == "," and depth == 0:
                parts.append(params_text[start:pos].strip()); start = pos + 1
        parts.append(params_text[start:].strip())
        clean_parts = []
        for part in parts:
            words = re.findall(r"[A-Za-z_]\w*|\*|\[|\]", part)
            if len(words) >= 2 and re.match(r"[A-Za-z_]\w*$", words[-1]) and words[-1] not in {"const", "volatile"}:
                words = words[:-1]
            clean_parts.append(" ".join(words))
        params = tuple(clean_parts)
    return result, params


def check_game_hooks(port_dir: Path, override_dir: Path) -> None:
    """Reject private override prototypes and compare every hook with its definition."""
    hooks_path = port_dir / "game_hooks.h"
    header = hooks_path.read_text(encoding="utf-8")
    declarations: dict[str, str] = {}
    for match in re.finditer(
        r"(?m)^\s*([A-Za-z_][\w\s*]*?)\b([A-Za-z_]\w*)\s*\(([^;{}]*)\)\s*;",
        re.sub(r"/\*[\s\S]*?\*/|//[^\r\n]*", " ", header),
    ):
        name = match.group(2)
        if name in {"void", "if", "while", "switch", "for"} or match.group(1).strip() == "typedef":
            continue
        declarations[name] = match.group(0).strip()
    if not declarations:
        raise ValueError("game_hooks.h contains no platform hooks")

    for path in sorted(override_dir.glob("*.c")):
        clean = re.sub(r"/\*[\s\S]*?\*/|//[^\r\n]*", " ",
                       path.read_text(encoding="latin1"))
        for name in declarations:
            if re.search(rf"(?m)^\s*(?:extern\s+)?[A-Za-z_][\w\s*]*\b{name}\s*\([^;{{}}]*\)\s*;", clean):
                raise ValueError(f"override {path} declares platform hook {name}; use game_hooks.h")

    definitions: dict[str, list[str]] = {name: [] for name in declarations}
    cmake_path = port_dir / "CMakeLists.txt"
    cmake_text = cmake_path.read_text(encoding="utf-8") if cmake_path.exists() else ""
    source_block = re.search(r"(?s)set\(PLATFORM_SOURCES(.*?)\)", cmake_text)
    if source_block:
        source_names = {Path(name).name for name in
                        re.findall(r'"([^"\n]+\.c)"', source_block.group(1))}
        platform_sources = [path for path in port_dir.rglob("*.c")
                            if path.name in source_names]
    else:
        platform_sources = [path for path in port_dir.rglob("*.c")
                            if "build" not in path.parts and "tests" not in path.parts]
    for path in platform_sources:
        raw = path.read_text(encoding="latin1", errors="replace")
        for name, start, end in function_definitions(raw):
            if name in definitions:
                opening = raw.find("{", start, end)
                definitions[name].append(raw[start:opening].strip())
    for name, declaration in declarations.items():
        found = definitions[name]
        if len(found) != 1:
            raise ValueError(f"hook {name} has {len(found)} platform definitions (expected one)")
        if normalized_hook_signature(declaration, name) != normalized_hook_signature(found[0], name):
            raise ValueError(f"hook declaration/definition disagree for {name}: {declaration} vs {found[0]}")


def inject_pc_spin(source: str, source_name: str,
                   report: list[dict[str, str]]) -> str:
    """Insert pc_halt in interrupt waits and retain pc_spin for pass-count pacing."""
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
        async_names = condition_names & SPIN_CONDITION_NAMES
        body_tokens = [tokens[p] for p in range(body_start + 1, body_end - 1)
                       if tokens[p].kind not in {"space", "line", "block"}]
        writes = set()
        for body_pos, body_token in enumerate(body_tokens):
            if body_token.kind != "ident" or body_token.text not in condition_names:
                continue
            prev = body_tokens[body_pos - 1].text if body_pos else ""
            nxt = body_tokens[body_pos + 1].text if body_pos + 1 < len(body_tokens) else ""
            if nxt in {"=", "++", "--", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^="} or prev in {"++", "--"}:
                writes.add(body_token.text)
        # Conditions may also include stable local thresholds (target_ticks), or globals such as
        # game_speed_setting that this loop does not modify.  Once an interrupt/port value is a
        # condition dependency, the loop can halt as long as its body writes none of the values
        # that the condition reads.
        is_async_wait = bool(async_names) and not writes
        if empty or is_async_wait:
            kind = "WAIT" if is_async_wait else "COUNTING"
            yield_call = "pc_halt" if is_async_wait else "pc_spin"
            reason = ("condition depends on interrupt/port state; body writes none of its condition values"
                      if is_async_wait else "empty/pass-count loop retains CPU pacing")
            report.append({"source": source_name,
                           "line": str(source.count("\n", 0, token.start) + 1),
                           "function": owner or "<unknown>", "classification": kind,
                           "condition": " ".join(sorted(condition_names)), "reason": reason})
            if tokens[body_start].text == "{":
                insert_at = tokens[body_start].end
                if empty:
                    insertions.append((insert_at, f"\n            {yield_call}();"))
                elif not any(
                    tokens[p].kind == "ident" and tokens[p].text in {"pc_spin", "pc_halt"}
                    for p in range(body_start + 1, body_end - 1)
                ):
                    insertions.append((insert_at, f"\n            {yield_call}();"))
            elif tokens[body_start].text == ";":
                insertions.append((tokens[body_start].start, f"{{ {yield_call}(); }}"))
            else:
                insertions.append((tokens[body_end - 1].end, " }"))
                insertions.append((tokens[body_start].start, f"{{ {yield_call}(); "))
        index += 1

    # The second title-screen timeout counter advances at a label rather than a loop header.
    for index, token in enumerate(tokens[:-1]):
        if token.kind != "ident" or token.text != "L_0652":
            continue
        colon = next_sig(index + 1)
        if colon is not None and tokens[colon].text == ":" and function_at(token.start) == "title_screen_and_menu":
            insertions.append((tokens[colon].end, " pc_spin();"))
            report.append({"source": source_name,
                           "line": str(source.count("\n", 0, token.start) + 1),
                           "function": "title_screen_and_menu", "classification": "COUNTING",
                           "condition": "label L_0652", "reason": "title-menu pass counter is its delay mechanism"})

    for position, text in sorted(insertions, reverse=True):
        source = source[:position] + text + source[position:]
    return source


def instrument_episode_state(source: str, episode: int, source_name: str,
                             report: list[dict[str, str]]) -> str:
    """Place mutable file and function statics in ordered per-episode PE sections."""
    scan_source = re.sub(r"(?m)^[ \t]*#.*$", lambda m: re.sub(r"[^\r\n]", " ", m.group()), source)
    tokens = lex(scan_source)
    definitions = function_definitions(source)
    function_starts: dict[int, tuple[str, int]] = {}
    for name, start, end in definitions:
        index = next((i for i, token in enumerate(tokens)
                      if token.start >= start and token.start < end), None)
        if index is not None:
            function_starts[index] = (name, end)

    insertions: list[tuple[int, str]] = []
    file_objects: set[str] = set()
    sectioned_file_objects: set[str] = set()
    depth = 0
    statement_start = 0
    index = 0
    while index < len(tokens):
        if index in function_starts:
            _, end = function_starts[index]
            index = next((i for i in range(index + 1, len(tokens))
                          if tokens[i].start >= end), len(tokens))
            statement_start = index
            depth = 0
            continue
        token = tokens[index]
        if token.kind in {"space", "line", "block"}:
            index += 1
            continue
        if token.text == "{":
            depth += 1
        elif token.text == "}":
            depth = max(0, depth - 1)
        elif token.text == ";" and depth == 0:
            start_index = next((i for i in range(statement_start, index)
                                if tokens[i].kind not in {"space", "line", "block"}), None)
            if start_index is not None:
                statement = source[tokens[start_index].start:token.end]
                names = defined_objects(statement)
                if names:
                    file_objects.update(names)
                    clean_tokens = [tokens[i].text for i in range(start_index, index)
                                    if tokens[i].kind not in {"space", "line", "block"}]
                    is_const = "const" in clean_tokens
                    initialized = "=" in clean_tokens
                    suffix = "r" if is_const else ("m" if initialized else "b")
                    attribute = f'__attribute__((section(".ep{episode}${suffix}"), used)) '
                    insertions.append((tokens[start_index].start, attribute))
                    sectioned_file_objects.update(names)
                    for name in sorted(names):
                        report.append({"episode": str(episode), "source": source_name,
                                       "function": "<file-scope>", "variable": name,
                                       "section": f".ep{episode}${suffix}",
                                       "storage": "const" if is_const else
                                                 ("initialized" if initialized else "uninitialized")})
            statement_start = index + 1
        index += 1

    if file_objects != sectioned_file_objects:
        missing = sorted(file_objects - sectioned_file_objects)
        raise ValueError(f"episode {episode} {source_name} file-scope objects escaped state sections: {missing}")

    # Function-local statics have their own storage and are not returned by defined_objects
    # at file scope. Add the same section attribute to each local static declaration.
    for function, start, end in definitions:
        first = next((i for i, token in enumerate(tokens)
                      if token.start >= start and token.start < end), None)
        if first is None:
            continue
        for i in range(first, len(tokens)):
            if tokens[i].start >= end:
                break
            if tokens[i].kind != "ident" or tokens[i].text != "static":
                continue
            parens = brackets = braces = 0
            semi = None
            for j in range(i + 1, len(tokens)):
                t = tokens[j]
                if t.kind in {"space", "line", "block", "string", "char"}:
                    continue
                if t.text == "(": parens += 1
                elif t.text == ")": parens -= 1
                elif t.text == "[": brackets += 1
                elif t.text == "]": brackets -= 1
                elif t.text == "{": braces += 1
                elif t.text == "}":
                    if braces == 0: break
                    braces -= 1
                elif t.text == ";" and parens == brackets == braces == 0:
                    semi = j
                    break
            if semi is None:
                continue
            declaration = source[tokens[i].start:tokens[semi].end]
            names = defined_objects(declaration)
            if not names:
                continue
            clean_tokens = [tokens[j].text for j in range(i, semi)
                            if tokens[j].kind not in {"space", "line", "block"}]
            is_const = "const" in clean_tokens
            initialized = "=" in clean_tokens
            suffix = "r" if is_const else ("m" if initialized else "b")
            attribute = f'__attribute__((section(".ep{episode}${suffix}"), used)) '
            insertions.append((tokens[i].start, attribute))
            for name in sorted(names):
                report.append({"episode": str(episode), "source": source_name,
                               "function": function, "variable": name,
                               "section": f".ep{episode}${suffix}",
                               "storage": "function-static-const" if is_const else
                                         ("function-static-initialized" if initialized else
                                          "function-static-uninitialized")})

    for position, attribute in sorted(insertions, reverse=True):
        source = source[:position] + attribute + source[position:]
    return source


def tag_sprite_draw_calls(source: str, first_site: int) -> tuple[str, int]:
    """Give every game sprite draw call a stable source-order identity."""
    tokens = lex(source)
    edits: list[tuple[int, int, str]] = []
    next_site = first_site
    for index, token in enumerate(tokens):
        if token.kind != "ident" or token.text != "blit_planar_sprite_rows":
            continue
        open_index = significant(tokens, index + 1)
        if open_index is None or tokens[open_index].text != "(":
            continue
        edits.append((token.start, token.end, "blit_planar_sprite_rows_at"))
        edits.append((tokens[open_index].end, tokens[open_index].end, f"{next_site}, "))
        next_site += 1
    for start, end, replacement in sorted(edits, reverse=True):
        source = source[:start] + replacement + source[end:]
    return source, next_site - first_site

def instrument_gameplay_capture(source: str) -> str:
    """Open a frame capture at the one routine that draws the gameplay tile strip."""
    definitions = function_definitions(source)
    match = next((item for item in definitions if item[0] == "draw_animated_level_strip"), None)
    if match is None:
        raise ValueError("could not find draw_animated_level_strip for frame capture")
    _, start, end = match
    opening = source.find("{", start, end)
    if opening < 0:
        raise ValueError("draw_animated_level_strip has no body")
    source = (source[:opening + 1] +
              "\n    capture_begin_gameplay_frame(level_scroll_x, level_map_y_offset);" +
              source[opening + 1:])
    # The map and tile pixels are sampled after the animation phase advances, so the wide
    # renderer sees the same animated source frame as the ordinary strip draw below.
    match = re.search(r"(?m)^\s*do\s*\{", source[opening + 1:end + 120])
    if match is None:
        raise ValueError("could not find tile-strip loop for wide-map capture")
    position = opening + 1 + match.start()
    source = (source[:position] +
              "    capture_snapshot_wide_tiles(level_tile_map, level_map_y_offset, world_animation_phase);\n" +
              source[position:])
    end_match = re.search(r"(?m)^\s*outport\(0x3ce,\s*5\);", source[opening + 1:end + 160])
    if end_match is None:
        raise ValueError("could not find tile-strip end for wide-map capture")
    end_position = opening + 1 + end_match.start()
    return source[:end_position] + "    capture_end_tile_strip();\n" + source[end_position:]


def instrument_modal_capture(source: str) -> str:
    """Publish an interim native frame from the page being drawn while a gameplay dialog
    waits for input.  The final page flip still publishes the completed frame as usual."""
    definition = next((item for item in function_definitions(source)
                       if item[0] == "wait_input_animated_sprite"), None)
    if definition is None:
        return source
    _, start, end = definition
    opening_brace = source.find("{", start, end)
    if opening_brace < 0:
        raise ValueError("wait_input_animated_sprite has no body")
    source = (source[:opening_brace + 1] +
              "\n    pc_capture_set_modal_capture_active(1);" +
              source[opening_brace + 1:])
    definition = next(item for item in function_definitions(source)
                      if item[0] == "wait_input_animated_sprite")
    _, start, end = definition
    tokens = lex(source)

    def matching(index: int, left: str, right: str) -> int | None:
        if index is None or tokens[index].text != left:
            return None
        depth = 1
        for pos in range(index + 1, len(tokens)):
            token = tokens[pos]
            if token.kind in {"string", "char", "line", "block"}:
                continue
            if token.text == left: depth += 1
            elif token.text == right:
                depth -= 1
                if depth == 0: return pos
        return None

    for pos, token in enumerate(tokens):
        if token.start < start or token.start >= end or token.kind != "ident" or token.text != "while":
            continue
        opening = significant(tokens, pos + 1)
        condition_end = matching(opening, "(", ")") if opening is not None else None
        body_open = significant(tokens, condition_end + 1) if condition_end is not None else None
        body_end = matching(body_open, "{", "}") if body_open is not None else None
        if body_end is None:
            continue
        insert_at = tokens[body_end].start
        source = (source[:insert_at] +
                  "        capture_publish_intermediate_gameplay_frame(draw_page_index);\n" +
                  source[insert_at:])
        definition = next(item for item in function_definitions(source)
                          if item[0] == "wait_input_animated_sprite")
        _, start, end = definition
        closing_brace = source.rfind("}", start, end)
        if closing_brace < 0:
            raise ValueError("wait_input_animated_sprite has no closing brace")
        return (source[:closing_brace] +
                "    capture_publish_intermediate_gameplay_frame(draw_page_index);\n"
                "    pc_capture_set_modal_capture_active(0);\n" + source[closing_brace:])
    raise ValueError("could not find the animated input loop for interim gameplay capture")


def classify_view_test_calls(source: str, source_name: str) -> tuple[str, list[dict[str, str]]]:
    """Classify each view-test call by the code its result controls, then route it to the
    wide draw-view seam or the conditional behavior seam.  Unclear cases stay behavior."""
    tokens = lex(source)

    def matching(index: int, left: str, right: str) -> int | None:
        if index is None or index >= len(tokens) or tokens[index].text != left:
            return None
        depth = 1
        for pos in range(index + 1, len(tokens)):
            token = tokens[pos]
            if token.kind in {"string", "char", "line", "block"}:
                continue
            if token.text == left:
                depth += 1
            elif token.text == right:
                depth -= 1
                if depth == 0:
                    return pos
        return None

    def statement_end(index: int) -> int | None:
        index = significant(tokens, index) if index is not None else None
        if index is None:
            return None
        if tokens[index].text == "{":
            close = matching(index, "{", "}")
            return close + 1 if close is not None else None
        parens = brackets = braces = 0
        for pos in range(index, len(tokens)):
            token = tokens[pos]
            if token.kind in {"string", "char", "line", "block"}:
                continue
            if token.text == "(": parens += 1
            elif token.text == ")": parens -= 1
            elif token.text == "[": brackets += 1
            elif token.text == "]": brackets -= 1
            elif token.text == "{": braces += 1
            elif token.text == "}":
                if braces == 0:
                    return pos
                braces -= 1
            elif token.text == ";" and parens == brackets == braces == 0:
                return pos + 1
        return None

    definitions = function_definitions(source)
    if_conditions: list[tuple[int, int]] = []
    for pos, token in enumerate(tokens):
        if token.kind == "ident" and token.text == "if":
            opening = significant(tokens, pos + 1)
            closing = matching(opening, "(", ")") if opening is not None else None
            if opening is not None and closing is not None:
                if_conditions.append((opening, closing))

    calls: list[tuple[int, int, str]] = []
    report: list[dict[str, str]] = []
    side_effect_ops = {"=", "++", "--", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="}
    control_effects = {"continue", "break", "return", "goto"}
    drawing_calls = {"blit_planar_sprite_rows", "copy_planar_video_region"}

    for pos, token in enumerate(tokens):
        if token.kind != "ident" or token.text != "is_world_position_outside_view":
            continue
        opening = significant(tokens, pos + 1)
        if opening is None or tokens[opening].text != "(":
            continue
        closing = matching(opening, "(", ")")
        if closing is None:
            continue
        after_call = significant(tokens, closing + 1)
        if after_call is not None and tokens[after_call].text == "{":
            continue  # the function definition, not a call

        containing = [(a, b) for a, b in if_conditions if a < pos < b]
        branch = min(containing, key=lambda span: span[1] - span[0]) if containing else None
        kind = "behaviour"
        reason = "not the direct condition of a drawing-only if branch"
        if branch:
            body_start = significant(tokens, branch[1] + 1)
            body_end = statement_end(body_start)
            if body_start is not None and body_end is not None:
                body = tokens[body_start:body_end]
                significant_body = [t for t in body if t.kind not in {"space", "line", "block"}]
                texts = [t.text for t in significant_body]
                called: list[str] = []
                for local, part in enumerate(body):
                    if part.kind != "ident":
                        continue
                    after = significant(body, local + 1)
                    if after is not None and body[after].text == "(":
                        called.append(part.text)
                effects = set(texts) & control_effects
                if set(texts) & side_effect_ops:
                    effects.add("state assignment/update")
                other_calls = {name for name in called
                               if name not in drawing_calls and name not in {"if", "for", "while", "switch", "sizeof"}
                               and not name.isupper()}
                effects.update(other_calls)
                if any(name in drawing_calls for name in called) and not effects:
                    kind = "draw"
                    reason = "controlled branch only issues draw calls"
                elif effects:
                    reason = "controlled branch also performs: " + ", ".join(sorted(effects))
                else:
                    reason = "controlled branch does not issue a draw call"

        function = next((name for name, start, end in definitions if start <= token.start < end), "<file-scope>")
        line = str(source.count("\n", 0, token.start) + 1)
        column = str(token.start - source.rfind("\n", 0, token.start))
        report.append({"source": source_name, "line": line, "column": column,
                       "function": function, "classification": kind, "reason": reason})

        if kind == "draw":
            args = source[tokens[opening].end:tokens[closing].start]
            calls.append((token.start, tokens[closing].end,
                          "pc_capture_is_world_position_outside_wide_view(" + args +
                          ", is_world_position_outside_view(" + args + "))"))
        else:
            # Keep the original test available as the fallback result; the helper substitutes
            # the wide bounds only when wide_activity is enabled.
            args = source[tokens[opening].end:tokens[closing].start]
            calls.append((token.start, tokens[closing].end,
                          "pc_capture_is_world_position_outside_wide_if_active(" + args +
                          ", is_world_position_outside_view(" + args + "))"))

    for start, end, replacement in sorted(calls, reverse=True):
        source = source[:start] + replacement + source[end:]
    return source, report


def generate(source_dir: Path, output_dir: Path, override_dir: Path,
             port_dir: Path | None = None) -> None:
    port_dir = port_dir or Path(__file__).resolve().parents[1] / "port"
    check_game_hooks(port_dir, override_dir)
    header_path = source_dir / "DUKE.H"
    game_paths = [source_dir / "GAME1.C", source_dir / "GAME2.C"]
    header = header_path.read_text(encoding="latin1")
    functions, globals_ = header_symbols(header)
    raw_units = {p: p.read_text(encoding="latin1") for p in game_paths}
    sound_doc = json.loads((port_dir / "sound_sources.json").read_text(encoding="utf-8"))
    if sound_doc.get("version") != 1 or not isinstance(sound_doc.get("sites"), dict):
        raise ValueError("port/sound_sources.json must contain version 1 and a sites object")
    sound_sites = sound_doc["sites"]
    for p, raw in raw_units.items():
        functions.update(name for name, _, _ in function_definitions(raw))
        globals_.update(defined_objects(raw))
    # The storage identifiers are intentionally mechanical and never alias library names.
    for raw in [header, *raw_units.values()]:
        globals_.update(re.findall(r"\bd_[0-9A-Fa-f]{4}_?\b", uncomment(raw)))
    prefixes = functions | globals_

    view_test_report: list[dict[str, str]] = []
    sound_site_report: list[dict[str, str]] = []
    spin_loop_report: list[dict[str, str]] = []
    episode_state_report: list[dict[str, str]] = []
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
            "#define DUKE_H\n", "#define DUKE_H\n\n#include <stdint.h>\n#include \"game_hooks.h\"\n#include \"platform.h\"\n", 1
        )
        generated_header = re.sub(
            rf"(ep{episode}_request_priority_sound_effect\s*\(\s*int16_t\s+sound_effect_id)\s*\)",
            r"\1, int16_t sound_source_x)", generated_header,
        )
        if f"ep{episode}_request_priority_sound_effect(int16_t sound_effect_id, int16_t sound_source_x)" not in generated_header:
            raise ValueError("could not widen the generated sound-request declaration")
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
        sprite_site = 1
        for source_path in game_paths:
            raw = replace_overrides(raw_units[source_path], source_path, override_dir)
            raw, classified = classify_view_test_calls(raw, source_path.name)
            if episode == 1:
                view_test_report.extend(classified)
            raw = instrument_modal_capture(raw)
            raw = inject_pc_spin(raw, source_path.name,
                                 spin_loop_report if episode == 1 else [])
            raw = instrument_episode_state(raw, episode, source_path.name,
                                           episode_state_report if episode == 1 else [])
            raw = rewrite_sound_requests(raw, source_path.name, sound_sites,
                                         sound_site_report if episode == 1 else [])
            raw, site_count = tag_sprite_draw_calls(raw, sprite_site)
            sprite_site += site_count
            if source_path.name.upper() == "GAME1.C":
                raw = instrument_gameplay_capture(raw)
            translated = translate(raw, episode, prefixes)
            if source_path.name.upper() == "GAME1.C":
                translated += (
                    f"\n__attribute__((section(\".ep{episode}$a\"), used)) "
                    f"unsigned char ep{episode}_state_begin = 0;\n"
                    f"__attribute__((section(\".ep{episode}$z\"), used)) "
                    f"unsigned char ep{episode}_state_end = 0;\n"
                )
            (ep_dir / source_path.name).write_text(translated, encoding="latin1", newline="\n")

    review_dir = output_dir.parent / "workers" / "luna-wide"
    review_dir.mkdir(parents=True, exist_ok=True)
    reports = [
        ("view-test-classification.csv", view_test_report,
         ["source", "line", "column", "function", "classification", "reason"]),
    ]
    for filename, rows, columns in reports:
        with (review_dir / filename).open("w", encoding="utf-8", newline="") as report_file:
            writer = csv.DictWriter(report_file, fieldnames=columns)
            writer.writeheader()
            writer.writerows(rows)
    flow_report_dir = output_dir.parent / "workers" / "luna-flow"
    flow_report_dir.mkdir(parents=True, exist_ok=True)
    for filename, rows, columns in [
        ("sound-sites.csv", sound_site_report,
         ["source", "line", "function", "occurrence", "x", "reason"]),
        ("spin-loops.csv", spin_loop_report,
         ["source", "line", "function", "classification", "condition", "reason"]),
        ("episode-state-layout.csv", episode_state_report,
         ["episode", "source", "function", "variable", "section", "storage"]),
    ]:
        with (flow_report_dir / filename).open("w", encoding="utf-8", newline="") as report_file:
            writer = csv.DictWriter(report_file, fieldnames=columns)
            writer.writeheader()
            writer.writerows(rows)


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
