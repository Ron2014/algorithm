/*
198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

示例 1：

输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1)，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。

示例 2：

输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2)，偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。

提示：

1 <= nums.length <= 100
0 <= nums[i] <= 400
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
     int rob(vector<int> &nums)
     {
          int n = nums.size();
          vector<int> dp(n, 0);   // dp[i] 0~i范围内的最高金额
          for (int i = 0; i < n; ++i)
          {
               int sum = nums[i] + ((i>=2)?dp[i-2]:0);
               dp[i] = max(sum, (i>0)?dp[i-1]:0);
          }
          return dp[n-1];
     }
};

int main(int argc, char *argv[])
{
     int n;
     Solution s;
     while (cin >> n)
     {
          vector<int> nums(n);
          for (int i = 0; i < n; ++i)
          {
               cin >> nums[i];
          }
          cout << s.rob(nums) << endl;
     }
     return 0;
}
