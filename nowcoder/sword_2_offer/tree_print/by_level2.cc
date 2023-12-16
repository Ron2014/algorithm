#include "../test.h"
class Solution {
public:
    void _Print(TreeNode *node, int depth, vector<vector<int> > &result) {
        if (!node) return;
        if (depth == result.size())
            result.push_back({});
        result[depth].push_back(node->val);
        _Print(node->left, depth+1, result);
        _Print(node->right, depth+1, result);
    }

    vector<vector<int> > Print(TreeNode* root) {
        vector<vector<int> > result;
        _Print(root, 0, result);
        return result;
    }
};

int main() {
    int iLevel;
    Solution s;

    while (cin>>iLevel) {
        INPUT_TREE(tree, iLevel, TreeNode);
        // PRE_SHOW_TREE(tree);
        vector<vector<int> > ret = s.Print(tree);
        TEST_INFO(level:, ret.size());
        for (auto it0=ret.begin(); it0!=ret.end(); it0++) {
            for (auto it1=(*it0).begin(); it1!=(*it0).end(); it1++) {
                cout << *it1 << " ";
            }
            cout << endl;
        }
    }
    return 0;
}