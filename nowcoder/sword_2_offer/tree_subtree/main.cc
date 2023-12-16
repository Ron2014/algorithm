#include "../test.h"
class Solution {
public:
    bool _isSame(TreeNode* pRoot1, TreeNode* pRoot2) {
        if (pRoot1 == pRoot2 || !pRoot2) return true;
        if (!pRoot1 || pRoot1->val != pRoot2->val) return false;
        return _isSame(pRoot1->left, pRoot2->left) && _isSame(pRoot1->right, pRoot2->right);
    }
    
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if (!pRoot1) return false;
        if (!pRoot2) return false;

        if (_isSame(pRoot1, pRoot2)) {
            return true;
        } else {
            return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
        }
    }
};

vector<int> g_pre;
vector<int> g_vin;

int main() {
    int iCount0, iCount1;
    Solution s;

    while (cin>>iCount0>>iCount1) {
        INPUT_TREE(tree0, iCount0, TreeNode);
        INPUT_TREE(tree1, iCount1, TreeNode);

        PRE_SHOW_TREE(tree0);
        PRE_SHOW_TREE(tree1);

        if (s.HasSubtree(tree0, tree1)) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}