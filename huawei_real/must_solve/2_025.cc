/*
有一棵二叉树，每个节点由一个大写字母标识(最多26个节点）。
现有两组字母，分别表示后序遍历（左孩子->右孩子->父节点）和中序遍历（左孩子->父节点->右孩子）的结果，请输出层次遍历的结果。
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


void travel(string &spostorder, string &sinorder, int root_pos, int is, int ie, vector<vector<char>> &result, int level)
{
    for (int i = is; i <= ie; ++i)
    {
        if (sinorder[i] == spostorder[root_pos])
        {
            while (result.size() <= level) result.push_back({});
            result[level].push_back(sinorder[i]);

            int l_cnt = i - is;
            int r_cnt = ie - i;
            // cout << sinorder[i] << " " << l_cnt << " " << r_cnt << endl;
            
            // 左子树 is - i-1
            if (l_cnt > 0)
            {
                travel(spostorder, sinorder, root_pos - 1 - r_cnt, is, i-1, result, level+1);
            }

            // 右子树 i+1, ie
            if (r_cnt > 0)
            {
                travel(spostorder, sinorder, root_pos - 1, i+1, ie, result, level+1);
            }
            break;
        }
    }
}


int main(int argc, char *argv[])
{
    string spostorder, sinorder;
    while (cin >> spostorder >> sinorder)
    {
        int n = spostorder.length();
        if (n != sinorder.length())
        {
            cerr << "invalid input: " << n << "," << sinorder.length() << endl;
            break;
        }
        if (n <= 0) break;
        vector<vector<char>> result;
        travel(spostorder, sinorder, n-1, 0, n-1, result, 0);
        for (int i = 0; i < result.size(); ++i)
        {
            for (int j = 0; j < result[i].size(); ++j)
            {
                cout << result[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}