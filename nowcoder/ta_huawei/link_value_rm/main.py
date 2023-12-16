from __future__ import print_function # never new line for <print> in python2
import sys

linkMaps = {}

def showSeq(seq, ri):
    global linkMaps
    if not seq:
        return

    # print(seq)
    l = len(seq)
    for i in xrange(l):
        v = seq[l-1-i]
        if v != ri:
            print(v, end=' ')
        showSeq(linkMaps.get(v, None), ri)

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break

    lines = line.split()
    linkCount = int(lines[0])
    linkMaps = {}
    vset = set([])

    print(len(lines))
    if len(lines) > 1:
        headv = int(lines[1])
        vset.add(headv)

        for i in xrange(1, linkCount):
            val, idx = int(lines[i*2]), int(lines[i*2+1])
            if val in vset:
                continue
            vset.add(val)
            seq = linkMaps.setdefault(idx, [])
            seq.append(val)
        ri = int(lines[-1])

    else:
        headv = int(sys.stdin.readline().strip())
        vset.add(headv)

        for i in xrange(1, linkCount):
            val, idx = map(int, sys.stdin.readline().strip().split())
            if val in vset:
                continue
            vset.add(val)
            seq = linkMaps.setdefault(idx, [])
            seq.append(val)
        ri = int(sys.stdin.readline().strip())

    # print(linkMaps)
    # print(linkMaps.get(headv, None))

    print(headv,end=' ')
    showSeq(linkMaps.get(headv, None), ri)
    print()
                    


