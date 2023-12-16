#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

/*
请设计一个算法完成两个超长正整数的加法。
输入参数：
string addend：加数
string augend：被加数
返回值：加法结果
*/
string AddLongInteger(string addend, string augend)
{
    int len0 = addend.length();
    int len1 = augend.length();

    if (len0 > len1) {
        string tmp = addend;
        addend = augend;
        augend = tmp;

        int ltmp = len0;
        len0 = len1;
        len1 = ltmp;
    }

    // short is addend:len0
    const char *ch0 = addend.c_str();
    const char *ch1 = augend.c_str();
    
    stack<char> digits;
    int carry = 0;
    int add0, add1;
    char digit;

    for (int i=1; i<=len0 || carry; i++){
        add0 = len0<i ? 0 : ch0[len0-i] - '0';
        add1 = len1<i ? 0 : ch1[len1-i] - '0';
        digit = (add0 + add1 + carry) % 10 + '0';
        carry = (add0 + add1 + carry) / 10;
        digits.push(digit);
    }
    int count = digits.size();
    while(count++<len1) {
        digits.push(ch1[len1-count]);
    }

    stringstream ss;
    while(!digits.empty()){
        ss << digits.top();
        digits.pop();
    }
    return ss.str();
}

int main() {
    string addend, augend;
    while (cin >> addend >> augend) {
        cout << AddLongInteger(addend, augend) << endl;
    }
    return 0;
}