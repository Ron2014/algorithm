#include <vector>
using namespace std;

class Solution {
    int getPeakIdx(vector<int> &nums, int s, int e, int n)
    {
        if (s > e) return -1;
        int m = (s+e)>>1;
        if ((m<=0 || nums[m] > nums[m-1]) && (m>=n-1 || nums[m] > nums[m+1]))
        {
            return m;
        }
        int ret = getPeakIdx(nums, s, m-1, n);
        if (ret >= 0) return ret;

        ret = getPeakIdx(nums, m+1, e, n);
        if (ret >= 0) return ret;

        return -1;
    }

public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums int整型vector 
     * @return int整型
     */
    int findPeakElement(vector<int>& nums) {
        // write code here
        int n = nums.size();
        if (n <= 0) return -1;
        return getPeakIdx(nums, 0, n - 1, n);
    }
};