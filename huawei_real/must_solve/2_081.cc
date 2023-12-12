/*
现需要在某城市进行5G网络建设
已经选取N个地点设置5G基站，编号固定为1到N，接下来需要各个基站之间使用光纤进行连接以确保基站能互联互通
不同基站之间架设光纤的成本各不相同，且有些节点之间已经存在光纤相连

请你设计算法，计算出能联通这些基站的最小成本是多少。

注意：基站的联通具有传递性
入基站A与基站B架设了光纤，基站B与基站C也架设了光纤，则基站A与基站C视为可以互相联通
*/

/*
dijkstra
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "common.h"
using namespace std;

class Node
{
public:
    int s;
    int e;
    int dist;
    Node():s(-1),e(-1),dist(0) {}
    Node(int i, int j, int d):s(i),e(j),dist(d) {}

    bool operator () (const Node &a, const Node &b)
    {
        return a.dist > b.dist;
    }
};

struct CompareNode
{
    bool operator () (const pair<int, int> &a, const pair<int, int> &b) const
    {
        return a.first > b.first;
    }
};

void dijkstra(vector<vector<int>> &weight, int N, int s)
{
    vector<int> distance(N+1, 0);
    vector<bool> visited(N+1, false);
    vector<int> last(N+1, 0);
    visited[s] = true;

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareNode> paths;
    for (int i = 1; i <= N; ++i)
    {
        if (visited[i]) continue;
        distance[i] = weight[s][i] < 0 ? MAX_INT: weight[s][i];
        paths.push({distance[i], i});
        last[i] = s;
    }

    while (!paths.empty())
    {
        const pair<int, int> &node = paths.top();
        int p = node.second;
        distance[p] = node.first;
        visited[p] = true;

        while (!paths.empty()) paths.pop();

        for (int i = 1; i <= N; ++i)
        {
            if (visited[i]) continue;
            if (weight[p][i] >= 0 && distance[p] + weight[p][i] < distance[i])
            {
                // p -> i
                distance[i] = distance[p] + weight[p][i];
                last[i] = p;
            }
            paths.push({distance[i], i});
        }
    }

    SHOW(distance, N+1);
    SHOW(last, N+1);

    int cost = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (last[i] <= 0) continue;
        if (weight[last[i]][i] < 0)
        {
            cost = MAX_INT;
            break;
        }
        cost += weight[last[i]][i];
    }
    cout << cost << endl;
}

int main(int argc, char *argv[])
{
    int N, n;
    while (cin >> N >> n)
    {
        // 已经存在路径，成本为0
        // 不能直连的路径，成本为MAX_INT，表示为-1
        vector<vector<int>> weight(N+1, vector<int>(N+1, -1));

        int mins = -1;
        for (int i = 0; i < n; ++i)
        {
            int s, e;
            cin >> s >> e;
            cin >> weight[s][e];
            weight[e][s] = weight[s][e];
            if (mins < 0) mins = s;
        }

        SHOW_M(weight, N+1, N+1);
        dijkstra(weight, N, mins);
    }
    return 0;
}