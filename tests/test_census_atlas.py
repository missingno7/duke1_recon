"""Census and atlas invariants: every first-party function is mapped exactly
once per episode, boundaries are closed, the runtime region is attributed."""
import json
import unittest

from util import ROOT, assets_available


@unittest.skipUnless(assets_available(), "original assets not present")
class CensusAtlas(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.census = {e: json.loads((ROOT / "build" / "census" / f"{e}.json").read_text())
                      for e in ("dn1", "dn2", "dn3")}
        cls.atlas = json.loads((ROOT / "evidence" / "atlas.json").read_text())

    def test_every_function_mapped_exactly_once(self):
        for e, c in self.census.items():
            starts = sorted(f["start"] for f in c["functions"])
            mapped = sorted(f["locations"][e]["start"] for f in self.atlas["functions"] if e in f["locations"])
            self.assertEqual(starts, mapped, f"{e}: atlas and census disagree")

    def test_logical_ids_unique_and_locations_consistent(self):
        ids = [f["id"] for f in self.atlas["functions"]]
        self.assertEqual(len(ids), len(set(ids)))
        for f in self.atlas["functions"]:
            for e, loc in f["locations"].items():
                cf = next(x for x in self.census[e]["functions"] if x["start"] == loc["start"])
                self.assertEqual((cf["size"], cf["sha256"]), (loc["size"], loc["sha256"]))

    def test_first_party_boundaries_closed(self):
        for e, c in self.census.items():
            game = [f for f in c["functions"] if f["segment"].startswith("G")]
            self.assertEqual(len(game), 248)
            self.assertTrue(all(f["status"] == "VERIFIED" for f in game))
            for seg in ("G1_TEXT", "G2_TEXT"):
                fs = sorted((f for f in game if f["segment"] == seg), key=lambda f: f["start"])
                s = next(x for x in c["segments"] if x["name"] == seg)
                self.assertEqual(fs[0]["start"], s["start"])
                self.assertEqual(fs[-1]["end"], s["start"] + s["size"])
                for a, b in zip(fs, fs[1:]):
                    self.assertEqual(a["end"], b["start"])

    def test_runtime_region_attributed(self):
        for e, c in self.census.items():
            lib = c["library_modules"]
            self.assertEqual(len(lib), 65)
            self.assertEqual(sum(h["size"] for h in lib), 12849)
            self.assertEqual([h["module"] for h in lib if h.get("positional")], ["REALCVT"])
            fill = sum(h.get("link_fill_before", 0) for h in lib)
            far = [h for h in lib if h["segment"] != "_TEXT"]
            covered = sum(h["size"] for h in far) + fill
            self.assertEqual(covered, far[-1]["start"] + far[-1]["size"] - far[0]["start"])

    def test_g1_identical_shape_in_all_episodes(self):
        g1 = [f for f in self.atlas["functions"] if f["segment"] == "G1_TEXT"]
        self.assertEqual(len(g1), 149)
        self.assertTrue(all(len({l["shape"] for l in f["locations"].values()}) == 1 for f in g1))


if __name__ == "__main__":
    unittest.main()
