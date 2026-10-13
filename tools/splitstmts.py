"""Split lines holding several statements (outside parentheses) into one
statement per line, then re-indent with tools/reindent.py.  Body only."""
import sys
sys.path.insert(0, r"D:\Prog\duke1_recon\tools")
import reindent


def split_line(line):
    out, cur, depth, i = [], "", 0, 0
    s = line.strip()
    in_str = False
    while i < len(s):
        ch = s[i]
        cur += ch
        if ch == '"' and (i == 0 or s[i - 1] != "\\"):
            in_str = not in_str
        elif not in_str:
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
            elif ch == ";" and depth == 0:
                out.append(cur.strip())
                cur = ""
            elif ch == ":" and depth == 0 and (cur.strip().startswith(("case ", "default"))):
                out.append(cur.strip())
                cur = ""
        i += 1
    if cur.strip():
        out.append(cur.strip())
    return out


t = open(sys.argv[1], encoding="latin-1").read()
pre, body = t.split("/*@body*/", 1)
lines = []
for line in body.split("\n"):
    st = line.strip()
    if st.startswith(("#", "/*", "*/")) or st.startswith("* ") or st == "*":
        lines.append(line)
        continue
    parts = split_line(line)
    if len(parts) <= 1:
        lines.append(line)
        continue
    lines += parts
body = reindent.reindent("\n".join(lines))
open(sys.argv[2], "w", encoding="latin-1").write(pre + "/*@body*/" + body.rstrip() + "\n")
