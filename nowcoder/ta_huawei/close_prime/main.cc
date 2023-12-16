#include <iostream>
using namespace std;

int num;

bool isPrime(int num) {
    for (int i=2; i*i<=num; i++)
        if (num%i==0) return false;
    return true;
}

int main() {
    while ( cin >> num ) {
        int factor = num / 2;
        while (factor>1 && (!isPrime(factor) || !isPrime(num-factor)))
            factor--;
        cout << factor << endl << num-factor << endl;
    }
    return 0;
}