import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        counts = {}
        remove_chars = set([])
        if line == "":
            break
        min_count = len(line)
        for c in line:
            counts[c] = counts.get(c, 0) + 1
        for k, v in counts.iteritems():
            if v < min_count:
                min_count = v
                remove_chars = set([])
                remove_chars.add(k)
            elif v == min_count:
                remove_chars.add(k)
        newline = []
        for c in line:
            if c not in remove_chars:
                newline.append(c)
        print "".join(newline)
            
except:
    pass