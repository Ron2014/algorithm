import sys
try:
    while True:
        line = sys.stdin.readline()
        if line == "":
            break
        num = int(line) * 1000  # decimal for 1
        x = max(1, num / 2)
        while x:
            approach_v = x * x * x
            approach_v -= approach_v % 1000
            if approach_v <= num:
                break
            x -= 1
        print x * 0.1
except:
    pass