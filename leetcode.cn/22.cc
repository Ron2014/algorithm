/*
22. 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]

示例 2：
输入：n = 1
输出：["()"]
 
提示：

1 <= n <= 8
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
    void dfs(int lcnt, int rcnt, int n, vector<char> &result, vector<string> &fresult)
    {
        // 解决 result[idx] = ?
        int idx = lcnt + rcnt;
        if (idx < (n<<1))
        {
            if (lcnt < n)
            {
                result[idx] = '(';
                dfs(lcnt+1, rcnt, n, result, fresult);
            }
            if (rcnt < lcnt)
            {
                result[idx] = ')';
                dfs(lcnt, rcnt+1, n, result, fresult);
            }
        }
        else
        {
            result[idx] = '\0';
            fresult.emplace_back(&result[0]);
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        int lcnt = 0;
        int rcnt = 0;
        vector<char> result((n<<1)+1);
        vector<string> fresult;
        dfs(0, 0, n, result, fresult);
        return fresult;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n;
    while (cin >> n)
    {
        for (const string &r : s.generateParenthesis(n))
        {
            cout << r << " ";
        }
        cout << endl;
    }
    return 0;
}
