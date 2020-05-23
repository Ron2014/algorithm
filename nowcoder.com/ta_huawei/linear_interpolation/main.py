import sys

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    count = int(lines[0])

    if len(lines) > 2:
        lines = lines[2:]
    else:
        lines = []
        for i in xrange(count):
            lines.append(sys.stdin.readline().strip())

    result = []
    last_idx, last_num = None, None
    for i, text in enumerate(lines):
        idx, num = map(int, text.split())
        if last_idx is not None and idx > last_idx:
            if num >= last_num:
                step = (num - last_num) / (idx - last_idx)
            else:
                step = -((last_num - num) / (idx - last_idx))
            for i in xrange(1, idx-last_idx):
                result.append("%d %d" % (last_idx+i, last_num+step*i))
        elif idx == last_idx:
            continue
        result.append("%d %d" % (idx, num))
        last_idx = idx
        last_num = num
    print("\n".join(result))
                

