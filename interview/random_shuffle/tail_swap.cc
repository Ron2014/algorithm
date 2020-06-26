#include <random>
#include <vector>
#include <time.h>
#include <iostream>
using namespace std;

// 又名 Fisher-Yates 
void tail_swap(vector<int> &array) {
    srand(time(NULL));
    int len = array.size();
    for (int i=len-1; i>=2; i--) {
        int rad = rand() % i;
        cout << "swap" << i << " " << rad << endl;
        int tmp = array[i];
        array[i] = array[rad];
        array[rad] = tmp;
    }
}