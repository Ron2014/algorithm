#include <iostream>
using namespace std;

int frontN;

bool isAutomorph(int num) {
    int square = num * num;
    while (num) {
        int digit = num % 10;
        if (square%10 != digit)
            return false;
        square = square / 10;
        num = num / 10;
    }
    return true;
}

int main() {
    while (cin >> frontN) {
        int sum = 0;
        for (int i=0; i<=frontN; i++)
            if (isAutomorph(i)) sum++;
        cout << sum << endl;
    }
    return 0;
}