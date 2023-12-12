/*
M（1<=M <=20）辆车需要在一条不能超车的单行道到达终点，起点到终点的距离为N（1<=N<=400）。
速度快的车追上前车后，只能以前车的速度继续行驶，求最后一车辆到达目的地花费的时间。
注：每辆车固定间隔1小时出发，比如第一辆车0时出发，第二辆车1时出发，依次类推
*/

/**
 * 模拟
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "common.h"
using namespace std;

int main(int argc, char *argv[])
{
    int M, N;
    while (cin >> M >> N)
    {
        vector<int> v(M+1);
        for (int i = 1; i <= M; ++i)
        {
            cin >> v[i];
        }

        vector<int> dists(M+1, 0);

        int hours = 0;
        while (dists[M] < N)
        {
            hours++;
            for (int i = 1; i <= M && i <= hours; ++i)
            {
                dists[i] += v[i] * 1;
                if (i > 1 && dists[i-1] <= N)
                {
                    dists[i] = min(dists[i], dists[i-1]);
                }
            }
            dists[0] = hours;
            SHOW(dists, M+1);
        }
        cout << hours << endl;
    }
    return 0;
}