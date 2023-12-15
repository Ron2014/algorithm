/*
322. 零钱兑换

给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。

示例 1：

输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1
示例 2：

输入：coins = [2], amount = 3
输出：-1
示例 3：

输入：coins = [1], amount = 0
输出：0
 

提示：

1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10^4
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    bool dfs(vector<int> &coins, int idx, int n, int amount, int cnt, int &result)
    {
        if (0 == amount)
        {
            result = min(result, cnt);
            return true;
        }

        if (idx >= n)
        {
            return false;
        }

        int ret = false;
        int max_cnt = amount / coins[idx];
        for (int i = 0; i <= max_cnt; ++i)
        {
            if (cnt + i >= result) break;
            if (dfs(coins, idx+1, n, amount - i * coins[idx], cnt + i, result))
            {
                ret = true;
            }
        }
        return ret;
    }

public:
    int coinChange(vector<int> &coins, int amount)
    {
        // sort(coins.begin(), coins.end(), greater<int>());
        sort(coins.begin(), coins.end());

        int n = coins.size();
        int result = INT_MAX;
        if (dfs(coins, 0, n, amount, 0, result))
        {
            return result;
        }
        return -1;
    }
};

int main()
{
    Solution s;
    int n, amount;
    while (cin >> n >> amount)
    {
        vector<int> coins(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> coins[i];
        }
        cout << s.coinChange(coins, amount) << endl;
    }
    return 0;
}