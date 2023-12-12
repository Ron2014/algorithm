/*
一只贪吃的猴子，来到一个果园，发现许多串香蕉排成一行，每串香蕉上有若干根香蕉。
每串香蕉的根数由数组numbers给出。
猴子获取香蕉，每次都只能从行的开头或者末尾获取，并且只能获取N次，求猴子最多能获取多少根香蕉。
*/

/*
1. 如果获取的方式可以不连续
将numbers排序，解为最大的N个数的和

2. 如果获取的方式必须是连续的
滑动窗口，取最大的值
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int get_connected_answer(vector<int> &numbers, int n, int N)
{
    int maxn = 0;
    for (int i = 0; i < N; ++i)
    {
        maxn += numbers[i];
    }
    int sum = maxn;
    for (int i = N; i < n; ++i)
    {
        sum -= numbers[i-N];
        sum += numbers[i];
        if (sum > maxn) maxn = sum;
    }
    return maxn;
}

int get_nonconnected_answer(vector<int> &numbers, int n, int N)
{
    int sum = 0;
    sort(numbers.begin(), numbers.end(), greater<int>());
    vector<int>::iterator it = numbers.begin();
    while (N-->0 && it != numbers.end())
    {
        sum += *it;
        ++it;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    int n, N;
    while (cin >> n)
    {
        vector<int> numbers(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> numbers[i];
        }
        cin >> N;
        cout << get_connected_answer(numbers, n, N) << endl;
        cout << get_nonconnected_answer(numbers, n, N) << endl;
    }
    return 0;
}