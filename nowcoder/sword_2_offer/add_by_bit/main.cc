#include "../test.h"

class Solution {
public:
    int Add(int num0, int num1)
    {
        int bit_count = sizeof(int) * 8;
        int sum, bit0, bit1, bitc; // bitc is carry
        sum = bit0 = bit1 = bitc = 0;

        for (int i=0; i<bit_count; i++) {
            bit0 = (1<<i)&num0 ? 1 : 0;
            bit1 = (1<<i)&num1 ? 1 : 0;

            // TEST_INFO2(bits:, bit0, bit1);
            // TEST_INFO(bitc:, bitc);

            if(bit0 & bit1) {
                sum |= bitc<<i;
                bitc = 1;
            } else {
                if ((bit0|bit1) & bitc) {
                    bitc = 1;
                } else {
                    sum |= (bit0|bit1|bitc)<<i;
                    bitc = 0;
                }
            }
        }

        return sum;
    }
};

int main() {
    Solution s;
    int num0, num1;
    while (cin>>num0>>num1) {
        cout << s.Add(num0, num1) << endl;
    }
    return 0;
}