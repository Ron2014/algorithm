import sys
try:
    while True:
        line = sys.stdin.readline()
        if line == "":
            break
        print len(line)
        print line[::-1]
except:
    pass