#include "../test.h"


#include <set>
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        set<ListNode *> backup;
        ListNode* p = pHead;
        while (p && backup.find(p)==backup.end()) {
            backup.insert(p);
            p = p->next;
        }
        return p;
    }
};

int main() {
    return 0;
}