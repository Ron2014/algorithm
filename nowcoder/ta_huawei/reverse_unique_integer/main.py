from __future__ import print_function # never new line for <print> in python2
import sys
try:
    while True:
        exists = set([])
        line = sys.stdin.readline().strip()
        if line == '':
            break
        line_len = len(line)
        for i in xrange(line_len):
            v = line[line_len - 1 - i]
            if v in exists:
                continue
            exists.add(v)
            print(v,end='')
        print()
except:
    pass