/*
1631. 最小体力消耗路径

你准备参加一场远足活动。

给你一个二维 rows x columns 的地图 heights ，其中 heights[row][col] 表示格子 (row, col) 的高度。

一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1) （注意下标从 0 开始编号）。

你每次可以往 上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。

一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。

请你返回从左上角走到右下角的最小 体力消耗值 。

示例 1：

输入：heights = [[1,2,2],[3,8,2],[5,3,5]]
输出：2
解释：路径 [1,3,5,3,5] 连续格子的差值绝对值最大为 2 。
这条路径比路径 [1,2,2,2,5] 更优，因为另一条路径差值最大值为 3 。

示例 2：

输入：heights = [[1,2,3],[3,8,4],[5,3,5]]
输出：1
解释：路径 [1,2,3,4,5] 的相邻格子差值绝对值最大为 1 ，比路径 [1,3,5,3,5] 更优。

示例 3：

输入：heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
输出：0
解释：上图所示路径不需要消耗任何体力。

提示：

rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 10^6

*/

/*
你想要找到耗费 体力 最小的一条路径
不要求这个路径最短
需要绕路

一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。

可以是深度优先搜索+剪枝
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int di[] = {0,0,1,-1};
const int dj[] = {1,-1,0,0};
const int DIRECT_CNT = 4;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int row = heights.size();
        if (row <= 0) return 0;
        int col = heights[0].size();
        if (col <= 0) return 0;

        auto cmp_fun = [](const tuple<int, int, int> &a, const tuple<int, int, int> &b)
        {
            return get<2>(a) > get<2>(b);
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp_fun)> q(cmp_fun);
        q.emplace(0, 0, 0);

        vector<vector<int>> dist(row, vector<int>(col, INT_MAX));
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        dist[0][0] = 0;

        while (!q.empty())
        {
            auto [i, j, cost] = q.top();
            q.pop();
            if (visited[i][j]) continue;
            if (i == row - 1 && j == col - 1) break;
            visited[i][j] = true;

            for (int k = 0; k < DIRECT_CNT; ++k)
            {
                int ni = i + di[k];
                int nj = j + dj[k];
                if (ni >= 0 && ni < row && nj >= 0 && nj < col)
                {
                    int new_cost = max(cost, abs(heights[ni][nj] - heights[i][j]));
                    if (new_cost < dist[ni][nj])
                    {
                        dist[ni][nj] = new_cost;
                        q.emplace(ni, nj, new_cost);
                    }
                }
            }
        }
        return dist[row-1][col-1];
    }
};

int main()
{
    Solution s;
    int r, c;
    while (cin >> r >> c)
    {
        vector<vector<int>> heights(r, vector<int>(c, 0));
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                cin >> heights[i][j];
            }
        }
        cout << s.minimumEffortPath(heights) << endl;
    }
    return 0;
}
