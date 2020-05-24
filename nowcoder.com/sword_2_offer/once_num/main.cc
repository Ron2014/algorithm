#include "../test.h"

#include <set>
class Solution {
public:
    void FindNumsAppearOnce(vector<int> data, int *num1, int *num2) {
        int num;
        set<int> onces;
        set<int> repeats;
        for (auto it=data.begin(); it!=data.end(); it++) {
            num = *it;
            if (repeats.find(num)!=repeats.end()) continue;
            if (onces.find(num)!=onces.end()) { // remove
                onces.erase(num);
                repeats.insert(num);
            } else onces.insert(num);
        }
        
        int *aNums[2];
        aNums[0] = num1;
        aNums[1] = num2;
        int top = 0;
        for (auto it=onces.begin(); it!=onces.end(); it++) {
            *(aNums[top++]) = *it;
        }
    }
};

int main() {

    return 0;
}