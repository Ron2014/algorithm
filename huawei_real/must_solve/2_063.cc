/*
给定两个字符串，分别为字符串A与字符串B。
例如A字符串为ABCABBA，B字符串为CBABAC可以得到下图m*n的二维数组
定义原点为(0, 0)，终点为(m, n)，水平与垂直的每一条边距离为1，映射成坐标系如下图

从原点(0, 0)到(0, A)为水平边，距离为1，从(0, A)到(A, C)为垂直边，距离为1；
假设两个字符串同一位置的两个字符相同则可以作一个斜边，如(A, C)到(B, B)最短距离为斜边，距离同样为1。
作出所有的斜边如下图，(0, 0)到(B, B)的距离为 1个水平边 + 1个垂直边 + 1个斜边 = 3。

根据定义可知，原点到终点的最短距离路径如下图红线标记，最短距离为9：
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Node
{
public:
    int i, j;
    vector<pair<int,int>> paths;
    Node():i(-1),j(-1) {}
    Node(int i, int j):i(i),j(j)
    {
        paths.emplace_back(i, j);
    }
    Node(vector<pair<int, int>> &paths, int i, int j):i(i),j(j)
    {
        this->paths = paths;
        this->paths.emplace_back(i, j);
    }
};

const int di[] = {1,1,0};
const int dj[] = {1,0,1};
const int DIRECT_CNT = 3;
const int DIRECT_SAME_IDX = 0;

void bfs(vector<vector<int>> &grid, int n, int m, string &B, string &A)
{
    deque<Node> nodes;
    nodes.emplace_back(0, 0);

    Node fresult;

    while (!nodes.empty())
    {
        Node &node = nodes.front();
        if (node.i == n && node.j == m)
        {
            if (fresult.paths.size() <= 0 || fresult.paths.size() > node.paths.size())
            {
                fresult = node;
            }
        }
        for (int k = 0; k < DIRECT_CNT; ++k)
        {
            int ni = node.i + di[k];
            int nj = node.j + dj[k];
            if (ni < 0 || ni > n || nj < 0 || nj > m)
                continue;
            if (k == DIRECT_SAME_IDX && (B[ni - 1]) != A[nj - 1])
                continue;
            nodes.emplace_back(node.paths, ni, nj);
            if (k == DIRECT_SAME_IDX) break;
        }
        nodes.pop_front();
    }

    for (auto &p : fresult.paths)
    {
        cout << p.first << "," << p.second << endl;
    }
}

int main(int argc, char *argv[])
{
    string A, B;
    while (cin >> A >> B)
    {
        int m = A.length();
        int n = B.length();
        vector<vector<int>> grid(n+1, vector<int>(m+1, 0));
        bfs(grid, n, m, B, A);
    }
    return 0;
}