#include <iostream>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    ListNode *reverseList(ListNode *head)
    {
        if (!head) return nullptr;

        ListNode *curr = head, *prev = nullptr, *next;
        while (curr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param head1 ListNode类 
     * @param head2 ListNode类 
     * @return ListNode类
     */
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        // write code here
        head1 = reverseList(head1);
        head2 = reverseList(head2);

        ListNode *curr = nullptr, *next = nullptr;
        int num, carry = 0;

        while (head1 && head2)
        {
            num = head1->val + head2->val + carry;

            carry = num / 10;
            num = num % 10;

            curr = new ListNode(num);
            curr->next = next;
            next = curr;

            head1 = head1->next;
            head2 = head2->next;

            cout << num << endl;
        }

        ListNode *head = head1 != nullptr ? head1 : head2;
        while (head)
        {
            num = head->val + carry;

            carry = num / 10;
            num = num % 10;

            curr = new ListNode(num);
            curr->next = next;
            next = curr;

            head = head->next;
        }

        cout << carry << endl;

        if (carry > 0)
        {
            curr = new ListNode(carry);
            curr->next = next;
            next = curr;
        }

        return curr;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n = atoi(argv[argc-1]);

    ListNode *curr = nullptr;
    ListNode *next = nullptr;
    for (int i = argc - n - 2; i >= 1; --i)
    {
        curr = new ListNode(atoi(argv[i]));
        if (next) curr->next = next;
        next = curr;
    }
    ListNode *head1 = next;

    curr = head1;
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;

    next = nullptr;
    for (int i = argc - 2; i >= 1 + n; --i)
    {
        curr = new ListNode(atoi(argv[i]));
        if (next) curr->next = next;
        next = curr;
    }
    ListNode *head2 = next;

    curr = head2;
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;

    ListNode *head = s.addInList(head1, head2);

    curr = head;
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
    return 0;
}