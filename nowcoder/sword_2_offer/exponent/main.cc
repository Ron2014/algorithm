#include "../test.h"
class Solution {
public:
    double Power(double base, int exponent) {
        double ret = 1.0;
        bool negative = (exponent<0);
        if (negative) exponent=-exponent;
        for(int i=0; i<exponent; i++)
            ret *= base;
        if (negative) return 1.0/ret;
        else return ret;
    }
};

int main() {
    double a;
    int b;
    Solution s;
    while (cin>>a>>b) {
        printf("%.5f\n", s.Power(a, b));
    }
}