"""Small dependency-free PNG reader/writer for the SDL port comparison tools."""

from __future__ import annotations

import struct
import zlib
from pathlib import Path

PNG_SIGNATURE = b"\x89PNG\r\n\x1a\n"


def _paeth(a: int, b: int, c: int) -> int:
    p = a + b - c
    pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
    return a if pa <= pb and pa <= pc else (b if pb <= pc else c)


def read_png(path: str | Path) -> tuple[int, int, bytes]:
    data = Path(path).read_bytes()
    if not data.startswith(PNG_SIGNATURE):
        raise ValueError(f"not a PNG: {path}")
    pos = len(PNG_SIGNATURE)
    width = height = bit_depth = colour_type = None
    compressed = bytearray()
    while pos < len(data):
        length = struct.unpack_from(">I", data, pos)[0]
        kind = data[pos + 4 : pos + 8]
        payload = data[pos + 8 : pos + 8 + length]
        pos += length + 12
        if kind == b"IHDR":
            width, height, bit_depth, colour_type, compression, filtering, interlace = struct.unpack(
                ">IIBBBBB", payload
            )
            if bit_depth != 8 or colour_type not in (2, 6) or compression or filtering or interlace:
                raise ValueError(f"unsupported PNG format in {path}")
        elif kind == b"IDAT":
            compressed.extend(payload)
        elif kind == b"IEND":
            break
    if width is None or height is None or colour_type is None:
        raise ValueError(f"missing PNG header: {path}")
    bpp = 3 if colour_type == 2 else 4
    stride = width * bpp
    raw = zlib.decompress(compressed)
    rows: list[bytearray] = []
    src = 0
    previous = bytearray(stride)
    for _ in range(height):
        filter_type = raw[src]
        src += 1
        row = bytearray(raw[src : src + stride])
        src += stride
        if filter_type == 1:
            for i in range(stride):
                row[i] = (row[i] + (row[i - bpp] if i >= bpp else 0)) & 0xFF
        elif filter_type == 2:
            for i in range(stride):
                row[i] = (row[i] + previous[i]) & 0xFF
        elif filter_type == 3:
            for i in range(stride):
                left = row[i - bpp] if i >= bpp else 0
                row[i] = (row[i] + ((left + previous[i]) >> 1)) & 0xFF
        elif filter_type == 4:
            for i in range(stride):
                left = row[i - bpp] if i >= bpp else 0
                row[i] = (row[i] + _paeth(left, previous[i], previous[i - bpp] if i >= bpp else 0)) & 0xFF
        elif filter_type != 0:
            raise ValueError(f"unknown PNG filter {filter_type} in {path}")
        rows.append(row)
        previous = row
    if bpp == 3:
        return width, height, b"".join(rows)
    rgb = bytearray(width * height * 3)
    out = 0
    for row in rows:
        for x in range(width):
            rgb[out : out + 3] = row[x * 4 : x * 4 + 3]
            out += 3
    return width, height, bytes(rgb)


def write_png(path: str | Path, width: int, height: int, rgb: bytes) -> None:
    if len(rgb) != width * height * 3:
        raise ValueError("RGB buffer size does not match image dimensions")

    def chunk(kind: bytes, payload: bytes) -> bytes:
        body = kind + payload
        return struct.pack(">I", len(payload)) + body + struct.pack(">I", zlib.crc32(body) & 0xFFFFFFFF)

    rows = bytearray()
    stride = width * 3
    for y in range(height):
        rows.append(0)
        rows.extend(rgb[y * stride : (y + 1) * stride])
    png = bytearray(PNG_SIGNATURE)
    png.extend(chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0)))
    png.extend(chunk(b"IDAT", zlib.compress(bytes(rows), 6)))
    png.extend(chunk(b"IEND", b""))
    Path(path).parent.mkdir(parents=True, exist_ok=True)
    Path(path).write_bytes(png)


def resize_nearest(width: int, height: int, rgb: bytes, out_width: int, out_height: int) -> bytes:
    output = bytearray(out_width * out_height * 3)
    for y in range(out_height):
        source_y = min(height - 1, (y * height) // out_height)
        for x in range(out_width):
            source_x = min(width - 1, (x * width) // out_width)
            src = (source_y * width + source_x) * 3
            dst = (y * out_width + x) * 3
            output[dst : dst + 3] = rgb[src : src + 3]
    return bytes(output)


def side_by_side(left: bytes, right: bytes, width: int, height: int) -> bytes:
    row_bytes = width * 3
    out = bytearray(width * 2 * height * 3)
    for y in range(height):
        src = y * row_bytes
        dst = y * row_bytes * 2
        out[dst : dst + row_bytes] = left[src : src + row_bytes]
        out[dst + row_bytes : dst + row_bytes * 2] = right[src : src + row_bytes]
    return bytes(out)


def absolute_difference(left: bytes, right: bytes) -> bytes:
    return bytes(abs(a - b) for a, b in zip(left, right))
