/*
小华和小为是很要好的朋友，他们约定周末一起吃饭。
通过手机交流，他们在地图上选择了多个聚餐地点（由于自然地形等原因，部分聚餐地点不可达），求小华和小为都能到达的聚餐地点有多少个？
*/


#include <iostream>
#include <vector>
#include <deque>
using namespace std;

const int FORBID    = -1;
const int TARGET    = -2;

const int di[] = {0, 0, 1, -1};
const int dj[] = {1, -1, 0, 0};
const int DIRECT_CNT = 4;

#define SHOW_M(a, n, m)               \
    for (int i = 0; i < (n); ++i)     \
    {                                 \
        for (int j = 0; j < (m); ++j) \
        {                             \
            printf("%2d ", a[i][j]);  \
        }                             \
        cout << endl;                 \
    }

class Node
{
public:
    int i, j, steps;
    Node():i(-1),j(-1),steps(0) {}
    Node(int i, int j, int s):i(i),j(j),steps(s) {}
};

int bfs(vector<vector<int>> &grid, int n, int m, int si0, int sj0, int si1, int sj1)
{
    deque<Node> paths;
    vector<vector<int>> targets = grid;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (targets[i][j] == TARGET) targets[i][j] = 0;
        }
    }
    SHOW_M(grid, n+2, m+2);
    SHOW_M(targets, n+2, m+2);

    cout << "------ " << si0 << "," << sj0 << endl;
    paths.emplace_back(si0, sj0, 0);
    while (!paths.empty())
    {
        Node &node = paths.front();
        targets[node.i][node.j] = min(1, targets[node.i][node.j] + 1);
        if (grid[node.i][node.j] != TARGET)
        {
            grid[node.i][node.j] = node.steps;
            for (int k = 0; k < DIRECT_CNT; ++k)
            {
                int ni = node.i + di[k];
                int nj = node.j + dj[k];
                if (grid[ni][nj] == FORBID) continue;
                if (targets[ni][nj] > 0) continue;
                paths.emplace_back(ni, nj, node.steps + 1);
            }
        }
        paths.pop_front();
    }
    SHOW_M(grid, n+2, m+2);
    SHOW_M(targets, n+2, m+2);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (grid[i][j] > 0) grid[i][j] = 0;
        }
    }

    cout << "------ " << si1 << "," << sj1 << endl;
    paths.emplace_back(si1, sj1, 0);
    while (!paths.empty())
    {
        Node &node = paths.front();
        targets[node.i][node.j] = min(2, targets[node.i][node.j] + 1);
        if (grid[node.i][node.j] != TARGET)
        {
            grid[node.i][node.j] = node.steps;
            for (int k = 0; k < DIRECT_CNT; ++k)
            {
                int ni = node.i + di[k];
                int nj = node.j + dj[k];
                if (grid[ni][nj] == FORBID) continue;
                if (targets[ni][nj] > 1) continue;
                paths.emplace_back(ni, nj, node.steps + 1);
            }
        }
        paths.pop_front();
    }
    SHOW_M(grid, n+2, m+2);
    SHOW_M(targets, n+2, m+2);

    int count = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (grid[i][j] == TARGET && targets[i][j] == 2) count++;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<int>> grid(n+2, vector<int>(m+2, 0));
        for (int i = 0; i < n+2; ++i)
        {
            grid[i][0] = grid[i][m+1] = -1;
        }
        for (int i = 0; i < m+2; ++i)
        {
            grid[0][i] = grid[n+1][i] = -1;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                cin >> grid[i][j];
            }
        }
        int si0, sj0, si1, sj1;
        cin >> si0 >> sj0 >> si1 >> sj1;
        cout << bfs(grid, n, m, si0, sj0, si1, sj1) << endl;
    }
    return 0;
}