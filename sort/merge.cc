/*
    归并排序，非 in-place
    O(NlogN)
*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

void merge(vector<int> &nums, int s, int e)
{
    if (s >= e) return;

    int m = (s + e) >> 1;
    merge(nums, s, m);
    merge(nums, m+1, e);

    vector<int> backup(nums.begin() + s, nums.begin() + m + 1);
    int i = 0, j = m + 1;
    for (int k = s; k <= e; ++k)
    {
        if (j > e)
        {
            nums[k] = backup[i++];
        }
        else if (i >= backup.size())
        {
            // i 先消耗完
            // 这种情况可以不用排序了
            // nums[k] = nums[j++];
            break;
        }
        else
        {
            if (backup[i] > nums[j])
            {
                nums[k] = nums[j++];
            }
            else
            {
                nums[k] = backup[i++];
            }
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

        merge(nums, 0, nums.size() - 1);

        for (const int &n :nums)
        {
            printf("%2d ", n);
        }
        cout << endl;
    }
    return 0;
}

