"""Rename BSS globals d_XXXX -> d_XXXX_ (rule BSS-ORDER) in sources.

    python tools/bssnames.py OUTDIR [FILES...]     write renamed copies to OUTDIR (same relative paths)

Only names whose DN1 DGROUP offset lies in [bss_start, bss_end) are renamed;
initialised data and episode-only names (d_dnN_XXXX) are untouched.  The
renamed copies are verified and published by the normal promotion path.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT  # noqa: E402
import symbols  # noqa: E402

NAME = re.compile(r"\bd_([0-9a-f]{4})\b(?!_)")


def rename(text: str) -> str:
    c = symbols.census("dn1")["startup"]
    lo, hi = c["bss_start"], c["bss_end"]
    return NAME.sub(lambda m: m.group(0) + "_" if lo <= int(m.group(1), 16) < hi else m.group(0), text)


def main() -> int:
    out = Path(sys.argv[1])
    files = [Path(f) for f in sys.argv[2:]] or sorted(
        list((ROOT / "src").rglob("*.c")) + list((ROOT / "src").rglob("*.asm")))
    n = 0
    for f in files:
        f = f if f.is_absolute() else ROOT / f
        t = f.read_text("latin-1")
        new = rename(t)
        if new != t:
            dst = out / f.relative_to(ROOT)
            dst.parent.mkdir(parents=True, exist_ok=True)
            dst.write_text(new, encoding="latin-1")
            n += 1
    print(f"{n} files renamed into {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
