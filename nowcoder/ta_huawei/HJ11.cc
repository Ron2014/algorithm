#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int n, len;
    char result[16];
    while (cin >> n)
    {
        len = 0;
        while (n > 0)
        {
            result[len++] = n % 10 + '0';
            n = n / 10;
        }
        if (len == 0)
        {
            result[len++] = '0';
        }
        result[len] = '\0';
        cout << result << endl;
    }
    return 0;
}