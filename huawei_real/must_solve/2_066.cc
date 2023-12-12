/*
一张地图上有n个城市，城市和城市之间有且只有一条道路相连：要么直接相连，要么通过其它城市中转相连（可中转一次或多次）。
城市与城市之间的道路都不会成环。

当切断通往某个城市 i 的所有道路后，地图上将分为多个连通的城市群，设该城市 i 的聚集度为 DPi（Degree of Polymerization）
DPi = max(城市群1的城市个数， 城市群2的城市个数, ... 城市群m的城市个数)。

请找出地图上 DP 值最小的城市（即找到城市 j，使得 DPj = min(DP1, DP2 ... DPn) )

提示：如果有多个城市都满足条件，这些城市都要找出来（可能存在多个解）
提示：DPi 的计算，可以理解为已知一棵树，删除某个节点后，生成的多个子树，求解多个子树节点数的问题。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define SHOW(a, n)                \
    for (int q = 0; q < (n); ++q) \
    {                             \
        printf("%2d ", (a)[q]);   \
    }                             \
    cout << endl;

#define SHOW_M(a, n, m)                   \
    for (int q = 0; q < (n); ++q)         \
    {                                     \
        for (int p = 0; p < (m); ++p)     \
        {                                 \
            printf("%2d ", (int)(a)[q][p]); \
        }                                 \
        cout << endl;                     \
    }

int dfs(int s, int n, vector<vector<bool>> &conn, vector<bool> &visited)
{
    visited[s] = true;

    int sum = 1;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i]) continue;
        if (conn[s][i])
        {
            sum += dfs(i, n, conn, visited);
        }
    }

    // visited[s] = false;
    return sum;
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<bool>> conn(n, vector<bool>(n, false));
        for (int k = 0; k < m; ++k)
        {
            int i, j;
            cin >> i >> j;
            conn[i][j] = true;
        }

        SHOW_M(conn, n, n);

        vector<int> dp(n, -1);
        vector<bool> visited(n, false);
        vector<vector<bool>> nconn = conn;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                nconn[i][j] = false;
                nconn[j][i] = false;
            }

            // 断开i之后，城市聚集度
            for (int j = 0; j < n; ++j)
            {
                if (i == j) continue;
                dp[i] = max(dp[i], dfs(j, n, nconn, visited));
                visited.assign(n, false);
            }

            // bug_found: 重复计算的次数很高
            // 可在断开前，算好各节点DP值和父节点（入度）信息

            for (int j = 0; j < n; ++j)
            {
                nconn[i][j] = conn[i][j];
                nconn[j][i] = conn[j][i];
            }
        }

        int mindp = -1;
        vector<int> result;
        for (int i = 0; i < n; ++i)
        {
            printf("%d: %d\n", i, dp[i]);
            if (mindp < 0 || dp[i] < mindp)
            {
                result = {i};
                mindp = dp[i];
            }
            else if (dp[i] == mindp)
            {
                result.push_back(i);
            }
        }
    }
    return 0;
}