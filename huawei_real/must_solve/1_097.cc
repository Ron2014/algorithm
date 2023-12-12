/*
某个产品的RESTful API集合部署在服务器集群的多个节点上，近期对客户端访问日志进行了采集，需要统计各个API的访问频次，根据热点信息在服务器节点之间做负载均衡，现在需要实现热点信息统计查询功能。
RESTful API的由多个层级构成，层级之间使用 / 连接，如 /A/B/C/D 这个地址，A属于第一级，B属于第二级，C属于第三级，D属于第四级。
现在负载均衡模块需要知道给定层级上某个名字出现的频次，未出现过用0次表示，实现这个功能。
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main(int argc, char *argv[])
{
    int n;
    string p;
    while (cin >> n)
    {
        vector<unordered_map<char, int>> stat;
        for (int i = 0; i < n; ++i)
        {
            cin >> p;
            for (int j = 1; j < p.length(); j+=2)
            {
                int level = j >> 1;
                while (stat.size() <= level) stat.push_back({});
                stat[level][p[j]]++;
            }
        }
        for (int i = 0; i < stat.size(); ++i)
        {
            printf("[%d] ", i);
            for (const auto &p : stat[i])
            {
                printf("%c,%d ", p.first, p.second);
            }
            cout << endl;
        }
    }
    return 0;
}