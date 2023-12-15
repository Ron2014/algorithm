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
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return false;
        sort(nums.begin(), nums.end());
        int sum = 0;
        for (const int &n: nums)
        {
            sum += n;
        }
        if (sum & 1) return false;
        sum >>= 1;

        int i = 0, j = 0, subsum = 0;
        while (i < n && j < n)
        {
            while (j < n && subsum < sum)
            {
                subsum += nums[j];
                j++;
            }
            if (subsum == sum) return true;
            while (i < n && subsum > sum)
            {
                subsum -= nums[i];
                i++;
            }
            if (subsum == sum) return true;
        }
        return false;
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