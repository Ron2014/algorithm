/*
给你一个字符串 s，字符串s首尾相连成一个环形 ，请你在环中找出'l'、'o'、'x' 字符都恰好出现了偶数次最长子字符串的长度。
*/

#include <iostream>
#include <unordered_map>
using namespace std;

bool check(unordered_map<char, int> &mp)
{
    if (mp['l'] & 1 > 0) return false;
    if (mp['o'] & 1 > 0) return false;
    if (mp['x'] & 1 > 0) return false;
    return true;
}

int main(int argc, char *argv[])
{
    // l o x 都是偶数       len
    // l o x 有1个是奇数    len-1
    // l o x 有2个是奇数    假设xy为奇数，z为偶数，找到不包含z的xy最短路径p, len-p
    // l o x 有3个是奇数    找到只包含1个lox的最短路径p, len-p

    string s;
    while (cin >> s)
    {
        int len = s.length();
        if (len <= 0) break;

        int maxn = -1;
        for (int i = 0; i < len; ++i)
        {
            unordered_map<char, int> mp;
            for (int j = i; j < len + i; ++j)
            {
                mp[s[j%len]]++;
                if (check(mp) && j - i + 1 > maxn)
                {
                    maxn = j - i + 1;
                    for (int k = i; k <= j; ++k)
                    {
                        cout << s[k%len];
                    }
                    cout << endl;
                }
            }
        }
        cout << maxn << endl;
    }
    return 0;
}