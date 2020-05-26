# -*- coding:utf-8 -*-
class Solution:
    def Sum_Solution(self, n):
        # write code here
        return n and n + self.Sum_Solution(n-1)

import sys
while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    s = Solution()
    print(s.Sum_Solution(int(line)))
