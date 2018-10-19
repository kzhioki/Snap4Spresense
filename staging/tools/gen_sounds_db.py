#!/usr/bin/env python3

import sys
import re

args = sys.argv

for line in open(args[1], "r"):
    result = re.search(r"\"\S+\.mp3\"", line)
    if result:
        print(result.group()[1:-1])
