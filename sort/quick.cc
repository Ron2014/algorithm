/*
    快速排序
    O(NlogN) ~ O(N^2)
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

void quick(vector<int> &nums, int s, int e)
{
    if (s >= e) return;
    int i = s, j = e, x, pivot;

    // bug_found: 随机 x 的位置，可以增加排序的效率
    // pivot = s;
    pivot = s+rand()%(e-s+1);
    x = nums[pivot];

    swap(nums, s, pivot);   // 移到最左边，让其不会被排序算法移动
    while (i < j)
    {
        // 一定要用 >= <=，不然交换后，因为和x相等 i j 会停住
        // 也因为 <= 基准值 x 所在的位置是不会动的
        while (i < j && nums[j] >= x) --j;
        while (i < j && nums[i] <= x) ++i;
        if (i < j) swap(nums, i, j);
    }
    swap(nums, s, j);       // 将基准值放到特定的位置

    quick(nums, s, j - 1);
    quick(nums, j + 1, e);
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
        } while (*sz != '\0');

        for (const int &n: nums)
        {
            printf("%2d ", n);
        }
        cout << endl;

        quick(nums, 0, nums.size() - 1);

        for (const int &n: nums)
        {
            printf("%2d ", n);
        }
        cout << endl;
        
    }
    return 0;
}