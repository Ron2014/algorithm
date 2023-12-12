/*
给定一个矩阵，包含N*M个整数，和一个包含K个整数的数组。
现在要求在这个矩阵中找一个宽度最小的子矩阵，要求子矩阵包含数组中所有的整数。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool contains(unordered_map<int, int> &dst, unordered_map<int, int> &src)
{
    for (const auto &p : src)
    {
        if (dst[p.first] < p.second) return false;
    }
    return true;
}

void add_column(unordered_map<int, int> &dst, vector<vector<int>> &grid, int N, int col)
{
    for (int i = 0; i < N; ++i)
    {
        dst[grid[i][col]]++;
    }
}

void rem_column(unordered_map<int, int> &dst, vector<vector<int>> &grid, int N, int col)
{
    for (int i = 0; i < N; ++i)
    {
        dst[grid[i][col]]--;
    }
}

int main(int argc, char *argv[])
{
    int N, M, K;
    while (cin >> N >> M >> K)
    {
        vector<vector<int>> grid(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                cin >> grid[i][j];
            }
        }

        vector<int> nums(K);
        unordered_map<int, int> src;
        unordered_map<int, int> dst;
        for (int i = 0; i < K; ++i)
        {
            cin >> nums[i];
            src[nums[i]]++;
        }

        int l = 0, r;
        int minl = -1, minr = -1;
        while (l < M)
        {
            r = l;
            while (r < M)
            {
                add_column(dst, grid, N, r);
                if (contains(dst, src)) break;
                r++;
            }
            if (r >= M) break;

            // 包含所有数字的矩阵
            if (minl < 0 || (r-l) < (minr-minl))
            {
                minl = l;
                minr = r;
            }

            while (l < M && l <= r)
            {
                rem_column(dst, grid, N, l);
                l++;
                if (!contains(dst, src)) break;
                if (minl < 0 || (r-l) < (minr-minl))
                {
                    minl = l;
                    minr = r;
                }
            }
        }

        cout << minl << " " << minr << endl;
    }
    return 0;
}