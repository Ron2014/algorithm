#include "../test.h"

#include <set>
class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        if(length<=0 || numbers==NULL)
            return false;

        set<int> onces;
        set<int> mores;
        int more_count = 0;
        int num;
        
        for (int i=0; i<length; i++) {
            num = numbers[i];
            if (mores.find(num)!=mores.end()) continue;     // removed
            if (onces.find(num)!=onces.end()) {             // remove
                // duplication[more_count++] = num;
                if (0==more_count++) *duplication = num;
                onces.erase(num);
                mores.insert(num);
                return true;

            } else onces.insert(num);
        }

        return more_count>0;
    }
};

int main() {
    int iCount;
    Solution s;
    while (cin>>iCount) {
        INPUT_ARRAY(aNums, iCount, int);
        // INIT_ARRAY_V(aRepeats, iCount, int, -1);
        // s.duplicate(aNums, iCount, aRepeats);
        // SHOW_ARRAY(aRepeats, iCount);
        int repeat;
        if (s.duplicate(aNums, iCount, &repeat)) cout << "true" << endl;
        else cout << "false" << endl;
        cout << repeat << endl;
    }
    return 0;
}