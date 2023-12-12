/*
输入两个字符串S和L，都只包含英文小写字母。S长度<=100，L长度<=500,000。判定S是否是L的有效字串。

判定规则：S中的每个字符在L中都能找到（可以不连续），且S在Ｌ中字符的前后顺序与S中顺序要保持一致。（例如，S="ace"是L="abcde"的一个子序列且有效字符是a、c、e，而"aec"不是有效子序列，且有效字符只有a、e）
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    string S, L;
    while (cin >> S >> L)
    {
        const char *szS = S.c_str();
        const char *szL = L.c_str();
        bool bIsSubstr = false;
        while (*szL != '\0')
        {
            if (*szS == *szL)
            {
                if (*(++szS) == '\0')
                {
                    bIsSubstr = true;
                    break;
                }
            }
            szL++;
        }
        cout << (int)bIsSubstr << endl;
    }
    return 0;
}