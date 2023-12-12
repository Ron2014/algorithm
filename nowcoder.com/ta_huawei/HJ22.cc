#include <iostream>
using namespace std;

int count_for_battle(int n)
{
    int res = 0;
    int change_cnt = 3, more_cnt;
    while (n >= change_cnt)
    {
        more_cnt = n / change_cnt;
        n = n % change_cnt + more_cnt;
        res += more_cnt;
    }
    if (n == 2) res++;
    return res;
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        if (n == 0) break;
        cout << count_for_battle(n) << endl;
    }
    return 0;
}