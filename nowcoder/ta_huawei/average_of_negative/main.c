#include <stdio.h>

int num;
int iCountOfNegative;
int iCountOfPositive;
int iSumOfPositive;

int main() {
    iCountOfNegative = 0;
    iSumOfPositive = 0;
    iCountOfPositive = 0;
    while(scanf("%d", &num) != EOF) {
        if (num < 0)
            iCountOfNegative++;
        else {
            iCountOfPositive++;
            iSumOfPositive += num;
        }
    }
    printf("%d\n%.1f\n", iCountOfNegative, iSumOfPositive * 1.0 / iCountOfPositive);
    return 0;
}