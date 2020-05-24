#include "../test.h"
class Solution {
public:
    void _FindPath(TreeNode *root, int num, vector<int> &route, vector<vector<int> > &all_routes) {
        if (root==NULL) return;

        route.push_back(root->val);
        if (num==root->val && !root->left && !root->right) {
            all_routes.push_back(route);
            route.pop_back();
            return;
        }

        // connect to last route -> find left
        _FindPath(root->left, num-root->val, route, all_routes);
        // connect to last route -> find right
        _FindPath(root->right, num-root->val, route, all_routes);
        route.pop_back();

        // new route -> find left
        // new route -> find right
    }

    vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
        vector<vector<int> > all_routes;
        vector<int> route;
        _FindPath(root, expectNumber, route, all_routes);
        return all_routes;
    }
};

int main() {
    int n, m;
    Solution s;
    while (cin>>n>>m) {
        INPUT_TREE(tree, n, TreeNode);
        vector<vector<int> > result = s.FindPath(tree, m);
        if (result.size()) {
            for (auto it0=result.begin(); it0!=result.end(); it0++) {
                vector<int> vRoute = *it0;
                for (auto it1=vRoute.begin(); it1!=vRoute.end(); it1++) {
                    if (it1!=vRoute.begin()) cout << "->";
                    cout << *it1;
                }
                cout << endl;
            }
        } else {
            cout << "None" << endl;
        }
    }
    return 0;
}