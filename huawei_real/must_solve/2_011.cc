/*
给出一个二叉树如下图所示：
                  6
                 /  \
                7    9
                 \   /   
                 -2 6   
 
请由该二叉树生成一个新的二叉树，它满足其树中的每个节点将包含原始树中的左子树和右子树的和。
 
                 20(7-2+9+6)
                 /      \
                -2       6
                 \      /   
                  0    0      
 
左子树表示该节点左侧叶子节点为根节点的一颗新树；右子树表示该节点右侧叶子节点为根节点的一颗新树

*/

#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode():val(0),left(nullptr),right(nullptr) {}
    TreeNode(int v)
    {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode *buildTree(int n)
{
    string s;
    vector<vector<TreeNode *>> level(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < pow(2, i); ++j)
        {
            cin >> s;
            if (s == "null")
            {
                level[i].push_back(nullptr);
            }
            else
            {
                level[i].push_back(new TreeNode(atoi(s.c_str())));
            }
        }
    }
    for (int i = 0; i < n-1; ++i)
    {
        for (int j = 0; j < pow(2, i); ++j)
        {
            int l_idx = 2 * j;
            int r_idx = 2 * j + 1;
            cout << "[" << i << "][" << j << "]->" << l_idx << " " << r_idx << endl;
            level[i][j]->left = level[i+1][l_idx];
            level[i][j]->right = level[i+1][r_idx];
        }
    }
    return level[0][0];
}

void printTree(TreeNode *root)
{
    deque<TreeNode *> visited;
    visited.push_back(root);
    while (!visited.empty())
    {
        int n = visited.size();
        for (int i = 0; i < n; ++i)
        {
            TreeNode *node = visited.front();
            if (!node)
            {
                cout << "null ";
            }
            else
            {
                cout << node->val << " ";
                visited.push_back(node->left);
                visited.push_back(node->right);
            }
            visited.pop_front();
        }
        cout << endl;
    }
}

int travel(TreeNode *node)
{
    if (!node) return 0;

    int val = node->val;

    int child_sum = 0;
    if (node->left)
    {
        child_sum += travel(node->left);
    }
    if (node->right)
    {
        child_sum += travel(node->right);
    }
    node->val = child_sum;

    return val + child_sum;
}

int main(int argc, char *argv[])
{
    // 后续遍历得到子节点得和
    int n;
    while (cin >> n)
    {
        TreeNode *root = buildTree(n);
        printTree(root);
        travel(root);
        printTree(root);
    }
    return 0;
}