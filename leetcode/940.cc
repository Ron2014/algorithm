/*
940. 不同的子序列 II

给定一个字符串 s，计算 s 的 不同非空子序列 的个数。因为结果可能很大，所以返回答案需要对 10^9 + 7 取余 。

字符串的 子序列 是经由原字符串删除一些（也可能不删除）字符但不改变剩余字符相对位置的一个新字符串。

例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是。
 

示例 1：

输入：s = "abc"
输出：7
解释：7 个不同的子序列分别是 "a", "b", "c", "ab", "ac", "bc", 以及 "abc"。
示例 2：

输入：s = "aba"
输出：6
解释：6 个不同的子序列分别是 "a", "b", "ab", "ba", "aa" 以及 "aba"。
示例 3：

输入：s = "aaa"
输出：3
解释：3 个不同的子序列分别是 "a", "aa" 以及 "aaa"。
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <cmath>
using namespace std;

const int MOD = pow(10, 9) + 7;

#define DO_MOD(x) (x)%MOD

class Solution {
public:
    int distinctSubseqII(string s) {
        int len = s.length();

        // dp[i] 表示长度为i的解，也就是S[0:i-1]子串的解
        vector<long long> dp(len+1, 0);
        unordered_map<char, int> last;
        dp[0] = 1;// 空字符算1个解

        for (int i = 1; i <= len; ++i)
        {
            auto it = last.find(s[i-1]);
            if (it != last.end())
            {
                dp[i] = DO_MOD(dp[i-1] * 2 - dp[it->second]);
            }
            else
            {
                dp[i] = DO_MOD(dp[i-1] * 2);
            }
            last[s[i-1]] = i-1;
        }
        return DO_MOD(dp[len] - 1);
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    string S;
    while (cin >> S)
    {
        int len = S.length();
        if (len <= 0) break;

        cout << s.distinctSubseqII(S) << endl;

    }
    return 0;
}