#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int num;
    while (cin >> num)
    {
        for (int i = 2; i * i <= num; ++i)
        {
            while (num % i == 0)
            {
                cout << i << " ";
                num = num / i;
            }
        }
        if (num > 1) cout << num;
        cout << endl;
    }
    return 0;
}