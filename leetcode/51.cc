/*
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例 1：

输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。

示例 2：

输入：n = 1
输出：[["Q"]]

提示：

1 <= n <= 9
*/

#include <iostream>
#include <vector>
using namespace std;

const int di[] = {-1, 1, -1, 1,};
const int dj[] = {-1, 1, 1, -1,};
const int DIRECT_CNT = 4;

class Solution {
    void set_visited(vector<vector<int>> &visited, int i, int j, bool val, int n)
    {
        for (int k = 0; k < DIRECT_CNT; ++k)
        {
            int ni = i, nj = j;
            while (ni >= 0 && ni < n && nj >= 0 && nj < n)
            {
                if (visited[ni][nj] < 0 || visited[ni][nj] == i)
                {
                    visited[ni][nj] = val ? i : -1;
                }
                else
                {
                    if (visited[ni][nj] == )
                }
                ni += di[k];
                nj += dj[k];
            }
        }
    }

    void dfs(int idx, int n, vector<vector<int>> &visited, 
        vector<int> &result, vector<vector<string>> &fresult)
    {
        // 解决第idx行放置 result[X] = idx; 第多少列被行占用
        if (idx >= n)
        {
            fresult.push_back({});
            vector<string> &node = fresult[fresult.size() - 1];
            node.resize(n);
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    node[result[i]] += j == i ? 'Q' : '.';
                }
            }
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            if (visited[idx][i] >= 0) continue;
            if (result[i] >= 0) continue;

            result[i] = idx;
            set_visited(visited, idx, i, true, n);

            dfs(idx+1, n, visited, result, fresult);

            result[i] = -1;
            set_visited(visited, idx, i, false, n);
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> visited(n, vector<int>(n, -1));
        vector<int> result(n, -1);
        vector<vector<string>> fresult;
        dfs(0, n, visited, result, fresult);
        return fresult;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n;
    while (cin >> n)
    {
        vector<vector<string>> result = s.solveNQueens(n);
        for (int i = 0; i < result.size(); ++i)
        {
            for (const string &s : result[i])
            {
                cout << s << endl;
            }
            cout << "------" << endl;
        }
        cout << result.size() << endl;
    }
    return 0;
}