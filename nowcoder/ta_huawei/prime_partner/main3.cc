#include "../test.h"

int aNumbersOdd[101];
int aNumbersEven[101];

int iCount;
int iCountOdd, iCountEven;

bool isPrime(int num) {
    for (int i=2; i < num/2; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

bool isPrimePartner(int a, int b) {
    return isPrime(a + b);
}

void swap(int *aArr, int i, int j) {
    int tmp = aArr[i];
    aArr[i] = aArr[j];
    aArr[j] = tmp;
}

void getMaxMatch(int *aShortNum, int sLen, int *aLongNum, int lLen, int totalLen) {
    bool hasMatched = false;
    for (int i=1; i<=sLen; i++) {
        for (int j=1; j<=lLen; j++) {
            if (isPrimePartner(aShortNum[i], aLongNum[j])) {
                swap(aShortNum, i, sLen);
                swap(aLongNum, j, lLen);

                getMaxMatch(aShortNum, sLen-1, aLongNum, lLen-1, totalLen);

                swap(aShortNum, i, sLen);
                swap(aLongNum, j, lLen);

                hasMatched = true;
            }
        }
    }
    if (!hasMatched) cout << totalLen-sLen << endl;
}

int main(int argc, char *argv[]) {
    while (scanf("%d", &iCount) != EOF) {
        iCountOdd = 0;
        iCountEven = 0;

        int n;
        for (int i=1; i<=iCount; i++) {
            scanf("%d", &n);
            if (n%2) aNumbersOdd[++iCountOdd] = n;
            else aNumbersEven[++iCountEven] = n;
        }
    }

    if (iCountOdd < iCountEven) getMaxMatch(aNumbersOdd, iCountOdd, aNumbersEven, iCountEven, iCountOdd);
    else getMaxMatch(aNumbersEven, iCountEven, aNumbersOdd, iCountOdd, iCountEven);
}