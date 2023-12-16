import sys

def upspring_height(height, times):
    return height * 1.0 / (2 ** times)

def upspring_distance(height, times):
    if times == 1:
        return height
    elif times == 2:
        return height * 2
    else:
        return upspring_distance(height, times-1) + upspring_height(height, times-2)
try:

    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break
        height = int(line)
        print "%.6f" % (upspring_distance(height, 5))
        print "%.6f" % (upspring_height(height, 5))
except:
    pass
