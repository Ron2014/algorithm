/*
算法工程师小明面对着这样一个问题，需要将通信用的信道分配给尽量多的用户：

信道的条件及分配规则如下：

1)     所有信道都有属性：”阶”。阶为r的信道的容量为2^r比特；
2)     所有用户需要传输的数据量都一样：D比特；
3)     一个用户可以分配多个信道，但每个信道只能分配给一个用户；
4)     只有当分配给一个用户的所有信道的容量和>=D，用户才能传输数据；

给出一组信道资源，最多可以为多少用户传输数据？
*/

/**
 * 信道资源数组 r[]，尽量平均分配到达 X*D
 * X 即最多的用户
 * 作业分配问题
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "common.h"
#include <queue>
using namespace std;

int main(int argc, char *argv[])
{
    int D, n;
    while (cin >> D >> n)
    {
        vector<int> r(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> r[i];
            r[i] = 1<<r[i];
        }

        sort(r.begin(), r.end());
        SHOW(r, n);

        int len = 0;
        int cnt = 0;
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            if (r[i]<D)
            {
                sum += r[i];
                len ++;
            }
            else
            {
                cnt++;
            }
        }

        int maxn = sum / D;     // 剩下的最多分配给maxn个用户
        while (maxn > 0)
        {
            if (maxn == 1)
            {
                cnt++;
                break;
            }

            int more = 0;
            priority_queue<int> q;
            for (int i = 0; i < maxn; ++i)
            {
                q.push(0);
            }
            for (int i = len-1; i >= 0; --i)
            {
                int num = q.top();
                q.pop();
                num += r[i];
                q.push(num);
            }
            while (!q.empty())
            {
                int num = q.top();
                q.pop();
                cout << num << " ";
                if (num >= D) more++;
            }
            cout << endl;
            if (more > 0)
            {
                cnt += more;
                break;
            }
            maxn--;
        }

        cout << cnt << endl;
    }
    return 0;
}
