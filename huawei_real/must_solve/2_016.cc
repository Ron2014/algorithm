#include <iostream>
#include <stack>
using namespace std;

int get_low_bit(unsigned int n, unsigned char bit, int pos)
{
    n >>= pos;
    while (n > 0)
    {
        if ((unsigned char)(n&1) == bit) return pos;
        n >>= 1;
        pos++;
    }
    return pos;
}

void show_bit(unsigned int n)
{
    stack<char> stk;
    for (int i = 0; i < sizeof(n)*8; ++i)
    {
        stk.push('0'+(n&1));
        n >>= 1;
    }
    while (!stk.empty())
    {
        cout << stk.top();
        stk.pop();
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    unsigned int n;
    while (cin >> n)
    {
        int low1 = get_low_bit(n, 1, 0);
        int low0 = get_low_bit(n, 0, low1);
        show_bit(n);
        cout << low1 << " " << low0 << endl;
        n &= ~(1<<low1);    // 1->0
        n |= 1<<low0;       // 0->1
        show_bit(n);
        cout << n << endl;
    }
    return 0;
}
