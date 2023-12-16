#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys, platform

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        lines = line.split()
        text = lines[0]

        if len(lines) > 1:
            sublen = int(lines[1])
        else:
            sublen = input()
        print text[:sublen]
except:
    pass