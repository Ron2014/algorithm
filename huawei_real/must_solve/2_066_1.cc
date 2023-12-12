#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

#define SHOW(a, n)                \
    for (int i = 0; i < (n); ++i) \
    {                             \
        printf("%d ", a[i]);      \
    }                             \
    cout << endl;

int dijkstra(int s, int n, vector<vector<bool>> &conn)
{
    int sum = 0;
    vector<bool> visited(n, false);
    deque<int> targets;
    targets.push_back(s);
    visited[s] = true;

    while (!targets.empty())
    {
        int p = targets.front();
        sum ++;
        for (int i = 0; i < n; ++i)
        {
            if (conn[p][i] && !visited[i])
            {
                targets.push_back(i);
                visited[i] = true;
            }
        }
        targets.pop_front();
    }

    return sum;
}

int dfs(int s, int n, vector<vector<bool>> &conn, vector<int> dp)
{
    int lost = dp[s];

    vector<bool> visited(n, false);
    deque<int> targets;
    targets.push_back(s);
    visited[s] = true;

    while (!targets.empty())
    {
        int p = targets.front();
        dp[p] -= lost;

        for (int i = 0; i < n; ++i)
        {
            if (conn[i][p] && !visited[i])
            {
                // bug_found: 除非 i 只有一条路径 conn[i][p]
                // 否则 dp[p] 不一定会影响到 dp[i]
                targets.push_back(i);
                visited[i] = true;
            }
        }
        targets.pop_front();
    }

    return *max_element(dp.begin(), dp.end());
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<int> dp(n);
        vector<vector<bool>> conn(n, vector<bool>(n, false));

        for (int k = 0; k < m; ++k)
        {
            int i, j;
            cin >> i >> j;
            conn[i][j] = true;
        }

        for (int i = 0; i < n; ++i)
        {
            dp[i] = dijkstra(i, n, conn);
        }

        SHOW(dp, n);

        int mindp = -1;
        vector<int> result;
        for (int i = 0; i < n; ++i)
        {
            int mdp = dfs(i, n, conn, dp);
            printf("%d: %d\n", i, mdp);
            if (mindp < 0 || mdp < mindp)
            {
                mindp = mdp;
                result = {i};
            }
            else if (mdp == mindp)
            {
                result.push_back(i);
            }
        }
    }
    return 0;
}