"""Re-indent the body of a candidate (after /*@body*/): 4 spaces per brace
level plus one level per pending single-statement control header."""
import re, sys
HDR = re.compile(r"^(\}\s*)?(else\s+)?(if|for|while|switch)\s*\(.*\)$|^(\}\s*)?else$")
def reindent(body):
    out, depth, pending = [], 0, 0
    for line in body.split("\n"):
        s = line.strip()
        if not s:
            out.append("")
            continue
        if s.startswith("#"):
            out.append(s)
            continue
        lead_close = s.startswith("}")
        if lead_close:
            depth -= 1
        label = re.match(r"^[A-Za-z_]\w*:$", s) and not s.startswith(("default", "case"))
        case = s.startswith(("case ", "default:"))
        ind = max(depth + pending - (1 if case or label else 0), 0)
        out.append("    " * ind + s)
        opens, closes = s.count("{"), s.count("}") - (1 if lead_close else 0)
        depth += opens - closes
        if s.endswith("{"):
            pending = 0
        elif HDR.match(s):
            pending += 1
        elif s.endswith(";") or s.endswith("}"):
            pending = 0
    return "\n".join(out)
if __name__ == "__main__":
    t = open(sys.argv[1], encoding="latin-1").read()
    pre, body = t.split("/*@body*/", 1)
    open(sys.argv[2], "w", encoding="latin-1").write(pre + "/*@body*/" + reindent(body).rstrip() + "\n")
