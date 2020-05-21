#include <iostream>
using namespace std;

int num;

int main() {
    while(cin>>num) {
        int bit_count = int(sizeof(num) * 8);
        int stat_count = 0;
        for (int i=0; i<bit_count; i++) {
            if ((1<<i) & num) stat_count++;
        }
        cout << stat_count << endl;
    }
    return 0;
}