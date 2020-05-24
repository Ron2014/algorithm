#include "../test.h"

#include <map>
class Solution {
public:
    int MoreThanHalfNum_Solution(const vector<int> &numbers) {
        int len = numbers.size();
        int half = len/2;
        map<int, int> stat;

        for (auto it=numbers.begin(); it!=numbers.end(); it++) {
            stat[*it] = stat[*it] + 1;
            if (stat[*it]>half) return *it;
        }

        return 0;
    }
};

int main() {
    int iCount;
    Solution s;
    while (cin>>iCount) {
        INPUT_ARRAY(aNums, iCount, int);
        vector<int> vNums(aNums, aNums+iCount);
        cout << s.MoreThanHalfNum_Solution(vNums);
    }
    return 0;
}