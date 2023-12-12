/*
2454. 下一个更大元素 IV

给你一个下标从 0 开始的非负整数数组 nums 。对于 nums 中每一个整数，你必须找到对应元素的 第二大 整数。

如果 nums[j] 满足以下条件，那么我们称它为 nums[i] 的 第二大 整数：

j > i
nums[j] > nums[i]
恰好存在 一个 k 满足 i < k < j 且 nums[k] > nums[i] 。
如果不存在 nums[j] ，那么第二大整数为 -1 。

比方说，数组 [1, 2, 4, 3] 中，1 的第二大整数是 4 ，2 的第二大整数是 3 ，3 和 4 的第二大整数是 -1 。
请你返回一个整数数组 answer ，其中 answer[i]是 nums[i] 的第二大整数。

示例 1：

输入：nums = [2,4,0,9,6]
输出：[9,6,6,-1,-1]
解释：
下标为 0 处：2 的右边，4 是大于 2 的第一个整数，9 是第二个大于 2 的整数。
下标为 1 处：4 的右边，9 是大于 4 的第一个整数，6 是第二个大于 4 的整数。
下标为 2 处：0 的右边，9 是大于 0 的第一个整数，6 是第二个大于 0 的整数。
下标为 3 处：右边不存在大于 9 的整数，所以第二大整数为 -1 。
下标为 4 处：右边不存在大于 6 的整数，所以第二大整数为 -1 。
所以我们返回 [9,6,6,-1,-1] 。

示例 2：

输入：nums = [3,3]
输出：[-1,-1]
解释：
由于每个数右边都没有更大的数，所以我们返回 [-1,-1] 。
 

提示：

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    vector<int> secondGreaterElement(vector<int> &nums)
    {
        vector<int> result;
        int n = nums.size();
        if (n <= 0) return result;
        result.assign(n, -1);
        vector<int> cnt(n, 0);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> targets[2];

        for (int i = 0; i < n; ++i)
        {
            while (!targets[1].empty())
            {
                auto [x, j] = targets[1].top();
                if (nums[i] > nums[j])
                {
                    result[j] = nums[i];
                    targets[1].pop();
                }
                else
                {
                    break;
                }
            }
            while (!targets[0].empty())
            {
                auto [x, j] = targets[0].top();
                if (nums[i] > nums[j])
                {
                    targets[1].emplace(x, j);
                    targets[0].pop();
                }
                else
                {
                    break;
                }
            }
            targets[0].emplace(nums[i], i);
        }
        return result;
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
        vector<int> result = s.secondGreaterElement(nums);
        for (const int &v : result)
        {
            printf("%d ", v);
        }
        cout << endl;
    }
    return 0;
}