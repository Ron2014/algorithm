
'''
YUANzhi1987
---
zvbo9441987
'''

PHONE_KEYS = {
    "1":"1",
    "abc":"2",
    "def":"3",
    "ghi":"4",
    "jkl":"5",
    "mno":"6",
    "pqrs":"7",
    "tuv":"8",
    "wxyz":"9",
    "0":"0",
}

PHONE_KEYS_X = {}
for k, v in PHONE_KEYS.iteritems():
    for c in k:
        PHONE_KEYS_X[c] = v

import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        newline = []
        for c in line:
            if c >= "A" and c < "Z":
                nc = chr(ord(c.lower()) + 1)
            elif c == "Z":
                nc = "a"
            else:
                nc = PHONE_KEYS_X.get(c, c)
            newline.append(nc)
        print "".join(newline)
            
except:
    pass