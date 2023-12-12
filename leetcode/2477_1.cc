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
    long long dfs(int s, int p, vector<set<int>> &conns, int seats, long long &result)
    {
        int num = 1;        // 城市s的代表
        for (const int &n : conns[s])
        {
            if (n != p)
            {
                int more = dfs(n, s, conns, seats, result);     // 从相邻城市n过来的人数
                result += (more + seats - 1) / seats;           // 该人数需要多少台车，每台车对应一升汽油
                num += more;
            }
        }
        return num;         // 从城市s出发的总人数
    }
public:
    long long minimumFuelCost(vector<vector<int>> &roads, int seats) {
        int n = roads.size();
        vector<set<int>> conns(n + 1);
        for (int i = 0; i < n; ++i)
        {
            int s = roads[i][0];
            int e = roads[i][1];
            conns[s].insert(e);
            conns[e].insert(s);
        }
        long long result = 0;
        dfs(0, -1, conns, seats, result);
        return result;
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