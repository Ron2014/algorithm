/*
现有N个任务需要处理，同一时间只能处理一个任务，处理每个任务所需要的时间固定为1。
每个任务都有最晚处理时间限制和积分值，在最晚处理时间点之前处理完成任务才可获得对应的积分奖励。
可用于处理任务的时间有限，请问在有限的时间内，可获得的最多积分。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Task
{
public:
    int idx;
    int deadline;
    int score;
    Task():idx(-1),deadline(-1),score(0) {}
    Task(int i, int d, int s):idx(i),deadline(d),score(s) {}
};

void dfs(vector<Task *> &order, int N, int idx, vector<bool> &visited, vector<int> &result, vector<int> &fresult)
{
    if (idx >= N)
    {
        return;
    }

    // 解决 result[idx]
    for (int i = 0; i < N; ++i)
    {
        Task *ptask = order[i];
        if (visited[ptask->idx]) continue;
        if (ptask->deadline < idx) break;

        result[idx] = ptask->idx;
        result[N] += ptask->score;
        visited[ptask->idx] = true;

        if (result[N] > fresult[N])
        {
            fresult = result;
        }

        dfs(order, N, idx+1, visited, result, fresult);

        result[idx] = 0;
        result[N] -= ptask->score;
        visited[ptask->idx] = false;
    }
}

int main(int argc, char *argv[])
{
    int N;
    while (cin >> N)
    {
        unordered_map<int, Task> mp;
        vector<Task *> order;
        for (int i = 1; i <= N; ++i)
        {
            Task &task = mp[i];
            task.idx = i;
            cin >> task.deadline;
            cin >> task.score;
            order.push_back(&task);
        }
        sort(order.begin(), order.end(), [](const Task *pa, const Task *pb) {
            return pa->deadline > pb->deadline;
        });

        // for (int i = 0; i < N; ++i)
        // {
        //     cout << order[i]->idx << " ";
        // }
        // cout << endl;

        vector<int> result(N+1);
        vector<int> fresult(N+1);
        vector<bool> visited(N+1, false);
        dfs(order, N, 0, visited, result, fresult);

        for (int i = 0; i <= N; ++i)
        {
            cout << fresult[i] << " ";
        }
        cout << endl;
    }
    return 0;
}