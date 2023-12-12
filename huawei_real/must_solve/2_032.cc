/*
部门在进行需求开发时需要进行人力安排。
当前部门需要完成N个需求，需求用requirements[]表示，requirements[i]表示第i个需求的工作量大小，单位：人月。
这部分需求需要在M个月内完成开发，进行人力安排后每个月的人力是固定的。

目前要求每个月最多有2个需求开发，并且每个月需要完成的需求不能超过部门人力。
请帮部门评估在满足需求开发进度的情况下，每个月需要的最小人力是多少？
*/

/*
设每个月人力为X，M个月能完成的需求为 X*M，要求
    1. X*M >= sum(requiremenets[])
    2. X上限：最高的两个需求和（每月两个需求）
    3. X下限：最高的需求（每月一个需求）
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    int N, M;
    while (cin >> N >> M)
    {
        if (N <= 0 || M <= 0) break;

        vector<int> requirements(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> requirements[i];
        }

        if (N == 1)
        {
            cout << requirements[0] << endl;
            continue;
        }

        int sum = 0;
        for (int i = 0; i < N; ++i)
        {
            sum += requirements[i];
        }

        sort(requirements.begin(), requirements.end());

        int s = requirements[N-1];
        int e = requirements[N-1] + requirements[N-2];
        int prev = -1;
        while (s <= e)
        {
            int m = (s+e)>>1;
            if (m*M == sum)
            {
                prev = m;
                break;
            }
            else if (m*M > sum)
            {
                prev = m;
                e = m - 1;
            }
            else
            {
                s = m + 1;
            }
        }
        if (prev > 0)
        {
            cout << prev << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}