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

void dfs(vector<pair<int, int>> &tasks, int n, int day, vector<bool> &visited, vector<int> &result, int &fresult)
{
    // 解决 result[day] 做什么
    if (day >= n) return;
    for (int i = 0; i < n; ++i)
    {
        pair<int, int> &t = tasks[i];
        if (t.second < day) break;      // 后面的 deadline 更小，更不用安排了
        if (t.first > day) continue;    // 第 day 天还不能开始 
        if (visited[i]) continue;       // 已经安排了

        result.push_back(i);
        visited[i] = true;

        if (result.size() > fresult)
        {
            fresult = result.size();
            for (const int &k : result)
            {
                cout << k << " ";
            }
            cout << endl;
        }
        dfs(tasks, n, day+1, visited, result, fresult);

        result.pop_back();
        visited[i] = false;
    }
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<pair<int, int>> tasks(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> tasks[i].first;      //startline
            cin >> tasks[i].second;     //deadline
        }
        sort(tasks.begin(), tasks.end(), [](const pair<int,int> &ta, const pair<int,int> &tb)
        {
            return ta.second > tb.second;
        });
        vector<int> result;
        vector<bool> visited(n, false);
        int fresult = 0;
        dfs(tasks, n, 0, visited, result, fresult);
        cout << fresult << endl;
    }
    return 0;
}

