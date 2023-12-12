/*
A、B两个人玩抢7游戏，游戏规则为

A先报一个起始数字X(10<起始数字<10000)，
B报下一个数字Y(X-Y<3),
A再报一个数字Z(Y-Z<3)，
以此类推，直到其中一个抢到7，抢到7即为胜者；

在B赢得比赛的情况下，一共有多少种组合？
*/

/*
dp[i] = dp[i-1] + dp[i-2]
A 出了数字i时，B能赢的组合数

dp[7]=0
dp[8]=dp[9]=1
dp[10]=0
    B:9,8   A胜
dp[11] = 1
    B:10 A:9,8 B:7  B胜
    B:9  A:8,7      A胜
dp[12] = 1
    B:11    A:10    B:9,8 A胜
            A:9     B:8,7 B胜
    B:12    A:11    dp[11] = 1
            A:10    dp[10] = 0
*/

#include <iostream>
#include <vector>
#include "common.h"
using namespace std;

const int MAX_CNT = 2;

int dps(int A, vector<int> &dp)
{
    int cnt = 0;
    for (int i = 1; i <= MAX_CNT; ++i)
    {
        int B = A - i;
        if (B == 7)
        {
            cnt++;
        }
        else
        {
            bool win = true;
            for (int j = 1; j <= MAX_CNT; ++j)
            {
                if (dp[B-j] <= 0) win = false;
            }
            if (win) cnt++;
        }
    }
    return cnt;
}

int main(int argc, char *argv[])
{
    int x;
    while(cin >> x)
    {
        vector<int> dp(x+1);
        dp[7] = 0;
        for (int i = 8; i <= x; ++i)
        {
            dp[i] = dps(i, dp);
        }
        cout << dp[x] << endl;
        SHOW(dp, x+1);
    }
}