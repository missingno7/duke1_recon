"""Promotion safety in a sandboxed copy of the repository: stale receipts,
conflicting writers, journals, regression protection, database loss."""
import json
import os
import subprocess
import sys
import unittest
from pathlib import Path

from util import Sandbox, assets_available

CANDIDATE = """/* sandbox candidate */
extern int d_02fb;
/*@body*/
void pascal g1_e92e(register int n)
{
    d_02fb = 0;
    while (d_02fb < n)
        ;
}
"""

NEW_FN = """extern int d_0518;
struct s8 { int a, b, c, d; };
extern struct s8 d_d4c3_[];
/*@body*/
void pascal g1_2a1d(void)
{
    register int i;

    for (i = 0; i < d_0518; i++)
        d_d4c3_[i].a = 0;
}
"""


@unittest.skipUnless(assets_available(), "original assets not present")
class Promotion(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.sb = Sandbox()
        # start from a sandbox without g1_2a1d so it can be promoted fresh
        for p in (cls.sb.dir / "recipes" / "g1_2a1d.json", cls.sb.dir / "src" / "g1" / "g1_2a1d.c"):
            p.unlink()
        log = cls.sb.dir / "evidence" / "promotions.jsonl"
        log.write_text("".join(x + "\n" for x in log.read_text().splitlines() if "g1_2a1d" not in x))
        cls.work = cls.sb.dir / "build" / "workers" / "t"
        cls.work.mkdir(parents=True)

    @classmethod
    def tearDownClass(cls):
        cls.sb.close()

    def write(self, name, text):
        p = self.work / name
        p.write_text(text)
        return p

    def test_1_stale_receipt_refused(self):
        cand = self.write("a.c", NEW_FN)
        rc = self.sb.run("search.py", str(cand), "--function", "g1_2a1d", "--receipt", str(self.work / "r.json"))
        self.assertEqual(rc.returncode, 0, rc.stdout + rc.stderr)
        # candidate edited after the receipt: refused
        cand.write_text(NEW_FN.replace("register int i;", "register int i;  "))
        r = self.sb.run("promote.py", "g1_2a1d", str(cand), "--receipt", str(self.work / "r.json"))
        self.assertIn("stale receipt", r.stdout)
        # proof context changed after the receipt: refused
        cand.write_text(NEW_FN)
        rj = json.loads((self.work / "r.json").read_text())
        rj["context_key"] = "0" * 64
        (self.work / "r.json").write_text(json.dumps(rj))
        r = self.sb.run("promote.py", "g1_2a1d", str(cand), "--receipt", str(self.work / "r.json"))
        self.assertIn("stale receipt", r.stdout)

    def test_2_promote_and_validate(self):
        cand = self.write("b.c", NEW_FN)
        r = self.sb.run("promote.py", "g1_2a1d", str(cand))
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertTrue((self.sb.dir / "src" / "g1" / "g1_2a1d.c").exists())
        v = self.sb.run("validate.py", "--quick")
        self.assertEqual(v.returncode, 0, v.stdout + v.stderr)

    def test_3_regression_refused(self):
        # a replacement that is EQUAL only in dn1 would lose dn2/dn3
        bad = CANDIDATE.replace("d_02fb = 0;", "#if EPISODE == 1\n    d_02fb = 0;\n#else\n    d_02fb = 1;\n#endif")
        cand = self.write("c.c", bad)
        r = self.sb.run("promote.py", "g1_e92e", str(cand))
        self.assertIn("regression", r.stdout)

    def test_4_missing_marker_and_lint(self):
        cand = self.write("d.c", CANDIDATE.replace("/*@body*/\n", ""))
        self.assertIn("marker", self.sb.run("promote.py", "g1_e92e", str(cand)).stdout)
        cand = self.write("e.c", CANDIDATE.replace("d_02fb = 0;", "asm mov ax, 0;\n    d_02fb = 0;"))
        self.assertIn("lint", self.sb.run("promote.py", "g1_e92e", str(cand)).stdout)

    def test_5_conflicting_writer_waits_or_fails(self):
        code = ("import sys,time; sys.path.insert(0,'tools'); import transaction\n"
                "with transaction.exclusive(owner='holder'):\n    print('locked', flush=True); time.sleep(6)\n")
        holder = subprocess.Popen([sys.executable, "-c", code], cwd=self.sb.dir, stdout=subprocess.PIPE, text=True)
        self.assertEqual(holder.stdout.readline().strip(), "locked")
        probe = ("import sys; sys.path.insert(0,'tools'); import transaction\n"
                 "try:\n    with transaction.exclusive(timeout=1, owner='second'): print('ACQUIRED')\n"
                 "except transaction.LockBusy as e: print('BUSY', e)\n")
        r = subprocess.run([sys.executable, "-c", probe], cwd=self.sb.dir, capture_output=True, text=True)
        self.assertIn("BUSY", r.stdout)
        holder.wait()
        holder.stdout.close()

    def test_6_dead_owner_lock_taken_over(self):
        lock = self.sb.dir / "build" / "locks" / "canonical.lock"
        lock.parent.mkdir(parents=True, exist_ok=True)
        dead = subprocess.run([sys.executable, "-c", "import os; print(os.getpid())"], capture_output=True, text=True)
        lock.write_text(json.dumps({"pid": int(dead.stdout), "owner": "crashed"}))
        probe = ("import sys; sys.path.insert(0,'tools'); import transaction\n"
                 "with transaction.exclusive(timeout=5, owner='next'): print('ACQUIRED')\n")
        r = subprocess.run([sys.executable, "-c", probe], cwd=self.sb.dir, capture_output=True, text=True)
        self.assertIn("ACQUIRED", r.stdout, r.stderr)
        self.assertIn("stale", r.stdout)

    def test_7_journal_conflict_and_recover(self):
        code = r"""
import sys; sys.path.insert(0, 'tools')
import transaction
from pathlib import Path
p = Path('src/g1/zz_test.c'); q = Path('recipes/zz_test.json')
j = transaction.prepare({'src/g1/zz_test.c': b'after', 'recipes/zz_test.json': b'{}'})
p.write_bytes(b'someone else')                  # concurrent edit
try:
    transaction.apply(j); print('APPLIED')
except transaction.Conflict as e:
    print('CONFLICT')
try:
    transaction.rollback(j); print('ROLLED')
except transaction.Conflict:
    print('REFUSED_TO_CLOBBER')
transaction.finish()
p.unlink()
# simulated crash after apply: recover() restores 'before'
j = transaction.prepare({'recipes/zz_test.json': b'{"x":1}'})
transaction.apply(j)
print('RECOVERED', transaction.recover(), q.exists())
"""
        r = subprocess.run([sys.executable, "-c", code], cwd=self.sb.dir, capture_output=True, text=True)
        self.assertIn("CONFLICT", r.stdout, r.stderr)
        self.assertIn("REFUSED_TO_CLOBBER", r.stdout)
        self.assertIn("RECOVERED ['recipes/zz_test.json'] False", r.stdout)

    def test_8_journal_may_not_write_outside_canonical(self):
        code = ("import sys; sys.path.insert(0,'tools'); import transaction\n"
                "try:\n    transaction.prepare({'layout/oracle.lock.json': b'x'}); print('WROTE')\n"
                "except transaction.Conflict: print('REFUSED')\n")
        r = subprocess.run([sys.executable, "-c", code], cwd=self.sb.dir, capture_output=True, text=True)
        self.assertIn("REFUSED", r.stdout)

    def test_10_batch_is_all_or_nothing(self):
        good = self.write("g.c", CANDIDATE.replace("/* sandbox candidate */", "/* batch good */"))
        bad = self.write("h.c", NEW_FN.replace("d_d4c3_[i].a = 0;", "d_d4c3_[i].b = 0;"))
        self.assertNotEqual(bad.read_text(), NEW_FN)
        lst = self.work / "batch.txt"
        lst.write_text(f"g1_e92e {good}\ng1_2a1d {bad}\n")
        before = (self.sb.dir / "src" / "g1" / "g1_e92e.c").read_bytes()
        r = self.sb.run("promote.py", "--batch", str(lst))
        self.assertIn("REFUSED", r.stdout, r.stdout + r.stderr)
        self.assertEqual((self.sb.dir / "src" / "g1" / "g1_e92e.c").read_bytes(), before)
        lst.write_text(f"g1_e92e {good}\ng1_e92e {good}\n")
        self.assertIn("each function once", self.sb.run("promote.py", "--batch", str(lst)).stdout)

    def test_9_losing_database_keeps_proofs(self):
        db = self.sb.dir / "state" / "research.sqlite"
        for suffix in ("", "-wal", "-shm"):
            p = Path(str(db) + suffix)
            if p.exists():
                p.unlink()
        v = self.sb.run("validate.py", "--quick")
        self.assertEqual(v.returncode, 0, v.stdout + v.stderr)
        r = self.sb.run("db.py", "rebuild")
        self.assertEqual(r.returncode, 0, r.stderr)


if __name__ == "__main__":
    unittest.main()
