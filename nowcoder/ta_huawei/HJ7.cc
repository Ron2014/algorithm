#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    float num;
    while (cin >> num)
    {
        cout << int(num + 0.5) << endl;
    }
    return 0;
}