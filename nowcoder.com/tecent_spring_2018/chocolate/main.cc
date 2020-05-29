#include <iostream>
#include <math.h>
using namespace std;

int getHead(int n, int &iDay) {
    int base = n;
    int sum = n;
    iDay = 1;
    n = (n%2) ? n/2+1 : n/2;
    while (n>=2) {
        sum += n;
        iDay++;
        n = (n%2) ? n/2+1 : n/2;
    }
    return sum;
}

int main() {
    // 2^k + (iN-k) <= iM
    int iN, iM;
    while (cin>>iN>>iM) {
        if (iN==1) {
            cout << iM << endl;
        } else {
            int ret;
            for (int i=iM; i>=1; i--) {
                int days;
                int headDayCost = getHead(i, days);
                // cout << headDayCost << " " << days << endl;
                if (headDayCost+iN-days<=iM) {
                    ret = i;
                    break;
                }
            }
            cout << ret << endl;
        }
    }
}