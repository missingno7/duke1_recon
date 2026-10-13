"""Mechanical rewrites of recurring unnatural-but-EQUAL candidate forms.

    python tools/naturalize.py mkfp IN.c OUT.c

mkfp: `MK_FP(d_HI, d_LO + e)` built from two int globals -> one far pointer
      global `extern char far *d_LO;` with `d_LO + e` (d_HI is d_LO's segment
      word).  The result must be re-verified with tools/search.py; this tool
      never claims equality.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path


def mkfp(text: str) -> str:
    pairs = set(re.findall(r"MK_FP\s*\(\s*(d_[0-9a-f]{4})\s*,\s*(d_[0-9a-f]{4})", text))
    for hi, lo in pairs:
        if int(hi[2:], 16) != int(lo[2:], 16) + 2:
            raise SystemExit(f"{hi} is not the segment word of {lo}")
        text = re.sub(r"\(\s*(?:unsigned\s+)?char\s+far\s*\*\s*\)\s*MK_FP", "MK_FP", text)
        text = re.sub(r"MK_FP\s*\(\s*" + hi + r"\s*,\s*" + lo + r"\s*([^()]*(?:\([^()]*\)[^()]*)*)\)",
                      lambda m: "(" + lo + m.group(1) + ")", text)
        text = re.sub(r"(?m)^extern\s+(?:unsigned\s+)?int\s+" + hi + r"\s*;\s*\n", "", text)
        text = re.sub(r"(?m)^extern\s+(?:unsigned\s+)?int\s+" + lo + r"\s*;",
                      "extern char far *" + lo + ";", text)
    return text


def main() -> int:
    mode, src, dst = sys.argv[1:4]
    text = Path(src).read_text("latin-1")
    out = {"mkfp": mkfp}[mode](text)
    Path(dst).write_text(out, encoding="latin-1")
    print(f"{mode}: {'changed' if out != text else 'unchanged'} -> {dst}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
