#include <iostream>
#include <map>
using namespace std;

int main(int argc, char *argv[])
{
    int n, index, value;
    map<int, int> result;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> index >> value;
        result[index] += value;
    }

    for (auto &p : result)
    {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}