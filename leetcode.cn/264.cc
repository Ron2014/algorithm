/*
264. 丑数 II
给你一个整数 n ，请你找出并返回第 n 个 丑数 。

丑数 就是质因子只包含 2、3 和 5 的正整数。

示例 1：

输入：n = 10
输出：12
解释：[1, 2, 3, 4, 5, 6, 8, 9, 10, 12] 是由前 10 个丑数组成的序列。
示例 2：

输入：n = 1
输出：1
解释：1 通常被视为丑数。
 

提示：

1 <= n <= 1690
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n+1);
        dp[1] = 1;
        int p1, p2, p3;
        p1 = p2 = p3 = 1;

        for (int i = 2; i <= n; ++i)
        {
            int n1 = dp[p1]*2, n2 = dp[p2]*3, n3 = dp[p3]*5;
            dp[i] = min(n1, min(n2, n3));
            if (dp[i] == n1) p1++;
            if (dp[i] == n2) p2++;
            if (dp[i] == n3) p3++;
        }
        return dp[n];
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n;
    while (cin >> n)
    {
        cout << s.nthUglyNumber(n) << endl;
    }
}