#include "../test.h"
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if (!pRoot) return;
        TreeNode *tmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tmp;

        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};

int main() {
    int iLevel;
    Solution s;
    while (cin>>iLevel) {
        INPUT_TREE(tree, iLevel, TreeNode);

        TEST_HINT(---------);
        PRE_SHOW_TREE(tree);
        s.Mirror(tree);
        PRE_SHOW_TREE(tree);
    }
    return 0;
}