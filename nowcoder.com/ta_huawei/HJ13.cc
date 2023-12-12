#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

int main(int argc, char *argv[])
{
    stack<char> stk;
    char buf[1001];
    std::cin.getline(buf, sizeof(buf));
    int n = strlen(buf);
    for (int i = n - 1; i >= 0; --i)
    {
        if (buf[i] == ' ')
        {
            while (!stk.empty())
            {
                cout << stk.top();
                stk.pop();
            }
            cout << " ";
        }
        else
        {
            stk.push(buf[i]);
        }
    }
    while (!stk.empty())
    {
        cout << stk.top();
        stk.pop();
    }
    cout << endl;
    return 0;
}