#include <iostream>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode *pA = pHead1;
        ListNode *pB = pHead2;
        while (pA != pB)
        {
            pA = (pA != nullptr) ? pA->next : pHead2;
            pB = (pB != nullptr) ? pB->next : pHead1;
        }
        return pA;
    }
};
