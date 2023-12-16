#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

vector<unordered_map<char, int>> g_state = {
    {{'d', 1,},},
    {{'d', 1,}, {'.', 0},},
};
vector<pair<const char *, const char *>> g_private_range = {
    {"10.0.0.0",    "10.255.255.255",   },
    {"172.16.0.0",  "172.31.255.255",   },
    {"192.168.0.0", "192.168.255.255",  },
};
vector<pair<unsigned char, unsigned char>> g_category = {
    // MASK, VALUE
    {0x80, 0x00},   // A    1000 0000       0000 0000
    {0xC0, 0x80},   // B    1100 0000       1000 0000
    {0xE0, 0xC0},   // C    1110 0000       1100 0000
    {0xF0, 0xE0},   // D    1111 0000       1110 0000
    {0xF0, 0xF0},   // E    1111 0000       1111 0000
};

// #define SHOW(x) printf("0x%x|%x|%x|%x\n", ((x)>>24)&0xFF, ((x)>>16)&0xFF, ((x)>>8)&0xFF, (x)&0xFF)
#define SHOW(x)

const int MAX_NUM = (1<<8) - 1;
const int MAX_DOT_NUM = 3;
const int END_STATE = 1;

bool dot2num(const char *sz, int len, unsigned char *ip)
{
    char ch;
    int stateIdx = 0;
    int dot = 0;
    for (int i = 0; i < len; ++i)
    {
        if (isdigit(sz[i]))
        {
            ch = 'd';
            if (ip[MAX_DOT_NUM - dot] * 10 + sz[i] - '0' > MAX_NUM) return false;
            ip[MAX_DOT_NUM - dot] = ip[MAX_DOT_NUM - dot] * 10 + sz[i] - '0';
        }
        else if (sz[i] == '.')
        {
            ch = '.';
            dot++;
            if (dot > MAX_DOT_NUM) return false;
        }
        else
        {
            ch = '?';
        }
        unordered_map<char, int>::iterator it = g_state[stateIdx].find(ch);
        if (it == g_state[stateIdx].end()) return false;
        stateIdx = it->second;
    }
    if (stateIdx != END_STATE) return false;
    if (dot != MAX_DOT_NUM) return false;
    return true;
}

bool check_mask(unsigned int mask)
{
    if (mask & 1 == 1) return false;
    bool flag = false;
    while (mask > 0)
    {
        if ((mask & 1) > 0) flag = true;
        else if (flag) return false;
        mask >>= 1;
    }
    return flag;
}

int get_category(unsigned char head_byte)
{
    for (int i = 0; i < g_category.size(); ++i)
    {
        if ((head_byte & g_category[i].first) == g_category[i].second)
        {
            return i;
        }
    }
    return -1;
}

bool is_private(vector<pair<unsigned int, unsigned int>> &private_range, unsigned int ip)
{
    for (auto &p : private_range)
    {
        if (ip >= p.first && ip <= p.second)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    char line[128];
    vector<int> result(g_category.size(), 0);
    const int A = 0, B = 1, C = 2, D = 3, E = 4;
    int ERR = 0, PRI = 0;

    vector<pair<unsigned int, unsigned int>> private_range(g_private_range.size());
    for (int i = 0; i < g_private_range.size(); ++i)
    {
        dot2num(g_private_range[i].first,   strlen(g_private_range[i].first),   (unsigned char *)&private_range[i].first);
        dot2num(g_private_range[i].second,  strlen(g_private_range[i].second),  (unsigned char *)&private_range[i].second);
    }

    while (std::cin.getline(line, sizeof(line)))
    {
        int n = strlen(line);
        if (n <= 0) break;

        int i = 0;
        while (i < n && line[i] != '~') i++;
        if (i >= n || line[i] != '~')
        {
            ERR++;
            continue;
        }

        unsigned int ip = 0, mask = 0;
        if (dot2num(line, i, (unsigned char *)&ip) && dot2num(line+i+1, n-i-1, (unsigned char *)&mask))
        {
            SHOW(ip);
            SHOW(mask);
            unsigned char head_byte = (ip>>24)&0xFF;
            if (head_byte == 0 || head_byte == 127) continue;;
            if (!check_mask(mask))
            {
                // cout << "mask error" << endl;
                ERR++;
                continue;
            }
            int idx = get_category(head_byte);
            if (idx < 0)
            {
                // cout << "get_category error" << endl;
                ERR++;
                continue;
            }
            if (is_private(private_range, ip & mask))
            {
                PRI++;
            }
            result[idx]++;
        }
        else
        {
            // cout << "dot2num error" << endl;
            ERR++;
        }
    }
    for (int &num : result)
    {
        cout << num << " ";
    }
    cout << ERR << " " << PRI << endl;
    return 0;
}