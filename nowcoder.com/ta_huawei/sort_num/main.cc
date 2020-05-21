#include <iostream>
using namespace std;

int iCountOfNumber;
int *aNumbers;
int reverseOrder;

void swap(int i, int j) {
    int tmp = aNumbers[i];
    aNumbers[i] = aNumbers[j];
    aNumbers[j] = tmp;
}

int main() {
    while(cin>>iCountOfNumber) {
        aNumbers = new int[iCountOfNumber];
        for (int i=0; i<iCountOfNumber; i++) {
            cin >> aNumbers[i];
        }
        cin >> reverseOrder;

        for (int i=0; i<iCountOfNumber-1; i++) {
            for (int j=i+1; j<iCountOfNumber; j++) {
                if (reverseOrder) {
                    if (aNumbers[i] < aNumbers[j]) swap(i, j);
                } else {
                    if (aNumbers[i] > aNumbers[j]) swap(i, j);
                }
            }
        }

        for (int i=0; i<iCountOfNumber; i++) {
            cout << aNumbers[i] << " ";
        }
        cout << endl;

        delete aNumbers;
    }
    return 0;
}