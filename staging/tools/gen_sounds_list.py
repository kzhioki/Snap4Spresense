#!/usr/bin/env python

import sys

begin = 0
for line in iter(sys.stdin.readline, ""):
    if (line[1:4] == r'-- '):
        if (begin == 1):
            print "}"
        word = line.split()
        print word[-1] + "={"
        begin = 1
    if (line[5:8] == r'-- '):
        word = line.split()
        print word[-1]

if (begin == 1):
    print "}"
