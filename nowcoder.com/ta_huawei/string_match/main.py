
import sys

try:
    while True:
        line = sys.stdin.readline()
        if line == "":
            break

        str_short = line
        str_long = sys.stdin.readline()

        set_short = set([])
        set_long = set([])

        for c in str_short:
            set_short.add(c)
        for c in str_long:
            set_long.add(c)

        if set_short.issubset(set_long):
            print "true"
        else:
            print "false"

except:
    pass