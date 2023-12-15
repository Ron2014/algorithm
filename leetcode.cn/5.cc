/*
给你一个字符串 s，找到 s 中最长的回文子串。

如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。

示例 1：

输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。

示例 2：

输入：s = "cbbd"
输出："bb"

提示：

1 <= s.length <= 1000
s 仅由数字和英文字母组成
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    int get_max_substr(string &str, int s, int e, int len)
    {
        while (s>=0 && e<len && str[s] == str[e])
        {
            s--;
            e++;
        }
        return e - s - 1;
    }

public:
    string longestPalindrome(string str)
    {
        int len = str.length();
        if (len <= 0) return "";

        int max_len = 0;
        int max_i = -1;
        for (int i = 0; i < len; ++i)
        {
            int sublen = get_max_substr(str, i, i, len);
            if (sublen > max_len)
            {
                max_len = sublen;
                max_i = i - (sublen>>1);
            }
            sublen = get_max_substr(str, i, i+1, len);
            if (sublen > max_len)
            {
                max_len = sublen;
                max_i = i - (sublen>>1) + 1;
            }
        }
        if (max_len <= 0) return "";
        else return str.substr(max_i, max_len);
    }
};

int main()
{
    Solution so;
    string s;
    while (cin >> s)
    {
        cout << so.longestPalindrome(s) << endl;
    }
    return 0;
}