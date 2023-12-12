/*
2477. 到达首都的最少油耗

给你一棵 n 个节点的树（一个无向、连通、无环图），每个节点表示一个城市，编号从 0 到 n - 1 ，且恰好有 n - 1 条路，0 是首都

给你一个二维整数数组 roads ，其中 roads[i] = [ai, bi] ，表示城市 ai 和 bi 之间有一条 双向路 。

每个城市里有一个代表，他们都要去首都参加一个会议。

每座城市里有一辆车。给你一个整数 seats 表示每辆车里面座位的数目。

城市里的代表可以选择乘坐所在城市的车，或者乘坐其他城市的车。相邻城市之间一辆车的油耗是一升汽油。

请你返回到达首都最少需要多少升汽油。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_set>
#include <stack>
#include <set>
using namespace std;

class Solution {
    long long dfs(int s, vector<int> &passed, vector<int> &taken, int seats)
    {
        if (s <= 0)
            return 0;
        int old_num = taken[s];
        taken[s]++;
        return ((old_num % seats == 0) ? 1 : 0) + dfs(passed[s], passed, taken, seats);
    }

    long long dijkstra(vector<vector<int>> &roads, int n, int seats)
    {
        unordered_set<int> targets;
        vector<int> passed(n, -1);                                  // passed[i] 到达i，需经过的城市
        stack<int> orders;
        vector<unordered_set<int>> grids(n);
        vector<int> dist(n, INT_MAX>>1);
        int p, np = -1;

        for (const vector<int> &r : roads)
        {
            grids[r[0]].insert(r[1]);
            grids[r[1]].insert(r[0]);

            if (r[0] == 0)
            {
                passed[r[1]] = 0;
                dist[r[1]] = 1;
                if (np < 0 || dist[np] > dist[r[1]])
                {
                    np = r[1];
                }
            }
            else if (r[1] == 0)
            {
                passed[r[0]] = 0;
                dist[r[0]] = 1;
                if (np < 0 || dist[np] > dist[r[0]])
                {
                    np = r[0];
                }
            }
        }
        p = np;
        dist[0] = 0;
        for (int i = 1; i < n; ++i)
            targets.insert(i);

        while (!targets.empty())
        {
            targets.erase(p);
            orders.push(p);
            np = -1;
            for (const int &t : targets)
            {
                if (grids[p].find(t) != grids[p].end())
                {
                    if (dist[p] + 1 < dist[t])
                    {
                        passed[t] = p;
                        dist[t] = dist[p] + 1;
                    }
                }
                if (np < 0 || dist[np] > dist[t])
                {
                    np = t;
                }
            }
            p = np;
        }

        for (int i = 1; i < n; ++i)
        {
            printf("%2d,%d ", passed[i], dist[i]);
        }
        cout << endl;

        long long result = 0;
        vector<int> taken(n, 0);
        while (!orders.empty())
        {
            int s = orders.top();
            result += dfs(s, passed, taken, seats);
            orders.pop();
        }

        return result;
    }

public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = 0;
        for (int i = 0; i < roads.size(); ++i)
        {
            int s = roads[i][0];
            int e = roads[i][1];
            n = max(n, s);
            n = max(n, e);
        }
        return dijkstra(roads, n+1, seats);
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int m, seats;
    while (cin >> m >> seats)
    {
        vector<vector<int>> roads(m, vector<int>(2));
        for (int i = 0; i < m; ++i)
        {
            cin >> roads[i][0] >> roads[i][1];
        }
        cout << s.minimumFuelCost(roads, seats) << endl;
    }

    return 0;
}