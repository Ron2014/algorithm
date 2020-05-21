#include <iostream>
using namespace std;

int iArrLen;
int iSubLen;
int *aNumbers;

void swap(int i, int j) {
    int tmp = aNumbers[i];
    aNumbers[i] = aNumbers[j];
    aNumbers[j] = tmp;
}

int main() {
    while(cin >> iArrLen >> iSubLen) {
        aNumbers = new int[iArrLen];
        for (int i=0; i<iArrLen; i++)
            cin >> aNumbers[i];

        for (int i=0; i<iArrLen-1; i++) {
            for (int j=i+1; j<iArrLen; j++) {
                if (aNumbers[i] > aNumbers[j]) swap(i, j);
            }
        }

        for (int i=0; i<iSubLen; i++) {
            cout << aNumbers[i] << " ";
        }
        cout << endl;

        delete aNumbers;
    }
    return 0;
}