#include <iostream>
#include <string>
#include <set>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    multiset<string> lines;
    char buf[101];
    std::cin.getline(buf, sizeof(buf));
    int n = atoi(buf);
    for (int i = 0; i < n; ++i)
    {
        std::cin.getline(buf, sizeof(buf));
        lines.emplace(buf);
    }
    for (auto &s : lines)
    {
        cout << s << endl;
    }

    return 0;
}