#include "../test.h"

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        TreeLinkNode *parent = pNode->next, *pChild;
        if (!parent || parent->right == pNode) {
            // on the right
            if (pNode->right) {
                // deep left leaf node of right child
                pChild = pNode->right;
                while(pChild->left) pChild = pChild->left;
                return pChild;
            } else {
                if (parent) {
                    if (parent->next && parent->next->left == parent)
                        return parent->next;
                    else
                        return NULL;
                } else return NULL;
            }
        } else {
            // on the left
            if (pNode->right) {
                // deep left leaf node of right child
                pChild = pNode->right;
                while(pChild->left) pChild = pChild->left;
                return pChild;
            } else 
                return parent; // parent
        }
    }
};