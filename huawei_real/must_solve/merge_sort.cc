#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include "common.h"
using namespace std;


void mergesort(vector<int> &nums, int s, int e)
{
    if (s >= e) return;
    int mid = (s+e)>>1;

    // 让前半部分略大
    // s mid, mid+1, e
    mergesort(nums, s, mid);
    mergesort(nums, mid+1, e);

    printf("[%d,%d]", s, mid);
    for (int i = s; i <= mid; ++i) cout << nums[i] << ",";
    cout << endl;
    printf("[%d,%d]", mid+1, e);
    for (int i = mid+1; i <= e; ++i) cout << nums[i] << ",";
    cout << endl;

    // 利用一个额外的空间，避免归并时覆盖的情况
    vector<int> backup(nums.begin() + s, nums.begin() + mid + 1);

    // 注意backup从0开始
    int i = 0, j = mid+1;
    for (int k = s; k <= e; ++k)
    {
        if (j > e)
        {
            nums[k] = backup[i++];
        }
        else if (i > mid - s)
        {
            nums[k] = nums[j++];
        }
        else
        {
            if (backup[i] <= nums[j])
            {
                nums[k] = backup[i++];
            }
            else
            {
                nums[k] = nums[j++];
            }
        }
    }
    printf("=>[%d,%d]", s, e);
    for (int i = s; i <= e; ++i) cout << nums[i] << ",";
    cout << endl;
}

int main(int argc, char *argv[])
{
    int N, num;
    while (cin >> N)
    {
        vector<int> nums(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> nums[i];
        }
        mergesort(nums, 0, N-1);
        SHOW(nums, N);
    }
    return 0;
}