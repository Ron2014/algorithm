#include <iostream>
#include <vector>
#include <algorithm>
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
     * @param head ListNode类 the head node
     * @return ListNode类
     */
    ListNode* sortInList(ListNode* head) {
        // write code here
        vector<ListNode*> sortedList;
        ListNode *curr = head;
        int n = 0;
        while (curr)
        {
            sortedList.push_back(curr);
            curr = curr->next;
            n++;
        }
        sort(sortedList.begin(), sortedList.end(), [](ListNode *a, ListNode *b) {
            return a->val < b->val;
        });
        for (int i = 0; i < n; ++i)
        {
            sortedList[i]->next = (i<n-1)? sortedList[i+1] : nullptr;
        }
        return sortedList[0];
    }
};