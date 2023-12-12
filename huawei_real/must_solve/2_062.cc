/*
警察在侦破一个案件时，得到了线人给出的可能犯罪时间，形如 “HH:MM” 表示的时刻。

根据警察和线人的约定，为了隐蔽，该时间是修改过的，解密规则为：利用当前出现过的数字，构造下一个距离当前时间最近的时刻，则该时间为可能的犯罪时间。
每个出现数字都可以被无限次使用。
*/
#include <iostream>
#include <cstring>
#include <set>
#include <deque>
#include <string>
using namespace std;

const int TIME_LEN = 5;

bool is_bigger_time(const char *src, const char *dst)
{
    if (strncmp(src, dst, 2) > 0) return false;
    if (strncmp(src, dst, 2) < 0) return true;
    return strncmp(src+3, dst+3, 2) < 0;
}

string bfs(const char *src, set<char> &digits, int idx)
{
    deque<string> candidates;
    candidates.emplace_back(src);
    
    char time[TIME_LEN+1];
    time[TIME_LEN] = '\0';

    while (!candidates.empty() && idx > 0)
    {
        idx--;
        if (idx == 2) idx--;

        int n = candidates.size();
        for (int i = 0; i < n; ++i)
        {
            string &s = candidates.front();
            strncpy(time, s.c_str(), TIME_LEN);

            for (const char &ch : digits)
            {
                // min: 00 - 60
                if (idx == 3 && ch > '6') continue;
                if (idx == 0)
                {
                    // hour: 00-24
                    if (time[idx + 1] > '3' && ch > '1') continue;
                    if (time[idx + 1] <= '3' && ch > '2') continue;
                }
                time[idx] = ch;
                if (is_bigger_time(src, time))
                {
                    return time;
                }
                candidates.emplace_back(time);
            }

            candidates.pop_front();
        }
    }
    return "";
}

int main(int argc, char *argv[])
{
    string s;
    while (cin >> s)
    {
        int len = s.length();
        if (len <= 0) break;

        set<char> digits;
        digits.insert(s[0]);
        digits.insert(s[1]);
        digits.insert(s[3]);
        digits.insert(s[4]);

        cout << bfs(s.c_str(), digits, TIME_LEN) << endl;
    }
    return 0;
}