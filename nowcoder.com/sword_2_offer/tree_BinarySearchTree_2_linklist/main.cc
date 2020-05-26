#include "../test.h"
class Solution {
public:
    // return circle linklist
    TreeNode* _Convert(TreeNode* pRootOfTree, unsigned int depth) {
        // TEST_INFO(depth:, depth);
        if (!pRootOfTree) return NULL;
        TreeNode *pHead, *pTail;
        TreeNode *childL = pRootOfTree->left;
        TreeNode *childR = pRootOfTree->right;

        // head
        pHead = _Convert(childL, depth+1);

        // middle
        // pHead->left ==> the last one
        if (pHead) {
            pHead->left->right = pRootOfTree;
            pRootOfTree->left = pHead->left;
            pRootOfTree->right = pHead;
            pHead->left = pRootOfTree;
        } else {
            pHead = pRootOfTree;
            pHead->left = pHead;
            pHead->right = pHead;
        }

        // tail
        pTail = _Convert(childR, depth+1);
        if (pTail) {
            TreeNode *tailH, *tailT;
            tailH = pTail;
            tailT = pTail->left;

            pHead->left->right = tailH;
            tailH->left = pHead->left;
            tailT->right = pHead;
            pHead->left = tailT;
        }

        if (!depth) {
            // break circle
            pHead->left->right = NULL;
            pHead->left = NULL;
        }

        return pHead;
    }

    //
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        return _Convert(pRootOfTree, 0);
    }
};

int main() {
    Solution s;
    int lv;
    while (cin>>lv) {
        INPUT_TREE(tree, lv, TreeNode);
        PRE_SHOW_TREE(tree);
        TreeNode *pHead = s.Convert(tree);
        SHOW_TREE_LINKLIST(pHead, TreeNode);
    }
    return 0;
}