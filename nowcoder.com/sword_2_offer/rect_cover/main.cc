#include "../test.h"
#include <map>

class Solution {
    static std::map<int, int> records;
public:
    // int rectCover(int number) {
    //     if (number<=0) return 0;
    //     int max_horizon = number/2;
    //     int sum = 0, vertical_count;
    //     for (int i=0; i<=max_horizon; i++) {
    //         vertical_count = number - i * 2;
    //         // pick vertical_count from number
    //         int rooms = number-i;
    //         int in = 1;
    //         for (int j=rooms; j>(rooms-vertical_count); j--)
    //             in *= j;
    //         int im = 1;
    //         for (int j=2; j<=vertical_count; j++)
    //             im *= j;
    //         sum += in/im;
    //     }
    //     return sum;
    // }

    // int rectCover(int number) {
    //     int *horizon_ways = new int[number+1];
    //     horizon_ways[0] = 0;
    //     for (int i=1; i<=number; i++) {
    //         horizon_ways[i] = (i%2) ? horizon_ways[i-1] : (horizon_ways[i-1]+1);
    //     }
    //     return 1+horizon_ways[number]; // 1 for no horizon at all
    // }

    // anothre fibonacci
    int rectCover(int number) {
        if (records.find(number)==records.end()) {
            switch(number) {
                case 0:
                    records[number] = 0;
                    break;
                case 1:
                    records[number] = 1;
                    break;
                case 2:
                    records[number] = 2;
                    break;
                default:
                    records[number] = rectCover(number-2) + rectCover(number-1);
                    break;
            }
        }
        return records[number];
    }
};
std::map<int, int> Solution::records;

int main() {
    int n;
    Solution s;
    while (cin>>n) {
        cout << s.rectCover(n) << endl;
    }
}