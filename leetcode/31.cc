/*
31. 下一个排列

整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。

例如，arr = [1,2,3] ，以下这些都可以视作 arr 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1] 。
整数数组的 下一个排列 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 下一个排列 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。
类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。
而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。
给你一个整数数组 nums ，找出 nums 的下一个排列。

必须 原地 修改，只允许使用额外常数空间。

示例 1：

输入：nums = [1,2,3]
输出：[1,3,2]
示例 2：

输入：nums = [3,2,1]
输出：[1,2,3]
示例 3：

输入：nums = [1,1,5]
输出：[1,5,1]
 

提示：

1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int cnt = nums.size();
        if (cnt <= 0) return;

        stack<int> stk;                 // 单调递增
        vector<int> lowL(cnt, -1);      // lowL[i] nums[i] 左边第一个更小的数

        // i, LowL, nums[i]
        auto cmp_tuple = [](const tuple<int,int,int> &a, const tuple<int,int,int> &b)
        {
            int w1 = 0, w2 = 0, rate = 1;
            // nums[i] 越小越优先
            if (get<2>(a) < get<2>(b))
            {
                w2 += rate;
            }
            if (get<2>(a) > get<2>(b))
            {
                w1 += rate;
            }
            rate <<= 1;
            // lowL 越大越优先
            if (get<1>(a) > get<1>(b))
            {
                w2 += rate;
            }
            if (get<1>(a) < get<1>(b))
            {
                w1 += rate;
            }
            return w1 > w2;
        };
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, decltype(cmp_tuple)> q(cmp_tuple);
        for (int i = 0; i < cnt; ++i)
        {
            int n = nums[i];
            while (!stk.empty() && nums[stk.top()] >= n)
            {
                stk.pop();
            }
            if(stk.empty())
            {
                q.emplace(i, -1, nums[i]);
            }
            else
            {
                q.emplace(i, stk.top(), nums[i]);
            }
            stk.push(i);
        }
        
        auto [ti, tj, n] = q.top();
        if (ti >= 0 && tj >= 0)
        {
            swap(nums[ti], nums[tj]);
            sort(nums.begin()+tj+1, nums.end());
        }
        else
        {
            reverse(nums.begin(), nums.end());
        }
    }
};

int main()
{
    Solution so;
    int n;
    while (cin >> n)
    {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i)
            cin >> nums[i];
        so.nextPermutation(nums);
        for (const int &k : nums)
        {
            printf("%d ", k);
        }
        cout << endl;
    }
    return 0;
}