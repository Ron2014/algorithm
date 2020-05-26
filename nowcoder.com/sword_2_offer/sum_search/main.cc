#include "../test.h"

#include <map>
#include <set>
class Solution {
public:
    vector<int> FindNumbersWithSum(const vector<int> &array, const int &sum) {
        set<int> travsed;
        map<int, int> oprands;
        int num, left, multiply;

        int min_multiply;
        int min_num;
        for (auto it=array.begin(); it!=array.end(); it++) {
            num = *it;
            // if (num>sum) break;
            
            // repeat num
            if (travsed.find(num)!=travsed.end()) continue;
            travsed.insert(num);

            left = sum - num;
            if (travsed.find(left)==travsed.end()) continue;    // not pair
            if (oprands.find(left)!=oprands.end()) continue;    // calculated

            multiply = num * left;
            if (oprands.size() || multiply < min_multiply) {
                min_multiply = multiply;
                min_num = num;
            }
            oprands[num] = multiply;
        }

        // for (auto it=oprands.begin(); it!=oprands.end(); it++) {
        //     TEST_INFO2(found:, it->first, it->second);
        // }
        
        vector<int> result;
        if (oprands.size()) {
            result.push_back(sum-min_num);
            result.push_back(min_num);
        }
        return result;
    }
};

int main() {
    int iCount, iNum;
    Solution s;
    while (cin>>iCount>>iNum) {
        INPUT_VECTOR(vNums, iCount, int);
        vector<int> result = s.FindNumbersWithSum(vNums, iNum);
        if (result.size()) TEST_INFO2(result:, result[0], result[1]);
        else TEST_HINT(NONE);
    }
    return 0;
}