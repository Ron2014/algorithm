#include <iostream>
#include <set>
using namespace std;

// #define TEST

#ifdef TEST

#define TEST_SHOW_ARRAY(a,l) \
    for (int i=0; i<l; i++) \
        std::cout << a[i] << " "; \
    std::cout << endl;

#define TEST_SHOW_ARRAY2(a,r,c) \
    for (int i=0; i<r; i++) {\
        for (int j=0; j<c; j++) \
            std::cout << a[i][j] << " "; \
        std::cout << endl; \
    } \
    std::cout << endl;

#define TEST_HINT(t) \
    std::cout << #t << endl;

#define TEST_INFO(t,v) \
    std::cout << #t << v << endl;

#define TEST_INFO2(t,i,j) \
    std::cout << #t << i << " " << j << endl;

#else

#define TEST_SHOW_ARRAY(a,l)
#define TEST_SHOW_ARRAY2(a,r,c)
#define TEST_HINT(t)
#define TEST_INFO(t,v)
#define TEST_INFO2(t,i,j)

#endif

#define SHOW_ARRAY(a,l) \
    for (int i=0; i<l; i++) \
        std::cout << a[i] << " "; \
    std::cout << endl;

#define SHOW_ARRAY2(a,r,c) \
    for (int i=0; i<r; i++) {\
        for (int j=0; j<c; j++) \
            std::cout << a[i][j] << " "; \
        std::cout << endl; \
    } \
    std::cout << endl;

#define INIT_ARRAY(a,l,t) \
    t *a = new t[l]
        
#define INPUT_ARRAY(a,l,t) \
    INIT_ARRAY(a,l,t); \
    for (int i=0; i<l; i++) \
        cin >> a[i];

#define DELETE_ARRAY(a) \
    delete[] a;

#define INIT_ARRAY2(a,r,c,t) \
    t **a = new t*[r]; \
    for (int i=0; i<r; i++) \
        a[i] = new t*[c];
        
#define INPUT_ARRAY2(a,r,c,t) \
    INIT_ARRAY2(a,r,c,t); \
    for (int i=0; i<r; i++) \
        for (int j=0; j<c; j++) \
            cin >> a[i][j];
        
#define DELETE_ARRAY2(a,r) \
    for (int i=0; i<r; i++) \
        delete[] a[i]; \
    delete[] a;

#define SHOW_LINKLIST(h,t,v,n) \
    { \
        t *ph = h; \
        while (ph) { \
            cout << ph->m_##v << " "; \
            ph = ph->m_##n; \
        } \
        cout << endl; \
    }

#define DELETE_LINKLIST(h,t,n) \
    while (h) { \
        t *tmp = h->m_##n; \
        delete h; \
        h = tmp; \
    }


struct ListNode
{
    int       m_nKey;
    ListNode* m_pNext;
};

int main() {
    int c, k, v;
    set<int> sVals;

    while (cin >> c) {
        sVals.clear();
        ListNode *head = new ListNode;
        cin >> head->m_nKey;
        sVals.insert(head->m_nKey);
        head->m_pNext = nullptr;

        ListNode *q, *p, *tail = head;
        for (int i=1; i<c; i++) {
            /****
             * for each input k, v means:
             * create a new node k (the value is k, so k not duplicate)
             * insert it after node v
             */
            cin >> k >> v;
            if (sVals.find(k) != sVals.end()) continue;
            sVals.insert(k);

            ListNode *node = new ListNode;
            node->m_nKey = k;
            node->m_pNext = nullptr;

            q = head;
            while(q && q->m_nKey!=v) {
                q = q->m_pNext;
            }
            if (q) {
                node->m_pNext = q->m_pNext;
                q->m_pNext = node;
            } else {
                tail->m_pNext = node;
            }
            if (!node->m_pNext) tail = node;
        }

        cin >> k;

        // SHOW_LINKLIST(head, ListNode, nKey, pNext);

        q = head;
        p = nullptr;
        while(q) {
            if (q->m_nKey == k) break;
            p = q;
            q = q->m_pNext;
        }
        if (q) {
            // delete q
            if (p) p->m_pNext = q->m_pNext;
            else head = q->m_pNext;  // delete head
            if (q==tail) tail = p ? p : head;
            delete q;
        }

        SHOW_LINKLIST(head, ListNode, nKey, pNext);

        DELETE_LINKLIST(head, ListNode, pNext);
    }
    return 0;
}