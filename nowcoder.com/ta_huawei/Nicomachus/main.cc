#include <iostream>
#include <sstream>
using namespace std;

// #define TEST

/*
功能: 验证尼科彻斯定理，即：任何一个整数m的立方都可以写成m个连续奇数之和。
原型：
    int GetSequeOddNum(int m,char * pcSequeOddNum);
输入参数：
    int m：整数(取值范围：1～100)

返回值：
    m个连续奇数(格式：“7+9+11”);
*/
string GetSequeOddNum(int m)
{
    // int cube = m * m * m;
    // cube = n0 + n1 + n2 + ... + nm
    // ni is odd
    // ni is sequence
    // middle num of sequence-ni is <m*m>

    int mid = m * m;
    int countL = m/2;
    int countR = m-countL;

    // odd * odd = odd
    // even * even = even
    if (m%2==0) mid ++;

    stringstream ss;

    // left
#ifdef TEST
    int sum = 0;
#endif
    for (int i=0; i<countL; i++) {
        ss << mid - (countL-i) * 2 << "+";
#ifdef TEST
        sum += mid - (countL-i) * 2;
#endif
    }
    // right
    for (int i=0; i<countR; i++) {
        ss << mid + i * 2;
        if (i<countR-1) ss << "+";
#ifdef TEST
        sum += mid + i * 2;
#endif
    }
#ifdef TEST
    cout << "mid:" << mid << endl;
    cout << "countL:" << countL << endl;
    cout << "countR:" << countR << endl;
    cout << "cube:" << m*m*m << endl;
    cout << "sum:" << sum << endl;
#endif
    
    return ss.str();
}

int main() {
    int m;
    while (cin >> m) {
        cout << GetSequeOddNum(m) << endl;
    }
}