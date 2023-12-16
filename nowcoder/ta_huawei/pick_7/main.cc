#include <iostream>
using namespace std;

#define TARGET_DIGIT 7

int frontN;

bool isMatched(int num) {
    if (num % TARGET_DIGIT == 0) return true;

    while (num) {
        int digit = num % 10;
        if (TARGET_DIGIT == digit)
            return true;
        num = num / 10;
    }
    return false;
}

int main() {
    while (cin >> frontN) {
        int sum = 0;
        for (int i=1; i<=frontN; i++)
            if (isMatched(i)) sum++;
        cout << sum << endl;
    }
    return 0;
}