/*
72. 编辑距离
给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符

示例 1：

输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

示例 2：

输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
 

提示：

0 <= word1.length, word2.length <= 500
word1 和 word2 由小写英文字母组成
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int len1 = word1.length();
        int len2 = word2.length();
        if (len1 <= 0) return len2;
        if (len2 <= 0) return len1;

        // dp[i][j] word1[0...i-1] word2[0...j-1] 的操作距离
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
        for (int i = 0; i <= len1; ++i)
        {
            dp[i][0] = i;   // B 插入字符
        }
        for (int i = 0; i <= len2; ++i)
        {
            dp[0][i] = i;   // A 插入字符
        }
        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                int a = dp[i-1][j] + 1;
                int b = dp[i][j-1] + 1;
                int c = dp[i-1][j-1];
                if (word1[i-1] != word2[j-1])
                {
                    c++;    // A B 其中选一个替换字符
                }
                dp[i][j] = min(min(a,b), c);
            }
        }
        return dp[len1][len2];
    }
};

int main()
{
    Solution so;
    string word1, word2;
    while (cin >> word1 >> word2)
    {
        cout << so.minDistance(word1, word2) << endl;
    }
    return 0;
}