/*
    插入排序
    O(N^2)
    类似扑克一样，每次从无序空间取出一个元素，插入到有序空间中

    分为两种
        1. 直接插入排序
        2. 二分插入排序
*/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

void binary_insert(vector<int> &nums, int n)
{
    // 已排序空间 nums[0:sorted_len]
    int sorted_len = 0;

    while (sorted_len < n)
    {
        int num = nums[sorted_len];     // 未排序的首个元素
        int insert_pos = sorted_len;    // 插入的位置
        
        int s = 0, e = sorted_len-1;
        while (s <= e)
        {
            int m = (s + e) >> 1;
            if (nums[m] < num)
            {
                s = m + 1;
            }
            else
            {
                insert_pos = m;
                e = m - 1;
            }
        }
        // 将插入位置的后半段移动1格
        // 一定要从尾部移，不然会覆盖
        for (int i = sorted_len-1; i >= insert_pos; --i)
        {
            nums[i+1] = nums[i];
        }
        nums[insert_pos] = num;
        sorted_len++;
    }
}

void straight_insert(vector<int> &nums, int n)
{
    // 已排序空间 nums[0:sorted_len]
    int sorted_len = 0;

    while (sorted_len < n)
    {
        int temp = nums[sorted_len];    // 未排序的首个元素
        int i;                          // 插入的位置
        // bug_found: 插入位置的搜索可以用二分查找优化
        for (i = sorted_len; i >= 1 && temp < nums[i-1]; --i)
        {
            nums[i] = nums[i-1];
        }
        nums[i] = temp;
        sorted_len++;
    }
}

int main(int argc, char *argv[])
{
    char line[1001];
    while (std::cin.getline(line, sizeof(line)))
    {
        int len = strlen(line);
        if (len <= 0) break;

        vector<int> nums;

        int n;
        const char *sz = line;
        while (*sz != '\0')
        {
            while (*sz != '\0' && *sz == ' ') sz++;
            if (sscanf(sz, "%d", &n) <= 0) break;
            nums.push_back(n);
            while (*sz != '\0' && *sz != ' ') sz++;
        }

        for (const int &n : nums)
        {
            printf("%2d ", n);
        }
        cout << endl;

        straight_insert(nums, nums.size());

        for (const int &n : nums)
        {
            printf("%2d ", n);
        }
        cout << endl;


    }
    return 0;
}