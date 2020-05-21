import sys

records = {}

def cmpFunc(x, y):
    global records
    wx, wy = 0, 0
    nx, ny = records.get(x, 0), records.get(y, 0)
    step = 1

    if ord(x) < ord(y):
        wy += step
    elif ord(x) > ord(y):
        wx += step
    
    step *= 2

    if nx < ny:
        wx += step
    elif nx > ny:
        wy += step

    return wx - wy
    
while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    count = int(lines[0])

    if len(lines) > 1:
        lines = lines[1:]
    else:
        lines = []
        for i in xrange(count):
            line = sys.stdin.readline().strip()
            lines.append(line)
            
    for line in lines:
        records = {}
        for c in line:
            records[c] = records.get(c, 0) + 1
        line = sorted(line, cmpFunc)

        nice_val = 0
        lastc = None
        value = 27
        for c in line:
            if lastc != c:
                value -= 1
                lastc = c
            nice_val += value
        
        # print line
        print nice_val