#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    std::string s;
    std::getline(std::cin, s);
    char target;
    cin >> target;
    if (target >= 'A' && target <= 'Z')
    {
        target += 'a' - 'A';
    }
    int cnt = 0;
    for (int i = 0; i < s.length(); ++i)
    {
        char ch = s[i];
        if (ch >= 'A' && ch <= 'Z')
        {
            ch += 'a' - 'A';
        }
        if (ch == target) cnt++;
    }
    cout << cnt << endl;
    return 0;
}