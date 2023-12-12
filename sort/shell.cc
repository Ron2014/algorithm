/*
    希尔排序
    O(NlogN) ~ O(N^2)
    是对插入/选择排序的改进
*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

void swap(vector<int> &nums, int i, int j)
{
    int t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}

void shell(vector<int> &nums, int n)
{
    int j;
    for (int gap = n>>1; gap > 0; gap >>= 1)
    {
        // 从第gap个元素，逐个对其所在组进行直接插入排序操作
        for (int i = gap; i < n; ++i)
        {
            int temp = nums[i];     // 待插入元素
            for (j = i; j >= gap && temp < nums[j - gap]; j -= gap)
            {
                // 元素后移
                nums[j] = nums[j - gap];
            }
            nums[j] = temp;
        }
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

        do
        {
            while (*sz != '\0' && *sz == ' ') sz++;
            if (sscanf(sz, "%d", &n) <= 0) break;
            nums.push_back(n);
            while (*sz != '\0' && *sz != ' ') sz++;
        }
        while (*sz != '\0');

        for (const int &n :nums)
        {
            printf("%2d ", n);
        }
        cout << endl;

        shell(nums, nums.size());

        for (const int &n :nums)
        {
            printf("%2d ", n);
        }
        cout << endl;
    }
    return 0;
}