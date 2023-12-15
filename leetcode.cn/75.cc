/*
75. 颜色分类

给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

必须在不使用库内置的 sort 函数的情况下解决这个问题。

示例 1：

输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]

示例 2：

输入：nums = [2,0,1]
输出：[0,1,2]

提示：

n == nums.length
1 <= n <= 300
nums[i] 为 0、1 或 2
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int len = nums.size();
        if (len <= 0) return;

        int i, j, cnt = 0;
        for (int t = 0; t < 2; ++t)
        {
            i = cnt, j = len;
            cnt = 0;
            while (i < j)
            {
                do
                {
                    // nums[j] 从右往左第一个为t的数
                    j--;
                    if (nums[j] == t)
                    {
                        cnt++;
                        break;
                    }
                } while (i < j);
                while (i < j)
                {
                    // nums[i] 从左往右第一个不为t的数
                    if (nums[i] != t)
                    {
                        break;
                    }
                    cnt++;
                    i++;
                }
                if (i < j)
                {
                    swap(nums[i], nums[j]);
                    i++;
                }
            }
        }
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
            cin >> nums[i];
        s.sortColors(nums);
        for (int i = 0; i < n; ++i)
            printf("%d ", nums[i]);
        cout << endl;
    }
    return 0;
}