/*
题目描述
    给你一个字符串 s，首尾相连成一个环形，请你在环中找出 'o' 字符出现了偶数次最长
输入描述
    输入是一个小写字母组成的字符串
输出描述
    输出是一个整数
备注
    1 ≤ s.length ≤ 500000
    s 只包含小写英文字母
*/
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    char line[500001];
    while (std::cin.getline(line, sizeof(line)))
    {
        int len = strlen(line);
        if (len <= 0) break;
        int cnt = 0;
        for (int i = 0; i < len; ++i)
        {
            if (line[i] == 'o')
            {
                cnt++;
            }
        }
        if (cnt & 1 == 0)
        {
            cout << len << endl;
        }
        else
        {
            cout << len - 1 << endl;
        }
    }
    return 0;
}