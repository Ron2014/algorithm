/*
763. 划分字母区间

给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。

注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。

返回一个表示每个字符串片段的长度的列表。

示例 1：
输入：s = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。 

示例 2：
输入：s = "eccbbbbdec"
输出：[10]
 

提示：

1 <= s.length <= 500
s 仅由小写英文字母组成
*/

/*
统计各字母对应的区间，然后合并区间
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Node
{
public:
    char ch;
    int s;
    int e;
    Node():ch('\0'),s(-1),e(-1) {}
};

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int len = s.length();
        vector<int> lastpos(26, -1);
        for (int i = 0; i < len; ++i)
        {
            lastpos[s[i] - 'a'] = i;
        }
        vector<int> result;
        int startIdx = 0, endIdx = 0;
        for (int i = 0; i < len; ++i)
        {
            endIdx = max(endIdx, lastpos[s[i] - 'a']);
            if (i == endIdx)
            {
                result.push_back(endIdx - startIdx + 1);
                startIdx = endIdx + 1;
            }
        }
        return result;
    }
};

int main(int argc, char *argv[])
{
    Solution so;
    string s;
    while (cin >> s)
    {
        int i = 0;
        for (const int &len : so.partitionLabels(s))
        {
            // cout << s.substr(i, len) << endl;
            // i += len;
            cout << len << endl;
        }
    }
    return 0;
}