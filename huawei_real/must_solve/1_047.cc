/*
RSA加密算法在网络安全世界中无处不在，它利用了极大整数因数分解的困难度，数据越大，安全系数越高
给定一个32位正整数，请对其进行因数分解，找出是哪两个素数的乘积。
*/
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        for (int i = 2; i*i <= n; ++i)
        {
            if (n % i == 0)
            {
                cout << i << " " << n/i << endl;
            }
        }
    }
    return 0;
}