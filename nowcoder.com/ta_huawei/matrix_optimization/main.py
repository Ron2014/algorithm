from __future__ import print_function # never new line for <print> in python2
import sys

def calcResult(matrixes):
    l = len(matrixes)
    maxCol = 0
    for i in xrange(l-1):
        # matrixes[i] * matriex[i+1]
        m = matrixes[i]
        if m[2] > maxCol:
            maxCol = m[2]
            idx = i

    if maxCol:
        # matrixes[i] * matriex[i+1]
        m = (0, matrixes[idx][1], matrixes[idx+1][2], matrixes[idx], matrixes[idx+1])
        matrixes[idx] = m
        for i in xrange(idx+1,l-1):
            matrixes[i] = matrixes[i+1]
        matrixes = matrixes[:-1]
        return calcResult(matrixes)
    else:
        return matrixes[0]

def showOrder(node):
    key, _, _, matrixL, matrixR = node
    if key:
        print(chr(key-1+ord('A')),end='')
        return
    print('(',end='')
    showOrder(matrixL)
    showOrder(matrixR)
    print(')',end='')

def analysisRule(matrixes, rule):
    stackMatrix = []
    stackScope = []

    calcNum = 0
    for c in rule:
        if c.isalpha():
            stackMatrix.append(matrixes[ord(c)-ord('A')])
        elif c=='(':
            stackScope.append(c)
        else:
            if len(stackScope):
                stackScope = stackScope[:-1]

            if len(stackMatrix)>1:
                m0 = stackMatrix[-2]
                m1 = stackMatrix[-1]
                calcNum += m0[1] * m0[2] * m1[2]

                nm = (0, m0[1], m1[2], m0, m1)
                stackMatrix[-2] = nm
                stackMatrix = stackMatrix[:-1]

    print(calcNum)

try:
    while True:
        line = sys.stdin.readline().strip()
        if not line:
            break
        lines = line.split()
        
        # print(len(lines))
        # print(lines[0])
        count = int(lines[0])
        matrixes = []

        # 1. id
        # 2. row
        # 3. col
        # 4. X x Y get

        if len(lines) > 1:
            lines = lines[1:]
            for i in xrange(count):
                matrixes.append((i+1, int(lines[i*2]), int(lines[i*2+1]), None, None))
        else:
            for i in xrange(count):
                lines = map(int, sys.stdin.readline().strip().split())
                matrixes.append((i+1, lines[0], lines[1], None, None))

        rule = sys.stdin.readline().strip()
        analysisRule(matrixes, rule)

        # node = calcResult(matrixes)
        # showOrder(node)
        # print()
except:
    pass
