#include "../test.h"
class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        int len = A.size();
        /**
         * aRecords[i][j] means:
         * mutiply from A[i] to A[j]
        */
        int **aRecords = new int*[len];
        for (int i=0; i<len; i++)
            aRecords[i] = new int[len];
    
        for (int i=0; i<len; i++) {
            for (int j=i; j<len; j++) {
                if (i==j) {
                    aRecords[i][j] = A[i];
                } else {
                    aRecords[i][j] = aRecords[i][j-1] * A[j];
                }
            }
        }

        int num;
        vector<int> result;
        for (int i=0; i<len; i++) {
            if (i==0) num = aRecords[1][len-1];
            else if (i==len-1) num = aRecords[0][len-2];
            else num = aRecords[0][i-1] * aRecords[i+1][len-1];
            result.push_back(num);
        }

        for (int i=0; i<len; i++)
            delete[] aRecords[i];
        delete[] aRecords;
        
        return result;
    }
};

int main() {
    Solution s;
    int iCount;
    while(cin>>iCount) {
        INPUT_VECTOR(vNums, iCount, int);
        vector<int> result = s.multiply(vNums);
        SHOW_ARRAY(result, result.size()); 
    }
    return 0;
}