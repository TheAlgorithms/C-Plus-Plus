import os
import subprocess
import sys

print("Python {}.{}.{}".format(*sys.version_info))  # Python 3.8
with open("git_diff.txt") as in_file:
    modified_files = sorted(in_file.read().splitlines())
    print("{} files were modified.".format(len(modified_files)))

    cpp_exts = tuple(".c .c++ .cc .cpp .cu .cuh .cxx .h .h++ .hh .hpp .hxx".split())
    cpp_files = [file for file in modified_files if file.lower().endswith(cpp_exts)]
    print(f"{len(cpp_files)} C++ files were modified.")
    if not cpp_files:
        sys.exit(0)

    subprocess.run(
        [
            "clang-tidy",
            "--fix",
            "-p=build",
            "--extra-arg=-std=c++11",
            *cpp_files,
            "--",
        ],
        check=True,
        text=True,
        stderr=subprocess.STDOUT,
    )
    subprocess.run(
        ["clang-format", "-i", "-style=file", *cpp_files],
        check=True,
        text=True,
        stderr=subprocess.STDOUT,
    )
    upper_files = [file for file in cpp_files if file != file.lower()]
    if upper_files:
        print(f"{len(upper_files)} files contain uppercase characters:")
        print("\n".join(upper_files) + "\n")
    space_files = [file for file in cpp_files if " " in file or "-" in file]
    if space_files:
        print(f"{len(space_files)} files contain space or dash characters:")
        print("\n".join(space_files) + "\n")
    nodir_files = [file for file in cpp_files if file.count(os.sep) != 1]
    if nodir_files:
        print(f"{len(nodir_files)} files are not in one and only one directory:")
        print("\n".join(nodir_files) + "\n")
    bad_files = len(upper_files + space_files + nodir_files)
    if bad_files:
        sys.exit(bad_files)
