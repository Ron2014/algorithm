/*
给定一个包含 0 和 1 的二维矩阵

给定一个初始位置和速度

一个物体从给定的初始位置触发, 在给定的速度下进行移动, 遇到矩阵的边缘则发生镜面反射

无论物体经过 0 还是 1, 都不影响其速度

请计算并给出经过 t 时间单位后, 物体经过 1 点的次数

矩阵以左上角位置为[0, 0](列(x), 行(行)), 例如下面A点坐标为[2, 1] (第二列, 第一行)


+--------------------------- 递增(x)
| 0 0 1 0 0 0 0 1 0 0 0 0
| 0 0 1 0 0 0 0 1 0 0 0 0
| 0 0 1 0 0 0 0 1 0 0 0 0
| 0 0 1 0 0 0 0 1 0 0 0 0
| 0 0 1 0 0 0 0 1 0 0 0 0
| 0 0 1 0 0 0 0 1 0 0 0 0
| 0 0 1 0 0 0 0 1 0 0 0 0
|
递增(y)

注意:

如果初始位置的点是 1, 也计算在内
时间的最小单位为1, 不考虑小于 1 个时间单位内经过的点
*/

#include <iostream>
#include <vector>
#include "common.h"
using namespace std;

int gcd (int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd (b, a % b);
}

int main(int argc, char *argv[])
{
    int n, m, si, sj, vi, vj, t;
    // while (cin >> n >> m)
    // {
    //     cout << gcd(n, m) << endl;
    // }
    while (cin >> si >> sj >> vi >> vj >> t)
    {
    // while (cin >> n >> m)
    // {
        // vector<vector<int>> grid(n, vector<int>(m));
        // for (int i = 0; i < n; ++i)
        // {
        //     for (int j = 0; j < m; j++)
        //     {
        //         cin >> grid[i][j];
        //     }
        // }
        vector<vector<int>> grid = {
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
        };
        n = grid.size();
        m = grid[0].size();

        if (vi != 0 && vj != 0)
        {
            int r = gcd(max(abs(vi), abs(vj)), min(abs(vi), abs(vj)));
            vi = vi / r;
            vj = vj / r;
            t *= r;
        }

        vector<vector<int>> paths(n, vector<int>(m, 0));

        int cnt = 0;
        for (int i = 1; i <= t; ++i)
        {
            int ni = si + vi;
            int nj = sj + vj;

            if (ni < 0)
            {
                ni = -ni;
                vi = -vi;
            }
            else if (ni >= n)
            {
                ni = n - (ni - n) - 1;
                vi = -vi;
            }

            if (nj < 0)
            {
                nj = -nj;
                vj = -vj;
            }
            else if (nj >= m)
            {
                nj = m - (nj - m) - 1;
                vj = -vj;
            }

            if (grid[ni][nj] == 1)
            {
                cnt++;
            }
            paths[ni][nj] = i;
            si = ni;
            sj = nj;
        }

        cout << cnt << endl;
        SHOW_M(grid, n, m);
        SHOW_M(paths, n, m);
    }
    return 0;
}