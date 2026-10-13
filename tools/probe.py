"""Re-run the compiler/toolchain rule register (evidence/compiler-rules.json).

    python tools/probe.py            run every rule, fail if any outcome differs
    python tools/probe.py RULE_ID    run one rule verbosely

Each rule names a check and the outcome it recorded.  Checks are small,
discriminating experiments against the pinned tools and the locked oracle:
flag-necessity (canonical source EQUAL with the profile, not EQUAL with the
flag changed), source variants, and object-level probes in probes/.
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import EVIDENCE, LAYOUT, RECIPES, ROOT, load_json  # noqa: E402
import disasm  # noqa: E402
import omf  # noqa: E402
import search  # noqa: E402
import tcc  # noqa: E402

RULES = EVIDENCE / "compiler-rules.json"


def _status_all(fid: str, text: str, flags: list) -> str:
    out = search.run(text, fid, flags=flags, profile=None, record=False)
    return "EQUAL" if out["best_status"] == "EQUAL" else "NOT_EQUAL"


def _canonical(fid: str) -> tuple:
    r = load_json(RECIPES / f"{fid}.json")
    return (ROOT / r["source"]).read_text("latin-1"), r["flags"]


def check_flag(args: dict) -> dict:
    """Profile EQUAL for all functions; changed flags NOT_EQUAL for >= 1."""
    rows = {}
    for fid in args["functions"]:
        text, flags = _canonical(fid)
        changed = [f for f in flags if f not in args.get("remove", [])] + args.get("add", [])
        rows[fid] = {"profile": _status_all(fid, text, flags), "changed": _status_all(fid, text, changed)}
    ok_profile = all(v["profile"] == "EQUAL" for v in rows.values())
    discriminated = any(v["changed"] != "EQUAL" for v in rows.values())
    outcome = ("CONFIRMED" if ok_profile and discriminated else
               "CONSISTENT_NOT_DISCRIMINATED" if ok_profile else "FALSIFIED")
    return {"outcome": outcome, "rows": rows}


def check_variant(args: dict) -> dict:
    rows = {}
    for fid in args["functions"]:
        text, flags = _canonical(fid)
        var = re.sub(args["pattern"], args["replace"], text)
        if var == text:
            raise RuntimeError(f"variant pattern does not apply to {fid}")
        rows[fid] = {"canonical": _status_all(fid, text, flags), "variant": _status_all(fid, var, flags)}
    ok = all(v["canonical"] == "EQUAL" and v["variant"] != "EQUAL" for v in rows.values())
    return {"outcome": "CONFIRMED" if ok else "FALSIFIED", "rows": rows}


def _listing(src: str, flags: list) -> list:
    r = tcc.compile_c((ROOT / src).read_text("latin-1"), flags)
    o = omf.OmfReader().read(r.obj)
    seg = next(s["name"] for s in o.segment_defs if s["class"] == "CODE")
    t = o.segments[seg]
    pubs = {p["offset"]: p["name"] for p in o.publics if p["segment"] == seg}
    fx = {f["offset"]: (f["loc"], f["target_kind"], f["target"]) for f in o.linker_fixups if f["segment"] == seg}
    rows, a, cur = [], 0, None
    while a < len(t):
        i = disasm.decode(t, a, 0)
        cur = pubs.get(a, cur)
        rows.append({"at": a, "fn": cur, "raw": i.raw.hex(), "asm": f"{i.mnem} {i.ops}".strip(),
                     "fixups": [fx[k] for k in range(a, a + i.size) if k in fx]})
        a += i.size
    return rows


def check_call_forms(args: dict) -> dict:
    rows = _listing("probes/call_forms.c", tcc.profile_flags("tc20-l-gzo"))
    caller = [r for r in rows if r["fn"] == "_caller"]
    seen = {}
    for k, r in enumerate(caller):
        if r["asm"].startswith("lcall"):
            seen.setdefault("far", []).append(r["fixups"])
        if r["asm"].startswith("call") and caller[k - 1]["raw"] == "0e":
            seen.setdefault("near", []).append(r["fixups"])
    far = seen.get("far", [])
    near = seen.get("near", [])
    facts = {
        "extern_far_call_with_extdef_fixup": any(f and f[0][1] == "external" for f in far),
        "later_public_far_call_with_own_segment_fixup": any(f and f[0][1] == "segment" for f in far),
        "earlier_and_static_calls_push_cs_near_without_fixup": len(near) == 3 and all(not f for f in near),
    }
    return {"outcome": "CONFIRMED" if all(facts.values()) else "FALSIFIED", "facts": facts}


def check_z_effect(args: dict) -> dict:
    base = tcc.profile_flags("tc20-l-gzo")
    on = [r["asm"] for r in _listing("probes/zflag.c", base) if r["fn"] == "_z1"]
    off = [r["asm"] for r in _listing("probes/zflag.c", [f for f in base if f != "-Z"]) if r["fn"] == "_z1"]
    facts = {"with_Z_store_reuses_ax": on.count("mov ax, word ptr [0]") == 1,
             "without_Z_reloads": off.count("mov ax, word ptr [0]") == 2}
    return {"outcome": "CONFIRMED" if all(facts.values()) else "FALSIFIED", "facts": facts}


def check_startup_model(args: dict) -> dict:
    import census
    import oracle
    import toolchain
    rows = {}
    for m in "STCMLH":
        o = omf.OmfReader().read(toolchain.tool(f"LIB/C0{m}.OBJ").read_bytes())
        t = o.segments["_TEXT"]
        mask = {k for f in o.fixups if f["segment"] == "_TEXT" for k in range(f["offset"], f["offset"] + f["width"])}
        rows[m] = {}
        for e in ("dn1", "dn2", "dn3"):
            img = oracle.load_image(e)[0]
            rows[m][e] = sum(1 for i in range(len(t)) if i not in mask and t[i] != img[i])
    del census
    ok = all(v == 0 for v in rows["L"].values()) and all(
        any(v > 0 for v in rows[m].values()) for m in "STCMH")
    return {"outcome": "CONFIRMED" if ok else "FALSIFIED", "differing_bytes": rows}


def check_c0_reassembly(args: dict) -> dict:
    import toolchain
    extra = {n: toolchain.tool(f"STARTUP/{n}").read_bytes() for n in ("RULES.ASI", "EMUVARS.ASI")}
    r = tcc.assemble(toolchain.tool("STARTUP/C0.ASM").read_text("latin-1"), ["/D__LARGE__", "/MX"],
                     extra_files=extra)
    a = omf.OmfReader().read(r.obj)
    b = omf.OmfReader().read(toolchain.tool("LIB/C0L.OBJ").read_bytes())
    facts = {"text_equal": a.segments["_TEXT"] == b.segments["_TEXT"],
             "fixups_equal": a.linker_fixups == b.linker_fixups,
             "publics_equal": a.publics == b.publics}
    return {"outcome": "CONFIRMED" if all(facts.values()) else "FALSIFIED", "facts": facts}


def check_runtime(args: dict) -> dict:
    import census
    import oracle
    rows = {}
    for e in ("dn1", "dn2", "dn3"):
        img = oracle.load_image(e)[0]
        lib = census.scan_library(img)
        rows[e] = {"modules": len(lib), "bytes": sum(h["size"] for h in lib)}
    ok = all(v["modules"] == args["modules"] and v["bytes"] == args["bytes"] for v in rows.values())
    return {"outcome": "CONFIRMED" if ok else "FALSIFIED", "rows": rows}


def check_relocs_sorted(args: dict) -> dict:
    import oracle
    rows = {}
    for e in ("dn1", "dn2", "dn3"):
        _, rel = oracle.load_image(e)
        lin = [(s << 4) + o for s, o in rel]
        rows[e] = {"ascending": lin == sorted(lin), "normalised_offsets": all(o < 16 for _, o in rel)}
    ok = all(all(v.values()) for v in rows.values())
    return {"outcome": "CONFIRMED" if ok else "FALSIFIED", "rows": rows}


def check_link_path(args: dict) -> dict:
    """TLINK 2.0 links a trivial large-model unit with C0L.OBJ and CL.LIB under
    the pinned runner; the far library segments it pulls in for the startup's
    own references come out in the same order as the originals' first ones."""
    import shutil
    import uuid
    import mz
    import oracle
    import census
    import toolchain
    from common import BUILD
    r = tcc.compile_c("int g;\nint main(void) { g = 3; return g; }\n", tcc.profile_flags("tc20-l-gzo"))
    w = BUILD / "scratch" / "link" / uuid.uuid4().hex[:8]
    w.mkdir(parents=True)
    (w / "UNIT.OBJ").write_bytes(r.obj)
    for f in ("LIB/C0L.OBJ", "LIB/CL.LIB"):
        shutil.copy(toolchain.tool(f), w / Path(f).name)
    rc, out, _ = toolchain.run_dos("BIN/TLINK.EXE", ["/c", "/d", "/s", "C0L.OBJ", "UNIT.OBJ,OUT.EXE,OUT.MAP,CL.LIB"], w)
    facts = {"tlink_ok": rc == 0 and (w / "OUT.EXE").exists()}
    if facts["tlink_ok"]:
        segs = [ln.split()[3] for ln in (w / "OUT.MAP").read_text("latin-1").splitlines()
                if ln.strip().endswith("CODE") and len(ln.split()) >= 5]
        linked = [x[:-5] for x in segs if x.endswith("_TEXT") and x not in ("_TEXT", "UNIT_TEXT")
                  and x != "STKLEN_TEXT"]
        img, _ = oracle.load_image("dn1")
        orig = [h["module"] for h in census.scan_library(img) if h["segment"] != "_TEXT"]
        n = args["prefix"]
        facts["library_prefix_order_equal"] = linked[:n] == orig[:n]
        facts["linked_prefix"] = linked[:n]
        facts["unpacked_mz"] = len(mz.parse((w / "OUT.EXE").read_bytes()).image) > 0
    shutil.rmtree(w, ignore_errors=True)
    ok = facts["tlink_ok"] and facts.get("library_prefix_order_equal") and facts.get("unpacked_mz")
    return {"outcome": "CONFIRMED" if ok else "FALSIFIED", "facts": facts}


CHECKS = {"flag": check_flag, "link_path": check_link_path, "variant": check_variant, "call_forms": check_call_forms,
          "z_effect": check_z_effect, "startup_model": check_startup_model,
          "c0_reassembly": check_c0_reassembly, "runtime": check_runtime, "relocs_sorted": check_relocs_sorted}


def run_rule(rule: dict) -> dict:
    res = CHECKS[rule["check"]](rule.get("args", {}))
    res["expected"] = rule["outcome"]
    res["ok"] = res["outcome"] == rule["outcome"]
    return res


def main() -> int:
    rules = load_json(RULES)["rules"]
    only = sys.argv[1] if len(sys.argv) > 1 else None
    bad = 0
    for r in rules:
        if only and r["id"] != only:
            continue
        res = run_rule(r)
        mark = "ok " if res["ok"] else "BAD"
        print(f"[{mark}] {r['id']:24s} {res['outcome']:30s} (recorded {r['outcome']})")
        if only or not res["ok"]:
            print(json.dumps({k: v for k, v in res.items() if k not in ("ok",)}, indent=1))
        bad += not res["ok"]
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
