#include "../test.h"

#include <sstream>
#include <vector>
#include <queue>

#define SEPRA_NODE " "
#define SEPRA_LINE ":"
#define PLACE_HOLD "#"

class Solution {
public:
    char* Serialize(TreeNode *root) {
        if (!root) return NULL;

        TreeNode *node;
        stringstream ss;
        int depth = 0;
        vector<vector<TreeNode *> > lvInfo;

        lvInfo.push_back({});
        lvInfo[depth].push_back(root);
        bool more;

        do {
            more = false;
            lvInfo.push_back({});
            for (auto it=lvInfo[depth].begin(); it!=lvInfo[depth].end(); it++) {
                node = (*it);
                if (node) {
                    ss << node->val;
                    more |= node->left || node->right;
                    lvInfo[depth+1].push_back(node->left);
                    lvInfo[depth+1].push_back(node->right);
                } else {
                    lvInfo[depth+1].push_back(NULL);
                    lvInfo[depth+1].push_back(NULL);
                    ss << PLACE_HOLD;
                }
                ss << SEPRA_NODE; // node end
            }
            ss << SEPRA_LINE; // level end
            depth++;
        } while(more);
        
        string result = ss.str();
        // TEST_INFO(result:, result);
        char *ret = new char[result.length()+1];
        strncpy(ret, result.c_str(), result.length());
        ret[result.length()] = 0;
        return ret;
    }

    TreeNode* Deserialize(char *str) {
        if (!str || !(*str)) return NULL;

        TreeNode *node, *parent;
        int depth = -1;
        string text = str, lv_line, node_info;
        if (text[text.length()-1]!=SEPRA_LINE[0]) {
            if (text[text.length()-1]!=SEPRA_NODE[0])
                text += SEPRA_NODE;
            text += SEPRA_LINE;
        }
        vector<vector<TreeNode *> > lvInfo;

        size_t lv_pos = text.find(SEPRA_LINE), node_pos;
        while (lv_pos!=string::npos) {
            depth++;
            lvInfo.push_back({});

            lv_line = text.substr(0, lv_pos);
            node_pos = lv_line.find(SEPRA_NODE);
            while (node_pos!=string::npos) {
                node_info = lv_line.substr(0, node_pos);
                // TEST_INFO(pos:, node_pos);
                // TEST_INFO2(node_info:, lv_line, node_info);
                if (node_info==PLACE_HOLD) {
                    lvInfo[depth].push_back(NULL);
                } else {
                    node = new TreeNode(atoi(node_info.c_str()));
                    if (depth) {
                        // find parent
                        int idx = lvInfo[depth].size();
                        parent = lvInfo[depth-1][idx/2];
                        if (idx%2) parent->right = node;
                        else parent->left = node;
                    }
                    lvInfo[depth].push_back(node);
                }

                lv_line = lv_line.substr(node_pos+1, lv_line.length()-node_pos-1);
                node_pos = lv_line.find(SEPRA_NODE);
            }

            text = text.substr(lv_pos+1, text.length()-lv_pos-1);
            lv_pos = text.find(SEPRA_LINE);
        }

        if (depth<0) return NULL;
        return lvInfo[0][0];
    }
};

int main() {
    string text;
    Solution s;
    while (getline(cin,text)) {
        if (text[text.length()-1] < 0x20)
            text = text.substr(0, text.length()-1); // remove CR
        TreeNode *tree = s.Deserialize(const_cast<char*>(text.c_str()));
        PRE_SHOW_TREE(tree);
        char *chArr = s.Serialize(tree);
        cout << chArr << endl;
    }
    return 0;
}