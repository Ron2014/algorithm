
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
#include <algorithm>
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

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Node
{
public:
    int len;
    vector<int> pass;
    Node():len(MAX_INT) {}
};

#define LEN(grid, i, j)     (grid[max((i),(j))][min((i),(j))].len)
#define PATH(grid, i, j)    (grid[max((i),(j))][min((i),(j))].pass)

void dijkstra(vector<vector<Node>> &grid, int n, int s)
{
    set<int> targets;

    int p = -1;
    for (int i = 0; i <= n; ++i)
    {
        if (i != s)
        {
            targets.insert(i);
            if (p < 0 || LEN(grid, s, i) < LEN(grid, s, p))
            {
                p = i;
            }
        }
    }
    targets.erase(p);

    while (!targets.empty())
    {
        int np = -1;
        for (const int &t : targets)
        {
            if (LEN(grid, s, p) != MAX_INT && LEN(grid, p, t) != MAX_INT)
            {
                int pass_len = LEN(grid, s, p) + LEN(grid, p, t);
                // 如果最短路径有多条，还得提供去重的方法
                // 因为路径可以反过来，假设 5-1 的最短路为 5-3-0-4-1
                // 那么在进行 1-5 的路径规划时，还是 3-0-4，没有反过来
                if (pass_len < LEN(grid, s, t))
                {
                    LEN(grid, s, t) = pass_len;
                    PATH(grid, s, t) = PATH(grid, s, p);
                    PATH(grid, s, t).push_back(p);
                }
                else if (pass_len == LEN(grid, s, t))
                {
                    if (PATH(grid, s, p).size() + 1 > PATH(grid, s, t).size())
                    {
                        // 经过更多的点
                        PATH(grid, s, t) = PATH(grid, s, p);
                        PATH(grid, s, t).push_back(p);
                    }
                }
            }
            if (np < 0 || LEN(grid, s, t) < LEN(grid, s, np))
            {
                np = t;
            }
        }
        p = np;
        targets.erase(p);
    }
}

void dfs(vector<vector<Node>> &grid, int s, int n, set<int> &targets, vector<int> &result, vector<int> &fresult)
{
    if (targets.empty())
    {
        // 回到投递站
        result[0] += LEN(grid, s, 0);
        if (fresult[0] > result[0])
        {
            fresult = result;
        }
        result[0] -= LEN(grid, s, 0);
        return;
    }

    vector<int> backup;
    for (int t = 1; t <= n; ++t)
    {
        if (targets.find(t) == targets.end()) continue;
        if (fresult[0] < result[0] + LEN(grid, s, t)) continue;

        vector<int> &pass = PATH(grid, s, t);
        for (const int &p : pass)
        {
            if (targets.find(p) != targets.end())
            {
                backup.push_back(p);
                targets.erase(p);
            }
            result.push_back(p);
        }
        targets.erase(t);
        result.push_back(t);
        result[0] += LEN(grid, s, t);

        dfs(grid, t, n, targets, result, fresult);

        result[0] -= LEN(grid, s, t);
        result.pop_back();
        targets.insert(t);
        for (const int &p : pass)
        {
            result.pop_back();
        }
        for (const int &p : backup)
        {
            targets.insert(p);
        }
        backup.clear();
    }
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<Node>> grid(n+1);
        for (int i = 0; i <= n; ++i)
        {
            grid[i].resize(i+1);
            grid[i][i].len = 0;
        }
        for (int i = 1; i <= n; ++i)
        {
            cin >> LEN(grid, 0, i);
        }
        for (int i = 0; i < m; ++i)
        {
            int s, e;
            cin >> s >> e;
            cin >> LEN(grid, s, e);
        }
        for (int i = 0; i <= n; ++i)
        {
            dijkstra(grid, n, i);
        }
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                Node &node = grid[i][j];
                cout << "[" << i << "," << j << "]: " << node.len << " ";
                if (node.pass.size() > 0)
                {
                    cout << "[ ";
                    for (auto &idx : node.pass) cout << idx << " ";
                    cout << "]";
                }
                cout << endl;
            }
        }

        vector<int> fresult = {MAX_INT};
        vector<int> result = {0};
        set<int> targets;
        for (int i = 1; i <= n; ++i) targets.insert(i);
        dfs(grid, 0, n, targets, result, fresult);
        for (const int &n : fresult) cout << n << " ";
        cout << endl;
    }
    return 0;
}