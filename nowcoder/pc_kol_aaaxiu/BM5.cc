#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    ListNode *mergeList(ListNode *head1, ListNode *head2)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *prev = dummyHead;
        while (head1 && head2)
        {
            if (head1->val < head2->val)
            {
                prev->next = head1;
                head1 = head1->next;
            }
            else
            {
                prev->next = head2;
                head2 = head2->next;
            }
            prev = prev->next;
        }
        if (head1) prev->next = head1;
        if (head2) prev->next = head2;
        return dummyHead->next;
    }

public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param lists ListNode类vector 
     * @return ListNode类
     */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // write code here
        int n = lists.size();
        if (n <= 0) return nullptr;

        ListNode *head = lists[0];
        for (int i = 1; i < n; ++i)
        {
            head = mergeList(head, lists[i]);
        }
        return head;
    }
};