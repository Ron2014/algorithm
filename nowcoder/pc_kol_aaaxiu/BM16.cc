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
     * @return ListNode类
     */
    ListNode* deleteDuplicates(ListNode* head) {
        // write code here
        ListNode *dummyHead = new ListNode(10000);
        dummyHead->next = head;
        ListNode *curr = dummyHead, *prev = nullptr, *pprev = nullptr;
        while (curr)
        {
            if (curr->next && curr->val == curr->next->val)
            {
                if (!pprev) pprev = prev;  // curr 是第一个重复的节点
            }
            else
            {
                if (pprev)
                {
                    // curr 是最后一个重复节点
                    pprev->next = curr->next;
                    curr = pprev;
                    pprev = nullptr;
                }
            }
            prev = curr;
            curr = curr->next;
        }
        return dummyHead->next;
    }
};