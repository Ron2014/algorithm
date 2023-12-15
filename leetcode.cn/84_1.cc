
/*
84. 柱状图中最大的矩形

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

示例 1:

输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10

示例 2：

输入： heights = [2,4]
输出： 4

提示：

1 <= heights.length <=10^5
0 <= heights[i] <= 10^4
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int cnt = heights.size();
        if (cnt <= 0) return 0;

        int ans = 0;
        for (int l = 0; l < cnt; ++l)
        {
            int minH = INT_MAX;
            for (int r = l; r < cnt; ++r)
            {
                minH = min(minH, heights[r]);
                ans = max(ans, minH * (r - l + 1));
            }
        }
        return ans;
    }
};

int main()
{
    Solution so;
    int n;
    while (cin >> n)
    {
        vector<int> heights(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> heights[i];
        }
        cout << so.largestRectangleArea(heights) << endl;
    }
    return 0;
}