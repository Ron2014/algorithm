/*
给定一个有向图，图中可能包含有环，图使用二维矩阵表示，每一行的第一列表示起始节点，第二列表示终止节点，如[0, 1]表示从0到1的路径。每个节点用正整数表示。
求这个数据的首节点与尾节点，题目给的用例会是一个首节点，但可能存在多个尾节点。
同时，图中可能含有环。如果图中含有环，返回[-1]。
说明：入度为0是首节点，出度为0是尾节点。
*/

#include <iostream>
#include <vector>
using namespace std;

// dfs 判断有向图有没有环

bool dsf_loop(vector<vector<bool>> &grid, int s, int n, vector<bool> &visited)
{
    if (visited[s]) return true;
    visited[s] = true;
    for (int i = 0; i < n; ++i)
    {
        if (grid[s][i] && dsf_loop(grid, i, n, visited))
            return true;
    }
    visited[s] = false;
    return false;
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<bool>> grid(n, vector<bool>(n, false));   // grid[i][j] 代表是否联通

        vector<int> ecnt(n, 0);     // 入度
        vector<int> ocnt(n, 0);     // 出度

        for (int i = 0; i < m; ++i)
        {
            int s, e;
            cin >> s >> e;
            ocnt[s]++;
            ecnt[e]++;
            grid[s][e] = true;
        }

        vector<int> s;
        vector<int> e;
        for (int i = 0; i < n; ++i)
        {
            if (ecnt[i] == 0) s.push_back(i);
            if (ocnt[i] == 0) e.push_back(i);
        }

        if (s.size() != 1) break;

        vector<bool> visited(n, false);
        if (dsf_loop(grid, s[0], n, visited))
        {
            cout << -1 << endl;
        }

        for (const int &n :s) cout << n << " ";
        cout <<endl;
        for (const int &n :e) cout << n << " ";
        cout <<endl;
    }
    return 0;
}