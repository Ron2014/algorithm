#include "../test.h"
#include <stack>
class Solution {
public:
    bool _possible(vector<int>::iterator push_start, vector<int>::iterator push_end, stack<int> &stack_nums, vector<int>::iterator pop_idx) {
        if (!stack_nums.empty() && stack_nums.top()==*pop_idx) {
            stack_nums.pop();
            return _possible(push_start, push_end, stack_nums, pop_idx+1);
        } else {
            if (push_start<push_end) {
                stack_nums.push(*push_start);
                return _possible(push_start+1, push_end, stack_nums, pop_idx);
            } else {
                return stack_nums.empty();
            }
        }
    }

    bool IsPopOrder(vector<int> &pushV, vector<int> &popV) {
        stack<int> stack_nums;
        return _possible(pushV.begin(), pushV.end(), stack_nums, popV.begin());
    }
};

int main () {
    int iCount;
    Solution s;
    while (cin>>iCount) {
        INPUT_ARRAY(aPush, iCount, int);
        INPUT_ARRAY(aPop, iCount, int);
        vector<int> vPush(aPush, aPush+iCount);
        vector<int> vPop(aPop, aPop+iCount);
        if (s.IsPopOrder(vPush, vPop)) cout << "true" << endl;
        else cout << "false" << endl;
        DELETE_ARRAY(aPush);
    }
    return 0;
}