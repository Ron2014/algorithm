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
    ListNode* oddEvenList(ListNode* head) {
        // write code here
        ListNode *odd_head = new ListNode(0);
        ListNode *even_head = new ListNode(0);
        int step = 0;
        ListNode *curr = head, *odd = odd_head, *even = even_head;
        while (curr)
        {
            step++;
            if (step & 1)
            {
                // odd
                odd->next = curr;
                odd = odd->next;
            }
            else
            {
                // even
                even->next = curr;
                even = even->next;
            }
            curr = curr->next;
        }
        odd->next = even_head->next;
        even->next = nullptr;
        return odd_head->next;
    }
};