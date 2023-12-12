/*
主管期望你来实现英文输入法单词联想功能。需求如下：

依据用户输入的单词前缀，从已输入的英文语句中联想出用户想输入的单词，按字典序输出联想到的单词序列，如果联想不到，请输出用户输入的单词前缀。

注意：

1.  英文单词联想时，区分大小写

2.  缩略形式如”don't”，判定为两个单词，”don”和”t”

3.  输出的单词序列，不能有重复单词，且只能是英文单词，不能有标点符号
*/

#include <iostream>
#include <cstring>
#include <map>
using namespace std;

class CPreMap
{
    map<char, CPreMap> m_mp;

public:
    CPreMap() {}

    void input(const char *sz, int len)
    {
        if (len <= 0)
        {
            return;
        }
        m_mp[sz[0]].input(sz+1, len-1);
    }

    void show_list(char *buff, int idx)
    {
        if (m_mp.size() <= 0)
        {
            buff[idx] = '\0';
            cout << buff << endl;
            return;
        }

        for (map<char, CPreMap>::iterator it = m_mp.begin(); it != m_mp.end(); ++it)
        {
            buff[idx] = it->first;
            it->second.show_list(buff, idx+1);
        }
    }
    
    void think(const char *sz, int len, int idx)
    {
        if (idx >= len)
        {
            char buffer[1001];
            strncpy(buffer, sz, len);
            show_list(buffer, len);
            return;
        }
        if (m_mp.size() <= 0) return;
        m_mp[sz[idx]].think(sz, len, idx+1);
    }
};

CPreMap g_map;

int main(int argc, char *argv[])
{
    string cmd, s;
    while (cin >> cmd)
    {
        int len = cmd.length();
        if (len <= 0) break;

        if (cmd == "input")
        {
            cin >> s;
            g_map.input(s.c_str(), s.length());
        }
        else if (cmd == "think")
        {
            cin >> s;
            g_map.think(s.c_str(), s.length(), 0);
        }

    }
    return 0;
}