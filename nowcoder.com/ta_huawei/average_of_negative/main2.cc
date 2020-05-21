#include <iostream>
using namespace std;

int n;
int num;
int iCountOfNegative;
int iCountOfPositive;
int iSumOfPositive;

int main() {
    while(cin >> n) {
        iCountOfNegative = 0;
        iSumOfPositive = 0;
        iCountOfPositive = 0;
        while(n--){
            cin >> num;
            if (num < 0)
                iCountOfNegative++;
            else if (num > 0) {
                iCountOfPositive++;
                iSumOfPositive += num;
            }
        }
        printf("%d %.1f\n", iCountOfNegative, iSumOfPositive * 1.0 / iCountOfPositive);
    }
    return 0;
}