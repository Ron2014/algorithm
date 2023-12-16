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
    void _TreeDepth(TreeNode *pRoot, int depth, int &max_depth) {
        if (!pRoot) return;
        
        _TreeDepth(pRoot->left, depth+1, max_depth);
        _TreeDepth(pRoot->right, depth+1, max_depth);

        if (!pRoot->left && !pRoot->right && depth > max_depth)
            max_depth = depth;
    }

    int TreeDepth(TreeNode* pRoot) {
        int max_depth = 0;
        _TreeDepth(pRoot, 1, max_depth);
        return max_depth;
    }
};

int main() {
    int n, m;
    Solution s;
    while (cin>>n) {
        INPUT_TREE(tree, n, TreeNode);
        cout << s.TreeDepth(tree) << endl;
    }
    return 0;
}