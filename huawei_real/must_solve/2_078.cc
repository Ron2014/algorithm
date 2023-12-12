/*
某业务需要根据终端的IP地址获取该终端归属的城市，可以根据公开的IP地址池信息查询归属城市。地址池格式如下城市名=起始IP,结束IP，起始和结束地址按照英文逗号分隔，多个地址段采用英文分号分隔。

比如City1=1.1.1.1,1.1.1.2;City1=1.1.1.11,1.1.1.16;City2=3.3.3.3,4.4.4.4;City3=2.2.2.2,6.6.6.6。
一个城市可以有多个IP段，比如City1有2个IP段。城市间也可能存在包含关系，如City3的IP段范围包含City2的IP段范围。现在要根据输入的IP列表，返回最佳匹配的城市列表。

注：最佳匹配即包含待查询IP且长度最小的IP段，比如例子中3.4.4.4最佳匹配是City2=3.3.3.3,4.4.4.4，5.5.5.5的最佳匹配是City3=2.2.2.2,6.6.6.6。
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include "common.h"
using namespace std;

class City
{
public:
    int idx;
    vector<pair<vector<int>, vector<int>>> ranges;

    City():idx(-1) {}

    void init(int idx, vector<int> &ip0, vector<int> &ip1)
    {
        this->idx = idx;
        this->ranges.emplace_back(ip0, ip1);
    }

    void show()
    {
        int n = ranges.size();
        for (int i = 0; i < n; ++i)
        {
            vector<int> &min_ip = ranges[i].first;
            vector<int> &max_ip = ranges[i].second;
            printf("[%d,%d] %d.%d.%d.%d ~ %d.%d.%d.%d\n", idx, i,
                min_ip[0], min_ip[1], min_ip[2], min_ip[3],
                max_ip[0], max_ip[1], max_ip[2], max_ip[3]);
        }
    }

    int in(vector<int> &ip)
    {
        int n = ranges.size();
        for (int i = 0; i < n; ++i)
        {
            vector<int> &min_ip = ranges[i].first;
            vector<int> &max_ip = ranges[i].second;
            if (ip >= min_ip && ip <= max_ip) return i;
        }
        return -1;
    }

    bool better(City &other, int oi, int i)
    {
        pair<vector<int>, vector<int>> &op = other.ranges[oi];
        pair<vector<int>, vector<int>> &p = ranges[i];
        if (op.first < p.first) return true;
        if (op.second > p.second) return true;
        return false;
    }
};

int main(int argc, char *argv[])
{
    char line[1001];
    while (std::cin.getline(line, sizeof(line)))
    {
        int len = strlen(line);
        if (len <= 0) break;

        unordered_map<int, City> citys;
        int i = 0;
        char *sz = line;
        while (i < len)
        {
            int idx;
            vector<int> ip0(4);
            vector<int> ip1(4);
            while (i < len && line[i]!=';') ++i;
            if (i < len)
            {
                line[i++] = '\0';
            }
            sscanf(sz, "City%d=%d.%d.%d.%d,%d.%d.%d.%d", &idx,
                &ip0[0], &ip0[1], &ip0[2], &ip0[3],
                &ip1[0], &ip1[1], &ip1[2], &ip1[3]);
            citys[idx].init(idx, ip0, ip1);
            sz = line + i;
        }
        // for (auto &p : citys)
        // {
        //     p.second.show();
        // }

        while (std::cin.getline(line, sizeof(line)))
        {
            int len = strlen(line);
            if (len <= 0) break;

            vector<int> ip(4);
            sscanf(line, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

            int matched = -1;
            int matchedi = -1;
            for (auto &p : citys)
            {
                int idx = p.second.in(ip);
                if (idx >= 0)
                {
                    if (matched < 0 || p.second.better(citys[matched], matchedi, idx))
                    {
                        matched = p.second.idx;
                        matchedi = idx;
                    }
                }
            }
            if (matched < 0)
            {
                cout << "null" << endl;
            }
            else
            {
                citys[matched].show();
            }
        }
    }
    return 0;
}