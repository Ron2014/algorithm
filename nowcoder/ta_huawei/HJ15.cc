#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int n, res;
    while (cin >> n)
    {
        res = 0;
        while (n > 0)
        {
            if (n & 1) res++;
            n >>= 1;
        }
        cout << res << endl;
    }
    return 0;
}