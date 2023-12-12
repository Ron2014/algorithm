/*
给定两个只包含数字的数组a, b, 调整数组a里面数字的顺序，使得尽可能多的a[i]>b[i]
数组a和b中的数字各不相同。
输出所有可以达到最优结果的a数组数量
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<int> a(n);
        vector<int> b(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> b[i];
        }
        sort(a.begin(), a.end());

        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i)
        {
            int j = 0;
            while (j < n && a[j] <= b[i]) ++j;
            for (int k = 0; k < n-j; ++k)
            {
                mp[k]++;        // 倒数第n-j 可以放置情况 mp[n-j]
            }
        }

        int cnt = 1;
        for (const auto &p : mp)
        {
            cnt *= p.second;
        }
        int left = n - mp.size();
        while (left > 0)
        {
            cnt *= left;
            left--;
        }
        cout << cnt << endl;
    }
    return 0;
}