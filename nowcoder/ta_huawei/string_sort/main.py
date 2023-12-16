'''
A Famous Saying: Much Ado About Nothing (2012/8).
---
A aaAAbc dFgghh: iimM nNn oooos Sttuuuy (2012/8).

'''
import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        input_char = []
        for i, c in enumerate(line):
            if (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z'):
                input_char.append(c)

        input_char = sorted(input_char, key=lambda x: x.lower())
        # print input_char

        char_idx = 0
        newline = []
        for i, c in enumerate(line):
            if (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z'):
                newline.append(input_char[char_idx])
                char_idx += 1
            else:
                newline.append(c)
        
        print "".join(newline)
except:
    pass