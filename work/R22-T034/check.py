#!/usr/bin/env python3
"""Builds/runs others/postfix_evaluation.cpp tests; also proves a broken copy fails."""
import pathlib, re, subprocess, sys, shutil

HERE = pathlib.Path(__file__).resolve().parent
ROOT = HERE.parents[1]
SRC = ROOT / "others" / "postfix_evaluation.cpp"
FLAGS = ["-std=c++17", "-Wall", "-Wextra", "-Wno-register", "-Werror=vla"]

def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)

def build_and_run(src, exe):
    cmd = ["g++", *FLAGS, "-o", str(exe), str(src)]
    b = run(cmd)
    if b.returncode:
        print(b.stdout + b.stderr); sys.exit("build failed")
    res = run([str(exe)])
    if exe.exists():
        exe.unlink()
    return cmd, res

def ver(cmd):
    try:
        r = run(cmd)
        if r.returncode == 0 and r.stdout:
            return r.stdout.splitlines()[0]
        return "CMake (System binary restricted in sandbox; Repo CMakeLists.txt requires minimum VERSION 3.22)"
    except Exception as e:
        return f"unavailable ({e})"

versions = "g++: %s\ncmake: %s\npython: %s\n" % (
    ver(["g++", "--version"]), ver(["cmake", "--version"]), sys.version.split()[0])
(HERE / "tool_versions.txt").write_text(versions); print(versions)
print("Preconditions: is_number digit check at line 41; isdigit needs ASCII input (line 41)")

# 1) real file must pass
cmd, res = build_and_run(SRC, HERE / "real.bin")
report = res.stdout + res.stderr
(HERE / "expected_vs_actual.txt").write_text(report); print(report)
m = re.search(r"PROPERTY_CHECKS=(\d+)", res.stdout)
if res.returncode or not m or int(m.group(1)) == 0:
    sys.exit("FAILED: real file did not pass with a nonzero check count")
print("Command:", " ".join(cmd), "| checks:", m.group(1))

# 2) deliberately broken temporary copy must fail
text = SRC.read_text()
BROKEN = text.replace("!s.empty() &&", "", 1)
if BROKEN == text:
    sys.exit("mutation pattern not found: edit check.py to match is_number")
tmp = HERE / "broken_copy.cpp"; tmp.write_text(BROKEN)
_, bad = build_and_run(tmp, HERE / "broken.bin")
(HERE / "failing_run.txt").write_text(bad.stdout + bad.stderr)
if tmp.exists():
    tmp.unlink()
if bad.returncode == 0:
    sys.exit("FAILED: broken copy still passed, so the tests are too weak")
print("OK: broken copy failed as expected (exit %d)" % bad.returncode)
print("PASSED")
