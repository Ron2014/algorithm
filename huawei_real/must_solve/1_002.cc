/*
给定一个数组，编写一个函数来计算它的最大N个数与最小N个数的和

你需要对数组进行去重。

说明：
    *数组中数字范围[0, 1000]
    *最大N个数与最小N个数不能有重叠，如有重叠，输入非法返回-1
    *输入非法返回-1
*/

#include <iostream>
#include <set>
using namespace std;

int main(int argc, char *argv[])
{
    int n, N;
    while (cin >> n)
    {
        set<int> nums;
        for (int i = 0; i < n; ++i)
        {
            cin >> N;
            nums.insert(N);
        }
        cin >> N;
        if (N<<1 > nums.size())
        {
            cout << -1 << endl;
            continue;;
        }
        int sum = 0;
        int count = 0;
        for (set<int>::reverse_iterator it = nums.rbegin(); it != nums.rend(); ++it)
        {
            sum += *it;
            if (++count == N) break;
        }
        count = 0;
        for (set<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        {
            sum += *it;
            if (++count == N) break;
        }
        cout << sum << endl;
    }
    return 0;
}