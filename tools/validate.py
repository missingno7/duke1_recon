"""Full validation from canonical inputs.  Nothing cached is trusted.

    python tools/validate.py                 oracle, toolchain, census+atlas check,
                                             fresh re-proof of every recipe, coverage
    python tools/validate.py --tests         also run the unit tests
    python tools/validate.py --write-progress  update docs/progress.md
    python tools/validate.py --quick         skip census/atlas regeneration check

Exit status 0 only if every accepted claim still holds in every episode it
claims, every recipe's source hash matches, and no canonical source is
orphaned.
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import (BUILD, EPISODES, EVIDENCE, LAYOUT, RECIPES, ROOT, SRC, atomic_json,  # noqa: E402
                    load_json, sha256)
import oracle  # noqa: E402
import search  # noqa: E402
import tcc  # noqa: E402
import toolchain  # noqa: E402


def recipes() -> dict:
    return {p.stem: load_json(p) for p in sorted(RECIPES.glob("*.json"))}


def prove_recipe(rid: str, r: dict, fresh: bool = True) -> dict:
    src = ROOT / r["source"]
    problems = []
    if not src.exists():
        return {"function": rid, "ok": False, "problems": [f"missing source {r['source']}"], "results": {}}
    text = src.read_text("latin-1")
    if sha256(src.read_bytes()) != r["source_sha256"]:
        problems.append("source hash differs from recipe")
    flags = r["flags"]
    out = search.run(text, rid, flags=flags, profile=r.get("profile"), name=r.get("name"),
                     record=False, fresh_compile=fresh)
    claimed = [e for e, v in r["episodes"].items() if v["status"] == "EQUAL"]
    for e in claimed:
        got = out["results"].get(e, {}).get("status")
        if got != "EQUAL":
            problems.append(f"{e}: claimed EQUAL, now {got}")
        elif out["results"][e]["size"][1] != r["episodes"][e]["size"]:
            problems.append(f"{e}: extent size changed")
    if out["lint"]:
        problems.append("lint: " + "; ".join(out["lint"]))
    return {"function": rid, "ok": not problems, "problems": problems,
            "results": {e: v["status"] for e, v in out["results"].items()}, "claimed": claimed}


def check_recipes(fresh: bool = True, only: set | None = None, workers: int = 6) -> list:
    rs = recipes()
    items = [(k, v) for k, v in rs.items() if only is None or k in only]
    with ThreadPoolExecutor(max_workers=workers) as pool:
        return list(pool.map(lambda kv: prove_recipe(kv[0], kv[1], fresh), items))


def coverage(results: list) -> dict:
    census = {e: load_json(BUILD / "census" / f"{e}.json") for e in EPISODES}
    rs = recipes()
    out = {}
    for e in EPISODES:
        c = census[e]
        img, relocs = oracle.load_image(e)
        segs = {s["name"]: s for s in c["segments"]}
        code_end = segs["DGROUP"]["start"]
        lib = sum(h["size"] for h in c["library_modules"])
        startup = segs["C0_TEXT"]["size"]
        asm = segs["ASM_TEXT"]["size"]
        game = sum(s["size"] for s in c["segments"] if s["kind"] == "game")
        proven = {}
        for r in results:
            if r["ok"] and e in r.get("claimed", []):
                proven[r["function"]] = rs[r["function"]]["episodes"][e]
        c_bytes = sum(v["size"] for v in proven.values())
        rel_lin = sorted((s << 4) + o for s, o in relocs)
        covered_rel = sum(1 for a in rel_lin for v in proven.values() if v["start"] <= a < v["start"] + v["size"])
        code_rel = sum(1 for a in rel_lin if a < code_end)
        data_size = c["startup"]["bss_start"]
        bss = c["startup"]["bss_end"] - c["startup"]["bss_start"]
        out[e] = {
            "code_bytes": code_end,
            "matching_c_code": c_bytes,
            "matching_c_functions": len(proven),
            "first_party_c_code": game,
            "first_party_c_functions": sum(1 for f in c["functions"] if f["segment"].startswith("G")),
            "matching_asm_code": 0,
            "asm_code": asm,
            "identified_runtime_code": startup + lib,
            "runtime_note": "C0L _TEXT and CL.LIB modules located by exact match outside fixups; identified, not yet linked",
            "unresolved_code": code_end - c_bytes - startup - lib,
            "code_relocations_in_proven_functions": covered_rel,
            "code_relocations": code_rel,
            "initialized_data_bytes": data_size,
            "matching_data_bytes": 0,
            "bss_bytes": bss,
            "bss_owned_bytes": 0,
            "natural_link": "not attempted",
            "relocation_order": "unobservable (LZ91 stores relocations as ascending deltas)",
            "unpacked_image_equal": False,
            "repacked_executable_equal": False,
        }
    return out


def progress_md(cov: dict, results: list) -> str:
    lines = ["# Progress", "", "Generated by `python tools/validate.py --write-progress` from a fresh re-proof of",
             "every recipe. Numbers are per episode; nothing here counts original bytes as source.", "",
             "| | DN1 | DN2 | DN3 |", "|---|---:|---:|---:|"]
    rows = [("Matching C functions", "matching_c_functions"), ("Matching C code bytes", "matching_c_code"),
            ("First-party C code bytes", "first_party_c_code"), ("First-party C functions", "first_party_c_functions"),
            ("Matching ASM code bytes", "matching_asm_code"), ("ASM code bytes (unresolved)", "asm_code"),
            ("Identified runtime code bytes (C0L + CL.LIB)", "identified_runtime_code"),
            ("Unresolved code bytes", "unresolved_code"),
            ("Code relocations inside proven functions", "code_relocations_in_proven_functions"),
            ("Code relocations", "code_relocations"),
            ("Initialized DGROUP bytes", "initialized_data_bytes"), ("Matching data bytes", "matching_data_bytes"),
            ("BSS bytes", "bss_bytes"), ("BSS bytes with proven ownership", "bss_owned_bytes")]
    for label, k in rows:
        lines.append(f"| {label} | " + " | ".join(str(cov[e][k]) for e in EPISODES) + " |")
    lines += ["", "Natural historical link: not attempted yet. Unpacked image equality: no. "
              "Repacked (LZEXE 0.91) equality: no.", "",
              "Relocation order is unobservable in the oracles: LZEXE 0.91 stores relocations as ascending deltas,",
              "so only the relocation *set* can be compared.", "", "## Accepted functions", "",
              "| Function | Episodes proven |", "|---|---|"]
    for r in sorted(results, key=lambda x: x["function"]):
        lines.append(f"| `{r['function']}` | {', '.join(r.get('claimed', []))} |")
    return "\n".join(lines) + "\n"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--tests", action="store_true")
    ap.add_argument("--quick", action="store_true")
    ap.add_argument("--write-progress", action="store_true")
    a = ap.parse_args()
    failures = []
    oracle.verify()
    print("oracle: lock verified")
    toolchain.verify_all()
    print("toolchain: pins verified")
    if not a.quick:
        r = subprocess.run([sys.executable, str(ROOT / "tools" / "census.py")], capture_output=True, text=True)
        if r.returncode:
            failures.append("census failed: " + r.stderr[-400:])
        r = subprocess.run([sys.executable, str(ROOT / "tools" / "atlas.py"), "--check"], capture_output=True, text=True)
        print("atlas:", r.stdout.strip())
        if r.returncode:
            failures.append("evidence/atlas.json is stale")
    rs = recipes()
    srcs = {Path(v["source"]).as_posix() for v in rs.values()}
    for p in sorted(SRC.rglob("*.c")):
        rel = p.relative_to(ROOT).as_posix()
        if rel not in srcs:
            failures.append(f"orphan canonical source without recipe: {rel}")
    results = check_recipes(fresh=True)
    for r in results:
        if not r["ok"]:
            failures.append(f"{r['function']}: {r['problems']}")
    print(f"recipes: {sum(r['ok'] for r in results)}/{len(results)} re-proven fresh")
    cov = coverage(results)
    for e in EPISODES:
        c = cov[e]
        print(f"  {e}: C {c['matching_c_functions']}/{c['first_party_c_functions']} functions, "
              f"{c['matching_c_code']}/{c['first_party_c_code']} bytes; runtime identified {c['identified_runtime_code']}; "
              f"relocs {c['code_relocations_in_proven_functions']}/{c['code_relocations']}")
    if a.tests:
        r = subprocess.run([sys.executable, "-m", "unittest", "discover", "-s", "tests"], cwd=ROOT,
                           capture_output=True, text=True)
        print(r.stderr.strip().splitlines()[-1] if r.stderr else "")
        if r.returncode:
            failures.append("unit tests failed")
    report = {"failures": failures, "coverage": cov, "results": results}
    atomic_json(BUILD / "validation" / "report.json", report)
    if a.write_progress and not failures:
        (ROOT / "docs").mkdir(exist_ok=True)
        (ROOT / "docs" / "progress.md").write_bytes(progress_md(cov, results).encode())
        print("docs/progress.md updated")
    if failures:
        print("VALIDATION FAILED")
        for f in failures:
            print("  -", f)
        return 1
    print("VALIDATION OK")
    return 0


if __name__ == "__main__":
    sys.exit(main())
