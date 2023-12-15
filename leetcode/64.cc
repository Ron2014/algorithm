/*
64. 最小路径和
给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

示例 1：

输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。

示例 2：

输入：grid = [[1,2,3],[4,5,6]]
输出：12

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 200
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

const int di[] = {0,1};
const int dj[] = {1,0};
const int DIRECT_CNT = 2;
#define MAX_INT 2147483647

class Solution {
    void dfs(vector<vector<int>> &grid, int m, int n, int si, int sj, int result, vector<vector<int>> &record)
    {
        if (result + grid[si][sj] >= record[si][sj]) return;

        result += grid[si][sj];
        record[si][sj] = result;

        for (int k = 0; k < DIRECT_CNT; ++k)
        {
            int ni = si + di[k];
            int nj = sj + dj[k];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n)
            {
                dfs(grid, m, n, ni, nj, result, record);
            }
        }

        result -= grid[si][sj];
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int fresult = 0;
        int m = grid.size();
        if (m <= 0) return fresult;
        int n = grid[0].size();
        if (n <= 0) return fresult;

        vector<vector<int>> record(m, vector<int>(n, MAX_INT));
        int result = 0;
        dfs(grid, m, n, 0, 0, result, record);
        return record[m-1][n-1];
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int m, n;
    while (cin >> m >> n)
    {
        vector<vector<int>> grid(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> grid[i][j];
            }
        }
        cout << s.minPathSum(grid) << endl;
    }
    return 0;
}
