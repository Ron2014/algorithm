import sys
'''
DKSq8qykpgKIZxiRKmQ9QkZt909PffE6Gyfc57dBx7p20D42bWJRzKqGGCzzQ4p7Z32Dsx2Cf8G2841lPuAZNb K0fHodOVFlbl220ov260TPOrmZ328d1E89OatcL88EXr622RdklXtXazO7wMoc6DEKU45eQ5VBUy2YFjgJX
---
000080844444444444C42CA2A2626A661E1E1E1E11919959BD7D73F3FBGBGBG7J7KGKHKILJNKOKOKOMOPPPQRQRQRQVSWTXUXUYVZXZX5ZDZ3Z353DBDBB7BFFgFjFkFkgkilllmlomoopqpqprqrsttutxvxwyxyyzzzz
'''
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        newline = "".join(line.split())
        str0, str1 = [], []
        for i, c in enumerate(newline):
            if i%2:
                str1.append(c)
            else:
                str0.append(c)
        str0 = sorted(str0)
        str1 = sorted(str1)
        total_len = len(newline)
        newline = []
        # print str0, str1
        for i in xrange(total_len):
            if i%2:
                newline.append(str1[i/2])
            else:
                newline.append(str0[i/2])
        # print newline
        result = []
        for c in newline:
            if c.isdigit() or (c >= 'a' and c <='f') or (c >= 'A' and c <= 'F'):
                str_bit = "%4s" % (bin(int(c, 16))[2:])
                str_bit = str_bit.replace(' ', '0')
                str_bit = str_bit[::-1]
                nc = hex(int(str_bit,2))[2:].upper()
            else:
                nc = c
            result.append(nc)
        print "".join(result)
                


except:
    pass