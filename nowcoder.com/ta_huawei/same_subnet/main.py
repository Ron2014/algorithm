def addr2dec(addr):
    try:
        items = map(int, addr.split("."))
    except:
        return None
    
    for i in xrange(4):
        if items[i] < 0 or items[i] > 0xFF:
            return None


    return sum([items[i] << [24, 16, 8, 0][i] for i in range(4)])

import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break

        if line.find(' ') > 0:
            mask, addr0, addr1 = line.split()
        else:
            mask = line
            addr0 = sys.stdin.readline().strip()
            addr1 = sys.stdin.readline().strip()

        # print mask, addr0, addr1
        dec_mask = addr2dec(mask)
        dec_addr0 = addr2dec(addr0)
        dec_addr1 = addr2dec(addr1)
    
        if not dec_mask or not dec_addr0 or not dec_addr1:
            print '1'
        elif dec_mask & dec_addr0 == dec_mask & dec_addr1:
            print '0'
        else:
            print '2'

except:
    pass