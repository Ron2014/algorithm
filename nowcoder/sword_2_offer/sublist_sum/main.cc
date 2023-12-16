#include "../test.h"
class Solution {
public:
    int FindGreatestSumOfSubArray(const vector<int> &array) {
        int len = array.size();
        INIT_ARRAY2_V(aResult, len+1, len+1, int, 0);

        // aResult[i][j] means:
        // sum of sublist[i-j, i]
        // aResult[i][j] = aResult[i-1][j-1] + array[i]

        int max_num = 0;
        if (len) max_num = array[0];
        for (int i=1; i<=len; i++) {
            for (int j=1; j<=i; j++) {
                aResult[i][j] = aResult[i-1][j-1] + array[i-1];
                if (aResult[i][j] > max_num) max_num = aResult[i][j];
            }
        }

        // TEST_SHOW_ARRAY2(aResult, len+1, len+1);
        DELETE_ARRAY2(aResult, len+1);
        return max_num;
    }
};

int main() {
    int n;
    Solution s;
    while(cin>>n) {
        INPUT_VECTOR(vNums, n, int);
        cout << s.FindGreatestSumOfSubArray(vNums) << endl;
    }
    return 0;
}