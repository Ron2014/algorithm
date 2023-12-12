/*
在某个项目中有多个任务（用 tasks 数组表示）需要您进行处理
其中 tasks[i] = [si, ei]，你可以在 si <= day <= ei 中的任意一天处理该任务。
请返回你可以处理的最大任务数。
注：一天可以完成一个任务的处理。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Task
{
public:
    int id;
    int si;
    int ei;
    Task():id(0),si(-1),ei(-1) {}
    Task(int i):id(1),si(-1),ei(-1) {}
    Task(int i, int s, int e):id(i),si(s),ei(e) {}
};

int arrange(vector<Task> &tasks, vector<int> &days, int s, int n, int m)
{
    int maxn = m;
    if (s >= n) return maxn;

    Task &t = tasks[s];
    // 分配任务s
    for (int j = t.si; j <= t.ei && j < n; ++j)
    {
        if (days[j] > 0) continue;
        days[j] = t.id;
        maxn = max(maxn, arrange(tasks, days, s+1, n, m+1));
        days[j] = 0;
    }
    // 不分配任务s 
    maxn = max(maxn, arrange(tasks, days, s+1, n, m));
    return maxn;
}

int main(int argc, char *argv[])
{
    int n, id, si, ei;
    while (cin >> n)
    {
        vector<Task> tasks(n);
        for (int i = 0; i < n; ++i)
        {
            Task &t = tasks[i];
            t.id = i+1;
            cin >> t.si >> t.ei;
        }
        sort(tasks.begin(), tasks.end(), [](Task &a, Task &b) {
            if (a.ei - a.si == b.ei - b.si)
            {
                return a.si < b.si;
            }
            return a.ei - a.si < b.ei - b.si;
        });
        vector<int> days(n, 0);
        cout << arrange(tasks, days, 0, n, 0) << endl;
    }
    return 0;
}