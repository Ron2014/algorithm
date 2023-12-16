#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int SUB_LEN = 8;

int main(int argc, char *argv[])
{
    char buf[SUB_LEN+1];
    buf[SUB_LEN] = '\0';

    string s;
    while (getline(std::cin, s))
    {
        int n = s.length();
        for (int i = 0; i < n; i+=SUB_LEN)
        {
            int len = min(SUB_LEN, n-i);
            if (n - i >= SUB_LEN)
            {
                strncpy(buf, s.c_str() + i, SUB_LEN);
            }
            else
            {
                strncpy(buf, s.c_str() + i, n - i);
                memset(buf+n-i, '0', SUB_LEN+i-n);
            }
            cout << buf << endl;
        }
    }
    return 0;
}