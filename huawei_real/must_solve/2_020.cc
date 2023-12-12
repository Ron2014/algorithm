/*
    假定街道是棋盘型的，每格距离相等，车辆通过每格街道需要时间均为 timePerRoad；
    街道的街口（交叉点）有交通灯，灯的周期T(=lights[row][col])各不相同；
    车辆可直行、左转和右转，其中直行和左转需要等相应T时间的交通灯才可通行，右转无需等待。

    现给出 n*m 个街口的交通灯周期，以及起止街口的坐标，计算车辆经过两个街口的最短时间。
    其中：
    1）起点和终点的交通灯不计入时间，且可以任意方向经过街口
    2）不可超出 n*m 个街口，不可跳跃，但边线也是道路（即 lights[0][0] -> lights[0][1] 是有效路径）
*/

/**
* 入口函数定义:
* lights : n*m 个街口每个交通灯的周期，值范围[0,120]，n和m的范围为[1,9]
* timePerRoad : 相邻两个街口之间街道的通过时间,范围为[0,600]
* rowStart : 起点的行号
* colStart : 起点的列号
* rowEnd : 终点的行号
* colEnd : 终点的列号
* return : lights[rowStart][colStart] 与 lights[rowEnd][colEnd] 两个街口之间的最短通行时间
* int calcTime(vector<vector<int> &lights, int timePerRoad, int rowStart, int colStart, int rowEnd, int colEnd);
*/

/*
* 车辆初始的朝向没给
* 那么车辆移动第一次后才具备朝向
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node
{
public:
    int i;
    int j;
    int cost;
    int di;
    int dj;
    Node():i(-1),j(-1),cost(0) {}
    Node(int ipos, int jpos, int c, int vi, int vj):i(ipos),j(jpos),cost(c),di(vi),dj(vj) {}
    bool operator<(const Node &other) const { return cost > other.cost; }
};

const int MAX_INT = 2147483647;

#define DISTANCE(si, sj, ei, ej)    (abs((ei)-(si))+abs((ej)-(sj)))
#define IS_TURN_BACK(di0, dj0, di1, dj1)    ((di0)*(di1)==-1||(dj0)*(dj1)==-1)
#define IS_TURN_RIGHT(di0, dj0, di1, dj1)   ((di0)*(dj1)==-1||(dj0)*(di1)==1)

#define SHOW_M(a, n, m)               \
    for (int i = 0; i < (n); ++i)     \
    {                                 \
        for (int j = 0; j < (m); ++j) \
        {                             \
            printf("%10d ", a[i][j]); \
        }                             \
        cout << endl;                 \
    }

void dijkstra(vector<vector<int>> &lights, vector<vector<int>> &distance, 
    int n, int m, int speed, int si, int sj, int ei, int ej)
{
    int minn = MAX_INT;

    vector<vector<bool>> visited(n+2, vector<bool>(m+2, false));
    priority_queue<Node> targets;
    targets.emplace(si, sj, 0, 0, 0);

    int di[] = {0,  0, -1, 1};
    int dj[] = {-1, 1, 0, 0,};

    while (!targets.empty())
    {
        Node node = targets.top();
        si = node.i;
        sj = node.j;
        distance[si][sj] = min(distance[si][sj], node.cost);
        visited[si][sj] = true;
        cout << "------ " << si << "," << sj << " " << node.di << "," << node.dj << endl;

        for (int k = 0; k < 4; ++k)
        {
            if (IS_TURN_BACK(node.di, node.dj, di[k], dj[k])) continue;

            int ni = si + di[k];
            int nj = sj + dj[k];
            
            if (distance[ni][nj] == -1 || visited[ni][nj]) continue;

            int waitTime = 0;
            if (!IS_TURN_RIGHT(node.di, node.dj, di[k], dj[k]))
            {
                waitTime = lights[si][sj];
            }

            int cost = node.cost + speed + waitTime;
            if (cost < distance[ni][nj])
            {
                distance[ni][nj] = cost;
                targets.emplace(ni, nj, cost, di[k], dj[k]);
            }
        }

        targets.pop();
        SHOW_M(distance, n+2, m+2);
    }
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<int>> lights(n+2, vector<int>(m+2, 0));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                cin >> lights[i][j];
            }
        }
        SHOW_M(lights, n+2, m+2);
        vector<vector<int>> distance(n+2, vector<int>(m+2, MAX_INT));
        for (int i = 0; i <= n+1; ++i)
        {
            distance[i][0] = distance[i][m+1] = -1;
        }
        for (int i = 0; i <= m+1; ++i)
        {
            distance[0][i] = distance[n+1][i] = -1;
        }
        SHOW_M(distance, n+2, m+2);
        int speed, si, sj, ei, ej;
        cin >> speed >> si >> sj >> ei >> ej;
        dijkstra(lights, distance, n, m, speed, si, sj, ei, ej);
        cout << distance[ei][ej] << endl;
    }

    return 0;
}