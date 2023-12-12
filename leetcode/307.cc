#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    int x, j = 1;
    for (int i = 1; i < argc; i++)
    {
        x = atoi(argv[i]);
        cout << x << " " << (x & -x) << " " << j << " " << j+(x&-x) << endl;
        j += x & -x;
    }
    return 0;
}