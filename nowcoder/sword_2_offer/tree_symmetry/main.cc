#include "../test.h"

/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/


class Solution {
public:
    TreeNode *_MirrorTree(TreeNode *pSrc) {
        if (!pSrc) return NULL;
        TreeNode *node = new TreeNode(pSrc->val);
        node->left = _MirrorTree(pSrc->right);
        node->right = _MirrorTree(pSrc->left);
        return node;
    }

    bool _isSame(TreeNode *node0, TreeNode *node1) {
        if (!node0 && !node1) return true;
        if (node0 && node1) {
            if (node0->val != node1->val) return false;
            return _isSame(node0->left, node1->left) && _isSame(node0->right, node1->right);
        } else return false;
    }

    bool isSymmetrical(TreeNode* pRoot) {
        TreeNode *mirror = _MirrorTree(pRoot);
        return _isSame(pRoot, mirror);
    }
};

int main() {
    Solution s;
    int iLevel;
    while (cin>>iLevel) {
        INPUT_TREE(tree, iLevel, TreeNode);
        if (s.isSymmetrical(tree)) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}
