/*
某部门计划通过结队编程来进行项目开发，已知该部门有N名员工，每个员工有独一无二的职级，每三个员工形成一个小组进行结队编程，结队分组规则如下：


从部门中选出序号分别为 i、j、k 的 3 名员工，他们的职级分别为 level[i]、level [j]、level [k]

结队小组需满足： level [i] < level [j] < level [k] 或者 level [i] > level [j] > level [k] ，其中  0 <= i < j < k < n

请你按上述条件计算可能组合的小组数量。同一员工可以参加多个小组。
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

const int GROUP_SIZE = 3;

int get_group_count(vector<int> &level, int s, int e, int left, vector<int> &result)
{
    if (left == 0)
    {
        int sum = 1;
        cout << "--";
        for (int &idx: result)
        {
            cout << "lv" << idx << ":" << level[idx] << ",";
            sum *= level[idx];
        }
        cout << endl;
        return sum;
    }
    if (s > e) return 0;

    int count = 0;
    for (int i = s; i <= e; ++i)
    {
        result.push_back(i);
        count += get_group_count(level, i+1, e, left-1, result);
        result.pop_back();
    }
    return count;
}

int main(int argc, char *argv[])
{
    int n;  // 员工数量
    while (cin >> n)
    {
        vector<int> level(n);               // level[i]         第i名员工对应的等级
        unordered_map<int, int> level_map;  // level_map[level] 第level等级对应的员工数量
        for (int i = 0; i < n; ++i)
        {
            cin >> level[i];
            level_map[level[i]]++;
        }

        int level_type_cnt = level_map.size();
        if (level_type_cnt < GROUP_SIZE)
        {
            cout << 0 << endl;
        }
        else
        {
            // 从 level_type_cnt 抽 GROUP_SIZE 的可能性
            n = 0;
            for (unordered_map<int, int>::iterator it = level_map.begin(); it != level_map.end(); ++it)
            {
                printf("%3d=%d\n", it->first, it->second);
                level[n++] = it->second;
            }
            vector<int> result;
            cout << get_group_count(level, 0, n-1, GROUP_SIZE, result) << endl;
        }
    }
    return 0;
}