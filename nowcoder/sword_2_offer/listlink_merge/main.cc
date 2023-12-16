#include "../test.h"
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        ListNode *pHead, *pTail;
        ListNode **curLink, *node;
        pHead = pTail = NULL;

        while (pHead1 || pHead2) {
            if (pHead1 && pHead2) {
                if (pHead1->val < pHead2->val)
                    curLink = &pHead1;
                else
                    curLink = &pHead2;
            } else {
                curLink = (pHead1) ? &pHead1 : &pHead2;
            }

            node = new ListNode((*curLink)->val);
            *curLink =  (*curLink)->next;

            if (pTail) {
                pTail->next = node;
                pTail = node;
            } else 
                pHead = pTail = node;
        }
        return pHead;
    }
};

int main() {
    int n1, n2;
    Solution s;
    while (cin>>n1>>n2) {
        INPUT_LINKLIST(l1, n1, ListNode);
        INPUT_LINKLIST(l2, n2, ListNode);
        SHOW_LINKLIST(s.Merge(l1, l2), ListNode);
    }
}