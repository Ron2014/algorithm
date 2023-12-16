#include "../test.h"

#include <vector>
#include <algorithm>
class Solution {
    vector<int> vNums;
public:
    void Insert(int num)
    {
        vNums.push_back(num);
    }

    double GetMedian()
    { 
        int len = vNums.size();
        if (!len) return 0;
        if (len==1) return vNums[0];

        sort(vNums.begin(), vNums.end());
        double ret = vNums[len/2];
        if (len%2) return ret;

        return (ret+vNums[len/2-1])*0.5;
    }

};

int main() {
    int iCount, iNum;
    while (cin>>iCount) {
        Solution s;
        while(iCount--) {
            cin >> iNum;
            s.Insert(iNum);
        }
        cout << s.GetMedian() << endl;
    }
    return 0;
}