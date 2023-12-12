/*
给定一个表示分数加减运算的字符串 expression ，你需要返回一个字符串形式的计算结果。 

这个结果应该是不可约分的分数，即最简分数。 如果最终结果是一个整数，例如 2，你需要将它转换成分数形式，其分母为 1。
所以在上述例子中, 2 应该被转换为 2/1。

示例 1:

输入: expression = "-1/2+1/2"
输出: "0/1"
 示例 2:

输入: expression = "-1/2+1/2+1/3"
输出: "1/3"
示例 3:

输入: expression = "1/3-1/2"
输出: "-1/6"
 

提示:

输入和输出字符串只包含 '0' 到 '9' 的数字，以及 '/', '+' 和 '-'。 
输入和输出分数格式均为 ±分子/分母。如果输入的第一个分数或者输出的分数是正数，则 '+' 会被省略掉。
输入只包含合法的最简分数，每个分数的分子与分母的范围是  [1,10]。 如果分母是1，意味着这个分数实际上是一个整数。
输入的分数个数范围是 [1,10]。
最终结果的分子与分母保证是 32 位整数范围内的有效整数。
*/

#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

int gcd(int a, int b)
{
    static unordered_map<int, unordered_map<int, int>> s_mp;

    if (b == 0)
    {
        return a;
    }
    if (b == 1)
    {
        return 1;
    }
    if (s_mp[a][b] == 0)
    {
        s_mp[a][b] = gcd(b, a%b);
    }
    return s_mp[a][b];
}

class Fraction
{
    void normalization()
    {
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = - denominator;
        }
        if (denominator == 1) return;
        int a = abs(numerator);
        int b = abs(denominator);
        int cd = gcd(max(a,b), min(a,b));
        numerator /= cd;
        denominator /= cd;
    }

public:
    int numerator;      // 分子
    int denominator;    // 分母

    Fraction():numerator(0),denominator(1) {}
    Fraction(int n):numerator(n),denominator(1) {}

    friend ostream &operator << (ostream &out, const Fraction &obj)
    {
        out << obj.numerator << "/" << obj.denominator;
        return out;
    }

    const char *serialize()
    {
        static char buf[1024];
        snprintf(buf, sizeof(buf), "%d/%d", numerator, denominator);
        return buf;
    }

    Fraction &operator +=(const Fraction &o)
    {
        if (o.denominator == denominator)
        {
            numerator += o.numerator;
        }
        else
        {
            int a = denominator;
            int b = o.denominator;
            int cd = gcd(max(a,b),min(a,b));
            a /= cd;
            b /= cd;
            numerator = numerator * b + o.numerator * a;
            denominator *= b;
        }
        normalization();
        return *this;
    }

    Fraction &operator -=(const Fraction &o)
    {
        if (o.denominator == denominator)
        {
            numerator -= o.numerator;
        }
        else
        {
            int a = denominator;
            int b = o.denominator;
            int cd = gcd(max(a,b),min(a,b));
            a /= cd;
            b /= cd;
            numerator = numerator * b - o.numerator * a;
            denominator *= b;
        }
        normalization();
        return *this;
    }

    Fraction &operator /(const Fraction &o)
    {
        numerator *= o.denominator;
        denominator *= o.numerator;
        normalization();
        return *this;
    }

    Fraction &operator +(int n)
    {
        numerator += n * denominator;
        normalization();
        return *this;
    }

    Fraction &operator *(int n)
    {
        numerator *= n;
        normalization();
        return *this;
    }

    bool is_zero() { return numerator == 0; }
};

class Solution {
public:
    string fractionAddition(string expression) {
        stack<Fraction> stkn;
        stack<char>     stko;
        Fraction num;
        const char *sz = expression.c_str();

        while (*sz != '\0')
        {
            if (isdigit(*sz))
            {
                num = num * 10 + (*sz - '0');
            }

            if (!isdigit(*sz) || *(sz+1) == '\0')
            {
                if (!stko.empty())
                {
                    if (stko.top() == '/')
                    {
                        num = stkn.top() / num;
                        stkn.pop();
                        stko.pop();
                    }
                }

                if (!isdigit(*sz))
                {
                    stko.push(*sz);
                }

                stkn.push(num);
                num = 0;
            }
            sz++;
        }

        Fraction result;
        while (!stko.empty())
        {
            switch(stko.top())
            {
            case '+':
                result += stkn.top();
                stkn.pop();
                stko.pop();
                break;
            case '-':
                result -= stkn.top();
                stkn.pop();
                stko.pop();
                break;
            }
        }
        result += stkn.top();
        stkn.pop();
        return result.serialize();
    }
};

int main(int argc, char *argv[])
{
    Solution so;
    string s;
    while (cin >> s)
    {
        cout << so.fractionAddition(s) << endl;
    }
    return 0;
}