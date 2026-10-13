"""SQLite research state (state/research.sqlite, WAL, never committed).

Two kinds of tables:
  derived   rebuilt deterministically from committed files + build/census
            (functions, locations, mapping_evidence, deps, symbols, units,
            promotions); `python tools/db.py rebuild` drops and refills them.
  research  experiments, sources, emissions, blockers, tasks: history that is
            useful but not required.  Losing the database never invalidates
            accepted source or proofs (those live in src/, recipes/, evidence/).

    python tools/db.py rebuild
    python tools/db.py status
    python tools/db.py query "SQL"
    python tools/db.py experiments FUNCTION [--all]
    python tools/db.py same-emission FUNCTION
    python tools/db.py blockers [--open]
    python tools/db.py block FUNCTION CATEGORY MECHANISM --evidence TEXT --next TEXT
    python tools/db.py export-blockers        (curated copy -> evidence/blockers.json)
"""
from __future__ import annotations

import argparse
import json
import sqlite3
import sys
import time
import zlib
from contextlib import contextmanager
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EPISODES, EVIDENCE, RECIPES, STATE, atomic_json, load_json, sha256  # noqa: E402

DB = STATE / "research.sqlite"
SCHEMA_VERSION = 1

BLOCKER_CATEGORIES = ("SOURCE_SHAPE", "DECLARATION_VIEW", "TU_LAYOUT", "DATA_OWNERSHIP", "CALL_BINDING",
                      "CFG_BOUNDARY", "RUNTIME_LIBRARY", "TOOLCHAIN", "EPISODE_DIVERGENCE", "ASM_REQUIRED")

DERIVED = ("locations", "mapping_evidence", "deps", "symbols", "promotions", "functions", "units")  # child tables first

SCHEMA = """
CREATE TABLE IF NOT EXISTS meta (key TEXT PRIMARY KEY, value TEXT NOT NULL);

-- derived ------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS units (
  id TEXT PRIMARY KEY, kind TEXT NOT NULL, description TEXT);
CREATE TABLE IF NOT EXISTS functions (
  id TEXT PRIMARY KEY, unit TEXT NOT NULL REFERENCES units(id), class TEXT NOT NULL,
  confidence TEXT NOT NULL, accepted_episodes TEXT NOT NULL DEFAULT '',
  min_size INTEGER, max_size INTEGER);
CREATE TABLE IF NOT EXISTS locations (
  function_id TEXT NOT NULL REFERENCES functions(id), episode TEXT NOT NULL,
  start INTEGER NOT NULL, frame INTEGER NOT NULL, offset INTEGER NOT NULL, size INTEGER NOT NULL,
  sha256 TEXT NOT NULL, boundary TEXT NOT NULL,
  PRIMARY KEY (function_id, episode), UNIQUE (episode, start));
CREATE TABLE IF NOT EXISTS mapping_evidence (
  function_id TEXT NOT NULL REFERENCES functions(id), signal TEXT NOT NULL, value TEXT NOT NULL,
  PRIMARY KEY (function_id, signal));
CREATE TABLE IF NOT EXISTS deps (
  caller TEXT NOT NULL, callee TEXT NOT NULL, kind TEXT NOT NULL, episode TEXT NOT NULL,
  count INTEGER NOT NULL, PRIMARY KEY (caller, callee, kind, episode));
CREATE TABLE IF NOT EXISTS symbols (
  name TEXT NOT NULL, episode TEXT NOT NULL, kind TEXT NOT NULL, address INTEGER NOT NULL,
  provenance TEXT NOT NULL, PRIMARY KEY (name, episode));
CREATE TABLE IF NOT EXISTS promotions (
  seq INTEGER PRIMARY KEY, function_id TEXT NOT NULL, episodes TEXT NOT NULL,
  source_sha256 TEXT NOT NULL, recipe_sha256 TEXT NOT NULL, at TEXT NOT NULL, note TEXT);

-- research -----------------------------------------------------------------
CREATE TABLE IF NOT EXISTS sources (
  sha256 TEXT PRIMARY KEY, bytes INTEGER NOT NULL, text_z BLOB NOT NULL);
CREATE TABLE IF NOT EXISTS experiments (
  key TEXT PRIMARY KEY,                 -- content address of (compile request, function, comparer, context)
  function_id TEXT NOT NULL, source_sha256 TEXT NOT NULL REFERENCES sources(sha256),
  profile TEXT, flags TEXT NOT NULL, compile_key TEXT NOT NULL, context_key TEXT NOT NULL,
  ok INTEGER NOT NULL, emission_key TEXT, results TEXT NOT NULL,   -- JSON {episode: summary}
  best_status TEXT NOT NULL, diff_bytes INTEGER, worker TEXT, note TEXT,
  created REAL NOT NULL, hits INTEGER NOT NULL DEFAULT 1);
CREATE INDEX IF NOT EXISTS experiments_fn ON experiments(function_id, best_status);
CREATE INDEX IF NOT EXISTS experiments_emission ON experiments(emission_key);
CREATE TABLE IF NOT EXISTS blockers (
  id INTEGER PRIMARY KEY AUTOINCREMENT, scope TEXT NOT NULL, category TEXT NOT NULL,
  mechanism TEXT NOT NULL, evidence TEXT NOT NULL, next_experiment TEXT NOT NULL,
  status TEXT NOT NULL DEFAULT 'OPEN', reporter TEXT, created REAL NOT NULL, resolved REAL,
  resolution TEXT);
CREATE TABLE IF NOT EXISTS tasks (
  id TEXT PRIMARY KEY, kind TEXT NOT NULL, targets TEXT NOT NULL, route TEXT NOT NULL,
  priority REAL NOT NULL, status TEXT NOT NULL, wave TEXT, packet TEXT, worker TEXT,
  created REAL NOT NULL, updated REAL NOT NULL, result TEXT);
"""


def connect(path: Path = DB) -> sqlite3.Connection:
    path.parent.mkdir(parents=True, exist_ok=True)
    con = sqlite3.connect(path, timeout=30, isolation_level=None)
    con.row_factory = sqlite3.Row
    con.execute("PRAGMA journal_mode=WAL")
    con.execute("PRAGMA synchronous=NORMAL")
    con.execute("PRAGMA foreign_keys=ON")
    con.execute("PRAGMA busy_timeout=30000")
    migrate(con)
    return con


def migrate(con: sqlite3.Connection) -> None:
    row = None
    try:
        row = con.execute("SELECT value FROM meta WHERE key='schema_version'").fetchone()
    except sqlite3.OperationalError:
        pass
    version = int(row[0]) if row else 0
    if version > SCHEMA_VERSION:
        raise RuntimeError(f"database schema {version} is newer than this tool ({SCHEMA_VERSION})")
    if version < SCHEMA_VERSION:
        with tx(con):
            for stmt in [s for s in SCHEMA.split(";") if s.strip()]:
                con.execute(stmt)
            # future migrations: if version < 2: ALTER TABLE ...
            con.execute("INSERT OR REPLACE INTO meta VALUES ('schema_version', ?)", (str(SCHEMA_VERSION),))


@contextmanager
def tx(con: sqlite3.Connection):
    """One bounded IMMEDIATE transaction (single writer at a time; readers
    continue under WAL)."""
    con.execute("BEGIN IMMEDIATE")
    try:
        yield con
        con.execute("COMMIT")
    except BaseException:
        con.execute("ROLLBACK")
        raise


# ----------------------------------------------------------------- derived
def rebuild(con: sqlite3.Connection) -> dict:
    atlas = load_json(EVIDENCE / "atlas.json")
    census = {e: load_json(BUILD / "census" / f"{e}.json") for e in EPISODES}
    recipes = {p.stem: load_json(p) for p in sorted(RECIPES.glob("*.json"))}
    promotions_path = EVIDENCE / "promotions.jsonl"
    promos = [json.loads(x) for x in promotions_path.read_text().splitlines() if x.strip()] \
        if promotions_path.exists() else []
    import symbols as sym
    with tx(con):
        for t in DERIVED:
            con.execute(f"DELETE FROM {t}")
        units = {"C0_TEXT": "startup", "ASM_TEXT": "asm", "G1_TEXT": "c", "G2_TEXT": "c"}
        for u, k in units.items():
            con.execute("INSERT INTO units VALUES (?,?,?)", (u, k, None))
        start_to_id = {}
        for f in atlas["functions"]:
            acc = ",".join(sorted(e for e, v in recipes.get(f["id"], {}).get("episodes", {}).items()
                                  if v.get("status") == "EQUAL"))
            sizes = [l["size"] for l in f["locations"].values()]
            con.execute("INSERT INTO functions VALUES (?,?,?,?,?,?,?)",
                        (f["id"], f["segment"], f["class"], f["confidence"], acc, min(sizes), max(sizes)))
            for e, l in f["locations"].items():
                con.execute("INSERT INTO locations VALUES (?,?,?,?,?,?,?,?)",
                            (f["id"], e, l["start"], l["frame"], l["offset"], l["size"], l["sha256"], l["boundary"]))
                start_to_id[(e, l["start"])] = f["id"]
            for k, v in f["evidence"].items():
                con.execute("INSERT INTO mapping_evidence VALUES (?,?,?)", (f["id"], k, json.dumps(v)))
        libnames = {}
        for e, c in census.items():
            for s in c["symbols"]:
                libnames[(e, s["linear"])] = sym.norm(s["name"])
                con.execute("INSERT OR IGNORE INTO symbols VALUES (?,?,?,?,?)",
                            (sym.norm(s["name"]), e, s["kind"], s["linear"], "census"))
        for e, c in census.items():
            counts = {}
            for f in c["functions"]:
                caller = start_to_id.get((e, f["start"]))
                if caller is None:
                    continue
                for cl in f["calls"]:
                    t = cl.get("target")
                    callee = start_to_id.get((e, t)) or libnames.get((e, t)) or (f"@{t:#x}" if t is not None else "?")
                    k = (caller, callee, cl["kind"], e)
                    counts[k] = counts.get(k, 0) + 1
            con.executemany("INSERT INTO deps VALUES (?,?,?,?,?)", [(*k, v) for k, v in counts.items()])
        for i, p in enumerate(promos):
            con.execute("INSERT INTO promotions VALUES (?,?,?,?,?,?,?)",
                        (i + 1, p["function"], ",".join(p["episodes"]), p["source_sha256"],
                         p["recipe_sha256"], p["at"], p.get("note")))
        con.execute("INSERT OR REPLACE INTO meta VALUES ('derived_from', ?)",
                    (json.dumps({"atlas_sha256": sha256((EVIDENCE / "atlas.json").read_bytes()),
                                 "recipes": len(recipes), "promotions": len(promos)}),))
    return {"functions": len(atlas["functions"]), "recipes": len(recipes), "promotions": len(promos)}


# ---------------------------------------------------------------- research
def put_source(con: sqlite3.Connection, text: str) -> str:
    data = text.encode("latin-1")
    h = sha256(data)
    con.execute("INSERT OR IGNORE INTO sources VALUES (?,?,?)", (h, len(data), zlib.compress(data, 9)))
    return h


def get_source(con: sqlite3.Connection, h: str) -> str | None:
    r = con.execute("SELECT text_z FROM sources WHERE sha256=?", (h,)).fetchone()
    return zlib.decompress(r[0]).decode("latin-1") if r else None


def lookup_experiment(con: sqlite3.Connection, key: str):
    r = con.execute("SELECT * FROM experiments WHERE key=?", (key,)).fetchone()
    if r:
        con.execute("UPDATE experiments SET hits=hits+1 WHERE key=?", (key,))
    return r


def record_experiment(con: sqlite3.Connection, rec: dict) -> None:
    with tx(con):
        put_source(con, rec["source_text"])
        con.execute(
            "INSERT OR IGNORE INTO experiments (key, function_id, source_sha256, profile, flags, compile_key,"
            " context_key, ok, emission_key, results, best_status, diff_bytes, worker, note, created)"
            " VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
            (rec["key"], rec["function"], rec["source_sha256"], rec.get("profile"), json.dumps(rec["flags"]),
             rec["compile_key"], rec["context_key"], int(rec["ok"]), rec.get("emission_key"),
             json.dumps(rec["results"], sort_keys=True), rec["best_status"], rec.get("diff_bytes"),
             rec.get("worker"), rec.get("note"), time.time()))


def add_blocker(con, scope, category, mechanism, evidence, next_experiment, reporter=None) -> int:
    if category not in BLOCKER_CATEGORIES:
        raise ValueError(f"category must be one of {BLOCKER_CATEGORIES}")
    if not mechanism or mechanism.upper() != mechanism or " " in mechanism:
        raise ValueError("mechanism must be an UPPER_SNAKE token naming the concrete mechanism")
    if not next_experiment.strip():
        raise ValueError("a blocker must name the next discriminating experiment")
    with tx(con):
        cur = con.execute("INSERT INTO blockers (scope, category, mechanism, evidence, next_experiment, reporter,"
                          " created) VALUES (?,?,?,?,?,?,?)",
                          (scope, category, mechanism, evidence, next_experiment, reporter, time.time()))
        return cur.lastrowid


def main() -> int:
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("rebuild")
    sub.add_parser("status")
    q = sub.add_parser("query")
    q.add_argument("sql")
    x = sub.add_parser("experiments")
    x.add_argument("function")
    x.add_argument("--all", action="store_true")
    s = sub.add_parser("same-emission")
    s.add_argument("function")
    b = sub.add_parser("blockers")
    b.add_argument("--open", action="store_true")
    k = sub.add_parser("block")
    k.add_argument("scope")
    k.add_argument("category", choices=BLOCKER_CATEGORIES)
    k.add_argument("mechanism")
    k.add_argument("--evidence", required=True)
    k.add_argument("--next", required=True)
    k.add_argument("--reporter")
    r = sub.add_parser("resolve")
    r.add_argument("id", type=int)
    r.add_argument("--resolution", required=True)
    sub.add_parser("export-blockers")
    a = ap.parse_args()
    con = connect()
    if a.cmd == "rebuild":
        print(rebuild(con))
    elif a.cmd == "status":
        for t in ("functions", "locations", "deps", "symbols", "promotions", "sources", "experiments",
                  "blockers", "tasks"):
            print(f"{t:12s} {con.execute(f'SELECT COUNT(*) FROM {t}').fetchone()[0]}")
        for r in con.execute("SELECT best_status, COUNT(*) n FROM experiments GROUP BY best_status"):
            print(f"  experiments {r[0]}: {r[1]}")
    elif a.cmd == "query":
        for r in con.execute(a.sql):
            print(json.dumps(dict(r)))
    elif a.cmd == "experiments":
        sql = "SELECT key, source_sha256, profile, best_status, diff_bytes, worker, note, results, hits " \
              "FROM experiments WHERE function_id=? ORDER BY created"
        for r in con.execute(sql, (a.function,)):
            d = dict(r)
            if not a.all:
                d["results"] = {e: v["status"] for e, v in json.loads(d["results"]).items()}
            print(json.dumps(d))
    elif a.cmd == "same-emission":
        sql = ("SELECT emission_key, COUNT(DISTINCT source_sha256) n, GROUP_CONCAT(DISTINCT source_sha256) srcs, "
               "MIN(best_status) st FROM experiments WHERE function_id=? AND emission_key IS NOT NULL "
               "GROUP BY emission_key HAVING n > 1")
        for r in con.execute(sql, (a.function,)):
            print(json.dumps(dict(r)))
    elif a.cmd == "blockers":
        sql = "SELECT * FROM blockers" + (" WHERE status='OPEN'" if a.open else "") + " ORDER BY id"
        for r in con.execute(sql):
            print(json.dumps(dict(r)))
    elif a.cmd == "block":
        print(add_blocker(con, a.scope, a.category, a.mechanism, a.evidence, a.next, a.reporter))
    elif a.cmd == "resolve":
        with tx(con):
            con.execute("UPDATE blockers SET status='RESOLVED', resolved=?, resolution=? WHERE id=?",
                        (time.time(), a.resolution, a.id))
    elif a.cmd == "export-blockers":
        rows = [dict(r) for r in con.execute("SELECT * FROM blockers ORDER BY id")]
        atomic_json(EVIDENCE / "blockers.json", {"note": "curated export of state/research.sqlite blockers",
                                                 "blockers": rows})
        print(len(rows))
    return 0


if __name__ == "__main__":
    sys.exit(main())
