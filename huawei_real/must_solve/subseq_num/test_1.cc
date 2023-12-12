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

        // 表示以字符 S[i] 结尾的不同子序列的个数。
        vector<int> dp(len, 0);
        unordered_map<char, int> more;

        for (int i = 0; i < len; ++i)
        {
            if (i == 0)
            {
                dp[i] = 1;
                more[S[i]] = 1;
            }
            else
            {
                dp[i] = dp[i-1] + dp[i-1] + 1;      // 长度为1~i-1的解 + 每项加上S[i] + S[i]独立字符
                dp[i] -= more[S[i]];                // 遇到S[i]字符累计增加的解的数量，这些数量会导致重复
                more[S[i]] += dp[i] - dp[i-1];
            }
        }
        cout << dp[len-1] << endl;
    }
    return 0;
}

/*
如例子aaa
i = 0
    dp[0] = 1
    a
i = 1
    dp[1] = dp[0]的解 + dp[0]解每项都加上字符a + a字符，就会得到
    a | aa | a
    发现多了一个a，这个a是计算dp[0]的时候新增的子序列，所以去掉，即公式等于
    dp[1] = dp[0]的解 + dp[0]解每项都加上字符a + a字符 - more['a']，才能得到去重的
    a aa
i = 2
    dp[2] = dp[1]的解 + dp[1]解每项都加上字符a + a字符，就会得到
    a aa | aa aaa | a
    发现这里多了两项 aa 和 a
    aa 是计算dp[1]时新增的子序列，a 是计算dp[0]时新增的子序列
    由此可推出 more['a'] 是个累计值，公式依然调整为
    dp[2] = dp[1]的解 + dp[1]解每项都加上字符a + a字符 - more['a']，去重后得到
    a aa aaa
*/
