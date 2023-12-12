#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string s;
    std::getline(std::cin, s);
    int n = s.length(), endIdx = -1;
    for (int i = n - 1; i >= 0; --i)
    {
        if (s[i] != ' ')
        {
            if (endIdx < 0) endIdx = i;
            if (i == 0)
            {
                cout << endIdx - i + 1 << endl;
            }
        }
        else
        {
            if (endIdx >= 0)
            {
                cout << endIdx - i << endl;
                break;
            }
        }
    }
    return 0;
}