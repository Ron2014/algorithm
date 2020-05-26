#include "../test.h"

class Solution {
public:
    int InversePairs(vector<int> data) {
        int len = data.size();
        int *aPairs = new int[len+1];
        aPairs[0] = 0;
        aPairs[1] = 0;

        int num, onum;
        unsigned long long sum = 0;

        for (int i=1; i<=len; i++) {
            num = data[i-1];
            aPairs[i] = 0;

            for (int j=i-1; j>=1; j--) {
                onum = data[j-1];
                if (num<onum) {
                    aPairs[i] += 1;     // pair i & j

                    if (aPairs[j] && onum-num==1) {
                        aPairs[i] += aPairs[j];
                        break;
                    }
                }
            }
            sum += aPairs[i];
        }

        // TEST_SHOW_ARRAY(aPairs, len+1);

        delete[] aPairs;
        int ret = sum%1000000007;
        return ret;
    }
};

int main() {
    Solution s;
    int iCount;
    while (cin>>iCount) {
        INPUT_VECTOR(vNums, iCount, int);
        cout << s.InversePairs(vNums) << endl;
    }
    return 0;
}