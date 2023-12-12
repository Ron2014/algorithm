/*
207. 课程表

你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。
先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。

示例 2：

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。
*/

/**
 * 打算用观察者模式处理
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> deps(numCourses, 0);
        unordered_map<int, vector<int>> trigger;
        deque<int> running_courses;

        for (const vector<int> &v : prerequisites)
        {
            deps[v[0]]++;
            trigger[v[1]].push_back(v[0]);
        }

        for (int i = 0; i < numCourses; ++i)
        {
            if (deps[i] <= 0) running_courses.push_back(i);
        }

        int cnt = 0;
        while (!running_courses.empty())
        {
            int i = running_courses.front();
            cout << i << " ";
            cnt++;
            for (const int &n: trigger[i])
            {
                if (--deps[n] <= 0)
                {
                    running_courses.push_back(n);
                }
            }
            running_courses.pop_front();
        }
        cout << endl;

        return cnt >= numCourses;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n, m;
    while (cin >> n >> m)
    {
        // n个课程
        // m个关系
        vector<vector<int>> prerequisites(m, vector<int>(2));
        for (int i = 0; i < m; ++i)
        {
            cin >> prerequisites[i][0] >> prerequisites[i][1];
        }
        printf("%d\n", int(s.canFinish(n, prerequisites)));
    }
}