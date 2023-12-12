/*
机器人搬砖，一共有N堆砖存放在N个不同的仓库中，第i堆砖中有bricks[i]块砖头，要求在8小时内搬完。
机器人每小时能搬砖的数量取决于有多少能量格，机器人一个小时中只能在一个仓库中搬砖，
机器人的能量格每小时补充一次且能量格只在这一个小时有效，为使得机器人损耗最小化尽量减小每次补充的能量格数。
为了保障在8小时内能完成搬砖任务，请计算每小时给机器人充能的最小能量格数。
备注：
1、无需考虑机器人补充能量格的耗时；
2、无需考虑机器人搬砖的耗时；
3、机器人每小时补充能量格只在这一个小时中有效；
*/

#include <iostream>
#include <vector>
using namespace std;

#define MAX_INT 2147483647

bool check(vector<int> &bricks, int k, int N, int h)
{
    int need = 0;
    for (int i = 0; i < N; ++i)
    {
        need += bricks[i] / k;
        if (bricks[i] % k > 0) need++;
    }
    return need <= h;
}

int main(int argc, char *argv[])
{
    // N <= h ，条件：机器人一个小时中只能在一个仓库中搬砖
    int N, h;
    while (cin >> N >> h)
    {
        vector<int> bricks(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> bricks[i];
        }

        // 下限，平均数
        // 上限，最大的数
        int mink = 0, maxk = 0;
        for (int i = 0; i < N; ++i)
        {
            mink += bricks[i];
            maxk = max(maxk, bricks[i]);
        }
        mink = mink / h;
        int prev = -1;
        while (mink <= maxk)
        {
            int mk = (mink + maxk) >> 1;
            if (check(bricks, mk, N, h))
            {
                prev = mk;
                maxk = mk - 1;
            }
            else
            {
                mink = mk + 1;
            }
        }
        cout << mink << " " << maxk << " " << prev << endl;
    }
    return 0;
}