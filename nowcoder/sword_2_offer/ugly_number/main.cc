#include "../test.h"

#include <math.h>
class Solution {
public:
    
    int GetUglyNumber_Solution(int index) {
        if (index < 7) return index;
        int *aNums = new int[index];
        aNums[0] = 1;
        int idx2, idx3, idx5;
        idx2 = idx3 = idx5 = 0;
        for (int i=1; i<index; i++) {
            aNums[i] = min(aNums[idx2]*2, min(aNums[idx3]*3, aNums[idx5]*5));
            if (aNums[i]==aNums[idx2]*2) idx2++;
            if (aNums[i]==aNums[idx3]*3) idx3++;
            if (aNums[i]==aNums[idx5]*5) idx5++;
        }
        int ret = aNums[index-1];
        delete[] aNums;
        return ret;
    }
};

int main() {
    int n;
    Solution s;
    while(cin>>n) {
        cout << s.GetUglyNumber_Solution(n) << endl; 
    }
    return 0;
}