/*
    提取字符串中最长合法简单表达式，字符串长度最长，并计算表达式的值。如果没有，返回0
    数字0-9, 符号 + - * /
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

vector<unordered_map<char, int>> g_state = {
    {{'d', 1}, },                   //  first
    {{'d', 1}, {'o', 2}, },         //  num
    {{'d', 3}, },                   //  num op
    {{'d', 3}, {'o', 2}, },         //  num op num
};

const int END_STATE = 3;

long calc(vector<char> &exp, int exp_len)
{
    stack<char> stkOp;
    stack<int> stkNum;
    int num = 0;
    for (int i = 0; i < exp_len; ++i)
    {
        if (isdigit(exp[i]))
        {
            num = num * 10 + exp[i] - '0';
        }
        if (i == exp_len - 1 || !isdigit(exp[i]))
        {
            if (!stkOp.empty())
            {
                switch (stkOp.top())
                {
                case '*':
                    num = stkNum.top() * num;
                    stkOp.pop();
                    stkNum.pop();
                    break;
                case '/':
                    num = stkNum.top() / num;
                    stkNum.pop();
                    stkOp.pop();
                    break;
                default:
                    break;
                }
            }
            stkNum.push(num);

            if (!isdigit(exp[i]))
            {
                stkOp.push(exp[i]);
            }
            num = 0;
        }
    }
    int sum = 0;
    while (!stkNum.empty())
    {
        num = stkNum.top();
        stkNum.pop();
        if (!stkOp.empty())
        {
            if (stkOp.top() == '-')
            {
                num = -num;
            }
            stkOp.pop();
        }
        sum += num;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    string s; 
    while (std::getline(std::cin, s))
    {
        int len = s.length();
        if (len <= 0) break;

        vector<char> expression(len, '\0');
        char ch;
        int state_idx = 0;
        int exp_len = 0;
        int max_exp_len = -1;
        int i = 0;
        while (i < len)
        {
            exp_len = 0;
            state_idx = 0;
            for (int j = i; j < len; ++j)
            {
                if (isdigit(s[j]))
                {
                    ch = 'd';
                }
                else if (s[j] == '+' || s[j] == '-' || s[j] == '*' || s[j] == '/')
                {
                    ch = 'o';
                }
                else
                {
                    ch = '?';
                }
                unordered_map<char, int>::iterator it = g_state[state_idx].find(ch);
                if (it != g_state[state_idx].end())
                {
                    state_idx = it->second;
                    expression[exp_len++] = s[j];
                }
                else
                {
                    break;
                }
            }
            if (state_idx == END_STATE)
            {
                if (exp_len > max_exp_len)
                {
                    // calc
                    for (int j = 0; j < exp_len; ++j)
                    {
                        cout << expression[j];
                    }
                    cout << "=" << calc(expression, exp_len) << endl;
                }
                i += exp_len;
            }
            else
            {
                i++;
            }
        }
    }
    return 0;
}