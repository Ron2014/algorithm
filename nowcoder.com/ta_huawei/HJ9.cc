#include <iostream>
#include <set>
using namespace std;

int main(int argc, char *argv[])
{
    int num, digit;
    set<int> exists;
    while (cin >> num)
    {
        while (num > 0)
        {
            digit = num % 10;
            if (exists.find(digit) == exists.end())
            {
                exists.insert(digit);
                cout << digit;
            }
            num = num / 10;
        }
    }
    return 0;
}