import sys
IDX_ALPHA = 0
IDX_SPACE = 1
IDX_NUM = 2
IDX_OTHER = 3

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        records = [0, 0, 0, 0]
        for c in line:
            if c.isalpha():
                records[IDX_ALPHA] += 1
            elif c.isspace():
                records[IDX_SPACE] += 1
            elif c.isdigit():
                records[IDX_NUM] += 1
            else:
                records[IDX_OTHER] += 1
        
        for v in records:
            print v
except:
    pass