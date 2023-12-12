#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
using namespace std;

bool digit_contain(int target, int r, int unit)
{
    if (target == r)
    {
        return true;
    }
    while (target > 0)
    {
        if (target % unit == r) return true;
        target /= 10;
    }
    return false;
}

int main(int argc, char *argv[])
{
    int n;
    vector<int> I;
    set<int> R;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        I.push_back(0);
        cin >> I[I.size()-1];
    }

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int r;
        cin >> r;
        R.insert(r);
    }

    vector<int> total;
    vector<int> result(I.size(), -1);
    int count;
    for (const int &r : R)
    {
        count = 0;
        int unit = pow(10, ((r>0)?(int)log10(r):0) + 1);
        // cout << r << " " << unit << endl;
        for (int i = 0; i < I.size(); ++i)
        {
            int target = I[i];
            if (digit_contain(I[i], r, unit))
            {
                result[count++] = i;
            }
        }
        if (count > 0)
        {
            total.push_back(r);
            total.push_back(count);
            for (int i = 0; i < count; ++i)
            {
                total.push_back(result[i]);
                total.push_back(I[result[i]]);
            }
        }
    }
    cout << total.size();
    for (int i = 0; i < total.size(); ++i)
    {
        cout << " " << total[i];
    }
    cout << endl;
    return 0;
}