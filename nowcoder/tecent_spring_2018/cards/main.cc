#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int iNum, iCard;
    while (cin>>iNum) {
        vector<int> vCards;
        for (int i=0; i<iNum; i++) {
            cin>>iCard;
            vCards.push_back(iCard);
        }
        sort(vCards.begin(), vCards.end());
        int len = vCards.size(), sum=0, flag=1;
        for (int i=len-1; i>=0; i--) {
            sum += vCards[i] * flag;
            flag = -flag;
        }
        cout << sum << endl;
    }
}