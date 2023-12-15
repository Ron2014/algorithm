#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
    vector<unordered_map<char, int>> g_state = {
        /*0*/ {{' ', 0}, {'d', 1}, {'s', 1}, },
        /*1*/ {{'d', 1},},
    };
    const int FIN_STATE = 1;
    const int ERR_STATE = 2;

public:
    int myAtoi(string str) {
        int len = str.length();
        if (len <= 0) return 0;

        int stateIdx = 0;
        long long num = 0;
        int unit = 1;
        for (int i = 0; i < len; ++i)
        {
            char ch;
            if (isdigit(str[i]))
            {
                ch = 'd';
            }
            else if (str[i] == '-' || str[i] == '+')
            {
                ch = 's';
            }
            else if (str[i] == ' ')
            {
                ch = ' ';
            }
            else
            {
                ch = '?';
            }
            auto it = g_state[stateIdx].find(ch);
            if (it != g_state[stateIdx].end())
            {
                stateIdx = it->second;
                if (isdigit(str[i]))
                {
                    num = num * 10 + (str[i] - '0');
                    if (num * unit > INT_MAX) return INT_MAX;
                    if (num * unit < INT_MIN) return INT_MIN;
                }
                else if (str[i] == '-')
                {
                    unit = -1;
                }
            }
            else
            {
                break;
            }
        }

        if (stateIdx == FIN_STATE)
        {
            return (int)(num * unit);
        }
        return 0;

    }
};

int main()
{
    Solution so;
    string str;
    while (std::getline(std::cin, str))
    {
        cout << so.myAtoi(str) << endl;
    }
    return 0;
}