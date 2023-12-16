import sys
while True:
    records = {}
    key_list = []

    try:
        count = input()
    except:
        break

    for i in xrange(count):
        line = sys.stdin.readline().strip()
        key, value = line.split()
        key = int(key)
        value = int(value)
        if key in records:
            records[key] += value
        else:
            records[key] = value
            key_list.append(key)
    
    for key in sorted(key_list):
        print("%d %d" % (key, records[key]))
