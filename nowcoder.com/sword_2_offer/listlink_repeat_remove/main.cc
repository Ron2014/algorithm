#include "../test.h"

#include <set>
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        set<int> onces;
        ListNode *p, *q = NULL, *r = NULL;
        p = pHead;
        while (p) {
            if (p->next && p->next->val == p->val) {
                // delete p p->next
                onces.insert(p->val);
                p = p->next->next;
                if (q) q->next = p;
                else pHead = p;
            } else if (onces.find(p->val)!=onces.end()) {
                // removed
                // delete p
                p = p->next;
                if (q) q->next = p;
                else pHead = p;
            } else {
                onces.insert(p->val);
                q = p;
                p = p->next;
            }
        }
        return pHead;
    }
};

int main() {
    Solution s;
    int iCount;
    while (cin>>iCount) {
        INPUT_LINKLIST(pHead, iCount, ListNode);
        // SHOW_LINKLIST(pHead, ListNode);
        pHead = s.deleteDuplication(pHead);
        SHOW_LINKLIST(pHead, ListNode);
    }
    return 0;
}