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
    const char *max_bnum(int n)
    {
        static char buf[10];
        for (int i = 0; i < n; ++i)
        {
            buf[i] = '0' + n;
        }
        buf[n] = '\0';
        return buf;
    }

    int num_len(int n)
    {
        int ret = 0;
        while (n > 0)
        {
            n /= 10;
            ret++;
        }
        return ret;
    }

    void extend(unordered_map<int, vector<set<int>>> &mp, int i)
    {
        vector<set<int>> &dst = mp[i];
        for (const set<int> &v : mp[i-1])
        {
            for (const int &n : v)
            {
                if (v.find(n+1) == v.end())
                {
                    dst.push_back(v);
                    dst[dst.size()-1].erase(n);
                    dst[dst.size()-1].insert(n+1);
                }
            }
            if (v.find(1) == v.end())
            {
                dst.push_back(v);
                dst[dst.size()-1].insert(1);
            }
        }
    }

    void fullswap(char *sz, int s, int e, set<int> &dst)
    {
        if (s == e)
        {
            dst.insert(atoi(sz));
            return;
        }
        for (int i = s; i <= e; ++i)
        {
            swap(sz[i], sz[s]);
            fullswap(sz, s+1, e, dst);
            swap(sz[i], sz[s]);
        }
    }

    void gen(vector<set<int>> &groups, set<int> &dst)
    {
        static char buf[10];
        for (const set<int> &v : groups)
        {
            int buf_len = 0;
            for (const int &n : v)
            {
                const char *sz = max_bnum(n);
                strncpy(buf + buf_len, sz, n);
                buf_len += n;
            }
            buf[buf_len] = '\0';
            fullswap(buf, 0, buf_len-1, dst);
        }
    }

public:
    int nextBeautifulNumber(int n)
    {
        int len = num_len(n);
        unordered_map<int, vector<set<int>>> mp1;
        unordered_map<int, set<int>> mp2;
        mp1[1].push_back({1});
        mp2[1].insert(1);

        for (int i = 2; i <= len+1; ++i)
        {
            extend(mp1, i);
            gen(mp1[i], mp2[i]);
        }

        for (int i = len; i <= len+1; ++i)
        {
            for (const int &num : mp2[i])
            {
                if ( num > n) return num;
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