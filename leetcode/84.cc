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

        vector<int> lowL(cnt, -1);      // 向左看，最低高度所在的下标
        vector<int> stkL(cnt, -1);      // 高度单调递增的下标
        int stkL_len = 0;
        for (int i = 0; i < cnt; ++i)
        {
            int h = heights[i];
            int area = h;
            while (stkL_len > 0 && heights[stkL[stkL_len-1]] >= h)
            {
                // 这个矩形比前面的矩形矮
                // 会对后面的面积计算造成影响
                stkL_len--;
            }
            stkL[stkL_len++] = i;
            lowL[i] = stkL[0];
        }

        vector<int> lowR(cnt, -1);      // 向右看，最低高度所在的下标
        vector<int> stkR(cnt, -1);      // 高度单调递增的下标
        int stkR_len = 0;
        for (int i = cnt-1; i >= 0; --i)
        {
            int h = heights[i];
            int area = h;
            while (stkR_len > 0 && heights[stkR[stkR_len-1]] >= h)
            {
                // 这个矩形比前面的矩形矮
                // 会对后面的面积计算造成影响
                stkR_len--;
            }
            stkR[stkR_len++] = i;
            lowR[i] = stkR[0];
        }

        int max_area = INT_MIN;
        for (int k = 0; k < cnt; ++k)
        {
            int i = lowL[k];
            int j = lowR[k];
            while (i <= k && j >= k)
            {
                int area = min(heights[i], heights[j]) * (j - i + 1);
                max_area = max(max_area, area);
                if (heights[i] < heights[j])
                {
                    i++;
                }
                else
                {
                    j--;
                }
            }
            
        }
        return max_area;
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