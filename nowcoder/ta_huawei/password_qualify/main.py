'''
021Abc9000
021Abc9Abc1
021ABC9000
021$bc9000
---
OK
NG
NG
OK

S^fc8G5-78hlgV3X#96C5+5$b7K4^!#(B39
I)S)1p0485$-ot4N7A9Mc*N3#46^Hd)9)-^Z!J**
F04bA$y6$1CAD4n)x1$9&
80-~8$~%x-F12P
@!7479Y^V^1$l*26x#2S9%Nx0H!dY78*w4Zl
16@%^nju+4d04U4*)1l!5+g!^k+P#vq*r#&v2059PsJ
4@M$68(Oh%!n%~9&08&Z@#+dN0&Z
D*09R~G1-$7GB&()$b1h^A^1b
80!2b^*t411699+^&4y@
xZ44332BZ-Ck0+ko~19(w!%
)3y@GT!(5V9G(8VeT+(tM3k4
O1r#K$C804E8-41J8*&%#13603
7v0T+6s!(7*)C4RX8*IB85yk+6&~#v6)q$+W3&8-8+
jJ8~7125d@DGmk~^~m637B20!61M5NdY^9CU9%R$1&h53iO+
831(l)8^$O+3T
---
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
'''

MIN_LEN = 9
COMBINE_CONDITION_COUNT = 3
CHILD_STR_LEN = 3

import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        
        length = len(line)
        if length < MIN_LEN:
            print "NG"
            continue

        conbine_conditions = set([])

        for c in line:
            if c.isalpha():
                if c.islower():
                    conbine_conditions.add("has_lower")
                else:
                    conbine_conditions.add("has_upper")
            elif c.isdigit():
                conbine_conditions.add("has_digit")
            else:
                conbine_conditions.add("has_other")
            if len(conbine_conditions) >= COMBINE_CONDITION_COUNT:
                break

        if len(conbine_conditions) < COMBINE_CONDITION_COUNT:
            print "NG"
            continue

        check_child_str = True
        for i in xrange(CHILD_STR_LEN, length-CHILD_STR_LEN):
            for j in xrange(i-CHILD_STR_LEN+1):
                child_str = line[j:i]
                if child_str in line[:j] or child_str in line[i:]:
                    check_child_str = False
                    break
            if not check_child_str:
                break
        if not check_child_str:
            print "NG"
            continue
        
        print "OK"
except:
    pass