/*
有一种特殊的加密算法，明文为一段数字串，经过密码本查找转换，生成另一段密文数字串。规则如下：

1.   明文为一段数字串由0~9组成

2.   密码本为数字0~9组成的二维数组

3.   需要按明文串的数字顺序在密码本里找到同样的数字串，密码本里的数字串是由相邻的单元格数字组成，上下和左右是相邻的，注意：对角线不相邻，同一个单元格的数字不能重复使用。

4.   每一位明文对应密文即为密码本中找到的单元格所在的行和列序号（序号从0开始）组成的两个数字。如明文 第i位Data[i] 对应密码本单元格为Book[x][y]，则明文第i位对应的密文为X Y，X和Y之间用空格隔开。如果有多条密文，返回字符序最小的密文。如果密码本无法匹配，返回”error”。

请你设计这个加密程序。

*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;

// top left right bottom
const int di[] = {-1, 0, 0, 1};
const int dj[] = {0, -1, 1, 0};
const int DIRECT_CNT = 4;

void dfs(vector<vector<char>> &grid, int n, int m, int si, int sj, const char *sz, int len, vector<int> &result, vector<int> &fresult)
{
    if (len <= 0)
    {
        if (fresult.size() <= 0 || fresult > result)
        {
            fresult = result;
        }
        return;
    }

    for (int k = 0; k < DIRECT_CNT; ++k)
    {
        int ni = si + di[k];
        int nj = sj + dj[k];
        if (grid[ni][nj] == *sz)
        {
            result.push_back(ni-1);
            result.push_back(nj-1);
            dfs(grid, n, m, ni, nj, sz+1, len-1, result, fresult);
            result.pop_back();
            result.pop_back();
        }
    }
}

int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<char>> grid(n+2, vector<char>(m+2, -1));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                cin >> grid[i][j];
            }
        }

        getchar();

        string s;
        std::getline(std::cin, s);
        vector<char> cipertext;
        for (const char &ch : s)
        {
            if (isdigit(ch)) cipertext.push_back(ch);
        }

        vector<int> result;
        vector<int> fresult;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (grid[i][j] == cipertext[0])
                {
                    result.push_back(i-1);
                    result.push_back(j-1);
                    dfs(grid, n, m, i, j, &cipertext[1], cipertext.size()-1, result, fresult);
                    result.pop_back();
                    result.pop_back();
                }
            }
        }

        if (fresult.size() <= 0)
        {
            cout << "error" << endl;
        }
        else
        {
            for (const int &num: fresult)
            {
                cout << num << " ";
            }
            cout << endl;
        }

    }
    return 0;
}