/*
2415. 反转二叉树的奇数层

给你一棵 完美 二叉树的根节点 root ，请你反转这棵树中每个 奇数 层的节点值。

例如，假设第 3 层的节点值是 [2,1,3,4,7,11,29,18] ，那么反转后它应该变成 [18,29,11,7,4,3,1,2] 。
反转后，返回树的根节点。

完美 二叉树需满足：二叉树的所有父节点都有两个子节点，且所有叶子节点都在同一层。

节点的 层数 等于该节点到根节点之间的边数。
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        queue<TreeNode *> q;
        q.push(root);
        int level = 0;
        while (!q.empty())
        {
            vector<TreeNode *> temp;
            int qn = q.size();
            while (qn-- > 0)
            {
                TreeNode *pnode = q.front();
                if (level & 1) temp.push_back(pnode);
                if (pnode->left) q.push(pnode->left);
                if (pnode->right) q.push(pnode->right);
                q.pop();
            }
            int tn = temp.size();
            int cnt = tn >> 1;
            for (int i = 0; i < cnt; ++i)
            {
                swap(temp[i]->val, temp[tn-i-1]->val);
            }
            level++;
        }
        return root;
    }
};

int main()
{
    getchar();
    return 0;
}