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
     * @param head ListNode类 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // write code here
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode *curr = dummyHead, *prev = nullptr;
        int step = 0;
        while (curr)
        {
            if (step > n)
            {
                if (prev) prev = prev->next;
                else prev = dummyHead;
            }
            curr = curr->next;
            step++;

        }

        if (prev)
        {
            prev->next = prev->next->next;
        }

        return dummyHead->next;
    }
};