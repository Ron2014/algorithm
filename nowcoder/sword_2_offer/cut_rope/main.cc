#include "../test.h"

class Solution {
public:
    int cutRope(int number) {
        /**
         * aRecords[i][j] means
         * max value for length i & segments j
        */
        int **aRecords = new int*[number+1];
        for (int i=0; i<=number; i++) {
            aRecords[i] = new int[number+1];
            aRecords[i][0] = 0;
        }
        aRecords[0][0] = 0;

        int value, max_value = 1;
        for (int i=1; i<=number; i++) {
            for (int j=1; j<=i; j++) {
                if (i==j) {
                    aRecords[i][j] = 1;
                    continue;
                } else if (j==1) {
                    aRecords[i][j] = i;
                    continue;
                }
                
                aRecords[i][j] = aRecords[i][0];
                // aRecords[i][j] =
                // max of 
                // aRecords[i-1][j-1] * 1
                // aRecords[i-2][j-1] * 2
                // ...
                for (int k=1; i-k>=j-1; k++) {
                    value = aRecords[i-k][j-1]*k;
                    if (value > aRecords[i][j])
                        aRecords[i][j] = value;
                }

                if (aRecords[i][j] > max_value)
                    max_value = aRecords[i][j];
            }
        }

        // TEST_SHOW_ARRAY2(aRecords, number+1, number+1);

        for (int i=0; i<=number; i++)
            delete[] aRecords[i];
        delete[] aRecords;

        return max_value;
    }
};

int main() {
    Solution s;
    int iLen;
    while (cin>>iLen) {
        cout << s.cutRope(iLen) << endl;
    }
    return 0;
}