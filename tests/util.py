"""Test helpers: a disposable copy of the repository for tests that write
canonical state (promotion, locking, journals)."""
from __future__ import annotations

import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

COPY = ("tools", "layout", "evidence", "recipes", "src", "probes", "include")
COPY_BUILD = ("census", "oracle")


def assets_available() -> bool:
    d = Path(os.environ.get("DUKE1_ASSET_DIR", ROOT / "assets"))
    return (d / "dn1.exe").exists() or (d / "DN1.EXE").exists()


class Sandbox:
    def __init__(self):
        self.dir = Path(tempfile.mkdtemp(prefix="duke1-sandbox-"))
        for name in COPY:
            if (ROOT / name).exists():
                shutil.copytree(ROOT / name, self.dir / name, ignore=shutil.ignore_patterns("__pycache__"))
        for name in COPY_BUILD:
            shutil.copytree(ROOT / "build" / name, self.dir / "build" / name)
        self.env = dict(os.environ, DUKE1_ASSET_DIR=str(ROOT / "assets"))

    def run(self, *args, timeout=600) -> subprocess.CompletedProcess:
        return subprocess.run([sys.executable, str(self.dir / "tools" / args[0]), *args[1:]], cwd=self.dir,
                              env=self.env, capture_output=True, text=True, timeout=timeout)

    def close(self):
        shutil.rmtree(self.dir, ignore_errors=True)
