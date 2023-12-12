/*
一只贪吃的猴子，来到一个果园，发现许多串香蕉排成一行，每串香蕉上有若干根香蕉。
每串香蕉的根数由数组numbers给出。
猴子获取香蕉，每次都只能从行的开头或者末尾获取，并且只能获取N次，求猴子最多能获取多少根香蕉。
*/

/*
    这题要注意猴子每次的选择都可以从两头选
    先算出香蕉总数
    计算滑动窗口 number.size() - N 最小值，即猴子取香蕉的最大值
*/
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int n, N;
    while (cin >> n >> N)
    {
        vector<int> numbers(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> numbers[i];
        }
        // sums[i] 前i个数的和
        vector<int> sums(n+1, 0);
        for (int i = 0; i < n; ++i)
        {
            sums[i+1] = sums[i] + numbers[i];
        }
        if (N >= n)
        {
            cout << sums[n] << endl;
        }
        else
        {
            int maxn = -1;
            for (int i = n-N; i <= n; ++i)
            {
                maxn = max(maxn, sums[n] - (sums[i] - sums[i-(n-N)]));
            }
            cout << maxn << endl;
        }
    }
    return 0;
}