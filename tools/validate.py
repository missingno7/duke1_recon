"""Check the repository: the originals, the DOS build from src/, and the SDL3 port.

    python tools/validate.py [--no-port]

1. assets/ holds the original DN1/DN2/DN3.EXE (config/oracle.lock.json);
2. src/ builds all three byte for byte with the original toolchain (tools/build.py);
3. the SDL3 port builds (CMake, port/) and its EGA self-test passes; skipped with --no-port.
Exit status 0 only when everything holds.
"""
from __future__ import annotations

import argparse
import glob
import os
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, ROOT, SRC  # noqa: E402
import build  # noqa: E402
import oracle  # noqa: E402


def find_cmake() -> str | None:
    found = shutil.which("cmake")
    if found:
        return found
    pattern = "C:/Program Files/Microsoft Visual Studio/2022/*/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe"
    hits = glob.glob(pattern)
    return hits[0] if hits else None


def port_build() -> tuple:
    cmake = find_cmake()
    if not cmake:
        return False, "cmake not found"
    env = dict(os.environ)
    mingw = "C:/msys64/mingw64/bin"
    if os.path.isdir(mingw):
        env["PATH"] = mingw + os.pathsep + env.get("PATH", "")
    out = BUILD / "port"
    for argv in ([cmake, "-S", str(ROOT / "port"), "-B", str(out), "-G", "MinGW Makefiles"],
                 [cmake, "--build", str(out), "--parallel", "6"]):
        r = subprocess.run(argv, cwd=ROOT, env=env, capture_output=True, text=True)
        if r.returncode != 0:
            return False, (r.stdout + r.stderr).strip().splitlines()[-1:]
    if not (out / "duke1.exe").exists():
        return False, "duke1.exe missing"
    r = subprocess.run([str(out / "vga_selftest.exe")], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        return False, "EGA self-test: " + (r.stdout + r.stderr).strip()
    return True, f"{out / 'duke1.exe'}; EGA self-test passed"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--no-port", action="store_true")
    a = ap.parse_args()
    ok = True
    oracle.verify()
    print("originals: DN1/DN2/DN3.EXE match config/oracle.lock.json")
    for ep in EPISODES:
        res = build.build(SRC, ep, BUILD / "scratch" / "validate" / ep)
        shutil.rmtree(BUILD / "scratch" / "validate" / ep, ignore_errors=True)
        print(f"DOS build {ep}: {res['status']}" + ("" if res["status"] == "EQUAL" else f"  {res}"))
        ok &= res["status"] == "EQUAL"
    if not a.no_port:
        built, detail = port_build()
        print(f"SDL3 port: {'built ' + str(detail) if built else 'FAILED ' + str(detail)}")
        ok &= built
    print("VALIDATION OK" if ok else "VALIDATION FAILED")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
