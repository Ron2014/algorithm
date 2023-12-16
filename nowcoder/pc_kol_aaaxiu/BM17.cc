#include <iostream>
#include <vector>
using namespace std;

class Solution {
    int bsearch(vector<int> &nums, int target, int s, int e)
    {
        if (s > e) return -1;
        int m = (s+e)>>1;
        if (nums[m] == target) return m;
        if (nums[m] < target) return bsearch(nums, target, m+1, e);
        else return bsearch(nums, target, s, m-1);
    }

public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums int整型vector 
     * @param target int整型 
     * @return int整型
     */
    int search(vector<int>& nums, int target) {
        // write code here
        return bsearch(nums, target, 0, nums.size()-1);
    }
};