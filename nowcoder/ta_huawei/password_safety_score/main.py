# -*- coding: cp936 -*-

def scoreLen(psw):
    l = len(psw)
    if l >= 8:
        return 25
    elif l >= 5:
        return 10
    else:
        return 5

def scoreAlpha(psw):
    r = {}
    for c in psw:
        if c.isupper():
            r[0] = 1
        elif c.islower():
            r[1] = 1
    l = len(r)
    if l==0:
        return 0
    elif l==1:
        return 10
    else:
        return 20

def scoreNum(psw):
    hasNum = False
    for c in psw:
        if c.isdigit():
            if hasNum:
                return 20
            else:
                hasNum = True
    if hasNum:
        return 10
    return 0

def scoreFlag(psw):
    hasFlag = False
    for c in psw:
        if not c.isalnum():
            if hasFlag:
                return 25
            else:
                hasFlag = True
    if hasFlag:
        return 10
    return 0

def scoreExtra(psw):
    r = {}
    for c in psw:
        if c.isdigit():
            r[0] = 1
        elif c.isupper():
            r.setdefault(1, {})[0] = 1
        elif c.islower():
            r.setdefault(1, {})[1] = 1
        else:
            r[2] = 1
    l = len(r)
    if l==2 and 0 in r and 1 in r:
        return 2
    if l==3:
        if len(r[1]) > 1:
            return 5
        else:
            return 3
    return 0

LEVEL_NAME = [
    (90,"VERY_SECURE"),
    (80,"SECURE"),
    (70,"VERY_STRONG"),
    (60,"STRONG"),
    (50,"AVERAGE"),
    (25,"WEAK"),
    (0,"VERY_WEAK"),
]

import sys
while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    score = 0
    score += scoreLen(line)
    score += scoreAlpha(line)
    score += scoreNum(line)
    score += scoreFlag(line)
    score += scoreExtra(line)

    for k, v in LEVEL_NAME:
        if score>=k:
            print v
            break
