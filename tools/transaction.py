"""Single-writer lock and journaled multi-file publication.

Lock: build/locks/canonical.lock, created O_EXCL and holding the owner PID.
A lock whose owner process is dead is reported and taken over; a live
owner is waited for (bounded).

Journal: build/locks/publication.json records base64 before/after images of
every file a publication writes.  apply() refuses to overwrite a file that no
longer equals its 'before' image (a concurrent or manual edit), writes each
file atomically, and rollback() restores 'before' images only where the file
still equals 'after' (it never clobbers an unrelated edit).  recover() finishes
a crashed publication by rolling it back.
"""
from __future__ import annotations

import base64
import json
import os
import time
from contextlib import contextmanager
from pathlib import Path

from common import BUILD, ROOT, atomic_bytes, atomic_json

LOCKS = BUILD / "locks"
LOCK = LOCKS / "canonical.lock"
JOURNAL = LOCKS / "publication.json"
WRITABLE = ("src/", "recipes/", "evidence/promotions.jsonl", "evidence/blockers.json")


class LockBusy(RuntimeError):
    pass


class Conflict(RuntimeError):
    pass


def _alive(pid: int) -> bool:
    from tcc import _pid_alive
    return _pid_alive(pid)


@contextmanager
def exclusive(timeout: float = 600.0, owner: str = ""):
    LOCKS.mkdir(parents=True, exist_ok=True)
    deadline = time.time() + timeout
    while True:
        try:
            fd = os.open(LOCK, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            os.write(fd, json.dumps({"pid": os.getpid(), "owner": owner, "at": time.time()}).encode())
            os.close(fd)
            break
        except FileExistsError:
            try:
                info = json.loads(LOCK.read_text() or "{}")
            except (OSError, ValueError):
                info = {}
            pid = int(info.get("pid", 0))
            if pid and not _alive(pid):
                print(f"[lock] taking over stale canonical lock of dead pid {pid}")
                try:
                    LOCK.unlink()
                except OSError:
                    pass
                continue
            if time.time() > deadline:
                raise LockBusy(f"canonical lock held by pid {pid} ({info.get('owner')})")
            time.sleep(0.25)
    try:
        if JOURNAL.exists():
            raise Conflict("an unfinished publication journal exists; run tools/promote.py --recover")
        yield
    finally:
        try:
            LOCK.unlink()
        except OSError:
            pass


def _check_path(rel: str) -> Path:
    if not any(rel == w or rel.startswith(w) for w in WRITABLE):
        raise Conflict(f"publication may not write {rel}")
    p = (ROOT / rel).resolve()
    if ROOT.resolve() not in p.parents:
        raise Conflict(f"path escapes repository: {rel}")
    return p


def prepare(changes: dict) -> dict:
    """changes: {relative path: new bytes, or None to delete}.  Returns the journal."""
    entries = []
    for rel, data in sorted(changes.items()):
        p = _check_path(rel)
        before = p.read_bytes() if p.exists() else None
        entries.append({"path": rel,
                        "before": None if before is None else base64.b64encode(before).decode(),
                        "after": None if data is None else base64.b64encode(data).decode()})
    journal = {"pid": os.getpid(), "at": time.time(), "entries": entries}
    atomic_json(JOURNAL, journal)
    return journal


def _b(x):
    return None if x is None else base64.b64decode(x)


def apply(journal: dict) -> None:
    for e in journal["entries"]:
        p = _check_path(e["path"])
        cur = p.read_bytes() if p.exists() else None
        if cur != _b(e["before"]) and cur != _b(e["after"]):
            raise Conflict(f"{e['path']} changed since the publication was prepared")
    for e in journal["entries"]:
        p = _check_path(e["path"])
        if e["after"] is None:
            if p.exists():
                p.unlink()
        else:
            atomic_bytes(p, _b(e["after"]))


def rollback(journal: dict) -> list:
    restored = []
    for e in journal["entries"]:
        p = _check_path(e["path"])
        cur = p.read_bytes() if p.exists() else None
        if cur == _b(e["after"]):
            if e["before"] is None:
                if p.exists():
                    p.unlink()
            else:
                atomic_bytes(p, _b(e["before"]))
            restored.append(e["path"])
        elif cur != _b(e["before"]):
            raise Conflict(f"{e['path']} matches neither journal image; refusing to clobber it")
    finish()
    return restored


def finish() -> None:
    try:
        JOURNAL.unlink()
    except FileNotFoundError:
        pass


def recover() -> list:
    if not JOURNAL.exists():
        return []
    return rollback(json.loads(JOURNAL.read_text()))
