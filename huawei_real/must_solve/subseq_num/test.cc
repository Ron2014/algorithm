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
using namespace std;

void dfs(const char *sz, char *temp, int idx, int len, set<string> &result)
{
    if (idx >= len)
    {
        temp[len] = '\0';
        result.insert(temp);
        return;
    }
    if (*sz == '\0') return;

    temp[idx] = *sz;
    dfs(sz+1, temp, idx+1, len, result);

    dfs(sz+1, temp, idx, len, result);
}

// dp[i] dp[i-1] 源字符串长度，dp[i]
// dp[i-1]
// 1 2 .. i-1
// s[i]
// 1 + 1
// 2 = 1 ..s[i]
// 3 = 2 ..s[i]

int main(int argc, char *argv[])
{
    string s;
    while (cin >> s)
    {
        int len = s.length();
        if (len <= 0) break;

        char temp[1001];
        set<string> result;
        for (int i = 1; i <= len; ++i)
        {
            dfs(s.c_str(), temp, 0, i, result);
        }
        for (const string &sub : result)
        {
            cout << sub << endl;
        }
    }
    return 0;
}