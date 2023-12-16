
#include <iostream>
using namespace std;


#define N_COUNT 4
#include <memory.h>

int offset[N_COUNT] = {
    25*25*25 + 25*25 + 25 + 1,
    25*25 + 25 + 1,
    25 + 1,
    1,
};


int main() {
    char input[N_COUNT+1];
    memset(input, 0, sizeof(char)*(N_COUNT+1));

    while (cin>>input) {
        int ret = 0, level=0;
        for (int i=0; i<4; i++) {
            if (input[i]) {
                ret += offset[i] * (input[i]-'a');
                // if (i==0) level = input[i]-'a';
                // else ret += level;
                if (i>0) ret ++;
            } else {
                break;
            }
        }
        cout << ret <<endl;
    }
}