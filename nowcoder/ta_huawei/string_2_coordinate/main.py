'''
A10;S20;W10;D30;X;A1A;B10A11;;A10;
---
10,-10

'''
x = 0
y = 0

def keyA(arg):
    global x
    x -= arg

def keyD(arg):
    global x
    x += arg

def keyW(arg):
    global y
    y += arg

def keyS(arg):
    global y
    y -= arg

import sys
try:
    moveFunc = {}
    moveFunc['A'] = keyA
    moveFunc['D'] = keyD
    moveFunc['W'] = keyW
    moveFunc['S'] = keyS

    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        x = 0
        y = 0
        commands = line.split(";")
        for cmd in commands:
            if not cmd:
                continue
            direct = cmd[0]
            func = moveFunc.get(direct, None)
            if not func:
                continue
            # print cmd
            try:
                arg = int(cmd[1:])
            except:
                continue
            # print arg
            # print func
            func(arg)
        print("%d,%d" % (x, y))
except:
    pass