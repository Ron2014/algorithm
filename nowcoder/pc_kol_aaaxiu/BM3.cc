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
     * @param k int整型 
     * @return ListNode类
     */
    ListNode* reverseKGroup(ListNode* head, int k) {
        // write code here
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;

        ListNode *curr = dummyHead;
        ListNode *prev = dummyHead;
        int step = 0;

        while (curr)
        {
            if (step == k)
            {
                // cout << prev->val << " " << curr->val << endl;

                // prev -> curr 交换
                ListNode *temp = prev->next;
                ListNode *next = curr->next;
                prev->next = curr;
                prev = temp;
                curr = temp;

                while (step > 0)
                {
                    // cout << curr->val << " " << next->val << endl;
                    temp = curr->next;
                    curr->next = next;
                    next = curr;
                    curr = temp;
                    step--;
                }
                curr = prev;
                // cout << step << endl;
                // cout << prev->val << " " << curr->val << endl;
            }

            curr = curr->next;
            step++;
        }
        return dummyHead->next;
    }
};

int main(int argc, char *argv[])
{
    ListNode *curr = nullptr;
    ListNode *next = nullptr;
    for (int i = argc - 2; i >= 1; --i)
    {
        curr = new ListNode(atoi(argv[i]));
        if (next) curr->next = next;
        next = curr;
    }
    ListNode *head = next;

    curr = head;
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;

    Solution s;
    head = s.reverseKGroup(next, atoi(argv[argc-1]));

    curr = head;
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
    return 0;
}