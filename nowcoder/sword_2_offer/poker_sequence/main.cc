#include "../test.h"

#include <set>
#include <vector>
#include <algorithm>
class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        if (!numbers.size()) return false;
        sort(numbers.begin(), numbers.end());

        set<int> onces;
        int kings = 0, lacks = 0, num, last_num;
        for (auto it=numbers.begin();it!=numbers.end(); it++) {
            num = *it;
            if (num) {
                if (onces.find(num)!=onces.end()) return false;
                if (onces.size()) {
                    if (num-last_num>1) lacks += num-last_num-1;
                }
                onces.insert(num);
                last_num = num;
            } else kings++;
        }
        return kings >= lacks;
    }
};

int main(){
    Solution s;
    int iNum;
    vector<int> vNums;
    while(true) {
        vNums.clear();
        for (int i=0; i<5; i++) {
            if (!(cin>>iNum)) exit(0);
            vNums.push_back(iNum);
        }
        if (s.IsContinuous(vNums)) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}