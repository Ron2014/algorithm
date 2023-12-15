/*
1582. 二进制矩阵中的特殊位置

给你一个大小为 rows x cols 的矩阵 mat，其中 mat[i][j] 是 0 或 1，请返回 矩阵 mat 中特殊位置的数目 。

特殊位置 定义：如果 mat[i][j] == 1 并且第 i 行和第 j 列中的所有其他元素均为 0（行和列的下标均 从 0 开始 ），则位置 (i, j) 被称为特殊位置。

 

示例 1：

输入：mat = [[1,0,0],
            [0,0,1],
            [1,0,0]]
输出：1
解释：(1,2) 是一个特殊位置，因为 mat[1][2] == 1 且所处的行和列上所有其他元素都是 0
示例 2：

输入：mat = [[1,0,0],
            [0,1,0],
            [0,0,1]]
输出：3
解释：(0,0), (1,1) 和 (2,2) 都是特殊位置
示例 3：

输入：mat = [[0,0,0,1],
            [1,0,0,0],
            [0,1,1,0],
            [0,0,0,0]]
输出：2
示例 4：

输入：mat = [[0,0,0,0,0],
            [1,0,0,0,0],
            [0,1,0,0,0],
            [0,0,1,0,0],
            [0,0,0,1,1]]
输出：3
 

提示：

rows == mat.length
cols == mat[i].length
1 <= rows, cols <= 100
mat[i][j] 是 0 或 1
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numSpecial(vector<vector<int>> &mat)
    {
        int row = mat.size();
        if (row <= 0) return 0;
        int col = mat[0].size();
        if (col <= 0) return 0;

        vector<pair<int,int>> row_cnt(row);
        vector<int> col_cnt(col, 0);
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (mat[i][j] > 0)
                {
                    col_cnt[j]++;
                    row_cnt[i].first++;
                    row_cnt[i].second = j;
                }
            }
        }
        int result = 0;
        for (int i = 0; i < row; ++i)
        {
            if (row_cnt[i].first != 1) continue;
            if (col_cnt[row_cnt[i].second] != 1) continue;
            result++;
        }
        return result;
    }
};

int main()
{
    Solution so;
    int m, n;
    while (cin >> m >> n)
    {
        vector<vector<int>> mat(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cin >> mat[i][j];
        cout << so.numSpecial(mat) << endl;
    }
}