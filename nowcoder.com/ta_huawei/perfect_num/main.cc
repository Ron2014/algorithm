#include <iostream>
#include <vector>
using namespace std;

// #define TEST

#ifdef TEST
vector<int> factor;
#endif

bool isPerfectNum(int num) {
    int sum = 0;

#ifdef TEST
    factor.clear();
#endif
    
    for(int i=1; i<=num/2; i++){
        if (num%i==0){
            sum+=i;
#ifdef TEST
            factor.push_back(i);
#endif
        }
    }

#ifdef TEST
    if (num == sum) {
        cout << num << ": ";
        for(auto it=factor.begin(); it!=factor.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
#endif

    return (num == sum);
}

int n;

int main() {
    while (cin >> n) {
        int sum = 0;
        do {
            if (isPerfectNum(n)) sum++;
        } while (--n);
        cout << sum << endl;
    }
    return 0;
}