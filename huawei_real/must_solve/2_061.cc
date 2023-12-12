/*
评估一个网络的信号质量，其中一个做法是将网络划分为栅格，然后对每个栅格的信号质量计算。路测的时候，希望选择一条信号最好的路线（彼此相连的栅格集合）进行演示。
现给出R行C列的整数数组Cov，每个单元格的数值S即为该栅格的信号质量（已归一化，无单位，值越大信号越好）。

要求从[0, 0]到[R-1, C-1]设计一条最优路测路线。返回该路线得分。
规则：

1.     路测路线可以上下左右四个方向，不能对角。
2.     路线的评分是以路线上信号最差的栅格为准的，例如路径8→4→5→9的值为 4，该线路评分为4。线路最优表示该条线路的评分最高。
*/

#include <iostream>
#include <vector>
using namespace std;

#define MAX_INT 2147483647

// 优先走左、下
const int di[] = {0,1,0,-1};
const int dj[] = {1,0,-1,0};

const int DIRECT_CNT = 4;

void dfs(vector<vector<int>> &Cov, int i, int j, int R, int C, vector<pair<int, int>> &route, int score, vector<pair<int, int>> &froute, int &fscore)
{
    int pscore = Cov[i][j];
    score = min(score, pscore);
    route.emplace_back(i, j);
    Cov[i][j] = 0;

    if (i == R && j == C)
    {
        if (fscore < 0 || score > fscore)
        {
            froute = route;
            fscore = score;
        }
    }
    else
    {
        for (int k = 0; k < DIRECT_CNT; ++k)
        {
            int ni = i + di[k];
            int nj = j + dj[k];

            if (Cov[ni][nj] <= 0) continue;
            if (min(score, Cov[ni][nj]) < fscore) continue;
            dfs(Cov, ni, nj, R, C, route, score, froute, fscore);
        }
    }

    route.pop_back();
    Cov[i][j] = pscore;
}

int main(int argc, char *argv[])
{
    int R, C;
    while (cin >> R >> C)
    {
        vector<vector<int>> Cov(R+2, vector<int>(C+2, 0));
        for (int i = 1; i <= R; ++i)
        {
            for (int j = 1; j <= C; ++j)
            {
                cin >> Cov[i][j];
            }
        }

        int score = MAX_INT;
        vector<pair<int, int>> route;

        int fscore = -1;
        vector<pair<int, int>> froute;

        dfs(Cov, 1, 1, R, C, route, score, froute, fscore);

        for (const pair<int, int> &p : froute)
        {
            cout << p.first << "," << p.second << endl;
        }
        cout << fscore << endl;
    }
}