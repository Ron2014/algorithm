#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) {
        int n = batteryPercentages.size();
        vector<int> dp(n+1, 0);     // dp[i]，测试第i个手机时，前面已经测试过的数量

        for (int i = 0; i < n; ++i)
        {
            int b = batteryPercentages[i] - dp[i];
            if (b > 0)
            {
                dp[i+1] = dp[i] + 1;
            }
            else
            {
                dp[i+1] = dp[i];
            }
        }
        return dp[n];
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