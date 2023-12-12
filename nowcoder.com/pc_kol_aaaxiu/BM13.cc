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
     * @param head ListNode类 the head
     * @return bool布尔型
     */
    bool isPail(ListNode* head) {
        // write code here
        vector<int> nums;
        ListNode *curr = head;
        while(curr)
        {
            nums.push_back(curr->val);
            curr = curr->next;
        }
        int i = 0, j = nums.size() - 1;
        while (i < j)
        {
            if (nums[i] != nums[j]) return false;
            i++;
            j--;
        }
        return true;
    }
};