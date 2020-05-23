#include <vector>
using namespace std;

class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        // rotateArray in order( from min to max ) with a spin
        int len = rotateArray.size();
        if (len <= 0) return 0;

        if (rotateArray[0] >= rotateArray[len-1]) {
            // traverse from tail
            for (int i=len-2; i>=0; i--) {
                if (rotateArray[i] > rotateArray[i+1])
                    return rotateArray[i+1];
            }
        }
        return rotateArray[0];
    }
};