/*
    冒泡排序
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

void bubble_sort(vector<int> &nums, int n)
{
    // 已排序空间 nums[n - i:i]
    int sorted_len = 0;
    while (sorted_len < n)
    {
        // 将最大的数冒泡至 nums[n - sorted_len - 1]
        for (int i = 1; i < n - sorted_len; ++i)
        {
            if (nums[i-1] > nums[i])
            {
                swap(nums, i-1, i);
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
        const char *sz = line;

        do
        {
            while ((*sz)!='\0' && !isdigit(*sz) && ((*sz)!='-' && (*sz)!='+')) sz++;
            if (sscanf(sz, "%d", &n) <= 0) break;
            nums.push_back(n);
            while ((*sz)!='\0' && (*sz)!=' ') sz++;
        } while ((*sz)!='\0' );

        for (int i = 0; i < nums.size(); ++i)
        {
            printf("%2d ", nums[i]);
        }
        cout << endl;

        bubble_sort(nums, nums.size());
        
        for (int i = 0; i < nums.size(); ++i)
        {
            printf("%2d ", nums[i]);
        }
        cout << endl;
    }
}

