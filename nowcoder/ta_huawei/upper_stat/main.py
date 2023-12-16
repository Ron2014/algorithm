import sys
try:
    while True:
        line = sys.stdin.readline()
        if line == "":
            break
        count = 0
        for c in line:
            if c.isupper():
                count += 1
        print count
except:
    pass