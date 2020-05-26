#include "../test.h"

#include <map>
class Solution {
    static map<int, int> records;
public:
    int _NumberOf1_Solution(int num) {
        int ret = (num%10==1) ? 1 : 0;
        if (num < 10) return ret;
        int left = num/10;
        if (records.find(left)!=records.end())
            ret += records[left];
        else {
            ret += _NumberOf1_Solution(left);
            records[num] = ret;
        }
        return ret;
    }

    int NumberOf1Between1AndN_Solution(int n)
    {
        int ret = 0;
        for (int i=1; i<=n; i++) {
            ret += _NumberOf1_Solution(i);
        }
        return ret;
    }
};
map<int, int> Solution::records;

int main() {
    Solution s;
    int n;
    while (cin>>n) {
        // TEST_HINT(--------);
        cout << s.NumberOf1Between1AndN_Solution(n) << endl;
    }
    return 0;
}