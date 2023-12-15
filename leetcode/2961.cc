/*
2961. 双模幂运算

给你一个下标从 0 开始的二维数组 variables ，其中 variables[i] = [ai, bi, ci, mi]，以及一个整数 target 。

如果满足以下公式，则下标 i 是 好下标：

0 <= i < variables.length
((aibi % 10)ci) % mi == target
返回一个由 好下标 组成的数组，顺序不限 。

示例 1：

输入：variables = [[2,3,3,10],[3,3,3,1],[6,1,1,4]], target = 2
输出：[0,2]
解释：对于 variables 数组中的每个下标 i ：
1) 对于下标 0 ，variables[0] = [2,3,3,10] ，(23 % 10)3 % 10 = 2 。
2) 对于下标 1 ，variables[1] = [3,3,3,1] ，(33 % 10)3 % 1 = 0 。
3) 对于下标 2 ，variables[2] = [6,1,1,4] ，(61 % 10)1 % 4 = 2 。
因此，返回 [0,2] 作为答案。

示例 2：

输入：variables = [[39,3,1000,1000]], target = 17
输出：[]
解释：对于 variables 数组中的每个下标 i ：
1) 对于下标 0 ，variables[0] = [39,3,1000,1000] ，(393 % 10)1000 % 1000 = 1 。
因此，返回 [] 作为答案。

提示：

1 <= variables.length <= 100
variables[i] == [ai, bi, ci, mi]
1 <= ai, bi, ci, mi <= 10^3
0 <= target <= 10^3
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<int> getGoodIndices(vector<vector<int>> &variables, int target)
    {
        vector<int> result;
        int n = variables.size();
        for (int i = 0; i < n; ++i)
        {
            int a = variables[i][0];
            int b = variables[i][1];
            int c = variables[i][2];
            int m = variables[i][3];

            int pow_ab = 1;
            for (int j = 0; j < b; ++j)
            {
                pow_ab = (pow_ab * a) % 10;
            }

            int pow_abc = 1;
            for (int j = 0; j < c; ++j)
            {
                pow_abc = (pow_abc * pow_ab) % m;
            }
            if (pow_abc == target)
            {
                result.push_back(i);
            }
        }
        return result;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n, t;
    while (cin >> n >> t)
    {
        vector<vector<int>> variables(n, vector<int>(4));
        for (int i = 0; i < n; ++i)
        {
            cin >> variables[i][0] >> variables[i][1] >> variables[i][2] >> variables[i][3];
        }
        vector<int> result = s.getGoodIndices(variables, t);
        for (const int &v : result)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    return 0;
}