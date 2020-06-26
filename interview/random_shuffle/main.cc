#include <iostream>
#include <vector>
#include "../test.h"
using namespace std;

// typedef void (*shuffle_func)(vector<int> &array) ;
// shuffle_func tail_swap;
void tail_swap(vector<int> &array);
#define shuffle(x) tail_swap(x)

int main(int argc, char *argv[]) {
    int iNum, iN;
    vector<int> inputs;
    while(cin>>iNum) {
        inputs.clear();
        for (int i=0; i<iNum; i++) {
            cin >> iN;
            inputs.push_back(iN);
        }
        shuffle(inputs);
        SHOW_ARRAY(inputs, iNum);
    }
    return 0;
}