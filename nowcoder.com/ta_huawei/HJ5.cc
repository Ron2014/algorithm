#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    string s;
    while (cin >> s)
    {
        int n = s.length();
        int sum = 0;
        for (int i = 2; i < n; ++i)
        {
            if (isdigit(s[i]))
            {
                sum = sum * 16 + (s[i] - '0');
            }
            else
            {
                sum = sum * 16 + (s[i] - 'A' + 10);
            }
        }
        cout << sum << endl;
    }
    return 0;
}