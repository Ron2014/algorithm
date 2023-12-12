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