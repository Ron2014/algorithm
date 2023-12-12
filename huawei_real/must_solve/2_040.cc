/*
一个应用启动时，会有多个初始化任务需要执行，并且任务之间有依赖关系，例如A任务依赖B任务，那么必须在B任务执行完成之后，才能开始执行A任务。

现在给出多条任务依赖关系的规则，请输入任务的顺序执行序列，规则采用贪婪策略，即一个任务如果没有依赖的任务，则立刻开始执行，如果同时有多个任务要执行，则根据任务名称字母顺序排序。

例如：B任务依赖A任务，C任务依赖A任务，D任务依赖B任务和C任务，同时，D任务还依赖E任务。那么执行任务的顺序由先到后是：A任务，E任务，B任务，C任务，D任务。这里A和E任务都是没有依赖的，立即执行
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<int> tasks(n, 0);                    // 记录依赖的未触发的父任务数量

        unordered_map<char, set<char>> triggers;    // 记录触发关系
        for (int i = 0; i < m; ++i)
        {
            char ch;
            string s;
            cin >> ch >> s;
            tasks[ch-'A']++;
            for (const char &p : s)
            {
                triggers[p].insert(ch);
            }
        }

        // for (auto it = triggers.begin(); it != triggers.end(); ++it)
        // {
        //     cout << it->first << ": ";
        //     for (auto it1 = it->second.begin(); it1 != it->second.end(); ++it1)
        //     {
        //         cout << *it1 << " ";
        //     }
        //     cout << endl;
        // }

        vector<set<char>> launch(2);
        int curr = 0, next = 1;

        for (int i = 0; i < n; ++i)
        {
            if (tasks[i] == 0) 
            {
                launch[curr].insert('A'+i);
                // cout << "first: " << char('A'+i) << endl;
            }
        }

        while (!launch[curr].empty())
        {
            for (auto it = launch[curr].begin(); it != launch[curr].end(); ++it)
            {
                // 执行任务
                char task_name = *it;
                cout << task_name << " ";

                unordered_map<char, set<char>>::iterator it1 = triggers.find(task_name);
                if (it1 == triggers.end()) continue;

                // 触发子任务
                set<char> &childs = it1->second;
                for (set<char>::iterator it2 = childs.begin(); it2 != childs.end(); ++it2)
                {
                    char child_task_name = *it2;
                    if (--tasks[child_task_name - 'A'] == 0)
                    {
                        launch[next].insert(child_task_name);
                    }
                }
            }

            // 清空当前缓冲区
            launch[curr].clear();

            // 交换双缓冲
            curr = (curr + 1) % launch.size();
            next = (next + 1) % launch.size();
        }
    }
    return 0;
}