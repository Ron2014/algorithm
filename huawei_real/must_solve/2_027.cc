/*
一个局域网内有很多台电脑，分别标注为0 - N-1的数字。相连接的电脑距离不一样，所以感染时间不一样，感染时间用t表示。
其中网络内一个电脑被病毒感染，其感染网络内所有的电脑需要最少需要多长时间。如果最后有电脑不会感染，则返回-1
给定一个数组times表示一个电脑把相邻电脑感染所用的时间。
如图：path[i]= {i,j, t} 表示电脑i->j 电脑i上的病毒感染j，需要时间t。
*/

#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

const int MAX_INT = 2147483647;

int min_path_dijkstra(vector<vector<int>> &times, int s, int N)
{
    vector<int> distance(N, MAX_INT);   // 从原点到达所有节点的最短距离
    distance[s] = 0;

    set<int> targets;                   // 目标节点，首先排除起点
    for (int i = 0; i < N; ++i)
    {
        if (i != s) targets.insert(i);
    }

    while (targets.size() > 0)
    {
        int news = -1;
        for (const int &t : targets)
        {
            if (times[s][t] > 0)
            {
                distance[t] = min(distance[t], distance[s] + times[s][t]);
            }

            // 离原点最近的目标，作为下一轮计算的起点
            if (news < 0 || distance[news] > distance[t])
            {
                news = t;
            }
        }
        s = news;
        if (s >= 0)
        {
            targets.erase(s);
        }
        else
        {
            break;
        }
    }

    int maxn = -1;
    for (int i = 0; i < N; ++i)
    {
        cout << "[" << i << "]=" << distance[i] << endl;
        maxn = max(maxn, distance[i]);
    }
    if (maxn == MAX_INT) return -1;
    return maxn;
}

int main(int argc, char *argv[])
{
    int N, p, i, j, t, k, s;
    while (cin >> N)
    {
        vector<vector<int>> times(N, vector<int>(N, -1));
        cin >> p;
        for (k = 0; k < p; ++k)
        {
            cin >> i >> j >> t;
            times[i][j] = t;
        }
        cin >> s;
        cout << min_path_dijkstra(times, s, N) << endl;
    }
    return 0;
}