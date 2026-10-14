#!/usr/bin/env python3
"""Run the SDL port and DOSBox-X reference with one key script and compare named frames."""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
import time
from pathlib import Path

from dosref import ROOT, parse_times
from png_utils import absolute_difference, read_png, side_by_side, write_png


def parse_script(path: Path) -> tuple[list[str], list[tuple[int, str]], int]:
    lines: list[str] = []
    shots: list[tuple[int, str]] = []
    latest = 0
    for line_number, raw in enumerate(path.read_text(encoding="utf-8-sig").splitlines(), 1):
        stripped = raw.strip()
        if not stripped or stripped.startswith("#"):
            lines.append(raw)
            continue
        parts = stripped.split()
        if len(parts) < 2:
            raise ValueError(f"{path}:{line_number}: malformed script line")
        try:
            when = int(parts[0])
        except ValueError as exc:
            raise ValueError(f"{path}:{line_number}: invalid time") from exc
        if when < 0:
            raise ValueError(f"{path}:{line_number}: time must be nonnegative")
        latest = max(latest, when)
        if parts[1].lower() == "shot":
            if len(parts) != 3:
                raise ValueError(f"{path}:{line_number}: expected '<ms> shot <file.png>'")
            shots.append((when, parts[2]))
        else:
            lines.append(raw)
    if not shots:
        raise ValueError("port script must include at least one shot event")
    return lines, shots, latest


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--episode", type=int, choices=(1, 2, 3), required=True)
    parser.add_argument("--script", type=Path, required=True, help="port script containing keys and shot actions")
    parser.add_argument("--port", type=Path, default=ROOT / "build/port/duke1.exe")
    parser.add_argument("--data", type=Path, default=ROOT / "assets")
    parser.add_argument("--out", type=Path, default=ROOT / "build/scratch/portcompare")
    parser.add_argument("--reference-ms", type=parse_times, help="capture times for DOSBox-X, by screen order")
    parser.add_argument("--cycles", default="auto", help="DOSBox-X cycles: auto or fixed:20000")
    parser.add_argument("--drain-ms", type=int, default=1200,
                        help="keep the port alive this long after its last scripted event")
    parser.add_argument("--trace", action="store_true", help="enable the port's file/IRQ trace")
    args = parser.parse_args()

    script_path = args.script.resolve()
    port_exe = args.port.resolve()
    data_dir = args.data.resolve()
    out_dir = args.out.resolve()
    if not port_exe.is_file():
        parser.error(f"port executable not found: {port_exe}")
    if not data_dir.is_dir():
        parser.error(f"game data directory not found: {data_dir}")
    out_dir.mkdir(parents=True, exist_ok=True)

    key_lines, shots, latest = parse_script(script_path)
    reference_times = args.reference_ms or [when for when, _ in shots]
    if len(reference_times) != len(shots):
        parser.error(f"{len(shots)} port shots require the same number of --reference-ms entries")

    port_script = out_dir / "port-script.txt"
    port_events = list(key_lines)
    for index, (when, _) in enumerate(shots):
        target = out_dir / f"port-{index:02d}.png"
        port_events.append(f"{when} shot {target}")
    port_script.write_text("\n".join(port_events) + "\n", encoding="utf-8")

    # The reference tool consumes the same key actions from the source script. Its screenshot
    # clock is independent and can be adjusted to match the same visible screen.
    reference_script = out_dir / "reference-script.txt"
    reference_script.write_text("\n".join(key_lines) + "\n", encoding="utf-8")

    port_command = [str(port_exe), "--data", str(data_dir), "--episode", str(args.episode), "--script", str(port_script), "--no-restart"]
    if args.trace:
        port_command.append("--trace")
    process = subprocess.Popen(
        port_command,
        cwd=ROOT,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    port_deadline = time.monotonic() + (max(latest, max((t for t, _ in shots), default=0)) / 1000.0) + max(0, args.drain_ms) / 1000.0
    port_output = ""
    try:
        port_output, _ = process.communicate(timeout=max(1.0, port_deadline - time.monotonic()))
    except subprocess.TimeoutExpired:
        # A comparison run is a capture harness, not an interactive session. Stop it after
        # the final requested frame instead of injecting a menu-dependent Escape/Y sequence.
        process.terminate()
        port_output, _ = process.communicate()
        print("port capture ended after the scripted frames", file=sys.stderr)
    (out_dir / "port-run.log").write_text(port_output, encoding="utf-8", errors="replace")

    dosref_command = [
        sys.executable,
        str(ROOT / "tools/dosref.py"),
        "--episode",
        str(args.episode),
        "--cycles",
        args.cycles,
        "--script",
        str(reference_script),
        "--at-ms",
        ",".join(map(str, reference_times)),
        "--out",
        str(out_dir / "reference"),
        "--data",
        str(data_dir),
    ]
    reference = subprocess.run(dosref_command, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    print(reference.stdout, end="")
    if reference.returncode:
        print("DOSBox-X capture failed; see the output above", file=sys.stderr)
        return reference.returncode

    sheet_rows = []
    metrics = []
    for index, ((port_ms, requested_name), ref_ms) in enumerate(zip(shots, reference_times)):
        port_path = out_dir / f"port-{index:02d}.png"
        ref_path = out_dir / "reference" / f"frame-{index:02d}.png"
        if not port_path.is_file() or not ref_path.is_file():
            print(f"missing comparison frame {index}: {port_path} or {ref_path}", file=sys.stderr)
            continue
        pw, ph, port_rgb = read_png(port_path)
        rw, rh, ref_rgb = read_png(ref_path)
        if (pw, ph) != (320, 200) or (rw, rh) != (320, 200):
            raise ValueError("comparison images must be exactly 320x200")
        diff = absolute_difference(ref_rgb, port_rgb)
        diff_path = out_dir / f"diff-{index:02d}.png"
        sheet_path = out_dir / f"compare-{index:02d}.png"
        write_png(diff_path, 320, 200, diff)
        write_png(sheet_path, 640, 200, side_by_side(ref_rgb, port_rgb, 320, 200))
        mean_error = sum(diff) / len(diff)
        differing = sum(1 for p in range(0, len(diff), 3) if diff[p] or diff[p + 1] or diff[p + 2])
        metrics.append(
            {
                "name": Path(requested_name).stem or f"frame-{index:02d}",
                "port_ms": port_ms,
                "reference_ms": ref_ms,
                "reference": str(ref_path),
                "port": str(port_path),
                "sheet": str(sheet_path),
                "difference": str(diff_path),
                "mean_absolute_channel_error": round(mean_error, 4),
                "different_pixels": differing,
            }
        )
        sheet_rows.append(side_by_side(ref_rgb, port_rgb, 320, 200))
    if sheet_rows:
        gap = bytes(640 * 3 * 6)
        height = len(sheet_rows) * 200 + (len(sheet_rows) - 1) * 6
        combined = bytearray(640 * height * 3)
        y = 0
        for row in sheet_rows:
            start = y * 640 * 3
            combined[start : start + len(row)] = row
            y += 200
            if y < height:
                y += 6
        write_png(out_dir / "sheet.png", 640, height, bytes(combined))
    manifest = {
        "episode": args.episode,
        "cycles": args.cycles,
        "script": str(script_path),
        "comparison_rule": "frames are paired by order/screen name; port and reference capture clocks may differ",
        "port_return_code": process.returncode,
        "frames": metrics,
    }
    (out_dir / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"port log: {out_dir / 'port-run.log'}")
    print(f"comparison sheet: {out_dir / 'sheet.png'}")
    for item in metrics:
        print(
            f"{item['name']}: port {item['port_ms']} ms vs reference {item['reference_ms']} ms, "
            f"mean channel error {item['mean_absolute_channel_error']}, different pixels {item['different_pixels']}"
        )
    return 0 if metrics else 1


if __name__ == "__main__":
    raise SystemExit(main())
