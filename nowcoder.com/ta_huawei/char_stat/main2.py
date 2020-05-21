'''
8v26ktzk069lm400061m0v965we88850o6omqi532ktir6esb55t0kqm026y8rk63aj82kcx48gd1tiylvs0xo32zem65q7z5ce2185d2ascz62a2p3ajr45h637t2p290lc043gicp5ldzzmx2
---
206583kmzct4aeil19dopqrsvx7gjybhw
88888888
333333
260z5mktxvylscrqip8woeajdghb34971
'''
import sys

records = {}

def cmpFunc(x, y):
    global records

    step = 1
    wx, wy = 0, 0
    cx, cy = ord(x), ord(y)
    freqx, freqy = records[cx], records[cy]

    if cx < cy:
        wy += step
    elif cx > cy:
        wx += step

    step *= 2

    if freqx > freqy:
        wy += step
    elif freqx < freqy:
        wx += step

    return wx - wy

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        records = {}
        result_line = []

        for c in line:
            cc = ord(c)
            if cc in records:
                records[cc] += 1
            else:
                records[cc] = 1
                result_line.append(c)
        
        result_line = "".join(sorted(result_line, cmpFunc))

        print result_line
except:
    pass