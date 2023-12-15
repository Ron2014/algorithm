/*
2963. 统计好分割方案的数目

给你一个下标从 0 开始、由 正整数 组成的数组 nums。

将数组分割成一个或多个 连续 子数组，如果不存在包含了相同数字的两个子数组，则认为是一种 好分割方案 。

返回 nums 的 好分割方案 的 数目。

由于答案可能很大，请返回答案对 109 + 7 取余 的结果。

示例 1：

输入：nums = [1,2,3,4]
输出：8
解释：有 8 种 好分割方案 ：([1], [2], [3], [4]), ([1], [2], [3,4]), ([1], [2,3], [4]), ([1], [2,3,4]), ([1,2], [3], [4]), ([1,2], [3,4]), ([1,2,3], [4]) 和 ([1,2,3,4]) 。
示例 2：

输入：nums = [1,1,1,1]
输出：1
解释：唯一的 好分割方案 是：([1,1,1,1]) 。
示例 3：

输入：nums = [1,2,1,3]
输出：2
解释：有 2 种 好分割方案 ：([1,2,1], [3]) 和 ([1,2,1,3]) 。
 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 109
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;

const int MOD = pow(10, 9) + 7;

class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums) {
        unordered_map<int, pair<int, int>> sections;
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            if (sections.find(nums[i]) != sections.end())
            {
                sections[nums[i]].second = i;
            }
            else
            {
                sections[nums[i]].first = i;
                sections[nums[i]].second = i;
            }
        }
        vector<pair<int,int>> orders;
        for (const auto &p : sections)
        {
            orders.emplace_back(p.second.first, p.second.second);
        }
        sort(orders.begin(), orders.end());

        vector<pair<int, int>> result;
        for (const auto &p : orders)
        {
            if (result.empty())
            {
                result.emplace_back(p.first, p.second);
            }
            else
            {
                auto &last = result[result.size() - 1];
                if (last.second < p.first)
                {
                    result.emplace_back(p.first, p.second);
                }
                else
                {
                    last.second = max(last.second, p.second);
                }
            }
        }

        for (const auto &p : result)
        {
            printf("%d,%d ", p.first, p.second);
        }
        cout << endl;

        int ans = 1;
        for (int i = 0; i < result.size() - 1; ++i)
        {
            ans = (ans * 2) % MOD;
        }
        return ans;
    }
};

int main()
{
    Solution s;
    int n;
    while (cin >> n)
    {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        cout << s.numberOfGoodPartitions(nums) << endl;
    }
    return 0;
}