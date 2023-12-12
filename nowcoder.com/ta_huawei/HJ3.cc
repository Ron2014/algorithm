#include <iostream>
#include <set>
using namespace std;

int main(int argc, char *argv[])
{
    int N, rand_num;
    set<int> uniq_nums;
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        cin >> rand_num;
        if (uniq_nums.find(rand_num) == uniq_nums.end())
        {
            uniq_nums.insert(rand_num);
        }
    }
    for (const int &num : uniq_nums)
    {
        cout << num << endl;
    }
    return 0;
}