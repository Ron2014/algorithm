/*
给定一个二维数组M行N列，二维数组里的数字代表图片的像素，为了简化问题，仅包含像素1和5两种像素，每种像素代表一个物体，2个物体相邻的格子为边界，求像素1代表的物体的边界个数。

像素1代表的物体的边界指与像素5相邻的像素1的格子，边界相邻的属于同一个边界
相邻需要考虑8个方向（上，下，左，右，左上，左下，右上，右下）。

其他约束：

地图规格约束为：

0<M<100

0<N<100

*/

/**
 * 通过BFS确定像素5的边界，并对不同的像素5集群给不同的标记
 * 如
 * 第1个集群标记为1，边界标记为-1
 * 第2个集群标记为2，边界标记为-2
 * 
 * 判断边界相邻，并合并边界
 * 直到未找到相邻的边界
 * 
 * 
*/

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include "common.h"
using namespace std;

const int di[] = {0,1,0,-1,-1,1,-1,1};
const int dj[] = {1,0,-1,0,-1,-1,1,1};
const int DIRECT_CNT = 8;
const int OBJ = 5;

void bfs(vector<vector<int>> &grid, int M, int N, int si, int sj, 
    vector<vector<int>> &board, int idx, unordered_map<int, vector<pair<int, int>>> &edges)
{
    deque<pair<int,int>> paths;
    paths.emplace_back(si, sj);
    board[si][sj] = idx;

    while (!paths.empty())
    {
        pair<int, int> &p = paths.front();

        for (int k = 0; k < DIRECT_CNT; ++k)
        {
            int ni = p.first + di[k];
            int nj = p.second + dj[k];
            if (ni < 0 || ni >= M || nj < 0 || nj >= N) continue;
            if (grid[ni][nj] == OBJ)
            {
                paths.emplace_back(ni, nj);
                board[ni][nj] = idx;
            }
            else
            {
                if (board[ni][nj] == 0)
                {
                    board[ni][nj] = -idx;
                    edges[-idx].emplace_back(ni, nj);
                }
                else if (board[ni][nj] != -idx)
                {
                    int old_idx = board[ni][nj];
                    vector<pair<int, int>> &old_edge = edges[old_idx];
                    for (const auto &p : old_edge)
                    {
                        board[p.first][p.second] = -idx;
                        edges[-idx].emplace_back(p.first, p.second);
                    }
                    edges.erase(old_idx);
                }
            }
        }

        paths.pop_front();
    }
}

void search_obj(vector<vector<int>> &grid, int M, int N)
{
    vector<vector<int>> board(M, vector<int>(N, 0));
    unordered_map<int, vector<pair<int, int>> > edges;
    int idx = 0;

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (grid[i][j] == OBJ && board[i][j] == 0)
            {
                idx++;
                bfs(grid, M, N, i, j, board, idx, edges);
            }
        }
    }

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j] < 0)
            {
                int old_idx = board[i][j];
                for (int k = 0; k < DIRECT_CNT; ++k)
                {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (ni < 0 || ni >= M || nj < 0 || nj >= N) continue;
                    int new_idx = board[ni][nj];
                    if (new_idx < 0 && old_idx != new_idx)
                    {
                        vector<pair<int, int>> &old_edge = edges[old_idx];
                        for (const auto &p : old_edge)
                        {
                            board[p.first][p.second] = new_idx;
                            edges[new_idx].emplace_back(p.first, p.second);
                        }
                        edges.erase(old_idx);
                    }
                }
            }
        }
    }

    SHOW_M(board, M, N);
    cout << edges.size() << endl;
}

int main(int argc, char *argv[])
{
    int M, N;
    while (cin >> M >> N)
    {
        vector<vector<int>> grid(M, vector<int>(N, 0));
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cin >> grid[i][j];
            }
        }
        search_obj(grid, M, N);
    }
}