/*
围棋棋盘由纵横各19条线垂直相交组成，棋盘上一共19x19=361个交点，对弈双方一方执白棋，一方执黑棋，落子时只能将棋子置于交点上。
“气”是围棋中很重要的一个概念，某个棋子有几口气，是指其上下左右方向四个相邻的交叉点中，有几个交叉点没有棋子，由此可知：
1、在棋盘的边缘上的棋子最多有3口气（黑1），在棋盘角点的棋子最多有2口气（黑2），其它情况最多有4口气（白1）
2、所有同色棋子的气之和叫作该色棋子的气，需要注意的是，同色棋子重合的气点，对于该颜色棋子来说，只能计算一次气，比如下图中，黑棋一共4口气，而不是5口气，因为黑1和黑2中间红色三角标出的气是两个黑棋共有的，对于黑棋整体来说只能算一个气。
3、本题目只计算气，对于眼也按气计算，如果您不清楚“眼”的概念，可忽略，按照前面描述的规则计算即可。
现在，请根据输入的黑棋和白棋的坐标位置，计算黑棋和白起一共各有多少气？
*/

#include <iostream>
#include <vector>
using namespace std;

const int N = 19;
const int W = 1;
const int B = 2;

const int di[] = {0,1,0,-1};
const int dj[] = {1,0,-1,0};
const int DIRECT_CNT = 4;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<vector<int>> grid(N+2, vector<int>(N+2, 0));
        for (int i = 0; i < N+2; ++i)
        {
            grid[0][i] = grid[N+1][i] = -1;
            grid[i][0] = grid[i][N+1] = -1;
        }
        for (int k = 0; k < n; ++k)
        {
            int i, j;
            cin >> i >> j;
            cin >> grid[i][j];
        }
        int iWcnt = 0, iBcnt = 0;
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (grid[i][j] != 0) continue;
                bool bFoundW = false, bFoundB = false;
                for (int k = 0; k < DIRECT_CNT; ++k)
                {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (!bFoundW && grid[ni][nj] == W)
                    {
                        bFoundW = true;
                        iWcnt++;
                    }
                    if (!bFoundB && grid[ni][nj] == B)
                    {
                        bFoundB = true;
                        iBcnt++;
                    }
                    if (bFoundW && bFoundB) break;
                }
            }
        }
        cout << iWcnt << " " << iBcnt << endl;
    }
    return 0;
}