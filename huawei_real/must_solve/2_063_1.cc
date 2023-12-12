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
using namespace std;

const int di[] = {1,1,0};
const int dj[] = {1,0,1};
const int DIRECT_CNT = 3;
const int SAME_IDX = 0;

void dfs(int i, int j, int n, int m, string &B, string &A, vector<pair<int,int>> &result, vector<pair<int,int>> &fresult)
{
    result.emplace_back(i, j);

    if (i == n && j == m)
    {
        if (fresult.size() <= 0 || fresult.size() > result.size())
        {
            fresult = result;
        }
    }
    else
    {
        for (int k = 0; k < DIRECT_CNT; ++k)
        {
            int ni = i + di[k];
            int nj = j + dj[k];

            if (ni > n || nj > m) continue;
            if (k == SAME_IDX && B[ni-1] != A[nj-1]) continue;

            if (fresult.size() > 0 && result.size() + 1 >= fresult.size()) continue;

            dfs(ni, nj, n, m, B, A, result, fresult);
        }
    }

    result.pop_back();
}

int main(int argc, char *argv[])
{
    string A, B;
    while (cin >> A >> B)
    {
        int m = A.length();
        int n = B.length();
        if (m <= 0 || n <= 0) break;

        vector<pair<int, int>> result;
        vector<pair<int, int>> fresult;
        dfs(0, 0, n, m, B, A, result, fresult);

        for (const auto &p : fresult)
        {
            cout << p.first << " " << p.second << endl;
        }
    }
    return 0;
}