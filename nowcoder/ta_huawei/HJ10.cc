#include <iostream>
#include <string>
#include <set>
using namespace std;

int main(int argc, char *argv[])
{
    std::string s;
    std::getline(std::cin, s);
    set<char> exists;
    int n = s.length();
    for (int i = 0; i < n; ++i)
    {
        if (s[i] < 0 || s[i] > 127) continue;
        exists.insert(s[i]);
    }
    cout << exists.size() << endl;
    return 0;
}