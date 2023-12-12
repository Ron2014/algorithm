/*
绘图机器的绘图笔初始位置在原点（0, 0），机器启动后其绘图笔按下面规则绘制直线：
1）尝试沿着横向坐标轴正向绘制直线，直到给定的终点值E。
2）期间可通过指令在纵坐标轴方向进行偏移，并同时绘制直线，偏移后按规则1 绘制直线；指令的格式为X offsetY，表示在横坐标X 沿纵坐标方向偏移，offsetY为正数表示正向偏移，为负数表示负向偏移。

给定了横坐标终点值E、以及若干条绘制指令，请计算绘制的直线和横坐标轴、以及 X=E 的直线组成图形的面积。
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
    int E;
    int X, offsetY;
    while (cin >> E)
    {
        vector<int> line(E, 0);
        while (scanf("%d %d", &X, &offsetY))
        {
            for (int i = X; i < E; ++i)
            {
                line[i] += offsetY;
            }
            int area = 0;
            for (int i = 0; i < E; ++i)
            {
                area += abs(line[i]);
            }
            cout << area << endl;
        }
    }
    return 0;
}