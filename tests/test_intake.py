"""Worker intake never trusts a claim: malformed results, candidates outside
the task directory and false EQUAL claims are rejected; nothing is promoted."""
import json
import unittest

from util import Sandbox, assets_available



@unittest.skipUnless(assets_available(), "original assets not present")
class Intake(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.sb = Sandbox()
        r = cls.sb.run("db.py", "rebuild")
        assert r.returncode == 0, r.stderr
        r = cls.sb.run("tasks.py", "plan")
        assert r.returncode == 0, r.stderr
        r = cls.sb.run("tasks.py", "packet", "g1_0042", "--worker", "t1")
        assert r.returncode == 0, r.stdout + r.stderr
        cls.dir = cls.sb.dir / r.stdout.strip()

    @classmethod
    def tearDownClass(cls):
        cls.sb.close()

    def intake(self):
        r = self.sb.run("tasks.py", "intake", str(self.dir))
        self.assertEqual(r.returncode, 0, r.stderr)
        return json.loads(r.stdout.strip().splitlines()[-1])

    def result(self, **kw):
        base = {"task": "fn-g1_0042", "function": "g1_0042", "status": "EQUAL_CANDIDATE",
                "candidate": str((self.dir / "cand.c").relative_to(self.sb.dir)).replace("\\", "/"),
                "receipt": None, "episodes_equal": ["dn1"], "experiments": 1, "blocker": None, "notes": ""}
        base.update(kw)
        (self.dir / "result.json").write_text(json.dumps(base))

    def test_packet_snapshot(self):
        task = json.loads((self.dir / "task.json").read_text())
        for k in ("revision", "context_key", "oracle_lock_sha256", "atlas_sha256", "locations", "verify",
                  "prior_experiments", "profile_hypotheses"):
            self.assertIn(k, task)
        self.assertIn("/*@body*/", (self.dir / "skeleton.c").read_text())

    def test_false_equal_claim_rejected(self):
        (self.dir / "cand.c").write_text("/*@body*/\nvoid pascal g1_0042(int a) { }\n")
        self.result()
        canon = lambda: {p: p.read_bytes() for d in ("recipes", "src", "evidence")  # noqa: E731
                         for p in (self.sb.dir / d).rglob("*") if p.is_file()}
        before = canon()
        self.assertEqual(self.intake()["outcome"], "EQUAL_CLAIM_REJECTED")
        self.assertEqual(before, canon(), "intake must never touch canonical files")

    def test_malformed_status(self):
        (self.dir / "cand.c").write_text("/*@body*/\nvoid pascal g1_0042(int a) { }\n")
        self.result(status="DONE!")
        self.assertEqual(self.intake()["outcome"], "MALFORMED_RESULT")

    def test_candidate_outside_task_dir(self):
        self.result(candidate="src/g1/g1_e92e.c")
        self.assertEqual(self.intake()["outcome"], "CANDIDATE_OUTSIDE_TASK_DIR")

    def test_blocker_without_mechanism_rejected(self):
        (self.dir / "cand.c").write_text("/*@body*/\nvoid pascal g1_0042(int a) { }\n")
        self.result(status="BLOCKED", blocker={"category": "SOURCE_SHAPE", "mechanism": "hard",
                                               "evidence": "x", "next_experiment": "y"})
        out = self.intake()
        self.assertIn("blocker_rejected", out)


if __name__ == "__main__":
    unittest.main()
