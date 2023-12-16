/*
2276. 统计区间中的整数数目

给你区间的 空 集，请你设计并实现满足要求的数据结构：

新增：添加一个区间到这个区间集合中。
统计：计算出现在 至少一个 区间中的整数个数。
实现 CountIntervals 类：

CountIntervals() 使用区间的空集初始化对象
void add(int left, int right) 添加区间 [left, right] 到区间集合之中。
int count() 返回出现在 至少一个 区间中的整数个数。
注意：区间 [left, right] 表示满足 left <= x <= right 的所有整数 x 。

示例 1：

输入
["CountIntervals", "add", "add", "count", "add", "count"]
[[], [2, 3], [7, 10], [], [5, 8], []]
输出
[null, null, null, 6, null, 8]

解释
CountIntervals countIntervals = new CountIntervals(); // 用一个区间空集初始化对象
countIntervals.add(2, 3);  // 将 [2, 3] 添加到区间集合中
countIntervals.add(7, 10); // 将 [7, 10] 添加到区间集合中
countIntervals.count();    // 返回 6
                           // 整数 2 和 3 出现在区间 [2, 3] 中
                           // 整数 7、8、9、10 出现在区间 [7, 10] 中
countIntervals.add(5, 8);  // 将 [5, 8] 添加到区间集合中
countIntervals.count();    // 返回 8
                           // 整数 2 和 3 出现在区间 [2, 3] 中
                           // 整数 5 和 6 出现在区间 [5, 8] 中
                           // 整数 7 和 8 出现在区间 [5, 8] 和区间 [7, 10] 中
                           // 整数 9 和 10 出现在区间 [7, 10] 中
 

提示：

1 <= left <= right <= 10^9
最多调用  add 和 count 方法 总计 10^5 次
调用 count 方法至少一次
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class CountIntervals {
    int m_cnt = 0;
    map<int, int> m_regions;

public:
    CountIntervals() {

    }
    
    void add(int left, int right) {
        auto it = m_regions.upper_bound(right);
        if (it != m_regions.begin())
        {
            --it;
        }

        while (it != m_regions.end() && it->first <= right && it->second >= left)
        {
            int l = it->first;
            int r = it->second;
            left = min(left, l);
            right = max(right, r);

            m_regions.erase(it);
            m_cnt -= (r - l + 1);

            it = m_regions.upper_bound(right);
            if (it != m_regions.begin())
            {
                --it;
            }
        }

        m_regions[left] = right;
        m_cnt += (right - left + 1);
    }
    
    int count() {
        return m_cnt;
    }
};

int main()
{
    CountIntervals ci;
    string cmd;
    while (cin >> cmd)
    {
        int len = cmd.length();
        if (len <= 0) break;

        if (cmd == "add")
        {
            int left, right;
            cin >> left >> right;
            ci.add(left, right);
        }
        else if (cmd == "count")
        {
            cout << ci.count() << endl;
        }
    }
    return 0;
}