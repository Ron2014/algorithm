#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
using namespace std;
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size(), sum, iCount = 0;
        vector<vector<int> > backup(n);
        for (int i = 0; i < n; i++)
        {
            backup[i].resize(i+1);
            backup[i][0] = nums[i];
            if (backup[i][0] == k) iCount++;
            for (int j = 1; j <= i; j++)
            {
                backup[i][j] = backup[i][j-1] + nums[i-j];
                if (backup[i][j] == k) iCount++;
            }
        }
        return iCount;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    vector<int> nums;
    for (int i = 1; i < argc - 1; i++)
    {
        nums.push_back(atoi(argv[i]));
    }
    int k = atoi(argv[argc-1]);
    cout << s.subarraySum(nums, k) << endl;
    return 0;
}