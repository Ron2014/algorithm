#include "../test.h"
#include <vector>
#include <algorithm>

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(const vector<int> &pre, const vector<int> &vin) {
        int len = pre.size();
        if (len==0) return NULL;

        int root_val = pre[0];
        TreeNode *node = new TreeNode(root_val);

        if (len>1) {
            int mid_pos = distance(vin.begin(), find(vin.begin(), vin.end(), root_val));
            if (mid_pos>0) {
                vector<int> vin_left(vin.begin(), vin.begin()+mid_pos);
                vector<int> pre_left(pre.begin()+1, pre.begin()+1+mid_pos);
                node->left = reConstructBinaryTree(pre_left, vin_left);
            }

            if (mid_pos<len-1) {
                vector<int> vin_right(vin.begin()+mid_pos+1, vin.end());
                vector<int> pre_right(pre.begin()+1+mid_pos, pre.end());
                node->right = reConstructBinaryTree(pre_right, vin_right);
            }
        }
        return node;
    }

    // no more memory
    TreeNode* reConstructBinaryTree(vector<int>::iterator pre_begin, vector<int>::iterator pre_end, \
        vector<int>::iterator vin_begin, vector<int>::iterator vin_end) {
        if(pre_begin == pre_end) return NULL;
        
        int root_val = *pre_begin;
        TreeNode *node = new TreeNode(root_val);

        int len = distance(pre_begin, pre_end);
        if (len>1) {
            int mid_pos = distance(vin_begin, find(vin_begin, vin_end, root_val));

            if (mid_pos>0) {
                node->left = reConstructBinaryTree(pre_begin+1, pre_begin+1+mid_pos, vin_begin, vin_begin+mid_pos);
            }

            if (mid_pos<len-1) {
                node->right = reConstructBinaryTree(pre_begin+1+mid_pos, pre_end, vin_begin+mid_pos+1, vin_end);
            }
        }
        return node;
    }
};


vector<int> g_pre;
vector<int> g_vin;

int main() {
    int iCount, iNum;
    Solution s;
    while (cin>>iCount) {
        g_pre.clear();
        g_vin.clear();

        for (int i=0; i<iCount; i++) {
            cin >> iNum;
            g_pre.push_back(iNum);
        }

        for (int i=0; i<iCount; i++) {
            cin >> iNum;
            g_vin.push_back(iNum);
        }
        
        // TreeNode *root = s.reConstructBinaryTree(g_pre, g_vin);
        TreeNode *root = s.reConstructBinaryTree(g_pre.begin(), g_pre.end(), g_vin.begin(), g_vin.end());

        PRE_SHOW_TREE(root);
        MID_SHOW_TREE(root);
        POS_SHOW_TREE(root);
    }
    return 0;
}