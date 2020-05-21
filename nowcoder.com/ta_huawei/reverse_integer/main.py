from __future__ import print_function # never new line for <print> in python2
import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        line_len = len(line)
        for i in xrange(line_len):
            print(line[line_len - 1 - i], end='')
        print()
except:
    pass