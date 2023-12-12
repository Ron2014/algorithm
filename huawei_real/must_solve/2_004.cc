/*
给定一个字符串，只包含字母和数字，按要求找出字符串中的最长（连续）子串的长度
字符串本身是其最长的子串

子串要求：
1、 只包含1个字母(a~z, A~Z)，其余必须是数字
2、 字母可以在子串中的任意位置；

如果找不到满足要求的子串，如全是字母或全是数字，则返回-1。
*/
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    string s;
    while (getline(std::cin, s))
    {
        int len = s.length();
        if (len <= 0) break;

        vector<int> numL(len+2, 0);   // numL[i] 包括s[i-1]在内，i左侧连续数字的长度
        vector<int> numR(len+2, 0);   // numR[i] 包括s[i-1]在内，i右侧连续数字的长度

        for (int i = 1; i <= len; ++i)
        {
            if (isdigit(s[i-1]))
            {
                numL[i] = numL[i-1] + 1;
            }
            else
            {
                numL[i] = 0;
            }
        }
        for (int i = len; i >= 1; --i)
        {
            if (isdigit(s[i-1]))
            {
                numR[i] = numR[i+1] + 1;
            }
            else
            {
                numR[i] = 0;
            }
        }
        int maxn = -1;
        for (int i = 1; i <= len; ++i)
        {
            if (isalpha(s[i-1]) && (numL[i-1] > 0 || numR[i+1] > 0))
            {
                int n = 1 + numL[i-1] + numR[i+1];
                if (n > maxn) maxn = n;
            }
        }
        cout << maxn << endl;
        for (int i = 0; i < numL.size(); ++i)
        {
            cout << numL[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < numR.size(); ++i)
        {
            cout << numR[i] << " ";
        }
        cout << endl;
    }
    return 0;
}