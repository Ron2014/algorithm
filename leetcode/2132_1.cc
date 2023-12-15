/*
2132. 用邮票贴满网格图

给你一个 m x n 的二进制矩阵 grid ，每个格子要么为 0 （空）要么为 1 （被占据）。

给你邮票的尺寸为 stampHeight x stampWidth 。我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：

覆盖所有 空 格子。
不覆盖任何 被占据 的格子。
我们可以放入任意数目的邮票。
邮票可以相互有 重叠 部分。
邮票不允许 旋转 。
邮票必须完全在矩阵 内 。
如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false 。

示例 1：

输入：grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 4, stampWidth = 3
输出：true
解释：我们放入两个有重叠部分的邮票（图中标号为 1 和 2），它们能覆盖所有与空格子。

示例 2：

输入：grid = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]], stampHeight = 2, stampWidth = 2 
输出：false 
解释：没办法放入邮票覆盖所有的空格子，且邮票不超出网格图以外。

提示：

m == grid.length
n == grid[r].length
1 <= m, n <= 10^5
1 <= m * n <= 2 * 10^5
grid[r][c] 要么是 0 ，要么是 1 。
1 <= stampHeight, stampWidth <= 10^5
*/

#include <iostream>
#include <vector>
#include <queue>
#include "common.h"
using namespace std;

// 右 左 下 上
const int di[] = {0,0,1,-1};
const int dj[] = {1,-1,0,0};
const int DIRECT_CNT = 4;

const int V_NO_STAMP = 0;
const int V_STAMP_HEAD = 1;

class Solution
{
    bool can(vector<vector<int>> &sums, int l, int t, int r, int b)
    {
        int res = 0;
        for (int i = t; i <= b; ++i)
        {
            res += sums[i][r+1] - sums[i][l];
            if (res > 0) return false;
        }
        return true;
    }

    bool is_visited(vector<vector<int>> &vsums, int l, int t, int r, int b)
    {
        int res = 0;
        for (int i = t; i <= b; ++i)
        {
            res += vsums[i][r+1] - vsums[i][l];
            if (res > 0) return true;
        }
        return false;
    }

    void bfs_move(vector<vector<int>> &sums, int l, int t, int m, int n, int stampHeight, int stampWidth, vector<vector<int>> &visited)
    {
        queue<pair<int,int>> q;
        q.emplace(t, l);
        visited[t][l] = V_STAMP_HEAD;

        // 类似推木箱的方法，往四个方向移动
        while (!q.empty())
        {
            auto [si, sj] = q.front();
            q.pop();

            for (int k = 0; k < DIRECT_CNT; ++k)
            {
                int ni = si + di[k];
                int nj = sj + dj[k];
                if (ni < 0 || ni > m - stampHeight || nj < 0 || nj > n - stampWidth) continue;
                if (visited[ni][nj] == V_STAMP_HEAD) continue;
                if (di[k] != 0)
                {
                    int i = ni + ((di[k] < 0) ? 0 : (stampHeight - 1));     // 新增的一行
                    if (!can(sums, nj, i, nj + stampWidth - 1, i)) continue;
                    q.emplace(ni, nj);
                    visited[ni][nj] = V_STAMP_HEAD;
                }
                else
                {
                    int j = nj + ((dj[k] < 0) ? 0 : (stampWidth - 1));      // 新增的一列
                    if (!can(sums, j, ni, j, ni + stampHeight - 1)) continue;
                    q.emplace(ni, nj);
                    visited[ni][nj] = V_STAMP_HEAD;
                }
            }
        }
    }

public:
    bool possibleToStamp(vector<vector<int>> &grid, int stampHeight, int stampWidth)
    {
        int m = grid.size();
        if (m <= 0) return false;
        int n = grid[0].size();
        if (n <= 0) return false;

        vector<vector<int>> sums(m, vector<int>(n+1));                  // 二维前缀和, sums[i][j] 第i行的前j个数的和
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                sums[i][j+1] = sums[i][j] + grid[i][j];
            }
        }

        vector<vector<int>> visited(m, vector<int>(n, V_NO_STAMP));     // 0：没有贴邮票 2：邮票锚点
        for (int t = 0; t <= m - stampHeight; ++t)
        {
            for (int l = 0; l <= n - stampWidth; ++l)
            {
                int r = l + stampWidth - 1, b = t + stampHeight - 1;
                if (visited[t][l] == V_STAMP_HEAD || !can(sums, l, t, r, b)) continue;
                bfs_move(sums, l, t, m, n, stampHeight, stampWidth, visited);
            }
        }

        vector<vector<int>> vsums(m, vector<int>(n+1));                 // 二维前缀和, vsums[i][j] 用于表示一个区域内是否有邮票锚点
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                vsums[i][j+1] = vsums[i][j] + visited[i][j];
            }
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (0 == grid[i][j])
                {
                    if (visited[i][j] != V_STAMP_HEAD)
                    {
                        int l = max(0, j - stampWidth + 1);
                        int t = max(0, i - stampHeight + 1);
                        if (!is_visited(vsums, l, t, j, i))
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main()
{
    Solution so;
    int m, n, h, w;
    while (cin >> m >> n >> h >> w)
    {
        vector<vector<int>> grid(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cin >> grid[i][j];
        cout << int(so.possibleToStamp(grid, h, w)) << endl;
    }
    return 0;
}