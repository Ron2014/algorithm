#include <math.h>
#include <map>

class Solution {
    static std::map<int, int> records;
public:
    int jumpFloorII(int number) {
        // 2^(n-1)
        // return pow(2, number-1);

        if (records.find(number)==records.end()) {
            switch(number) {
                case 0:
                    records[number] = 1;
                    break;
                case 1:
                    records[number] = 1;
                    break;
                default: {
                    records[number] = 1;
                    for (int i=1; i<=number-1; i++)
                        records[number] += jumpFloorII(number-i);
                }   break;
            }
        }
        return records[number];
    }
};
std::map<int, int> Solution::records;