#include "../test.h"
class Solution {
public:
    void _TreeDepth(TreeNode *pRoot, int depth, int &max_depth) {
        if (!pRoot) return;
        
        _TreeDepth(pRoot->left, depth+1, max_depth);
        _TreeDepth(pRoot->right, depth+1, max_depth);

        if (!pRoot->left && !pRoot->right && depth > max_depth)
            max_depth = depth;
    }

    bool IsBalanced_Solution(TreeNode* pRoot) {
        if (!pRoot) return true;
        if (!IsBalanced_Solution(pRoot->left)) return false;
        if (!IsBalanced_Solution(pRoot->right)) return false;

        int depthL = 0;
        _TreeDepth(pRoot->left, 0, depthL);
        int depthR = 0;
        _TreeDepth(pRoot->right, 0, depthR);

        int diffDepth = depthL - depthR;
        return (diffDepth >=-1 && diffDepth <= 1);
    }
};

int main() {
    Solution s;
    int n;
    while (cin>>n) {
        INPUT_TREE(tree, n, TreeNode);
        PRE_SHOW_TREE(tree);
        if (s.IsBalanced_Solution(tree)) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}