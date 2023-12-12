#include <iostream>
#include <vector>
#include "common.h"
using namespace std;

int main(int argc, char *argv[])
{
    string line;
    while (getline(std::cin, line))
    {
        int len = line.length();
        if (len <= 0) break;

        int n = 0;
        vector<int> nums;
        for (int k = 0; k < len; ++k)
        {
            if (isdigit(line[k]))
            {
                n= n * 10 + line[k] - '0';
            }
            else
            {
                nums.push_back(n);
                n = 0;
            }

            if (k == len - 1)
            {
                nums.push_back(n);
                n = 0;
            }
        }

        int N = nums[0];
        int M = nums[1];
        int pos = 0;
        vector<vector<int>> grid(N, vector<int>(M, 0));
        for (int k = 2; k < nums.size(); k+=2)
        {
            int val = nums[k];
            int cnt = nums[k+1];
            while (cnt-- > 0)
            {
                int i = pos / M;
                int j = pos % M;
                grid[i][j] = val;
                pos++;
            }
        }
        SHOW_M(grid, N, M);
    }
}
