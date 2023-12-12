/*
1038. 从二叉搜索树到更大和树
给定一个二叉搜索树 root (BST)，请将它的每个节点的值替换成树中大于或者等于该节点值的所有节点值之和。

提醒一下， 二叉搜索树 满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。

示例 1：
输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

示例 2：
输入：root = [0,null,1]
输出：[1,null,1]
*/

#include <iostream>
#include <vector>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
    void travel(TreeNode *node, vector<TreeNode *> &orders)
    {
        if (!node) return;
        travel(node->left, orders);
        orders.push_back(node);
        travel(node->right, orders);
    }

public:
    TreeNode* bstToGst(TreeNode* root) {
        // 将二叉搜索树进行中序遍历，放入一个数组中（有序）
        // 然后倒序对数组赋值
        vector<TreeNode *> orders;
        int presum = 0;
        for (vector<TreeNode *>::reverse_iterator it = orders.rbegin(); it != orders.rend(); ++it)
        {
            (*it)->val += presum; 
            presum = (*it)->val;
        }
        return root;
    }
};