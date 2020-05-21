import sys
tongji = {}

while True:
    c = sys.stdin.read(1)
    c = c.lower()
    if c == '\n':
        break
    else:
        tongji[c] = tongji.get(c, 0) + 1

t = sys.stdin.read(1)
t = t.lower()
print(tongji.get(t, 0))
