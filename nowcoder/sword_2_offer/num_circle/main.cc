#include "../test.h"

struct ListNodeDuplexing {
    int val;
    ListNodeDuplexing *left;
    ListNodeDuplexing *right;
    ListNodeDuplexing() : left(NULL), right(NULL) {}
    ListNodeDuplexing(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int LastRemaining_Solution(int n, int m) {
        if (n<=0) return -1;

        // // WAY 1. array
        // int *aChilds = new int[n];
        // for (int i=0; i<n; i++) {
        //     aChilds[i] = i;
        // }
        // int startIdx = 0;
        // while(n>1) {
        //     int gift_idx = (startIdx + m - 1) % n;
        //     int child_id = aChilds[gift_idx];

        //     TEST_INFO(gift for:, child_id);
        // // move memory!!!
        //     for (int i=gift_idx; i<n-1; i++) {
        //         aChilds[i] = aChilds[i+1];
        //     }
        //     aChilds[n-1] = child_id;

        //     n--;
        //     startIdx = gift_idx;
        // }
        // int ret = aChilds[0];
        // delete[] aChilds;

        // WAY 2. two-way listlink
        ListNodeDuplexing *lChilds = new ListNodeDuplexing[n];
        for (int i=0; i<n; i++) {
            lChilds[i].val = i;
            lChilds[i].right = &(lChilds[(i+1)%n]);
            lChilds[i].left = &(lChilds[(i+n-1)%n]);
        }

        ListNodeDuplexing *pChild = &(lChilds[0]);
        while(n>1) {
            int moves = (m-1)%n;
            while(moves--)
                pChild = pChild->right;
            // TEST_INFO(gift for:, pChild->val);

            // remove child
            pChild->left->right = pChild->right;
            pChild->right->left = pChild->left;

            // new round
            pChild = pChild->right;
            n--;
        }

        int ret = pChild->val;
        delete[] lChilds;

        return ret;
    }
};

int main() {
    int iChild, iM;
    Solution s;
    while (cin>>iChild>>iM) {
        cout << s.LastRemaining_Solution(iChild, iM) << endl;
    }
    return 0;
}