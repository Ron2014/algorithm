#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
using namespace std;

vector<unordered_map<char, int>> g_state = {
    {{'o', 1}, {';', 0}, },
    {{'d', 1}, {';', 0}, },
    {{';', 0},},
};
const int invalid_state = 2;

int main(int argc, char *argv[])
{
    char line[10001];
    std::cin.getline(line, sizeof(line));
    int x = 0, y = 0, n = strlen(line);
    int *target = nullptr;
    int sign = 1;
    int step = 0;
    char ch;
    unordered_map<char, int> *s = &g_state[0];
    for (int i = 0; i < n; ++i)
    {
        if (isdigit(line[i]))
        {
            ch = 'd';
            step = step * 10 + (line[i] - '0');
        }
        else if (line[i] == ';')
        {
            ch = ';';
            if (target)
            {
                // cout << x << "," << y;
                *target += step * sign;
                target = nullptr;
                step = 0;
                sign = 1;
                // cout << " -> " << x << "," << y << endl;
            }
        }
        else
        {
            switch (line[i])
            {
            case 'a':
                ch = 'o';
                target = &x;
                sign = -1;
                break;
            case 'w':
                ch = 'o';
                target = &y;
                sign = 1;
                break;
            case 's':
                ch = 'o';
                target = &y;
                sign = -1;
                break;
            case 'd':
                ch = 'o';
                target = &x;
                sign = 1;
                break;
            default:
                ch = '?';
                break;
            }
        }
        unordered_map<char, int>::iterator it = s->find(ch);
        if (it != s->end())
        {
            // 合法字符，切换下个状态
            s = &g_state[it->second];
        }
        else
        {
            // 非法字符，重新开始
            // cout << "invalid:[" << i << "]=" << line[i] << endl;
            s = &g_state[invalid_state];
            target = nullptr;
            step = 0;
            sign = 1;
        }
    }
    printf("%d,%d\n", x, y);
    return 0;
}