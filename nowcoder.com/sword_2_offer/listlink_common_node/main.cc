#include "../test.h"
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* _FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2, int depth1, int depth2, int &match_depth) {
        if (!pHead1 || !pHead2)
            return NULL;
        if (pHead1->val == pHead2->val) {
            match_depth = depth1;
            if (depth1 > depth2) match_depth = depth2;
            return pHead1;
        }

        ListNode *ret0 = _FindFirstCommonNode(pHead1->next, pHead2, depth1+1, depth2, match_depth);
        int mdepth0 = match_depth;

        ListNode *ret1 = _FindFirstCommonNode(pHead1, pHead2->next, depth1, depth2+1, match_depth);
        int mdepth1 = match_depth;

        if (!ret0) return ret1;
        else if (!ret1) return ret0;
        else {
            if (mdepth0 < mdepth1){
                match_depth = mdepth0;
                return ret0;
            } else {
                match_depth = mdepth1;
                return ret1;
            }
        }
        
    }

    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        int match_depth = 0;
        return _FindFirstCommonNode(pHead1, pHead2, 0, 0, match_depth);
    }
};

int main() {
    int l0, l1;
    ListNode *link0, *link1, *node;
    Solution s;
    while(cin>>l0>>l1) {
        INPUT_LINKLIST(link0, l0, ListNode);
        INPUT_LINKLIST(link1, l1, ListNode);
        node = s.FindFirstCommonNode(link0, link1);
        if (node) cout << node->val << endl;
        else cout << "NONE" << endl;
    }
    return 0;
}

