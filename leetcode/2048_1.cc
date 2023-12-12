/*
2048. 下一个更大的数值平衡数

如果整数  x 满足：对于每个数位 d ，这个数位 恰好 在 x 中出现 d 次。那么整数 x 就是一个 数值平衡数 。

给你一个整数 n ，请你返回 严格大于 n 的 最小数值平衡数 。

示例 1：

输入：n = 1
输出：22
解释：
22 是一个数值平衡数，因为：
- 数字 2 出现 2 次 
这也是严格大于 1 的最小数值平衡数。

示例 2：

输入：n = 1000
输出：1333
解释：
1333 是一个数值平衡数，因为：
- 数字 1 出现 1 次。
- 数字 3 出现 3 次。 
这也是严格大于 1000 的最小数值平衡数。
注意，1022 不能作为本输入的答案，因为数字 0 的出现次数超过了 0 。

示例 3：

输入：n = 3000
输出：3133
解释：
3133 是一个数值平衡数，因为：
- 数字 1 出现 1 次。
- 数字 3 出现 3 次。 
这也是严格大于 3000 的最小数值平衡数。
 

提示：

0 <= n <= 106
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <cstring>
using namespace std;

class Solution {
    int num_len(int n)
    {
        int ret = 0;
        while (n > 0)
        {
            ret++;
            n /= 10;
        }
        return ret;
    }

    int max_bnum(int n)
    {
        char buf[10];
        for (int i = 0; i < n; ++i)
        {
            buf[i] = '0' + n;
        }
        buf[n] = '\0';
        return atoi(buf);
    }

    bool is_balance(int n)
    {
        vector<int> cnts(10, 0);
        while (n > 0)
        {
            cnts[n%10]++;
            n /= 10;
        }
        for (int i = 0; i < 10; ++i)
        {
            if (cnts[i] > 0 && cnts[i] != i) return false;
        }
        return true;
    }

public:
    int nextBeautifulNumber(int n)
    {
        int len = num_len(n);
        int maxn = max_bnum(len+1);
        for (int i = n+1; i <= maxn; ++i)
        {
            if (is_balance(i) && i > n)
            {
                return i;
            }
        }
        return -1;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n;
    while (cin >> n)
    {
        cout << s.nextBeautifulNumber(n) << endl;
    }
    return 0;
}