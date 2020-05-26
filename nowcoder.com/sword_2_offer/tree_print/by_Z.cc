#include "../test.h"

class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int> > result;
        if (!pRoot) return result;

        int depth = 0;
        vector<vector<TreeNode *> > tmp;
        TreeNode *node;
        tmp.push_back({});
        tmp[depth].push_back(pRoot);
        bool more;

        do {
            more = false;
            tmp.push_back({});
            for (auto it=tmp[depth].begin(); it!=tmp[depth].end(); it++) {
                node = (*it);
                more |= node->left || node->right;
                if (node->left) tmp[depth+1].push_back(node->left);
                if (node->right) tmp[depth+1].push_back(node->right);
            }
            depth++;
        }while(more);

        int len = tmp.size(), count;
        for (int i=0; i<len; i++) {
            count = tmp[i].size();
            if (!count) break;

            result.push_back({});
            // TEST_INFO2(level info:, i, count);
            for (int j=0; j<count; j++) {
                if (i%2) result[i].push_back(tmp[i][count-1-j]->val);
                else result[i].push_back(tmp[i][j]->val);
            }
        }

        return result;
    }
    
};

int main() {
    Solution s;
    int iLevel;
    while (cin>>iLevel) {
        INPUT_TREE(tree, iLevel, TreeNode);
        PRE_SHOW_TREE(tree);
        
        vector<vector<int> > result = s.Print(tree);

        for (auto it0=result.begin(); it0!=result.end(); it0++) {
            for (auto it1=(*it0).begin(); it1!=(*it0).end(); it1++)
                cout << *it1 << " ";
            cout << endl;
        }
    }
}