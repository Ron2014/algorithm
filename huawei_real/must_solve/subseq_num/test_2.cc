/*
给定一个字符串 S，计算 S 的不同非空子序列的个数。
输入：abc
输出：7
输入：aaa
输出：3

a b c
ab bc ac
abc

a
aa
aaa

*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

int main(int argc, char *argv[])
{
    string S;
    while (cin >> S)
    {
        int len = S.length();
        if (len <= 0) break;

        // dp[i] 表示长度为i的解，也就是S[0:i-1]子串的解
        vector<int> dp(len+1, 0);
        unordered_map<char, int> last;
        dp[0] = 1;// 空字符算1个解

        for (int i = 1; i <= len; ++i)
        {
            dp[i] = dp[i-1] << 1;       // 长度为i-1的解 + 每项加上S[i-1]（因为有空字符，所以这里已经包含单个S[i-1]的情况）
            auto it = last.find(S[i-1]);
            if (it != last.end())
            {
                dp[i] = dp[i] - dp[it->second];
            }
            last[S[i-1]] = i-1;
        }
        cout << dp[len] - 1 << endl;
    }
    return 0;
}