import sys

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    strMatch = lines[0]
    if len(lines) > 1:
        strTarget = lines[1]
    else:
        strTarget = sys.stdin.readline().strip()
    lenM = len(strMatch)
    lenT = len(strTarget)

    subs = {}
    for i, c in enumerate(strMatch):
        last = subs.get(i-1, None)
        cur = subs.setdefault(i, set([]))
        if c =='?':
            if last:
                for s in last:
                    # match strTarget[:s]
                    if s<lenT:
                        cur.add(s+1)
            else:
                if lenT>0:
                    cur.add(1)
        elif c == '*':
            if last:
                for s in last:
                    # match strTarget[:s]
                    cur.add(s)
                    for j in xrange(lenT-s):
                        cur.add(s+j+1)
            else:
                cur.add(0)
                for j in xrange(lenT):
                    cur.add(j+1)
        else:
            if last:
                for s in last:
                    # match strTarget[:s]
                    # print i,s,lenT,strMatch[i],strTarget[s]
                    if s<lenT and strMatch[i] == strTarget[s]:
                        cur.add(s+1)
            else:
                if strMatch[i] == strTarget[i]:
                    cur.add(1)
        if not cur:
            break
    # print subs
    if subs.get(lenM-1, None):
        print "true"
    else:
        print "false"

