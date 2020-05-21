from __future__ import print_function # never new line for <print> in python2
import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        words = line.split()
        words_count = len(words)
        for i in xrange(words_count):
            print(words[words_count - 1 - i], end=' ')
        print()
except:
    pass