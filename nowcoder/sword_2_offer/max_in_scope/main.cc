#include "../test.h"

class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        /**
         * aMaxNums[i][j] means;
         * the max value from num[i] to num[j]
        */
        int len = num.size();
        int **aMaxNums = new int*[len];
        for (int i=0; i<len; i++)
            aMaxNums[i] = new int[len];
        for (int i=0; i<len; i++) {
            for (int j=i; j<len; j++) {
                if (i==j) aMaxNums[i][j] = num[i];
                else aMaxNums[i][j] = aMaxNums[i][j-1]>num[j] ? aMaxNums[i][j-1] : num[j];
            }
        }
        vector<int> result;
        if (size>0) {
            for (int i=0; i<len-size+1; i++) {
                result.push_back(aMaxNums[i][i+size-1]);
            }
        }
        return result;
    }
};

int main() {
    int iCount, iNum;
    Solution s;
    while (cin>>iCount>>iNum) {
        INPUT_VECTOR(vNums, iCount, int);
        vector<int> result = s.maxInWindows(vNums, iNum);
        SHOW_ARRAY(result, result.size());
    }
    return 0;
}