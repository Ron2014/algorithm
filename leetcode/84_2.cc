
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
#include <stack>
using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int cnt = heights.size();
        if (cnt <= 0) return 0;

        vector<int> lowL(cnt, -1);
        vector<int> lowR(cnt, cnt);
        stack<int> stkL;     // 单调递增
        stack<int> stkR;     // 单调递增
        for (int i = 0; i < cnt; ++i)
        {
            int h = heights[i];
            while (!stkL.empty() && heights[stkL.top()] >= h)
            {
                stkL.pop();
            }
            if (!stkL.empty()) lowL[i] = stkL.top();
            stkL.push(i);
        }
        for (int i = cnt-1; i >= 0; --i)
        {
            int h = heights[i];
            while (!stkR.empty() && heights[stkR.top()] >= h)
            {
                stkR.pop();
            }
            if (!stkR.empty()) lowR[i] = stkR.top();
            stkR.push(i);
        }

        int ans = 0, l, r, h;
        for (int i = 0; i < cnt; ++i)
        {
            h = heights[i];
            l = lowL[i] + 1;
            r = lowR[i] - 1;
            ans = max(ans, (r - l + 1) * h);
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