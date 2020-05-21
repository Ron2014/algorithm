#include <iostream>
#include <map>
using namespace std;

string text;
map<char, int> mTimes;

int main() {
    while(cin >> text) {
        int len = text.length();
        mTimes.clear();

        for (auto it=text.begin(); it<text.end(); it++) {
            char c = *it;
            // printf("%c\n", c);
            if (mTimes.find(c) == mTimes.end()) mTimes[c] = 1;
            else mTimes[c]++;
        }

        int idx = -1;
        for (int i=0; i<len; i++) {
            char c = text[i];
            if (mTimes[c] == 1) {
                idx = i;
                break;
            }
        }
        if (idx<0)
            printf("%d\n", idx);
        else
            printf("%c\n", text[idx]);
    }
    return 0;
}