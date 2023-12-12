#include <iostream>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *pslow = head;
        ListNode *pfast = head;

        while (pfast && pfast->next)
        {
            pslow = pslow->next;
            pfast = pfast->next->next;
            if (pslow == pfast) return true;
        }

        return false;
    }
};