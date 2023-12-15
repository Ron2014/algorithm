/*
416. 分割等和子集

给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例 1：

输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。

示例 2：

输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。
 

提示：

1 <= nums.length <= 200
1 <= nums[i] <= 100
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) return false;
        int sum = 0;
        int maxn = INT_MIN;
        for (const int &n: nums)
        {
            sum += n;
            maxn = max(maxn, n);
        }
        if (sum & 1) return false;
        sum >>= 1;
        if (maxn > sum) return false;
        sort(nums.begin(), nums.end());

        // dp[i] 累计和能加到i的近似值
        vector<int> dp(sum+1);
        for (int i = 0; i < len; ++i)
        {
            int n = nums[i];
            for (int j = sum; j >= nums[i]; --j)
            {
                dp[j] = max(dp[j], dp[j-n] + n);
            }
        }
        return dp[sum] == sum;
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
        cout << int(so.canPartition(nums)) << endl;
    }
    return 0;
}