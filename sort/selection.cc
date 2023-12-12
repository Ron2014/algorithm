/*
    选择排序
    O(N^2)
*/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

void swap(vector<int> &nums, int i, int j)
{
    int t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}

void selection(vector<int> &nums, int n)
{
    // 已排序空间 nums[0:sorted_len]
    int sorted_len = 0;
    while (sorted_len < n)
    {
        for (int i = sorted_len; i < n; ++i)
        {
            // 每次都将最小的数字放到 nums[sorted_len]
            // nums[sorted_len] 即插入位置
            if (nums[i] < nums[sorted_len])
            {
                swap(nums, i, sorted_len);
            }
        }
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

        int n;
        vector<int> nums;

        char *sz = line;
        while ((*sz) != '\0' )
        {
            while ((*sz) != '\0' && (*sz) == ' ') sz++;
            if (sscanf(sz, "%d", &n) == 0) break;
            nums.push_back(n);
            while ((*sz) != '\0' && (*sz) != ' ') sz++;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            printf("%2d ", nums[i]);
        }
        cout << endl;

        selection(nums, nums.size());

        for (int i = 0; i < nums.size(); ++i)
        {
            printf("%2d ", nums[i]);
        }
        cout << endl;

    }
    return 0;
}