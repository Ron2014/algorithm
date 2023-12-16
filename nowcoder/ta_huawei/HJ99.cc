#include <iostream>
#include <cmath>
using namespace std;

bool check(int n)
{
    int square = n * n;
    int len = log10(n) + 1;
    int unit = 1;
    for (int i = 0; i < len; ++i) unit *= 10;
    return n == (square % unit);
}

int main(int argc, char *argv[])
{
    int n, cnt = 0;
    while (cin >> n)
    {
        for (int i = 0; i <= n; ++i)
        {
            if (check(i)) cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}