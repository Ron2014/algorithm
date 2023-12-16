import sys

def solved(nums, depth):
    num = nums[0]
    if num == 24: return True
    if len(nums)==1: return False

    # 5 ways: 
    # print nums
    nums0 = nums[1:]

    for i, other in enumerate(nums0):
        if other == 24: return True

        nums1 = nums0[:i]
        nums1.extend(nums0[i+1:])

        nums1.append(num + other)
        # print " "*depth, num, "+", other
        if solved(nums1, depth+1): return True
        nums1 = nums1[:-1]

        nums1.append(num * other)
        # print " "*depth, num, "*", other
        if solved(nums1, depth+1): return True
        nums1 = nums1[:-1]

        nums1.append(num - other)
        # print " "*depth, num, "-", other
        if solved(nums1, depth+1): return True
        nums1 = nums1[:-1]

        nums1.append(other - num)
        # print " "*depth, other, "-", num
        if solved(nums1, depth+1): return True
        nums1 = nums1[:-1]

        if (num!=0 and other%num==0):
            nums1.append(other/num)
            # print " "*depth, other, "/", num
            if solved(nums1, depth+1): return True
            nums1 = nums1[:-1]

        if (other!=0 and num%other==0):
            nums1.append(num/other)
            # print " "*depth, num, "/", other
            if solved(nums1, depth+1): return True
            nums1 = nums1[:-1]

    return False


while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    
    lines = line.split()
    nums = map(int, lines)
    if solved(nums, 0):
        print "true"
    else:
        print "false"

