/*
4. 寻找两个正序数组的中位数

给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。

示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2

示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

提示：

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int n1 = nums1.size();
        int n2 = nums2.size();
        int len = n1 + n2;
        int half = (len>>1);
        int i1 = 0, i2 = 0;
        int last = -1, curr = -1;
        for (int i = 0; i <= half; ++i)
        {
            last = curr;
            if ((i1 < n1 && i2 < n2 && nums1[i1] < nums2[i2]) || (i2 >= n2))
            {
                curr = nums1[i1++];
            }
            else
            {
                curr = nums2[i2++];
            }
        }
        if (len & 1)
        {
            return curr;
        }
        else
        {
            return (curr + last) * 0.5;
        }
    }
};

int main()
{
    Solution so;
    int n1, n2;
    while (cin >> n1 >> n2)
    {
        vector<int> nums1(n1);
        vector<int> nums2(n2);
        for (int i = 0; i < n1; ++i)
        {
            cin >> nums1[i];
        }
        for (int i = 0; i < n2; ++i)
        {
            cin >> nums2[i];
        }
        cout << so.findMedianSortedArrays(nums1, nums2) << endl;
    }
    return 0;
}