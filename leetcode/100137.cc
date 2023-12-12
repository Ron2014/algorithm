#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int maxn = *max_element(nums.begin(), nums.end());
        long long ans = 0;
        int cnt_max = 0, left = 0;
        for (const int &n : nums)
        {
            cnt_max += n == maxn;
            while (cnt_max == k)
            {
                cnt_max -= nums[left++] == maxn;
            }
            ans += left;
        }
        return ans;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n, k;
    while (cin >> n >> k)
    {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        cout << s.countSubarrays(nums, k) << endl;
    }
    return 0;
}