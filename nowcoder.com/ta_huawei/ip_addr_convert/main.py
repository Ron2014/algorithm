def addr2dec(addr):
    items = map(int, addr.split("."))
    return sum([items[i] << [24, 16, 8, 0][i] for i in range(4)])

def dec2addr(num):
    items = ['0', '0', '0', '0']
    for i in xrange(4):
        items[3-i] = str(num & 0xFF)
        num >>= 8
    return ".".join(items)
    

is_addr2dec = True

import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break

        if is_addr2dec:
            print addr2dec(line)
        else:
            print dec2addr(int(line))
    
        is_addr2dec = not is_addr2dec
except:
    pass