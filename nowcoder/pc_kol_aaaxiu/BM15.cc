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
        ListNode *curr = head, *prev = nullptr;
        while (curr)
        {
            if (prev && prev->val == curr->val)
            {
                prev->next = curr->next;
            }
            else
            {
                prev = curr;
            }
            curr = curr->next;
        }
        return head;
    }
};