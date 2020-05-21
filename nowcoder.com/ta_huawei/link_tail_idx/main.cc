#include <iostream>
#include <cstring>
using namespace std;

struct ListNode{
    int       m_nKey;
    ListNode* m_pNext;
};

// use a limited queue to save browse history
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    if (k <= 0) return nullptr;

    ListNode **aBackup = new ListNode*[k];
    memset(aBackup, NULL, sizeof(ListNode*) * k);
    
    int cur_pos = 0;

    while(pListHead) {
        aBackup[cur_pos] = pListHead;
        cur_pos = (cur_pos + 1) % k;
        pListHead = pListHead->m_pNext;
    }

    ListNode *node = aBackup[cur_pos];
    delete [] aBackup;

    return node;
}

int listLen;
int num;
unsigned int lastIdx;
ListNode *head;
ListNode *tail;

int main() {
    while (cin >> listLen) {
        head = tail = nullptr;
        ListNode *node;

        while(listLen--) {
            node = new ListNode;
            cin >> node->m_nKey;
            node->m_pNext = nullptr;

            if (tail) {
                tail->m_pNext = node;
                tail = node;
            } else {
                head = tail = node;
            }
        }

        cin >> lastIdx;
        node = FindKthToTail(head, lastIdx);
        if (node) cout << node->m_nKey << endl;
        else cout << '0' << endl;

        while(head) {
            node = head->m_pNext;
            delete head;
            head = node;
        }
        head = tail = nullptr;
    }
    return 0;
}