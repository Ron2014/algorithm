#include <iostream>
using namespace std;
#include <sstream>

int main() {
    int iNum;
    while (cin>>iNum) {
        stringstream ss;
        int precision = 6, mid;
        int start = -90;
        int end = 90;

        while (precision--) {
            mid = (start + end) / 2;
            if (iNum<mid) {
                ss << 0;
                end = mid;
            } else {
                ss << 1;
                start = mid;
            }
        }

        cout << ss.str() << endl;
    }
    return 0;
}