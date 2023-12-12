/*
提取字符串中的最长合法简单数学表达式，字符串长度最长的，并计算表达式的值。如果没有，则返回0
简单数学表达式只能包含以下内容
0-9数字，符号 +-*
说明：
1. 所有数字，计算结果都不超过long
2. 如果有多个长度一样的，请返回第一个表达式的结果
3. 数学表达式，必须是最长的，合法的
4. 操作符不能连续出现，如 +--+1 是不合法的
*/

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <cstring>
using namespace std;

vector<unordered_map<char, int>> g_state = {
    {{'d', 1},},                // 第一个操作数
    {{'d', 1}, {'o', 2}, },     // 第一个操作数和符号
    {{'d', 3}, },               // 第二个操作数开头
    {{'d', 3}, {'o', 2}, },
};

const int FINISH_STATE = 3;

int calc(char *sz, int len)
{
    sz[len] = '\0';
    cout << sz << endl;
    stack<int> stkn;
    stack<int> stko;
    int num = 0;
    for (int i = 0; i < len; ++i)
    {
        if (isdigit(sz[i]))
        {
            num = num * 10 + (sz[i] - '0');
        }
        if (!isdigit(sz[i]) || i == len-1)
        {
            if (!stko.empty())
            {
                switch (stko.top())
                {
                case '*':
                    num = stkn.top() * num;
                    stkn.pop();
                    stko.pop();
                    break;
                // 判断除0
                // case '/':
                //     num = stkn.top() / num;
                //     stkn.pop();
                //     stko.pop();
                //     break;
                default:
                    break;
                }
            }
            stkn.push(num);
            if (!isdigit(sz[i]))
            {
                stko.push(sz[i]);
            }
            num = 0;
        }
    }
    int sum = 0;
    while (!stko.empty())
    {
        num = stkn.top();
        switch (stko.top())
        {
        case '-':
            sum = sum - num;
            break;
        case '+':
            sum = sum + num;
            break;
        default:
            break;
        }
        stko.pop();
        stkn.pop();
    }
    return sum + stkn.top();
}

int expression(char *sz, int len)
{
    int maxi = -1, maxlen = 0;
    for (int i = 0; i < len; ++i)
    {
        int stateIdx = 0;
        int exp_len = 0;
        for (int j = i; j < len; ++j)
        {
            char ch = '?';
            if (isdigit(sz[j]))
            {
                ch = 'd';
            }
            else if (sz[j] == '+' || sz[j] == '-' || sz[j] == '*' || sz[j] == '/')
            {
                ch = 'o';
            }

            unordered_map<char, int>::iterator it = g_state[stateIdx].find(ch);
            if (it == g_state[stateIdx].end()) break;
            stateIdx = it->second;
            exp_len++;
        }

        if (stateIdx == FINISH_STATE)
        {
            if (exp_len > maxlen)
            {
                maxlen = exp_len;
                maxi = i;
            }
            i += exp_len;
        }
        else
        {
            i++;
        }
    }
    if (maxi >= 0)
    {
        return calc(sz + maxi, maxlen);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char line[10001];
    while (std::cin.getline(line, sizeof(line)))
    {
        int len = strlen(line);
        if (len <= 0) break;
        cout << expression(line, len) << endl;
    }
    return 0;
}