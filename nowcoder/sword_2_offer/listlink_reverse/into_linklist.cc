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
    ListNode* ReverseList(ListNode* pHead) {
        ListNode* p = pHead;
        ListNode* node;
        ListNode* pNewHead = NULL;

        while (p) {
            node = new ListNode(p->val);
            node->next = pNewHead;
            pNewHead = node;
            p=p->next;
        }

        return pNewHead;
    }
};

int main() {
    int iCount, n;
    ListNode *node;
    ListNode *pHead, *pTail;
    Solution s;

    while (cin >> iCount) {
        pHead = pTail = NULL;

        while(iCount--) {
            cin >> n;
            node = new ListNode(n);
            if (pTail) {
                pTail->next = node;
                pTail = node;
            } else
                pHead = pTail = node;
        }

        SHOW_LINKLIST(pHead, ListNode);
        SHOW_LINKLIST(s.ReverseList(pHead), ListNode);
    }
    return 0;
}