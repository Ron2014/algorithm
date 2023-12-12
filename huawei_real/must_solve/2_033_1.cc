/*
马是象棋(包括中国象棋和国际象棋)中的棋子，走法是每步直一格再斜一格，即先横着或直着走一格，然后再斜着走一个对角线，可进可退，可越过河界，俗称“马走‘日’字。

给顶m行n列的棋盘（网格图），棋盘上只有有棋子象棋中的棋子“马”，并且每个棋子有等级之分，等级为k的马可以跳1~k步（走的方式与象棋中“马”的规则一样，不可以超出棋盘位置），问是否能将所有马跳到同一位置，如果存在，输出最少需要的总步数（每匹马的步数相加），不存在则输出-1。

注：允许不同的马在跳的过程中跳到同一位置，坐标为(x,y)的马跳一次可以跳到到坐标为(x+1, y+2), (x+1, y-2), (x+2, y+1), (x+2, y-1), (x-1, y+2), (x-1, y-2), (x-2, y+1), (x-2, y-1),的格点上，但是不可以超出棋盘范围。
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int di[] = {-1, 1,-2, 2,-1, 1,-2, 2,};
const int dj[] = {-2,-2,-1,-1, 2, 2, 1, 1,};
const int DIRECT_CNT = 8;

void bfs(vector<vector<int>> &visited, int si, int sj, int m, int n, int k)
{
    deque<pair<int, int>> paths;
    visited[si][sj] = 0;
    paths.emplace_back(si, sj);

    int steps = 0;
    while (!paths.empty() && k > steps)
    {
        steps++;    // 走了1步，还剩k步
        int pn = paths.size();
        for (int i = 0; i < pn; ++i)
        {
            pair<int, int> &p = paths.front();
            si = p.first;
            sj = p.second;

            for (int j = 0; j < DIRECT_CNT; ++j)
            {
                int ni = si + di[j];
                int nj = sj + dj[j];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && visited[ni][nj] < 0)
                {
                    visited[ni][nj] = steps;
                    paths.emplace_back(ni, nj);
                }
            }
            paths.pop_front();
        }
    }

}

int main(int argc, char *argv[])
{
    int m, n, cnt;
    while (cin >> m >> n >> cnt)
    {
        vector<vector<pair<int, int>>> grid(m, vector<pair<int, int>>(n, {0, 0}));
        vector<vector<int>> visited(m, vector<int>(n, -1));

        for (int k = 0; k < cnt; ++k)
        {
            int si, sj, steps;
            cin >> si >> sj >> steps;

            bfs(visited, si, sj, m, n, steps);

            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    printf("%2d ", visited[i][j]);
                    if (visited[i][j] >= 0)
                    {
                        grid[i][j].first++;
                        grid[i][j].second += visited[i][j];
                        visited[i][j] = -1;
                    }
                }
                cout << endl;
            }
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                printf("%2d,%2d ", grid[i][j].first, grid[i][j].second);
            }
            cout << endl;
        }

        int minn = INT_MAX;
        int mini = -1, minj = -1;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j].first == cnt && grid[i][j].second < minn)
                {
                    minn = grid[i][j].second;
                    mini = i;
                    minj = j;
                }
            }
        }

        if (minn < INT_MAX)
        {
            printf("[%d][%d]=%d\n", mini, minj, minn);
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}
