/*
给定两个只包含数字的数组a, b, 调整数组a里面数字的顺序，使得尽可能多的a[i]>b[i]
数组a和b中的数字各不相同。
输出所有可以达到最优结果的a数组数量
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<int> a(n), b(m);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < m; ++i) cin >> b[i];
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int idxa = 0, idxb = 0, cnt = 0;
        while (idxa < n && idxb < m)
        {
            if (a[idxa] > b[idxb])
            {
                cnt++;
                idxb++;
            }
            else
            {
                idxa++;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}