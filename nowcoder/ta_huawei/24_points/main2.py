from __future__ import print_function # never new line for <print> in python2

CARDS = {
    "2":2,
    "3":3,
    "4":4,
    "5":5,
    "6":6,
    "7":7,
    "8":8,
    "9":9,
    "10":10,
    "J":11,
    "Q":12,
    "K":13,
    "A":1,
    "JOKER":0,
    "joker":0,
}

CARDS2 = ["A","2","3","4","5","6","7","8","9","10","J","Q","K",]

import sys

result = []

def checkValue(node):
    global result
    if node[0] == 24:
        result.append(node)

def priority(ch):
    if ch=='+' or ch=='-':
        return 1
    if ch=='*' or ch=='/':
        return 2
    return 0

def operateValue(op, node0, node1):
    node = [0, node0, op, node1]
    if op == '+':
        node[0] = node0[0] + node1[0]
    elif op == '*':
        node[0] = node0[0] * node1[0]
    elif op == '-':
        node[0] = node0[0] - node1[0]
    elif op == '/':
        if (node1[0] and node0[0]%node1[0]==0):
            node[0] = node0[0] / node1[0]
        else:
            node = None
    # if node: print(node)
    return node

def getResult(num, nums):
    if not nums:
        checkValue(num)
        return
    
    l = len(nums)
    if not num:
        for i in xrange(l):
            num = nums[i]
            nums1 = nums[:i]
            nums1.extend(nums[i+1:])
            getResult(num, nums1)
    else:
        for i in xrange(l):
            other = nums[i]
            nums1 = nums[:i]
            nums1.extend(nums[i+1:])

            node = operateValue('+', num, other)
            getResult(node, nums1)

            node = operateValue('*', num, other)
            getResult(node, nums1)

            node = operateValue('-', num, other)
            getResult(node, nums1)

            node = operateValue('/', num, other)
            if node:
                getResult(node, nums1)

def showResult(node):
    v, oprandL, op, oprandR = node
    if not op:
        print(CARDS2[v-1],end='')
        return

    showResult(oprandL)
    print(op,end='')
    showResult(oprandR)

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break

    invalid = False
    lines = line.split()

    nums = []
    for s in lines:
        n = CARDS.get(s, 0)
        if n==0:
            invalid = True
            break
        nums.append([n, 0, '', 0])
    
    if (invalid or len(nums)!=4):
        print("ERROR")
    else:
        getResult(None, nums)
        if result:
            # for ret in result:
            #     showResult(ret)
            #     print()
            showResult(result[0])
            print()
        else:
            print("NONE")

            