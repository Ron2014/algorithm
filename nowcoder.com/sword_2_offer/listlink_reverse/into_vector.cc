#include <vector>
#include <stack>
using namespace std;
struct ListNode {
      int val;
      struct ListNode *next;
      ListNode(int x) :
            val(x), next(NULL) {
      }
};

/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        stack<int> backup;
        ListNode *p = head;
        while(p) {
            backup.push(p->val);
            p=p->next;
        }
        vector<int> result;
        while(!backup.empty()) {
            result.push_back(backup.top());
            backup.pop();
        }
        return result;
    }
};