/*
给定一个表达式，求其分数计算结果 
 
表达式的限制如下：

1. 所有的输入数字皆为正整数(包括0)
2. 仅支持四则运算(+ - * /)和括号
3. 结果为整数或分数, 分数必须化为最简格式(比如6, 3/4, 7/8, 90/7)
4. 除数可能为0，如果遇到这种情况，直接输出"ERROR"
5. 输入和最终计算结果中的数字都不会超出整型范围

用例的输入一定合法, 不会出现括号不匹配的情况

*/

#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>
using namespace std;

#define TOP(v) ((v)[(v).size()-1])

int bracket(vector<int> &stkn, stack<char> &stko)
{
    int sum = 0;
    while (stko.top() != '(')
    {
        if (stko.top() == '-')
        {
            sum = sum - TOP(stkn);
        }
        else
        {
            sum = sum + TOP(stkn);
        }
        stko.pop();
        stkn.pop_back();
    }
    sum += TOP(stkn);
    stko.pop();
    stkn.pop_back();
    return sum;
}

int prev_calc(vector<int> &stkn, stack<char> &stko, int num, int &multi)
{
    switch(stko.top())
    {
    case '*':
        num = TOP(stkn) * num;
        stkn.pop_back();
        stko.pop();
        break;
    case '/':
        if (num == 0)
        {
            cerr << "ERROR" << endl;
            return -1;
        }
        if (TOP(stkn) % num == 0)
        {
            num = TOP(stkn) / num;
        }
        else
        {
            num = TOP(stkn) / num;
            // multi *= num;
        }
        stkn.pop_back();
        stko.pop();
        break;
    default:
        break;
    }
    return num;
}


void expression(const char *sz, int len)
{
    vector<int> stkn;
    stack<char> stko;

    int num = 0;
    int multi = 1;

    for (int i = 0; i < len; ++i)
    {
        if (isdigit(sz[i]))
        {
            num = num * 10 + sz[i] - '0';
        }

        if (!isdigit(sz[i]) || i == len-1)
        {
            if (sz[i] == ')')
            {
                num = prev_calc(stkn, stko, num, multi);
                if (num < 0) return;

                // 清算括号内的值
                stkn.push_back(num);
                num = bracket(stkn, stko);
                cout << num << endl;
            }

            if (!stko.empty() && sz[i] != '(')
            {
                num = prev_calc(stkn, stko, num, multi);
                if (num < 0) return;
            }

            if (i == len - 1)
            {
                stkn.push_back(num);
                num = 0;
            }
            else if (sz[i] == '(')
            {
                stko.push(sz[i]);
            }
            else if (sz[i] != ')')
            {
                stko.push(sz[i]);
                stkn.push_back(num);
                num = 0;
            }
        }
    }

    int sum = 0;
    while (!stko.empty())
    {
        if (stko.top() == '-')
        {
            sum = sum - TOP(stkn);
        }
        else
        {
            sum = sum + TOP(stkn);
        }
        stko.pop();
        stkn.pop_back();
    }
    sum += TOP(stkn);
    stkn.pop_back();

    if (multi > 1)
    {
        cout << sum << "/" << multi << endl;
    }
    else
    {
        cout << sum << endl;
    }
}

int main(int argc, char *argv[])
{
    string s;
    while (cin >> s)
    {
        int len = s.length();
        if (len <= 0) break;
        expression(s.c_str(), len);
    }
    return 0;
}