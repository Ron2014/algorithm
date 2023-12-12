/*
输入字符串s，输出s中包含所有整数的最小和
说明
1. 字符串s，只包含 a-z A-Z +- ；
2. 合法的整数包括
    1） 正整数 一个或者多个0-9组成，如 0 2 3 002 102
    2）负整数 负号 - 开头，数字部分由一个或者多个0-9组成，如 -0 -012 -23 -00023
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
using namespace std;

vector<unordered_map<char, int>> g_state = {
    {{'d', 1}, {'s', 1},},
    {{'d', 1}},
};

const int FIN_STATE = 1;
const int MAX_INT = 2147483647;

int main(int argc, char *argv[])
{
    char line[1001];
    while (std::cin.getline(line, sizeof(line)))
    {
        int len = strlen(line);
        if (len <= 0) break;

        int i = 0;
        int minsum = 0;
        int minnum = MAX_INT;
        vector<int> nums;
        while (i < len)
        {
            int j = i;
            int stateIdx = 0;
            char ch;

            while (j < len)
            {
                if (isdigit(line[j]))
                {
                    ch = 'd';
                }
                else if (line[j] == '+' || line[j] == '-')
                {
                    ch = 's';
                }
                else
                {
                    ch = '?';
                }
                auto it = g_state[stateIdx].find(ch);
                if (it != g_state[stateIdx].end())
                {
                    stateIdx = it->second;
                    j++;
                }
                else
                {
                    break;
                }
            }

            if (stateIdx == FIN_STATE)
            {
                int num = 0;
                for (int k = i; k < j; ++k)
                {
                    if (isdigit(line[k]))
                    {
                        num = num * 10 + line[k] - '0';
                    }
                }

                if (line[i] == '-')
                {
                    num = -num;
                    minsum += num;
                }
                else
                {
                    minnum = min(minnum, num);
                }

                i = j;
            }
            else
            {
                i++;
            }
        }

        if (minsum < 0)
        {
            cout << minsum << endl;
        }
        else
        {
            cout << ((minnum<MAX_INT)?minnum:0) << endl;
        }
    }
    return 0;
}