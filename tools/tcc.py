"""Isolated, content-addressed Turbo C 2.0 / TASM 1.0 compiles.

Every compile:
  * stages UNIT.C (CRLF, latin-1) plus the pinned TC headers (INCLUDE\\) and the
    project headers (include/*.H) into a fresh scratch directory;
  * runs the pinned TCC.EXE under the pinned MS-DOS Player;
  * preserves the complete object, the compiler log and a receipt;
  * is keyed by sha256(staged inputs, flags, toolchain identity, this file),
    so an identical request is served from build/cc-cache and two processes
    asking for the same key at once coalesce on one compile (O_EXCL in-flight
    marker holding the owner PID; a dead owner's marker is taken over).

The cache is research state: deleting build/ only costs time.  Acceptance
(promote/validate) can force fresh compiles with fresh=True.
"""
from __future__ import annotations

import json
import os
import shutil
import sys
import time
import uuid
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, CONFIG, atomic_json, content_key, load_json, sha256, sha256_file  # noqa: E402
import toolchain  # noqa: E402

CACHE = BUILD / "cc-cache"
SCRATCH = BUILD / "scratch" / "cc"
INFLIGHT = CACHE / "inflight"
SELF_SHA = sha256_file(Path(__file__))


@dataclass
class Receipt:
    key: str
    ok: bool
    obj: bytes | None
    log: str
    directory: Path
    cached: bool
    data: dict


def profiles() -> dict:
    return load_json(CONFIG / "profiles.json")["profiles"]


def profile_flags(profile: str) -> list:
    p = profiles().get(profile)
    if p is None:
        raise KeyError(f"unknown compiler profile {profile!r}")
    return list(p["flags"])


def dos_text(text: str) -> bytes:
    """Historical tools want CRLF; TASM 1.0 misparses LF-only input."""
    return text.replace("\r\n", "\n").replace("\n", "\r\n").encode("latin-1")


def _stage_headers() -> dict:
    files = {}
    tc = toolchain.root()
    for rel in sorted(toolchain.lock()["files"]):
        if rel.startswith("INCLUDE/"):
            files[rel] = toolchain.tool(rel).read_bytes()
    del tc
    return files


def _pid_alive(pid: int) -> bool:
    if pid <= 0:
        return False
    if os.name == "nt":
        import ctypes
        h = ctypes.windll.kernel32.OpenProcess(0x1000, False, pid)  # QUERY_LIMITED_INFORMATION
        if not h:
            return False
        code = ctypes.c_ulong()
        ctypes.windll.kernel32.GetExitCodeProcess(h, ctypes.byref(code))
        ctypes.windll.kernel32.CloseHandle(h)
        return code.value == 259  # STILL_ACTIVE
    try:
        os.kill(pid, 0)
        return True
    except OSError:
        return False


def _load_cached(key: str) -> Receipt | None:
    d = CACHE / key[:2] / key
    rp = d / "receipt.json"
    if not rp.exists():
        return None
    data = load_json(rp)
    obj = None
    if data["ok"]:
        op = d / "UNIT.OBJ"
        if not op.exists() or sha256_file(op) != data["object_sha256"]:
            return None  # corrupted cache entry: recompile
        obj = op.read_bytes()
    log = (d / "compiler.log").read_text("latin-1") if (d / "compiler.log").exists() else ""
    return Receipt(key, data["ok"], obj, log, d, True, data)


def compile_c(source: str, flags: list, *, extra_files: dict | None = None,
              fresh: bool = False, timeout: int = 300, name: str = "UNIT.C") -> Receipt:
    """Compile `source` as `name` (default UNIT.C) with TCC `flags` (without -c/-I,
    added here).  In the large model the code segment is named after the file
    (G1.C -> G1_TEXT), which matters when several units are linked together."""
    src_name = name.upper()
    staged = {src_name: dos_text(source)}
    for hname, data in _stage_headers().items():
        staged[hname] = data
    for xname, data in (extra_files or {}).items():
        staged[xname.upper()] = data if isinstance(data, bytes) else dos_text(data)
    argv = ["-c", "-IINCLUDE", *flags, src_name]
    request = {"kind": "tcc", "argv": argv,
               "inputs": {k: sha256(v) for k, v in sorted(staged.items())},
               "toolchain": toolchain.identity(), "wrapper": SELF_SHA}
    key = content_key(request)
    if not fresh:
        hit = _load_cached(key)
        if hit:
            return hit
    INFLIGHT.mkdir(parents=True, exist_ok=True)
    marker = INFLIGHT / key
    owned = False
    deadline = time.time() + timeout + 60
    while not owned:
        try:
            fd = os.open(marker, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            os.write(fd, str(os.getpid()).encode())
            os.close(fd)
            owned = True
        except FileExistsError:
            if not fresh:
                hit = _load_cached(key)
                if hit:
                    return hit
            try:
                pid = int(marker.read_text() or "0")
            except (OSError, ValueError):
                pid = 0
            if not _pid_alive(pid):
                try:
                    marker.unlink()
                except OSError:
                    pass
                continue
            if time.time() > deadline:
                raise TimeoutError(f"compile {key} held by live pid {pid} too long")
            time.sleep(0.2)
    try:
        if not fresh:
            hit = _load_cached(key)
            if hit:
                return hit
        work = SCRATCH / uuid.uuid4().hex
        for name, data in staged.items():
            p = work / name
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_bytes(data)
        toolchain.verify_all()
        rc, out, cmd = toolchain.run_dos("BIN/TCC.EXE", argv, work, timeout=timeout)
        (work / "compiler.log").write_bytes(out)
        obj_path = work / "UNIT.OBJ"
        produced = work / (src_name.rsplit(".", 1)[0] + ".OBJ")
        if produced != obj_path and produced.exists():
            produced.replace(obj_path)          # the cache always holds UNIT.OBJ
        ok = rc == 0 and obj_path.exists()
        data = {"key": key, "request": request, "ok": ok, "returncode": rc,
                "host_argv": [Path(cmd[0]).name, *cmd[1:2], "TCC.EXE", *argv],
                "object_sha256": sha256_file(obj_path) if ok else None,
                "log_sha256": sha256(out)}
        atomic_json(work / "receipt.json", data)
        for sname in list(staged):
            if sname != src_name:
                (work / sname).unlink()
        shutil.rmtree(work / "INCLUDE", ignore_errors=True)
        dest = CACHE / key[:2] / key
        dest.parent.mkdir(parents=True, exist_ok=True)
        if dest.exists():
            shutil.rmtree(dest)
        os.replace(work, dest)
        return Receipt(key, ok, (dest / "UNIT.OBJ").read_bytes() if ok else None,
                       out.decode("latin-1"), dest, False, data)
    finally:
        try:
            marker.unlink()
        except OSError:
            pass


def assemble(source: str, flags: list, *, extra_files: dict | None = None,
             fresh: bool = False, timeout: int = 300) -> Receipt:
    """TASM 1.0 counterpart of compile_c (UNIT.ASM -> UNIT.OBJ)."""
    staged = {"UNIT.ASM": dos_text(source)}
    for name, data in (extra_files or {}).items():
        staged[name.upper()] = data if isinstance(data, bytes) else dos_text(data)
    argv = [*flags, "UNIT.ASM,UNIT.OBJ;"]
    request = {"kind": "tasm", "argv": argv,
               "inputs": {k: sha256(v) for k, v in sorted(staged.items())},
               "toolchain": toolchain.identity(), "wrapper": SELF_SHA}
    key = content_key(request)
    if not fresh:
        hit = _load_cached(key)
        if hit:
            return hit
    work = SCRATCH / uuid.uuid4().hex
    for name, data in staged.items():
        (work / name).parent.mkdir(parents=True, exist_ok=True)
        (work / name).write_bytes(data)
    rc, out, cmd = toolchain.run_dos("BIN/TASM.EXE", argv, work, timeout=timeout)
    (work / "compiler.log").write_bytes(out)
    obj_path = work / "UNIT.OBJ"
    ok = rc == 0 and obj_path.exists()
    data = {"key": key, "request": request, "ok": ok, "returncode": rc,
            "object_sha256": sha256_file(obj_path) if ok else None, "log_sha256": sha256(out)}
    atomic_json(work / "receipt.json", data)
    dest = CACHE / key[:2] / key
    dest.parent.mkdir(parents=True, exist_ok=True)
    if not dest.exists():
        os.replace(work, dest)
    else:
        shutil.rmtree(work, ignore_errors=True)
    return Receipt(key, ok, (dest / "UNIT.OBJ").read_bytes() if ok else None,
                   out.decode("latin-1"), dest, False, data)


if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser(description="compile one C file with a pinned profile")
    ap.add_argument("source")
    ap.add_argument("--profile", default=None)
    ap.add_argument("--flags", nargs="*", default=None)
    ap.add_argument("--fresh", action="store_true")
    a = ap.parse_args()
    fl = a.flags if a.flags is not None else profile_flags(a.profile or load_json(CONFIG / "profiles.json")["default"])
    r = compile_c(Path(a.source).read_text("latin-1"), fl, fresh=a.fresh)
    print(json.dumps({"ok": r.ok, "key": r.key, "cached": r.cached, "dir": str(r.directory)}, indent=1))
    print(r.log)
