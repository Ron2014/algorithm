#include <iostream>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        ListNode *pslow = pHead;
        ListNode *pfast = pHead;
        bool bcycle = false;

        while (pfast && pfast->next)
        {
            pslow = pslow->next;
            pfast = pfast->next->next;
            if (pslow == pfast)
            {
                pfast = pHead;
                bcycle = true;
                break;
            }
        }

        if (!bcycle) return nullptr;
        while (pfast != pslow)
        {
            pfast = pfast->next;
            pslow = pslow->next;
        }
        return pfast;
    }
};