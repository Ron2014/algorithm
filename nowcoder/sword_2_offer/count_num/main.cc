#include "../test.h"
class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int count = 0;
        for (auto it=data.begin(); it!=data.end(); it++) {
            if (*it==k) count++;
            else if (*it>k) break;
        }
        return count;
    }
};

int main () {
    int n, m;
    Solution s;
    while (cin>>n>>m) {
        INPUT_VECTOR(vNums, n, int);
        cout << s.GetNumberOfK(vNums, m) << endl;
    }
    return 0;
}