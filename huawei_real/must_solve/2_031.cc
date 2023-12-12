/*
现有若干个会议，所有会议共享一个会议室，用数组表示每个会议的开始时间和结束时间，格式：[[会议1开始时间，会议1结束时间], [会议2开始时间，会议2结束时间]]。
请计算会议室占用时间段。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstring>
using namespace std;

const char *FMT_TIME_I = "%04d%02d%02d-%02d:%02d";
const char *FMT_TIME_O = "%Y%m%d-%H:%M";

time_t convertStrToTimestamp(const string &s)
{
    std::tm timeinfo = {};
    sscanf(s.c_str(), FMT_TIME_I,
        &timeinfo.tm_year, &timeinfo.tm_mon, &timeinfo.tm_mday,
        &timeinfo.tm_hour, &timeinfo.tm_min);
    timeinfo.tm_year -= 1900;
    timeinfo.tm_mon -= 1;
    timeinfo.tm_sec = 0;
    timeinfo.tm_isdst = 0;
    return ::mktime(&timeinfo);
}

const char *convertTimestampToStr(time_t t)
{
    std::tm *timeinfo = ::localtime(&t);
    static char buffer[80];
    ::strftime(buffer, sizeof(buffer), FMT_TIME_O, timeinfo);
    return buffer;
}

#define T2S convertTimestampToStr
#define S2T convertStrToTimestamp

#define SHOW(a, n)                                        \
    for (int i = 0; i < n; ++i)                           \
    {                                                     \
        cout << a[i].first << " " << a[i].second << endl; \
    }

int main(int argc, char *argv[])
{
    int n;
    string s, e;
    while (cin >> n)
    {
        if (n <= 0) break;

        vector<pair<int, int>> inputs(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> s >> e;
            inputs[i].first = S2T(s);
            inputs[i].second = S2T(e);
        }
        sort(inputs.begin(), inputs.end());

        SHOW(inputs, n);

        vector<pair<int, int>> result;
        result.emplace_back(inputs[0].first, inputs[0].second);

        for (int i = 1; i < n; ++i)
        {
            pair<int, int> &last_period = result[result.size()-1];
            pair<int, int> &input = inputs[i];
            if (last_period.second < input.first)
            {
                result.emplace_back(input.first, input.second);
            }
            else
            {
                last_period.second = input.second;
            }
        }

        for (const auto &p : result)
        {
            s = T2S(p.first);
            e = T2S(p.second);
            cout << s << "-" << e << endl;
        }
    }
    return 0;
}