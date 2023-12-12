/*
项目组共有N个开发人员，项目经理接到了M个独立的需求，每个需求的工作量不同，且每个需求只能由一个开发人员独立完成，不能多人合作。
假定各个需求直接无任何先后依赖关系，请设计算法帮助项目经理进行工作安排，使整个项目能用最少的时间交付。
*/

/**
 * 深度优先搜索/回溯
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define MAX_INT 2147483647

void dfs(vector<int> &req, int idx, int M, vector<int> &devs, int N, vector<int> &fresult)
{
    if (idx >= M)
    {
        int maxr = *max_element(devs.begin(), devs.end());
        if (maxr < fresult[N])
        {
            for (int i = 0; i < N; ++i) fresult[i] = devs[i];
            fresult[N] = maxr;
        }
        return;
    }

    int r = req[idx];
    for (int i = 0; i < N; ++i)
    {
        if (devs[i] + r >= fresult[N]) continue;
        devs[i] += r;
        dfs(req, idx+1, M, devs, N, fresult);
        devs[i] -= r;
    }
}

int main(int argc, char *argv[])
{
    int N, M;
    while (cin >> N >> M)
    {
        vector<int> req(M);
        for (int i = 0; i < M; ++i)
        {
            cin >> req[i];
        }

        vector<int> fresult(N+1, 0);
        fresult[N] = MAX_INT;

        vector<int> devs(N);
        dfs(req, 0, M, devs, N, fresult);
        for (int i = 0; i <= N; ++i) cout << fresult[i] << " ";
        cout << endl;
    }
    return 0;
}
