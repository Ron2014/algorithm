/*
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 
满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
请你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。
示例 1：
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n-2; ++i)
        {
            if (i > 0 && nums[i] == nums[i-1]) continue;            // 过滤重复的 num[i]
            int target = 0 - nums[i];                               // 越来越小
            int k = n - 1;                                          // num[k] 越来越小
            for (int j = i + 1; j < k; ++j)
            {                
                if (j>i+1 && nums[j] == nums[j-1]) continue;        // 过滤重复的 num[j]
                while (j < k && nums[j] + nums[k] > target) --k;
                if (j == k) break;                                  // 不满足条件了
                if (nums[j] + nums[k] == target)
                {
                    ret.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
        return ret;
    }
};

int main(int argc, char *argv[])
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
        vector<vector<int>> result = s.threeSum(nums);
        for (const vector<int> &v: result)
        {
            for (const int &n : v)
            {
                printf("%d ", n);
            }
            cout << endl;
        }
    }
    return 0;
}