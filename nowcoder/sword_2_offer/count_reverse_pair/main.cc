#include "../test.h"

struct OrderTreeNode {
    int val;
    OrderTreeNode *left;        // less
    OrderTreeNode *right;       // more
    int lessCount;
    int moreCount;
    OrderTreeNode(int x): val(x), moreCount(0), left(NULL), right(NULL){}
};

#include <algorithm>
#include <memory.h>
class Solution {
    OrderTreeNode *pHead;
public:
    Solution(): pHead(NULL) {}

    void _InsertAndGetMoreCount(OrderTreeNode *curOne, OrderTreeNode *newOne) {
        if (curOne->val < newOne->val) {
            curOne->moreCount++;
            newOne->lessCount = curOne->lessCount + 1;

            if (curOne->right) _InsertAndGetMoreCount(curOne->right, newOne);
            else curOne->right = newOne;

        } else if (curOne->val > newOne->val) {
            newOne->moreCount = curOne->moreCount + 1;
            curOne->lessCount ++;
            if (curOne->left) _InsertAndGetMoreCount(curOne->left, newOne);
            else curOne->left = newOne;
        }

        // 测试用例保证了不会有 val 相等的情况
    }

    /**
     * 利用二叉搜索树快速得到(插入时)比自己大的数有多少
     * 这个值应立即返回记录下来,因为后面的逻辑会修改 moreCount记录
    */
    int _GetMoreCount(int num) {
        OrderTreeNode *node = new OrderTreeNode(num);
        if (pHead) _InsertAndGetMoreCount(pHead, node);
        else pHead = node;
        return node->moreCount;
    }

    int InversePairs(vector<int> data) {
        int len = data.size(), ret = 0;
        unsigned long long sum = 0;
        
        for (int i=0; i<len; i++) {
            // 前面有多少比自己大的数, 就有多少个 new reverse-pair
            sum += _GetMoreCount(data[i]);
        }

        SHOW_TREE((TreeNode*)pHead);

/*      WAY 1. N x N 的遍历
        int *aPairs = new int[len];
        memset(aPairs, 0, sizeof(int)*len);

        // aPairs[i] means:
        // the max reverse-pairs for data[i] maked from data[i-j] to data[i-1]
        // we need calculate from tail to head
        
        int last_one, new_one;
        for (int i=0; i<len; i++) {
            for (int j=i-1; j>=0; j--) {
                // head one is data[i];
                // new one is the front one data[j]                
                aPairs[i] += (data[j]>data[i]) ? 1 : 0;
                
                // 我需要很快得知道在前面有多少个数比我大 O(1)
                // 而不是遍历后才知道 O(n)
            }
            sum += aPairs[i];
        }
        delete[] aPairs;
*/

/*      WAY 2. N x N 的遍历. 加了个小范围排序, 但是更加耗时了
        int last_one, new_one;
        for (int i=0; i<len; i++) {
            for (int j=i-1; j>=0; j--) {
                // head one is data[i];
                // new one is the front one data[j]
                if (data[j]>data[i]) aPairs[i] += 1;
                else break;
            }
            if (i>0) sort(data.begin(), data.begin()+i+1);
            sum += aPairs[i];
        }
        delete[] aPairs;
*/

        ret = sum%1000000007;
        return ret;
    }
};

int main() {
    int iCount;
    while (cin>>iCount) {
        Solution s;
        INPUT_VECTOR(vNums, iCount, int);
        cout << s.InversePairs(vNums) << endl;
    }
    return 0;
}