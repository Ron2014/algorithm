import sys

# low to high
def cmpFunc0(x, y):
    _, scorex, ix = x
    _, scorey, iy = y
    wx, wy = 0, 0
    step = 1

    if ix < iy:
        wy += step
    elif ix > iy:
        wx += step
    
    step *= 2

    if scorex < scorey:
        wy += step
    elif scorex > scorey:
        wx += step
    
    return wx - wy

# high to low
def cmpFunc1(x, y):
    _, scorex, ix = x
    _, scorey, iy = y
    wx, wy = 0, 0
    step = 1

    if ix < iy:
        wy += step
    elif ix > iy:
        wx += step
    
    step *= 2

    if scorex < scorey:
        wx += step
    elif scorex > scorey:
        wy += step
    
    return wx - wy

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    count = int(line)
    low2high = int(sys.stdin.readline().strip())
    score_list = []
    for i in xrange(count):
        name, score = sys.stdin.readline().strip().split()
        score = int(score)
        score_list.append((name, score, i))
    
    if low2high:
        score_list = sorted(score_list, cmpFunc0)
    else:
        score_list = sorted(score_list, cmpFunc1)
    
    for name, score, _ in score_list:
        print "%s %d" % (name, score)

