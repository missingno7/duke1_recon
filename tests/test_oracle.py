import struct
import unittest

from util import assets_available

import lz91
import mz


def _packed_reloc_table(entries):
    """Encode linear relocation addresses the way LZEXE 0.91 does."""
    out = bytearray()
    prev = 0
    for a in entries:
        span = a - prev
        while span > 0xFFFF:
            out += b"\0" + struct.pack("<H", 0)
            span -= 0xFFF0
        if span < 0x100 and span:
            out.append(span)
        else:
            out += b"\0" + struct.pack("<H", span)
        prev = a
    out += b"\0" + struct.pack("<H", 1)
    return bytes(out)


class RelocDecoder(unittest.TestCase):
    def test_ascending_spans_and_escapes(self):
        entries = [0x10, 0x20, 0x1234, 0x1236, 0x8000]
        got = lz91._relocs(_packed_reloc_table(entries), 0)
        self.assertEqual([(s << 4) + o for s, o in got], entries)
        self.assertTrue(all(o < 16 for _, o in got))

    def test_truncated_table_is_refused(self):
        with self.assertRaises(lz91.LZ91Error):
            lz91._relocs(b"\x05\x06", 0)


class Decoder(unittest.TestCase):
    def test_corrupt_stream_is_refused(self):
        with self.assertRaises(lz91.LZ91Error):
            lz91._decode(b"\x00\x00\x01", 0, 10)

    def test_not_lz91(self):
        with self.assertRaises(lz91.LZ91Error):
            lz91.unpack(b"MZ" + b"\0" * 64)


@unittest.skipUnless(assets_available(), "original assets not present")
class LockedOracle(unittest.TestCase):
    def test_lock_verifies_and_roundtrips(self):
        import oracle
        lock = oracle.verify()
        for ep in ("dn1", "dn2", "dn3"):
            raw = oracle.find_asset(oracle.EXE_NAMES[ep]).read_bytes()
            u = lz91.unpack(raw)
            back = mz.parse(lz91.build_mz(u))
            self.assertEqual(back.image, u.image)
            self.assertEqual(back.relocs, u.relocs)
            self.assertEqual(len(u.image), lock["episodes"][ep]["unpacked"]["image_size"])

    def test_emulated_stub_crosscheck(self):
        import lz91_emulate
        import oracle
        raw = oracle.find_asset("DN2.EXE").read_bytes()
        u = lz91.unpack(raw)
        res = lz91_emulate.crosscheck(raw, u.image, u.relocs)
        self.assertTrue(res["relocation_set_equal"] and res["image_equal"])

    def test_stale_materialisation_detected(self):
        import oracle
        from common import BUILD
        p = BUILD / "oracle" / "dn3" / "image.bin"
        good = p.read_bytes()
        try:
            p.write_bytes(good[:-1] + bytes([good[-1] ^ 1]))
            with self.assertRaises(oracle.OracleError):
                oracle.load_image("dn3")
        finally:
            p.write_bytes(good)
