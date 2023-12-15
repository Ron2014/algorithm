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

class Solution
{
    void bfs_move(vector<vector<bool>> &dp, int l, int t, int m, int n, int stampHeight, int stampWidth, vector<vector<bool>> &visited, int &vcnt)
    {
        queue<pair<int,int>> q;
        q.emplace(t, l);

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
                if (visited[ni][nj]) continue;

                int s = ni * n + nj, e;
                if (di[k] != 0)
                {
                    e = ni * n + nj + stampWidth - 1;       // 上/下
                }
                else
                {
                    e = (ni + stampHeight - 1) * n + nj;    // 左/右
                }
                if (!dp[s][e]) continue;

                if (di[k] != 0)
                {
                    // 上/下 横向
                    int more_i = ni + ((di[k] < 0) ? 0 : (stampHeight - 1));
                    for (int j = nj; j <= nj + stampWidth - 1; ++j)
                    {
                        vcnt++;
                        visited[more_i][j] = true;
                    }
                }
                else
                {
                    // 上/下 纵向
                    int more_j = nj + ((dj[k] < 0) ? 0 : (stampWidth - 1));
                    for (int i = ni; i <= ni + stampHeight - 1; ++i)
                    {
                        vcnt++;
                        visited[i][more_j] = true;
                    }
                }
                q.emplace(ni, nj);
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

        int cnt = m * n;
        vector<vector<bool>> dp(cnt, vector<bool>(cnt, false));
        for (int i = cnt - 1; i >= 0; --i)
        {
            int si = i / n;
            int sj = i % n;
            for (int j = i; j < cnt; ++j)
            {
                int ei = j / n;
                int ej = j % n;
                if (i == j)
                {
                    dp[i][j] = (grid[ei][ej] == 0);
                }
                else if (si == ei)
                {
                    dp[i][j] = (grid[ei][ej] == 0) && dp[i][j-1];
                }
                else if (sj == ej)
                {
                    dp[i][j] = (grid[ei][ej] == 0) && dp[i][j-n];
                }
                else if (sj > ej)
                {
                    dp[i][j] = false;
                }
                else
                {
                    dp[i][j] = (grid[ei][ej] == 0) && dp[i][j-1] && dp[si * n + ej - 1][j-n];
                }
            }
        }

        // SHOW_M(dp[i][j], cnt, cnt);

        int vcnt = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                visited[i][j] = grid[i][j] > 0;
                vcnt += grid[i][j] > 0;
            }
        }

        for (int t = 0; t <= m - stampHeight; ++t)
        {
            for (int l = 0; l <= n - stampWidth; ++l)
            {
                int r = l + stampWidth - 1, b = t + stampHeight - 1;
                int s = t * n + l;
                int e = b * n + r;
                if (dp[s][e] && !visited[t][l])
                {
                    bfs_move(dp, l, t, m, n, stampHeight, stampWidth, visited, vcnt);

                    for (int i = t; i <= b; ++i)
                    {
                        for (int j = l; j <= r; ++j)
                        {
                            if (visited[i][j]) continue;
                            vcnt++;
                            visited[i][j] = true;
                        }
                    }
                }
            }
        }
        return vcnt >= cnt;
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