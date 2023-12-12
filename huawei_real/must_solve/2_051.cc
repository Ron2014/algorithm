/*
开头和结尾都是元音字母（aeiouAEIOU）的字符串为 元音字符串 ，其中混杂的非元音字母数量为其 瑕疵度 。比如:

·         “a” 、 “aa”是元音字符串，其瑕疵度都为0

·         “aiur”不是元音字符串（结尾不是元音字符）

·         “abira”是元音字符串，其瑕疵度为2

给定一个字符串，请找出指定瑕疵度的最长元音字符子串，并输出其长度，如果找不到满足条件的元音字符子串，输出0。

子串：字符串中任意个连续的字符组成的子序列称为该字符串的子串。
*/

#include <iostream>
#include <string>
#include <cstring>
#include <set>
using namespace std;

set<char> source = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

int main(int argc, char *argv[])
{
    int n;
    string s;
    while (cin >> s >> n)
    {
        int len = s.length();
        if (len <= 0) break;

        set<int> pos;
        int i = 0, j = 0;
        int maxlen = 0;
        int maxi = -1;

        while (i < len && j < len)
        {
            while (j < len)
            {
                if (source.find(s[j]) == source.end())
                {
                    // 非元音
                    pos.insert(j);
                    if (pos.size() == n+1)
                    {
                        break;
                    }
                }
                j++;
            }

            if (pos.size() == n+1)
            {
                int sublen = j - i;
                if (sublen > maxlen)
                {
                    maxlen = sublen;
                    maxi = i;
                }

                auto it = pos.begin();
                i = *it + 1;
                pos.erase(it);
                j++;
            }
            else
            {
                if (pos.size() == n)
                {
                    int sublen = j - i;
                    if (sublen > maxlen)
                    {
                        maxlen = sublen;
                        maxi = i;
                    }
                }
            }
        }

        if (maxi >= 0)
        {
            cout << s.substr(maxi, maxlen) << endl;
        }
        cout << maxlen << endl;
    }
    return 0;
}
