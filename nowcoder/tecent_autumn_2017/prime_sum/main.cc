// #include "../test.h"
#include <iostream>
using namespace std;
bool isPrime(int n) {
    if (n==1) return false;
    for (int i=2; i*i<=n; i++)
        if (n%i==0) return false;
    return true;
}

int main() {
    int sum;
    while (cin>>sum) {
        int half = sum/2;
        int ret = 0;
        for (int i=2; i<=half; i++) {
            if (isPrime(i) && isPrime(sum-i)){
                // TEST_INFO2(sum:, i, sum-i);
                ret++;
            }
        }
        cout << ret << endl;
    }
    return 0;
}