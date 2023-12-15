/*
现有一棵无向、无根的树，树中有 n 个节点，按从 0 到 n - 1 编号。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间存在一条边。

每个节点都关联一个价格。给你一个整数数组 price ，其中 price[i] 是第 i 个节点的价格。

给定路径的 价格总和 是该路径上所有节点的价格之和。

另给你一个二维整数数组 trips ，其中 trips[i] = [starti, endi] 表示您从节点 starti 开始第 i 次旅行，并通过任何你喜欢的路径前往节点 endi 。

在执行第一次旅行之前，你可以选择一些 非相邻节点 并将价格减半。

返回执行所有旅行的最小价格总和。

示例1：

输入：n = 4, edges = [[0,1],[1,2],[1,3]], price = [2,2,10,6], trips = [[0,3],[2,1],[2,3]]
输出：23
解释：
上图表示将节点 2 视为根之后的树结构。第一个图表示初始树，第二个图表示选择节点 0 、2 和 3 并使其价格减半后的树。
第 1 次旅行，选择路径 [0,1,3] 。路径的价格总和为 1 + 2 + 3 = 6 。
第 2 次旅行，选择路径 [2,1] 。路径的价格总和为 2 + 5 = 7 。
第 3 次旅行，选择路径 [2,1,3] 。路径的价格总和为 5 + 2 + 3 = 10 。
所有旅行的价格总和为 6 + 7 + 10 = 23 。可以证明，23 是可以实现的最小答案。

示例2：

输入：n = 2, edges = [[0,1]], price = [2,2], trips = [[0,0]]
输出：1
解释：
上图表示将节点 0 视为根之后的树结构。第一个图表示初始树，第二个图表示选择节点 0 并使其价格减半后的树。 
第 1 次旅行，选择路径 [0] 。路径的价格总和为 1 。 
所有旅行的价格总和为 1 。可以证明，1 是可以实现的最小答案。
 

提示：

1 <= n <= 50
edges.length == n - 1
0 <= ai, bi <= n - 1
edges 表示一棵有效的树
price.length == n
price[i] 是一个偶数
1 <= price[i] <= 1000
1 <= trips.length <= 100
0 <= starti, endi <= n - 1
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
    bool dfs4count(int s, int e, int p, vector<unordered_set<int>> &conns, unordered_map<int, int> &counts)
    {
        if (s == e)
        {
            counts[s]++;
            return true;
        }

        for (const int &n : conns[s])
        {
            if (n == p) continue;
            if (dfs4count(n, e, s, conns, counts))
            {
                counts[s]++;
                return true;
            }
        }
        return false;
    }

    void dfs4price(vector<pair<int, int>> &nodes, int idx, vector<bool> &discount, vector<unordered_set<int>> &conns, int result, int &fresult)
    {
        if (idx >= nodes.size())
        {
            if (fresult > result)
            {
                // for (const bool &b : discount)
                // {
                //     printf("%d ", int(b));
                // }
                // cout << endl;
                fresult = result;
            }
            return;
        }

        int more = nodes[idx].first;
        int num = nodes[idx].second;

        // 相邻景点有一个打折了，自己就不能打折
        bool can = true;
        for (const int &n : conns[num])
        {
            if (discount[n])
            {
                can = false;
                break;
            }
        }

        if (discount[num] && (result + (more>>1)) < fresult)
        {
            discount[num] = false;
            result += (more>>1);
            dfs4price(nodes, idx+1, discount, conns, result, fresult);
            result -= (more>>1);
            discount[num] = true;
        }

        if (result + more < fresult)
        {
            result += more;
            dfs4price(nodes, idx+1, discount, conns, result, fresult);
            result -= more;
        }
    }

public:
    int minimumTotalPrice(int n, vector<vector<int>> &edges, vector<int> &price, vector<vector<int>> &trips)
    {
        vector<unordered_set<int>> conns(n);
        for (const auto &v : edges)
        {
            int s = v[0], e = v[1];
            conns[s].insert(e);
            conns[e].insert(s);
        }
        unordered_map<int, int> counts;
        for (const auto &v : trips)
        {
            int s = v[0], e = v[1];
            dfs4count(s, e, -1, conns, counts);
        }
        vector<pair<int, int>> nodes;
        int fresult = 0;        // 全价
        for (const auto &p : counts)
        {
            nodes.emplace_back(p.second * price[p.first], p.first);
            fresult += p.second * price[p.first];
            // printf("%d,%d ", p.first, p.second);
        }
        // cout << endl;
        sort(nodes.begin(), nodes.end(), [](const pair<int, int> &pa, const pair<int, int> &pb)
        {
            return pa.first > pb.first;
        });

        int result = 0;
        vector<bool> discount(n, false);
        dfs4price(nodes, 0, discount, conns, result, fresult);
        return fresult;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n, m;
    while (cin >> n >> m)
    {
        vector<int> price(n, 0);
        vector<vector<int>> edges(n-1, vector<int>(2));
        vector<vector<int>> trips(m, vector<int>(2));

        getchar();
        for (int i = 0; i < n-1; ++i)
        {
            scanf("[%d,%d],", &edges[i][0], &edges[i][1]);
        }

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &price[i]);
        }

        getchar();
        for (int i = 0; i < m; ++i)
        {
            scanf("[%d,%d],", &trips[i][0], &trips[i][1]);
        }

        cout << s.minimumTotalPrice(n, edges, price, trips) << endl;
    }
    return 0;
}