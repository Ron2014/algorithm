#include "../test.h"

#include <queue>
class Solution {
public:
    // WAY 1. queue
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        queue<TreeNode *> qLevel;
        qLevel.push(root);

        vector<int> result;
        TreeNode *node;
        while (!qLevel.empty()) {
            node = qLevel.front();
            if (node) {
                result.push_back(node->val);
                qLevel.push(node->left);
                qLevel.push(node->right);
            }
            qLevel.pop();
        }
        return result;
    }
};

int main() {
    int iLevel;
    Solution s;

    while (cin>>iLevel) {
        INPUT_TREE(tree, iLevel, TreeNode);
        PRE_SHOW_TREE(tree);
        vector<int> ret = s.PrintFromTopToBottom(tree);
        SHOW_ARRAY(ret, ret.size());
    }
    return 0;
}