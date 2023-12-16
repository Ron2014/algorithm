#include "../test.h"

class Solution {
public:
    int NumberOf1(int n) {
        int bit_count = sizeof(n) * 8;
        int sum = 0;
        for (int i=0; i<bit_count; i++)
        if ((1<<i)&n) sum += 1;
        return sum;
    }
};

int main() {
    int n;
    Solution s;
    while(cin>>n) {
        cout << s.NumberOf1(n) << endl;
    }
    return 0;
}