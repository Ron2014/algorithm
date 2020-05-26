#include "../test.h"
/**
 * 搜索二叉树的中序遍历即排序结果
*/
#include <vector>
class Solution {
public:
    void _GetOrder(TreeNode* node, vector<TreeNode *> &orders) {
        if (!node) return;
        _GetOrder(node->left, orders);
        orders.push_back(node);
        _GetOrder(node->right, orders);
    }

    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if (k<=0) return NULL;
        vector<TreeNode *> orders;
        _GetOrder(pRoot, orders);
        if (orders.size()<k) return NULL;
        return orders[k-1];
    }  
};

int main() {
    Solution s;
    int iLevel, iNum;
    while (cin>>iLevel>>iNum) {
        INPUT_TREE(tree, iLevel, TreeNode);
        TreeNode *node = s.KthNode(tree, iNum);
        if (node) cout << node->val << endl;
        else cout << "NONE" << endl;
    }
}