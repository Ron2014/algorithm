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
#include <vector>
#include <stack>
using namespace std;

unordered_map<int, unordered_map<int, int>> g_map;

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    if (b == 1)
    {
        return 1;
    }

    if (g_map[a][b] > 0)
    {
        return g_map[a][b];
    }

    int ret = gcd(b, a%b);
    g_map[a][b] = ret;
    return ret;
}

class Number
{
    void format()
    {
        int a = abs(fenzi);
        int b = abs(fenmu);

        int cd = gcd(max(a, b), min(a, b));
        this->fenmu /= cd;
        this->fenzi /= cd;

        if (fenmu < 0)
        {
            fenmu = -fenmu;
            fenzi = -fenzi;
        }
    }

public:
    int fenzi;
    int fenmu;

    Number(int n):fenzi(n),fenmu(1) {}
    Number(int n, int m):fenzi(n),fenmu(m) {
        this->format();
    }

    friend ostream &operator<<(ostream &os, const Number &o)
    {
        os << o.fenzi;
        if (o.fenmu > 1)
        {
            os << "/" << o.fenmu;
        }
        return os;
    }


    Number &operator +=(const Number &o)
    {
        if (this->fenmu == o.fenmu)
        {
            this->fenzi += o.fenzi;
        }
        else
        {
            int a = this->fenmu;
            int b = o.fenmu;

            int cd = gcd(max(a, b), min(a, b));
            int t0 = this->fenmu / cd;
            int t1 = o.fenmu / cd;

            this->fenzi = (this->fenzi * t1) + (o.fenzi * t0);
            this->fenmu *= t1;
        }
        this->format();
        return *this;
    }

    Number &operator +(int num)
    {
        this->fenzi += this->fenmu * num;
        this->format();
        return *this;
    }

    Number &operator -=(Number &o)
    {
        if (this->fenmu == o.fenmu)
        {
            this->fenzi -= o.fenzi;
        }
        else
        {
            int a = this->fenmu;
            int b = o.fenmu;

            int cd = gcd(max(a, b), min(a, b));
            int t0 = this->fenmu / cd;
            int t1 = o.fenmu / cd;

            this->fenzi = (this->fenzi * t1) - (o.fenzi * t0);
            this->fenmu *= t1;
        }
        this->format();
        return *this;
    }

    Number &operator -(int num)
    {
        this->fenzi -= this->fenmu * num;
        this->format();
        return *this;
    }

    Number &operator *=(Number &o)
    {
        this->fenzi *= o.fenzi;
        this->fenmu *= o.fenmu;
        this->format();
        return *this;
    }

    Number &operator *(int num)
    {
        this->fenzi *= num;
        this->format();
        return *this;
    }

    Number &operator /(Number &o)
    {
        this->fenzi *= o.fenmu;
        this->fenmu *= o.fenzi;
        this->format();
        return *this;
    }

    Number &operator /(int num)
    {
        this->fenmu *= num;
        this->format();
        return *this;
    }

    bool is_zero() { return this->fenzi == 0; }
};

bool calc_bracket(stack<Number> &stkn, stack<char> &stko, Number &num)
{
    if (!stko.empty())
    {
        if (stko.top() == '*')
        {
            num *= stkn.top();
            stkn.pop();
            stko.pop();
        }
        else if (stko.top() == '/')
        {
            if (num.is_zero())
            {
                cout << "ERROR" << endl;
                return false;
            }
            num = stkn.top() / num;
            stkn.pop();
            stko.pop();
        }
    }
    stkn.push(num);

    num = 0;
    while (!stko.empty())
    {
        if (stko.top() == '-')
        {
            num -= stkn.top();
            stkn.pop();
            stko.pop();
        }
        else if (stko.top() == '+')
        {
            num += stkn.top();
            stkn.pop();
            stko.pop();
        }
        else if (stko.top() == '(')
        {
            num += stkn.top();
            stkn.pop();
            stko.pop();
            break;
        }
    }
    
    return true;
}

bool calc(const char *sz, Number &result)
{
    stack<Number> stkn;
    stack<char> stko;

    Number num = 0;
    while (*sz != '\0')
    {
        if (isdigit(*sz))
        {
            num = num * 10 + (*sz - '0');
        }

        if (!isdigit(*sz))
        {
            if (*sz == ')')
            {
                if (!calc_bracket(stkn, stko, num))
                {
                    return false;
                }
                if (!stko.empty())
                {
                    if (stko.top() == '*')
                    {
                        num *= stkn.top();
                        stkn.pop();
                        stko.pop();
                    }
                    else if (stko.top() == '/')
                    {
                        if (num.is_zero())
                        {
                            cout << "ERROR" << endl;
                            return false;
                        }
                        num = stkn.top() / num;
                        stkn.pop();
                        stko.pop();
                    }
                }
            }
            else if (*sz == '(')
            {
                stko.push(*sz);
            }
            else
            {
                if (!stko.empty())
                {
                    if (stko.top() == '*')
                    {
                        num *= stkn.top();
                        stkn.pop();
                        stko.pop();
                    }
                    else if (stko.top() == '/')
                    {
                        if (num.is_zero())
                        {
                            cout << "ERROR" << endl;
                            return false;
                        }
                        num = stkn.top() / num;
                        stkn.pop();
                        stko.pop();
                    }
                }
                // 运算符，需要保存操作数
                stkn.push(num);
                stko.push(*sz);
                num = 0;
            }
        }

        if (*(sz+1) == '\0')
        {
            if (!stko.empty())
            {
                if (stko.top() == '*')
                {
                    num *= stkn.top();
                    stkn.pop();
                    stko.pop();
                }
                else if (stko.top() == '/')
                {
                    if (num.is_zero())
                    {
                        cout << "ERROR" << endl;
                        return false;
                    }
                    num = stkn.top() / num;
                    stkn.pop();
                    stko.pop();
                }
            }
            stkn.push(num);
            num = 0;
        }
        sz++;
    }

    while (!stko.empty())
    {
        if (stko.top() == '-')
        {
            result -= stkn.top();
            stkn.pop();
            stko.pop();
        }
        else if (stko.top() == '+')
        {
            result += stkn.top();
            stkn.pop();
            stko.pop();
        }
    }
    result += stkn.top();
    stkn.pop();

    return true;
}

int main(int argc, char *argv[])
{
    string exp;
    while (cin >> exp)
    {
        int len = exp.length();
        if (len <= 0) break;
        Number result(0);
        calc(exp.c_str(), result);
        cout << result << endl;
        for (auto it = g_map.begin(); it != g_map.end(); ++it)
        {
            for (auto it1 = it->second.begin(); it1 != it->second.end(); ++it1)
            {
                printf("[%d][%d]=%d\n", it->first, it1->first, it1->second);
            }
        }
    }
    return 0;
}
