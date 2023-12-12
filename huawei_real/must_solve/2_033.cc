/*
马是象棋(包括中国象棋和国际象棋)中的棋子，走法是每步直一格再斜一格，即先横着或直着走一格，然后再斜着走一个对角线，可进可退，可越过河界，俗称“马走‘日’字。

给顶m行n列的棋盘（网格图），棋盘上只有有棋子象棋中的棋子“马”，并且每个棋子有等级之分，等级为k的马可以跳1~k步（走的方式与象棋中“马”的规则一样，不可以超出棋盘位置），问是否能将所有马跳到同一位置，如果存在，输出最少需要的总步数（每匹马的步数相加），不存在则输出-1。

注：允许不同的马在跳的过程中跳到同一位置，坐标为(x,y)的马跳一次可以跳到到坐标为(x+1, y+2), (x+1, y-2), (x+2, y+1), (x+2, y-1), (x-1, y+2), (x-1, y-2), (x-2, y+1), (x-2, y-1),的格点上，但是不可以超出棋盘范围。
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Node
{
public:
    int i;
    int j;
    int s;
    Node():i(-1),j(-1),s(0) {}
    Node(int ipos, int jpos, int steps):i(ipos), j(jpos), s(steps) {}
};

#define SHOW_M(a, m, n)               \
    for (int i = 0; i < (m); ++i)     \
    {                                 \
        for (int j = 0; j < (n); ++j) \
        {                             \
            printf("%2d ", a[i][j]);  \
        }                             \
        cout << endl;                 \
    }

#define TRY_ADD_NODE(ni, nj, m, n, visited, paths, nsteps)                            \
    if ((ni) >= 1 && (ni) <= m && (nj) >= 1 && (nj) <= n && visited[(ni)][(nj)] >= 0) \
    {                                                                                 \
        paths.emplace_back((ni), (nj), (nsteps));                                     \
    }

void bfs(vector<vector<int>> &grid, vector<vector<int>> &move, int m, int n, int si, int sj, int total)
{
    if (total < 0) return;
    vector<vector<int>> visited = grid;
    deque<Node> paths;
    paths.emplace_back(si, sj, total);
    while (!paths.empty())
    {
        Node &node = paths.front();
        int i = node.i;
        int j = node.j;
        int steps = node.s;
        grid[i][j]++;
        move[i][j]+= total - steps;
        visited[i][j] = -1;
        if (steps > 0)
        {
            // left top
            TRY_ADD_NODE(i-2, j-1, m, n, visited, paths, steps-1);
            TRY_ADD_NODE(i-1, j-2, m, n, visited, paths, steps-1);
            // left bottom
            TRY_ADD_NODE(i+2, j-1, m, n, visited, paths, steps-1);
            TRY_ADD_NODE(i+1, j-2, m, n, visited, paths, steps-1);
            // right top
            TRY_ADD_NODE(i-2, j+1, m, n, visited, paths, steps-1);
            TRY_ADD_NODE(i-1, j+2, m, n, visited, paths, steps-1);
            // right bottom
            TRY_ADD_NODE(i+2, j+1, m, n, visited, paths, steps-1);
            TRY_ADD_NODE(i+1, j+2, m, n, visited, paths, steps-1);
        }
        paths.pop_front();
    }
}

int main(int argc, char *argv[])
{
    int m, n, N, si, sj, level;
    while (cin >> m >> n >> N)
    {
        if (m <= 0 || n <= 0) break;
        vector<vector<int>> grid(m+2, vector<int>(n+2, 0));     // 记录格子上马的数量
        // edge: left right
        for (int i = 0; i <= m+1; ++i)
        {
            grid[i][0] = grid[i][n+1] = -1;
        }
        // edge: top bottom
        for (int i = 0; i <= n+1; ++i)
        {
            grid[0][i] = grid[m+1][i] = -1;
        }
        vector<vector<int>> move = grid;   // 记录总步数
        // horse info
        for (int i = 0; i < N; ++i)
        {
            cin >> si >> sj >> level;
            bfs(grid, move, m, n, si, sj, level);
        }
        SHOW_M(grid, m+2, n+2);
        SHOW_M(move, m+2, n+2);
        int minn = -1;
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (grid[i][j] == N)
                {
                    minn = (minn < 0) ? move[i][j] : min(minn, move[i][j]);
                }
            }
        }
        cout << minn << endl;
    }
    return 0;
}