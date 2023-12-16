import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        kinds = set([])
        count = 0
        if line == "":
            break
        for c in line:
            if c in kinds:
                continue
            count += 1
            kinds.add(c)
        print(count)
except:
    pass