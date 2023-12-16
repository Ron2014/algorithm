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
     * @param m int整型 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // write code here
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        // 保留 n - m + 1 个节点
        ListNode *curr = dummyHead;
        ListNode *prev = dummyHead;
        int step = 0;
        while (curr && step < n)
        {
            if (step > n - m)
            {
                prev = prev->next;
            }
            curr = curr->next;
            step++;
        }

        // cout << prev->val << " " << curr->val << endl;
        ListNode *temp = prev->next;
        ListNode *next = curr->next;
        prev->next = curr;
        curr = temp;

        while (m++ <= n)
        {
            temp = curr->next;
            curr->next = next;
            next = curr;
            curr = temp;
        }

        return dummyHead->next;
    }
};

int main(int argc, char *argv[])
{
    ListNode *curr = nullptr;
    ListNode *next = nullptr;
    for (int i = argc - 3; i >= 1; --i)
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
    head = s.reverseBetween(next, atoi(argv[argc-2]), atoi(argv[argc-1]));

    curr = head;
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
    return 0;
}