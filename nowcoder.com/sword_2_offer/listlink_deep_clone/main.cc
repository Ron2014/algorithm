#include "../test.h"

#include <map>
class Solution {
public:
    RandomListNode* _Clone(RandomListNode* pHead, map<RandomListNode*, RandomListNode*> &backup) {
        if(!pHead) return NULL;

        RandomListNode *node;
        auto it = backup.find(pHead);
        if (it==backup.end())
            backup[pHead] = new RandomListNode(pHead->label);
        node = backup[pHead];

        if (pHead->random) {
            it = backup.find(pHead->random);
            if (it==backup.end())
                backup[pHead->random] = new RandomListNode(pHead->random->label);
            node->random = backup[pHead->random];
        }

        node->next = _Clone(pHead->next, backup);
        return node;
    }
    
    RandomListNode* Clone(RandomListNode* pHead) {
        map<RandomListNode*, RandomListNode*> backup;
        return _Clone(pHead, backup);
    }
};

int main() {
    return 0;
}