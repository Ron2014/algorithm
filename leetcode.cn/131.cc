/*
131. 分割回文串

给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

回文串 是正着读和反着读都一样的字符串。

示例 1：

输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]

示例 2：

输入：s = "a"
输出：[["a"]]
 

提示：

1 <= s.length <= 16
s 仅由小写英文字母组成
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
    void dfs(vector<vector<bool>> &is_loop, string &s, int i, int len, vector<string> &res, vector<vector<string>> &ans)
    {
        // 已得到 s[0...i-1] 的解 ans
        if (i >= len)
        {
            ans.push_back(res);
            return;
        }

        for (int j = i; j < len; ++j)
        {
            if (is_loop[i][j])
            {
                res.push_back(s.substr(i, j - i + 1));
                dfs(is_loop, s, j + 1, len, res, ans);
                res.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        int len = s.length();
        if (len <= 0) return ans;
        vector<vector<bool>> is_loop(len, vector<bool>(len, false));
        for (int i = len - 1; i >= 0; --i)
        {
            for (int j = 0; j <= i; ++j)
            {
                is_loop[i][j] = true;
            }
            for (int j = i + 1; j < len; ++j)
            {
                is_loop[i][j] = s[i] == s[j] && is_loop[i+1][j-1];
            }
        }
        vector<string> res;
        dfs(is_loop, s, 0, len, res, ans);
        return ans;
    }
};

int main()
{
    Solution so;
    string s;
    while (cin >> s)
    {
        vector<vector<string>> result = so.partition(s);
        for (const auto &v : result)
        {
            for (const string &str : v)
            {
                cout << str << " ";
            }
            cout << endl;
        }
    }
    return 0;
}