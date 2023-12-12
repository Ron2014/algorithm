/*
题目描述：
中秋节，公司分月饼，m个员工，买了n个月饼，m<=n，每个员工至少分1个月饼，但可以分多个，单人分到最多月饼的个数是Max1，单人分到第二多月饼个数是Max2
Max1-Max2 <= 3，单人分到第n-1多月饼个数是Max(n-1)，单人分到第n多月饼个数是Max(n)，Max(n-1)–Max(n)<=3

问有多少种分月饼的方法
*/

#include <iostream>
#include <vector>
using namespace std;
std::vector<int> vec;

int get_count(int n, int m, int minn, int maxn, int idx)
{
    if (n <= 0 || m <= 0)
    {
        return 0;
    }

    if (m == 1)
    {
        if (n < minn || n > maxn)
        {
            return 0;
        }
        for (int &num : vec)
        {
            cout << num << " ";
        }
        cout << n << endl;
        return 1;
    }

    int count = 0;
    for (int i = minn; i <= maxn; ++i)
    {
        // 第idx个额外得i个
        vec.push_back(i);
        count += get_count(n-i, m-1, i, i+3, idx+1);
        vec.pop_back();
    }
    return count;
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        if (n < m)
        {
            cout << -1 << endl;
        }
        else if (n == m)
        {
            cout << 1 << endl;
        }
        else
        {
            int avg = n/m;
            int count = get_count(n, m, 1, avg, 0);
            cout << count << endl;
        }
    }
    return 0;
}