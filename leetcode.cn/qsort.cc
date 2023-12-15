#include <vector>
#include <iostream>
using namespace std;

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

int main(int argc, char *argv[])
{
    vector<int> nums;
    for (int i = 1; i < argc; i++)
    {
        nums.push_back(atoi(argv[i]));
    }

    qsort(nums, 0, nums.size() - 1);

    for (int num : nums)
    {
        printf("%d ", num);
    }
    printf("\n");
}