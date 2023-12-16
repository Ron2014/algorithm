#include <iostream>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pHead1 ListNode类 
     * @param pHead2 ListNode类 
     * @return ListNode类
     */
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        // write code here
        ListNode *dummyHead = new ListNode(0);
        ListNode *prev = dummyHead;
        while (pHead1 && pHead2)
        {
            if (pHead1->val < pHead2->val)
            {
                prev->next = pHead1;
                pHead1 = pHead1->next;
            }
            else
            {
                prev->next = pHead2;
                pHead2 = pHead2->next;
            }
            prev = prev->next;
        }
        if (pHead1) prev->next = pHead1;
        if (pHead2) prev->next = pHead2;
        return dummyHead->next;
    }
};