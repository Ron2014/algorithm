#include <vector>
using namespace std;
class Solution {
    void swap(vector<int> &nums, int i, int j)
    {
        int iTemp = nums[i];
        nums[i] = nums[j];
        nums[j] = iTemp;
    }

    void qsort(vector<int> &nums, int iStart, int iEnd)
    {
        if (iStart >= iEnd) return;
        int i = iStart, j = iEnd, x = nums[iStart];
        while (i < j)
        {
            while (nums[j] >= x && i < j) j--;
            while (nums[i] <= x && i < j) i++;
            swap(nums, i, j);
        }
        swap(nums, iStart, j);
        qsort(nums, iStart, j - 1);
        qsort(nums, j + 1, iEnd);
    }

public:
    int singleNumber(vector<int>& nums) {
        qsort(nums, 0, nums.size() - 1);

        int iStart = -1;
        for (int i = 0 ; i < nums.size(); i++)
        {
            if (iStart < 0)
            {
                iStart = i;
            }
            else
            {
                if (nums[iStart] != nums[i])
                {
                    if (i - iStart > 1)
                    {
                        iStart = i;
                    }
                    else
                    {
                        return nums[iStart];
                    }
                }
            }
        }
        if (nums.size() - iStart <= 1)
        {
            return nums[nums.size() - 1];
        }
        return -1;
    }
};