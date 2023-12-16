import sys

def getSumFromNum(nums, sum):
    if not nums: return False
    
    for i, n in enumerate(nums):
        if n==sum:
            return True
        nums1 = nums[:i]
        nums1.extend(nums[i+1:])
        if (getSumFromNum(nums1, sum-n)): return True

    return False


while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    cout = int(lines[0])

    if len(lines) > 1:
        nums = map(int, lines[1:])
    else:
        nums = map(int, sys.stdin.readline().strip().split())

    if sum(nums)%2:
        print "false"
    else:
        half = sum(nums) / 2
    
        others = []
        group3 = []
        group5 = []

        for n in nums:
            if n%3 == 0:
                group3.append(n)
            elif n%5 == 0:
                group5.append(n)
            else:
                others.append(n)
        
        left3 = half - sum(group3)
        
        # print group3
        # print group5
        # print others
        # print left3
        
        if getSumFromNum(others, left3):
            print "true"
        else:
            print "false"
        
