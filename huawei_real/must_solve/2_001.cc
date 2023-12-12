/*
宝宝和妈妈参加亲子游戏，在一个二维矩阵（N*N）的格子地图上，宝宝和妈妈抽签决定各自的位置
地图上每个格子有不同的糖果数量，部分格子有障碍物

游戏规则是妈妈必须在最短的时间（每个单位时间只能走一步）到达宝宝的位置，路上的所有糖果都可以拿走，不能走障碍物的格子，只能上下左右走。

请问妈妈在最短到达宝宝位置的时间内最多拿到多少糖果（优先考虑最短时间到达的情况下尽可能多拿糖果）

// grid[i][j]
0 障碍
1 起点
2 终点
3 糖果
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

const int FLAG_FORBID = 0;
const int FLAG_NORMAL = 1;
const int FLAG_AWARD = 2;
const int FLAG_START = 3;
const int FLAG_END = 4;

class Node
{
public:
    int i;
    int j;
    int cnt;
    Node():i(-1),j(-1),cnt(0) {}
    Node(int x, int y, int c)
    {
        i = x;
        j = y;
        cnt = c;
    }

};


int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<vector<int>> grid(n+2, vector<int>(n+2, FLAG_FORBID));
        deque<Node> visited;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                cin >> grid[i][j];
                if (grid[i][j] == FLAG_START)
                {
                    visited.emplace_back(i, j, 0);
                }
            }
        }
        int maxn = 0, finished = false;
        while (visited.size() > 0 && !finished)
        {
            n = visited.size();
            for (int i = 0; i < n; ++i)
            {
                Node &curr = visited.front();
                if (grid[curr.i][curr.j] == FLAG_END)
                {
                    maxn = max(maxn, curr.cnt);
                    finished = true;
                }
                else
                {
                    if (grid[curr.i][curr.j] == FLAG_AWARD)
                    {
                        curr.cnt++;
                    }
                    if (grid[curr.i-1][curr.j] != FLAG_FORBID)
                    {
                        // up
                        visited.emplace_back(curr.i-1, curr.j, curr.cnt);
                    }
                    if (grid[curr.i+1][curr.j] != FLAG_FORBID)
                    {
                        // down
                        visited.emplace_back(curr.i+1, curr.j, curr.cnt);
                    }
                    if (grid[curr.i][curr.j-1] != FLAG_FORBID)
                    {
                        // left
                        visited.emplace_back(curr.i, curr.j-1, curr.cnt);
                    }
                    if (grid[curr.i][curr.j+1] != FLAG_FORBID)
                    {
                        // right
                        visited.emplace_back(curr.i, curr.j+1, curr.cnt);
                    }
                }
                visited.pop_front();
            }
        }
        cout << maxn << endl;
        // for (int i = 0; i < grid.size(); ++i)
        // {
        //     for (int j = 0; j < grid[i].size(); ++j)
        //     {
        //         cout << grid[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
    return 0;
}