#include <iostream>
using namespace std;

int main() {
    unsigned long long n, m;
    while(cin>>n>>m) {
        // int flag = -1;
        // unsigned long long sum = 0;
        // for (int i=0; i<n; i++) {
        //     sum += (i+1) * flag;
        //     if ((i+1)%m==0) flag = -flag;
        // }
        // cout << sum << endl;
        cout << n * m / 2 << endl;
    }
}