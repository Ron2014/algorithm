/*
快递公司每日早晨，给每位快递员推送需要送到客户手中的快递以及路线信息
快递员自己又查找了一些客户与客户之间的路线距离信息，请你依据这些信息，给快递员设计一条最短路径，告诉他最短路径的距离。

注意：

1.     不限制快递包裹送到客户手中的顺序，但必须保证都送到客户手中
2.     用例保证一定存在投递站到每位客户之间的路线，但不保证客户与客户之间有路线，客户位置及投递站均允许多次经过
3.     所有快递送完后，快递员需回到投递站
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define MAX_INT 2147483647

#define SHOW(a, n)                \
    for (int q = 0; q < (n); ++q) \
    {                             \
        printf("%2d ", (a)[q]);   \
    }                             \
    cout << endl;

#define SHOW_M(a, n, m)                \
    for (int q = 0; q < (n); ++q)      \
    {                                  \
        for (int p = 0; p < (m); ++p)  \
        {                              \
            printf("%10d ", (a)[q][p]); \
        }                              \
        cout << endl;                  \
    }

class Node
{
public:
    int value;
    vector<int> paths;

    Node():value(MAX_INT) {}
    Node(int v):value(v) {}
};

void dfs(vector<Node> &dist, vector<vector<int>> &route, vector<int> &visited, int s, int n, int depth, vector<int> &fresult)
{
    bool all_visited = true;
    vector<int> paths;

    for (int i = 1; i <= n; ++i)
    {
        if (visited[i] > 0) continue;
        all_visited = false;
        if (s > 0)
        {
            if (route[s][i] < dist[s].value + dist[i].value)
            {
                if (fresult.size() > 0 && fresult[n+1] < visited[n+1] + route[s][i])
                {
                    continue;
                }

                // cout << i << " by " << s << endl;
                visited[i] = depth;
                visited[n+1] += route[s][i];

                dfs(dist, route, visited, i, n, depth+1, fresult);

                visited[n+1] -= route[s][i];
                visited[i] = 0;
            }
            else
            {
                if (fresult.size() > 0 && fresult[n+1] < visited[n+1] + dist[s].value + dist[i].value)
                {
                    continue;
                }

                // cout << i << " by " << 0 << endl;
                for (const int &idx: dist[i].paths)
                {
                    if (visited[idx] <= 0)
                    {
                        visited[idx] = depth + paths.size();
                        paths.push_back(idx);
                    }
                }
                visited[i] = depth + paths.size();
                visited[n+1] += dist[s].value + dist[i].value;

                dfs(dist, route, visited, i, n, depth+paths.size()+1, fresult);

                visited[n+1] -= dist[s].value + dist[i].value;
                for (const int &idx : paths) visited[idx] = 0;
                visited[i] = 0;
                paths.clear();
            }
        }
        else
        {
            if (fresult.size() > 0 && fresult[n+1] < visited[n+1] + dist[i].value)
            {
                continue;
            }

            // cout << i << " by " << 0 << endl;
            for (const int &idx: dist[i].paths)
            {
                if (visited[idx] <= 0)
                {
                    visited[idx] = depth + paths.size();
                    paths.push_back(idx);
                }
            }
            visited[i] = depth + paths.size();
            visited[n+1] += dist[i].value;

            dfs(dist, route, visited, i, n, depth+paths.size()+1, fresult);

            visited[n+1] -= dist[i].value;
            for (const int &idx : paths) visited[idx] = 0;
            visited[i] = 0;
            paths.clear();
        }
    }

    if (all_visited)
    {
        visited[n+1] += dist[s].value;
        if (fresult.size() <= 0 || fresult[n+1] > visited[n+1])
        {
            fresult = visited;
        }
    }
}

void dijkstra(vector<int> &source, vector<vector<int>> &route, int n)
{
    vector<Node> dist(n+1);     // dist[i] 到达客户i的最短距离和路径
    dist[0].value = 0;

    int s = -1;
    set<int> targets;
    for (int i = 1; i <= n; ++i)
    {
        dist[i].value = source[i];
        targets.insert(i);
        if (s < 0 || dist[i].value < dist[s].value)
        {
            s = i;
        }
    }
    targets.erase(s);

    while (!targets.empty())
    {
        int ns = -1;
        for (const int &t: targets)
        {
            if (route[s][t] < dist[t].value - dist[s].value)
            {
                dist[t].value = dist[s].value + route[s][t];
                dist[t].paths = dist[s].paths;
                dist[t].paths.push_back(s);
            }
            if (ns < 0 || dist[t].value < dist[ns].value)
            {
                ns = t;
            }
        }
        s = ns;
        targets.erase(s);
    }

    // dfs
    // for (int i = 1; i <= n; ++i)
    // {
    //     targets.insert(i);
    // }

    SHOW(source, n+1);
    SHOW_M(route, n+1, n+1);
    for (int i = 0; i <= n; ++i)
    {
        cout << "[" << i << "] " << dist[i].value << " ";
        if (dist[i].paths.size() > 0)
        {
            cout << "[ ";
            for (const int &idx: dist[i].paths) cout << idx << " ";
            cout << "]";
        }
        cout << endl;
    }

    // return 0;
    vector<int> fresult;
    vector<int> visited(n+2, 0);
    visited[0] = 1;
    dfs(dist, route, visited, 0, n, 2, fresult);

    SHOW(fresult, n+2);
}

int main(int argc, char *argv[])
{
    int n, m;  // n 个客户
    while (cin >> n >> m)
    {
        // 投递站到每个客户的原始距离
        vector<int> source(n+1, 0);
        for (int i = 1; i <= n; ++i)
        {
            cin >> source[i];
        }
        
        // 客户之间的路线
        vector<vector<int>> route(n+1, vector<int>(n+1, MAX_INT));
        for (int i = 1; i <= m; ++i)
        {
            int s, e, d;
            cin >> s >> e >> d;
            route[s][e] = d;
            route[e][s] = d;
        }

        dijkstra(source, route, n);
    }
    return 0;
}
