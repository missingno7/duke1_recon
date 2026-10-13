"""Content-addressed compile cache, coalesced duplicate requests, experiment
deduplication, blocker discipline."""
import os
import shutil
import tempfile
import threading
import unittest
from pathlib import Path
from unittest import mock

from util import assets_available

import tcc

SRC = "int probe_fn(int a) { return a * %d; }\n"


class CompileCache(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp(prefix="duke1-cc-"))
        self.patches = [mock.patch.object(tcc, "CACHE", self.tmp / "cache"),
                        mock.patch.object(tcc, "INFLIGHT", self.tmp / "cache" / "inflight"),
                        mock.patch.object(tcc, "SCRATCH", self.tmp / "scratch")]
        for p in self.patches:
            p.start()

    def tearDown(self):
        for p in self.patches:
            p.stop()
        shutil.rmtree(self.tmp, ignore_errors=True)

    def test_duplicate_requests_coalesce(self):
        flags = tcc.profile_flags("tc20-l-gzo")
        results = []

        def work():
            results.append(tcc.compile_c(SRC % 7, flags))
        threads = [threading.Thread(target=work) for _ in range(4)]
        for t in threads:
            t.start()
        for t in threads:
            t.join()
        self.assertEqual(len({r.key for r in results}), 1)
        self.assertEqual(sum(not r.cached for r in results), 1, "exactly one real compile")
        self.assertEqual(len({r.obj for r in results}), 1)

    def test_key_covers_flags_and_source(self):
        a = tcc.compile_c(SRC % 3, tcc.profile_flags("tc20-l-gzo"))
        b = tcc.compile_c(SRC % 3, tcc.profile_flags("tc20-l-plain"))
        c = tcc.compile_c(SRC % 5, tcc.profile_flags("tc20-l-gzo"))
        self.assertEqual(len({a.key, b.key, c.key}), 3)
        again = tcc.compile_c(SRC % 3, tcc.profile_flags("tc20-l-gzo"))
        self.assertTrue(again.cached)
        self.assertEqual(again.key, a.key)

    def test_corrupted_cache_entry_is_recompiled(self):
        a = tcc.compile_c(SRC % 9, tcc.profile_flags("tc20-l-gzo"))
        (a.directory / "UNIT.OBJ").write_bytes(b"garbage")
        b = tcc.compile_c(SRC % 9, tcc.profile_flags("tc20-l-gzo"))
        self.assertFalse(b.cached)
        self.assertEqual(b.obj[:1], b"\x80")

    def test_dead_inflight_marker_is_taken_over(self):
        flags = tcc.profile_flags("tc20-l-gzo")
        req_src = SRC % 11
        # find the key by doing a dry compile in another cache, then plant a dead marker
        a = tcc.compile_c(req_src, flags)
        shutil.rmtree(a.directory)
        tcc.INFLIGHT.mkdir(parents=True, exist_ok=True)
        (tcc.INFLIGHT / a.key).write_text("999999")
        b = tcc.compile_c(req_src, flags)
        self.assertTrue(b.ok)

    def test_compile_error_is_a_result(self):
        r = tcc.compile_c("int broken( {", tcc.profile_flags("tc20-l-gzo"))
        self.assertFalse(r.ok)
        self.assertIn("Error", r.log)


@unittest.skipUnless(assets_available(), "original assets not present")
class ExperimentsAndBlockers(unittest.TestCase):
    def setUp(self):
        import db
        self.tmp = Path(tempfile.mkdtemp(prefix="duke1-db-"))
        self.con = db.connect(self.tmp / "t.sqlite")

    def tearDown(self):
        self.con.close()
        shutil.rmtree(self.tmp, ignore_errors=True)

    def test_experiment_dedup_and_failed_hypotheses_searchable(self):
        import db
        import search
        text = (Path(__file__).resolve().parents[1] / "src/g1/g1_1053.c").read_text()
        with mock.patch.object(db, "connect", lambda *a, **k: self.con):
            first = search.run(text, "g1_1053", flags=tcc.profile_flags("tc20-l-gzo"), profile="tc20-l-gzo")
            second = search.run(text, "g1_1053", flags=tcc.profile_flags("tc20-l-gzo"), profile="tc20-l-gzo")
            bad = search.run(text, "g1_1053", flags=tcc.profile_flags("tc20-l-plain"), profile="tc20-l-plain",
                             note="control profile")
        self.assertFalse(first["cached"])
        self.assertTrue(second["cached"])
        self.assertEqual(first["key"], second["key"])
        rows = self.con.execute("SELECT best_status, hits FROM experiments WHERE function_id='g1_1053' "
                                "ORDER BY created").fetchall()
        self.assertEqual([r[0] for r in rows], ["EQUAL", bad["best_status"]])
        self.assertEqual(rows[0][1], 2)
        failed = self.con.execute("SELECT note FROM experiments WHERE best_status != 'EQUAL'").fetchall()
        self.assertEqual(failed[0][0], "control profile")

    def test_blockers_require_mechanism_and_next_experiment(self):
        import db
        with self.assertRaises(ValueError):
            db.add_blocker(self.con, "g1_0042", "SOURCE_SHAPE", "it is hard", "x", "y")
        with self.assertRaises(ValueError):
            db.add_blocker(self.con, "g1_0042", "SOURCE_SHAPE", "REGISTER_SWAP", "x", " ")
        with self.assertRaises(ValueError):
            db.add_blocker(self.con, "g1_0042", "VIBES", "REGISTER_SWAP", "x", "y")
        bid = db.add_blocker(self.con, "g1_0042", "SOURCE_SHAPE", "REGISTER_SWAP", "si/di swapped",
                             "declare the loop counter first")
        self.assertGreater(bid, 0)


if __name__ == "__main__":
    unittest.main()
