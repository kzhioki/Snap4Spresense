#!/usr/bin/env python3

import sys
import re

args = sys.argv

begin = 0
for line in open(args[1], "r"):
    start = re.search(r"const char *bg_list", line)
    if start:
        begin = 1

    end = re.search(r"};", line)
    if begin and end:
        break
        
    result = re.search(r"\"\S+\.rgab\"", line)
    if result:
        print(result.group()[1:-6])
