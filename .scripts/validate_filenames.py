#!/usr/bin/env python3

import os
import sys
from typing import Iterator


def good_filepaths(top_dir: str = ".") -> Iterator[str]:
    for dirpath, dirnames, filenames in os.walk(top_dir):
        dirnames[:] = [d for d in dirnames if d[0] not in "._"]
        for filename in filenames:
            if os.path.splitext(filename)[1].lower() == ".cpp":
                yield os.path.join(dirpath, filename).lstrip("./")


filepaths = list(good_filepaths())
upper_files = sorted(file for file in filepaths if file != file.lower())
if upper_files:
    print(f"{len(upper_files)} files contain uppercase characters:")
    print("\n".join(upper_files) + "\n")

space_files = sorted(file for file in filepaths if " " in file or "-" in file)
if space_files:
    print(f"{len(space_files)} files contain space or dash characters:")
    print("\n".join(space_files) + "\n")

nodir_files = sorted(file for file in filepaths if os.sep not in file)
if nodir_files:
    print(f"{len(nodir_files)} files are not in a directory:")
    print("\n".join(nodir_files) + "\n")

bad_files = len(upper_files + space_files + nodir_files)
if bad_files:
    sys.exit(bad_files)
