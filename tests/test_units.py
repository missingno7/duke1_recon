"""Whole-unit proofs: G2 initialised data, the assembly unit, and the journal's
file deletions used when functions move into a shared module source."""
import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from util import ROOT, Sandbox, assets_available

import tubuild


@unittest.skipUnless(assets_available(), "original assets not present")
class UnitData(unittest.TestCase):
    def test_g2_data_equal(self):
        res = tubuild.check("G2_TEXT", "dn1", data=True)
        self.assertEqual(res["status"], "EQUAL", res.get("function_failures"))
        self.assertEqual(res["data"]["status"], "EQUAL", res["data"])

    def test_changed_initialiser_is_detected(self):
        """One character of an initialised table differs: the data proof fails
        and points at the byte."""
        plan = tubuild.data_plan("G2_TEXT")
        src = (ROOT / plan["fragments"][0]["file"]).read_text("latin-1")
        bad = src.replace("GET DUKE NUKUM NOW!", "GET DUKE NUKEM NOW!", 1)
        self.assertNotEqual(src, bad)
        tmp = Path(tempfile.mkdtemp(prefix="duke1-data-"))
        try:
            frag = tmp / "prefix.c"
            frag.write_text(bad, encoding="latin-1")
            plan2 = dict(plan, fragments=[{"file": str(frag), "before": "start"}])
            res = tubuild.check("G2_TEXT", "dn1", plan=plan2, data=True)
            self.assertEqual(res["data"]["status"], "DIFFER")
            self.assertEqual(res["data"]["differing_bytes"], 1)
        finally:
            shutil.rmtree(tmp, ignore_errors=True)


@unittest.skipUnless(assets_available(), "original assets not present")
class AsmUnit(unittest.TestCase):
    def test_asm_unit_equal(self):
        for ep in ("dn1", "dn2", "dn3"):
            res = tubuild.check("ASM_TEXT", ep)
            self.assertEqual(res["status"], "EQUAL", res)

    def test_changed_banner_is_detected(self):
        src = (ROOT / json.loads((ROOT / "layout/asm-unit.json").read_text())["source"]).read_text("latin-1")
        tmp = Path(tempfile.mkdtemp(prefix="duke1-asm-"))
        try:
            f = tmp / "toolbox.asm"
            f.write_text(src.replace("'ProGraphx EGA/VGA Toolbox'", "'ProGraphx EGA/VGA ToolboX'", 1),
                         encoding="latin-1")
            res = tubuild.check("ASM_TEXT", "dn1", override=f)
            self.assertEqual(res["status"], "DIFFER")
            self.assertEqual(res["differing_bytes"], 1)
        finally:
            shutil.rmtree(tmp, ignore_errors=True)


class JournalDeletion(unittest.TestCase):
    def test_delete_apply_and_rollback(self):
        sb = Sandbox()
        try:
            target = sb.dir / "src" / "g1" / "zz_delete_me.c"
            target.write_bytes(b"old")
            code = ("import sys; sys.path.insert(0,'tools'); import transaction\n"
                    "j = transaction.prepare({'src/g1/zz_delete_me.c': None, 'src/g1/zz_new.c': b'new'})\n"
                    "transaction.apply(j)\n"
                    "import os; print('GONE' if not os.path.exists('src/g1/zz_delete_me.c') else 'THERE')\n"
                    "transaction.rollback(j)\n"
                    "print(open('src/g1/zz_delete_me.c','rb').read().decode(), os.path.exists('src/g1/zz_new.c'))\n")
            r = subprocess.run([sys.executable, "-c", code], cwd=sb.dir, capture_output=True, text=True)
            self.assertIn("GONE", r.stdout, r.stderr)
            self.assertIn("old False", r.stdout, r.stderr)
        finally:
            sb.close()


if __name__ == "__main__":
    unittest.main()
