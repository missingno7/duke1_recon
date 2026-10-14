#!/usr/bin/env python3
"""Run an original DNn.EXE in the pinned DOSBox-X acceptance build and capture 320x200 frames."""

from __future__ import annotations

import argparse
import json
import shutil
import subprocess
import sys
from pathlib import Path

from png_utils import read_png, resize_nearest, write_png

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_DOSBOX = Path(r"C:/tools/dosbox-x-2026.08.31-simant-acceptance/dosbox-x-v3.exe")


def parse_times(value: str) -> list[int]:
    try:
        times = [int(item.strip()) for item in value.split(",") if item.strip()]
    except ValueError as exc:
        raise argparse.ArgumentTypeError("capture times must be comma-separated milliseconds") from exc
    if not times or any(item < 0 for item in times):
        raise argparse.ArgumentTypeError("at least one nonnegative capture time is required")
    return times


def read_script(path: Path | None) -> list[str]:
    if path is None:
        return []
    result: list[tuple[int, int, str]] = []
    for line_number, raw in enumerate(path.read_text(encoding="utf-8-sig").splitlines(), 1):
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        parts = line.split()
        if len(parts) < 2:
            raise ValueError(f"{path}:{line_number}: expected '<ms> key <name>'")
        try:
            when = int(parts[0])
        except ValueError as exc:
            raise ValueError(f"{path}:{line_number}: invalid millisecond time") from exc
        if when < 0:
            raise ValueError(f"{path}:{line_number}: time must be nonnegative")
        action = parts[1].lower()
        if action == "key" and len(parts) == 3:
            result.append((when, line_number, f"{when} key {parts[2]}"))
        elif action == "keydown" and len(parts) == 3:
            # The acceptance build exposes key taps only. A down is represented as the
            # same mapper key event; the paired keyup is already part of that tap.
            result.append((when, line_number, f"{when} key {parts[2]}"))
        elif action in {"keyup", "shot", "quit"}:
            continue
        else:
            raise ValueError(f"{path}:{line_number}: unsupported reference action: {line}")
    return [item[2] for item in sorted(result)]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--episode", type=int, choices=(1, 2, 3), required=True)
    parser.add_argument("--cycles", default="auto", help="DOSBox-X cycles: auto or fixed:20000")
    parser.add_argument("--script", type=Path, help="port key script; shot/quit actions are ignored")
    parser.add_argument("--at-ms", type=parse_times, required=True, help="comma-separated capture times")
    parser.add_argument("--out", type=Path, default=ROOT / "build/scratch/dosref/frames")
    parser.add_argument("--data", type=Path, default=ROOT / "assets")
    parser.add_argument("--dosbox", type=Path, default=DEFAULT_DOSBOX)
    args = parser.parse_args()

    if not args.dosbox.is_file():
        parser.error(f"DOSBox-X acceptance executable not found: {args.dosbox}")
    if not args.data.is_dir():
        parser.error(f"game data directory not found: {args.data}")
    cycles = args.cycles.lower()
    if cycles == "auto":
        cycles_line = "cycles=auto"
        cycle_label = "auto"
    elif cycles.startswith("fixed:") and cycles[6:].isdigit():
        cycles_line = f"cycles=fixed {int(cycles[6:])}"
        cycle_label = f"fixed {int(cycles[6:])}"
    else:
        parser.error("--cycles must be 'auto' or 'fixed:<cycles>' (for example fixed:20000)")

    scratch = ROOT / "build/scratch/dosref"
    data_copy = scratch / "game"
    scratch.mkdir(parents=True, exist_ok=True)
    if data_copy.exists():
        shutil.rmtree(data_copy)
    shutil.copytree(args.data.resolve(), data_copy)
    out_dir = args.out.resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    key_lines = read_script(args.script.resolve() if args.script else None)
    key_script = scratch / "keys.txt"
    key_script.write_text("\n".join(key_lines) + ("\n" if key_lines else ""), encoding="ascii")
    config = scratch / "ref.conf"
    config.write_text(
        "\n".join(
            [
                "[sdl]",
                "output=surface",
                "windowresolution=640x400",
                "[dosbox]",
                "machine=svga_s3",
                "working directory option=noprompt",
                f"acceptance script={key_script}",
                "[cpu]",
                "core=normal",
                "cputype=386",
                cycles_line,
                "[mixer]",
                "nosound=true",
                "[autoexec]",
                f'mount c "{data_copy}"',
                "c:",
                f"dn{args.episode}",
                "",
            ]
        ),
        encoding="ascii",
    )

    powershell = shutil.which("powershell.exe") or shutil.which("powershell")
    if not powershell:
        parser.error("Windows PowerShell is required by tools/capture_window.ps1")
    print(f"DOSBox-X reference: DN{args.episode}, cycles={cycle_label}")
    print(f"key script: {key_script}")
    capture_prefix = out_dir / "_window"
    command = [
        powershell,
        "-NoLogo",
        "-NoProfile",
        "-ExecutionPolicy",
        "Bypass",
        "-File",
        str(ROOT / "tools/dosref_capture.ps1"),
        "-Exe",
        str(args.dosbox.resolve()),
        "-Config",
        str(config),
        "-OutPrefix",
        str(capture_prefix),
        "-AtMsCsv",
        ",".join(map(str, args.at_ms)),
    ]
    completed = subprocess.run(command, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    print(completed.stdout, end="")
    if completed.returncode:
        print(f"dosref_capture.ps1 exited with {completed.returncode}", file=sys.stderr)
        return completed.returncode

    frames = []
    for index, at_ms in enumerate(args.at_ms):
        raw_path = out_dir / f"_window-{index}.png"
        if not raw_path.is_file():
            print(f"missing capture at {at_ms} ms: {raw_path}", file=sys.stderr)
            continue
        width, height, rgb = read_png(raw_path)
        scaled = resize_nearest(width, height, rgb, 320, 200)
        target = out_dir / f"frame-{index:02d}.png"
        write_png(target, 320, 200, scaled)
        frames.append({"at_ms": at_ms, "path": str(target), "source_size": [width, height]})
        raw_path.unlink()
    manifest = {
        "episode": args.episode,
        "cycles": cycle_label,
        "executable": str(args.dosbox.resolve()),
        "config": str(config),
        "reference_script": str(key_script),
        "frames": frames,
    }
    manifest_path = out_dir / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"manifest: {manifest_path}")
    return 0 if frames else 1


if __name__ == "__main__":
    raise SystemExit(main())
