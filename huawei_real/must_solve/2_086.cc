/*
一根X米长的树木，伐木工切割成不同长度的木材后进行交易，交易价格为每根木头长度的乘积。
规定切割后的每根木头长度都为正整数；也可以不切割，直接拿整根树木进行交易。请问伐木工如何尽量少的切割，才能使收益最大化？
*/

/*
    动态规划
*/

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            dp[i] = i;
            for (int j = 1; j < i; ++j)
            {
                dp[i] = max(dp[i], dp[j] * dp[i-j]);
            }
        }
        cout << dp[n] << endl;
    }
    return 0;
}