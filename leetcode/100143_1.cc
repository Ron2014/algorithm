#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) {
        int ans = 0;
        for (const int &n : batteryPercentages)
        {
            if (n > ans) ans++;
        }
        return ans;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n;
    while (cin >> n)
    {
        vector<int> batteryPercentages(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> batteryPercentages[i];
        }
        cout << s.countTestedDevices(batteryPercentages) << endl;
    }
    return 0;
}