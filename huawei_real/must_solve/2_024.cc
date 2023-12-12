/*
在一个机房中，服务器的位置标识在 n*m 的整数矩阵网格中，1 表示单元格上有服务器，0 表示没有。如果两台服务器位于同一行或者同一列中紧邻的位置，则认为它们之间可以组成一个局域网。
请你统计机房中最大的局域网包含的服务器个数。
*/

/*
BPS
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define SHOW_M(a, n, m)                \
    for (int i = 0; i < (n); ++i)      \
    {                                  \
        for (int j = 0; j < (m); ++j)  \
        {                              \
            printf("%2d ", (a)[i][j]); \
        }                              \
        cout << endl;                  \
    }

int bfs(vector<vector<int>> &grid, int i, int j)
{
    deque<pair<int, int>> servers;
    servers.emplace_back(i, j);

    int count = 0;
    while (!servers.empty())
    {
        pair<int, int> &p = servers.front();
        count++;

        i = p.first;
        j = p.second;
        grid[i][j] = 0;

        if (grid[i-1][j]==1)
        {
            servers.emplace_back(i-1, j);
        }
        if (grid[i+1][j]==1)
        {
            servers.emplace_back(i+1, j);
        }
        if (grid[i][j-1]==1)
        {
            servers.emplace_back(i, j-1);
        }
        if (grid[i][j+1]==1)
        {
            servers.emplace_back(i, j+1);
        }

        servers.pop_front();
    }
    return count;
}

int main(int argc, char *argv[])
{
    int n, m, k, p, q;
    while (cin >> n >> m)
    {
        if (n<=0 || m<=0) break;
        vector<vector<int>> grid(n+2, vector<int>(m+2, 0));

        cin >> k;
        for (int i = 0; i < k; ++i)
        {
            cin >> p >> q;
            if (p < 1 || p > n || q < 1 || q > m)
            {
                cerr << "invalid [p,q]=" << p << "," << q << endl;
                continue;
            }
            grid[p][q] = 1;
        }

        SHOW_M(grid, n+2, m+2)

        int maxn = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (grid[i][j] == 1)
                {
                    int cnt = bfs(grid, i, j);
                    if (cnt > maxn) maxn = cnt;
                }
            }
        }
        cout << maxn << endl;
    }
    return 0;
}