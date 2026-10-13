"""Strict comparison: corrupted objects, relocation and binding mismatches,
episode-mapping errors."""
import struct
import unittest
from pathlib import Path
from unittest import mock

from util import ROOT, assets_available

import compare
import tcc

PROFILE = None


def _obj(fid):
    import json
    r = json.loads((ROOT / "recipes" / f"{fid}.json").read_text())
    text = (ROOT / r["source"]).read_text("latin-1")
    rec = tcc.compile_c(text, r["flags"])
    assert rec.ok, rec.log
    return rec.obj


def _records(obj):
    i, out = 0, []
    while i < len(obj):
        n = struct.unpack_from("<H", obj, i + 1)[0]
        out.append(bytearray(obj[i:i + 3 + n]))
        i += 3 + n
    return out


def _join(recs):
    out = b""
    for r in recs:
        r[-1] = (-sum(r[:-1])) & 0xFF
        out += bytes(r)
    return out


@unittest.skipUnless(assets_available(), "original assets not present")
class StrictCompare(unittest.TestCase):
    def test_pilot_equal_all_episodes(self):
        obj = _obj("g1_006f")
        for ep in ("dn1", "dn2", "dn3"):
            self.assertEqual(compare.compare_object(obj, "g1_006f", ep).status, "EQUAL")

    def test_bad_checksum_is_object_error(self):
        obj = bytearray(_obj("g1_e92e"))
        obj[10] ^= 0x40
        self.assertEqual(compare.compare_object(bytes(obj), "g1_e92e", "dn1").status, "OBJECT_ERROR")

    def test_truncated_object_is_object_error(self):
        obj = _obj("g1_e92e")
        self.assertEqual(compare.compare_object(obj[:-5], "g1_e92e", "dn1").status, "OBJECT_ERROR")

    def test_unknown_record_is_object_error(self):
        recs = _records(_obj("g1_e92e"))
        recs.insert(1, bytearray(b"\xc2\x02\x00\x00\x00"))     # COMDAT-like record, not reviewed
        self.assertEqual(compare.compare_object(_join(recs), "g1_e92e", "dn1").status, "OBJECT_ERROR")

    def test_missing_fixup_with_correct_bytes_is_rejected(self):
        """Hard-coding the original far-call bytes without a FIXUPP must fail:
        the original word is an MZ relocation."""
        recs = _records(_obj("g1_006f"))
        img, _ = __import__("oracle").load_image("dn1")
        import symbols
        loc = symbols.atlas()["g1_006f"]["locations"]["dn1"]
        orig = img[loc["start"]:loc["start"] + loc["size"]]
        out = []
        for r in recs:
            if r[0] == 0x9C:            # drop every FIXUPP
                continue
            if r[0] == 0xA0:            # LEDATA: inject the original bytes
                start = 3 + 1 + 2       # type,len | seg index | offset
                payload = r[start:-1]
                payload[:len(orig)] = orig
                r = r[:start] + payload + r[-1:]
            out.append(bytearray(r))
        res = compare.compare_object(_join(out), "g1_006f", "dn1")
        self.assertNotEqual(res.status, "EQUAL")
        self.assertTrue(any("relocations without candidate fixups" in d for d in res.detail), res.detail)

    def test_wrong_call_binding_is_rejected(self):
        text = (ROOT / "src/g1/g1_006f.c").read_text().replace("g1_0e30", "g1_0acc")
        rec = tcc.compile_c(text, tcc.profile_flags("tc20-l-gzo"))
        res = compare.compare_object(rec.obj, "g1_006f", "dn1")
        self.assertNotEqual(res.status, "EQUAL")
        self.assertTrue(any("g1_0acc" in d for d in res.detail), res.detail)

    def test_wrong_near_call_relation_is_rejected(self):
        text = (ROOT / "src/g1/g1_0acc.c").read_text().replace("g1_0a0e", "g1_0e30")
        rec = tcc.compile_c(text, tcc.profile_flags("tc20-l-gzo"))
        res = compare.compare_object(rec.obj, "g1_0acc", "dn1")
        self.assertNotEqual(res.status, "EQUAL")

    def test_episode_mapping_error_is_detected(self):
        """If the dn2 data map pointed at the dn1 address, dn2 must fail."""
        obj = _obj("g1_0acc")
        import datamap
        with mock.patch.object(datamap, "to_episode", lambda ep, x: x):
            res = compare.compare_object(obj, "g1_0acc", "dn2")
        self.assertEqual(res.status, "BINDING_ERROR", res.detail)

    def test_wrong_function_extent(self):
        obj = _obj("g1_e92e")
        res = compare.compare_object(obj, "g1_1053", "dn1", name="g1_e92e")
        self.assertIn(res.status, ("EXTENT_MISMATCH", "DIFFER"))

    def test_data_offset_mismatch(self):
        text = (ROOT / "src/g1/g1_0acc.c").read_text().replace("d_4ed4", "d_4ed6")
        rec = tcc.compile_c(text, tcc.profile_flags("tc20-l-gzo"))
        res = compare.compare_object(rec.obj, "g1_0acc", "dn1")
        self.assertEqual(res.status, "BINDING_ERROR")


if __name__ == "__main__":
    unittest.main()
