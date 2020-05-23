import sys

max_sum = 0

def isPrime(num):
    for i in xrange(2, num/2):
        if num%i==0: return False
    return True

def getMaxPair(short_num, short_len, long_num, long_len):
    match_list = []
    short_matches = {}
    long_matches = {}

    for i in xrange(short_len):
        sn = short_num[i]
        for j in xrange(long_len):
            ln = long_num[j]
            if isPrime(sn+ln):
                match = short_matches.setdefault(i, set([]))
                match.add(j)
                match = long_matches.setdefault(j, set([]))
                match.add(i)
    
    # print(short_matches)

    for i in xrange(short_len):
        match_list.append((i, short_matches.get(i, set([]))))
    match_list = sorted(match_list, key=lambda x: len(x[1]))

    sum = 0
    for node in match_list:
        si, smatch = node
        if smatch:
            minlmatch = None
            for lj in smatch:
                lmatch = long_matches.get(lj)
                if minlmatch is None:
                    minlmatch = lmatch
                elif len(lmatch) < len(minlmatch):
                    minlmatch = lmatch
            for mi in minlmatch:
                short_matches[mi].discard(lj)
            sum += 1
    print(sum)

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    count = int(lines[0])

    if len(lines) > 1:
        nums = map(int, lines[1])
    else:
        nums = map(int, sys.stdin.readline().strip().split())

    max_sum = 0
    nums_odd = []
    nums_even = []
    for n in nums:
        if n%2:
            nums_odd.append(n)
        else:
            nums_even.append(n)
    
    count_odd = len(nums_odd)
    count_even = len(nums_even)

    if count_odd < count_even:
        # print("odd is short")
        getMaxPair(nums_odd, count_odd, nums_even, count_even)
    else:
        # print("even is short")
        getMaxPair(nums_even, count_even, nums_odd, count_odd)

    
