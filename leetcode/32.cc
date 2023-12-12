/*
32. 最长有效括号

给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。

示例 1：

输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"
示例 2：

输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"
示例 3：

输入：s = ""
输出：0
 

提示：

0 <= s.length <= 3 * 104
s[i] 为 '(' 或 ')'
*/
#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len <= 0) return 0;

        int ans = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < len; ++i)
        {
            if (s[i] == '(')
            {
                stk.push(i);
            }
            else
            {
                stk.pop();
                if (stk.empty())
                {
                    stk.push(i);
                }
                else
                {
                    ans = max(ans, i - stk.top());
                }
            }
        }
        return ans;
    }
};

int main()
{
    Solution so;
    string s;
    while (cin >> s)
    {
        cout << so.longestValidParentheses(s);
    }
    return 0;
}