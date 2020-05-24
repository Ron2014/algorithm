#include "../test.h"

#include <set>
#include <map>
#include <algorithm>

class Solution {
public:
    int FirstNotRepeatingChar(string &str) {
        set<char> onces;
        set<char> mores;
        map<char, int> idxes;

        char ch;
        for (auto it=str.begin(); it!=str.end(); it++) {
            ch = *it;
            if (mores.find(ch)!=mores.end()) continue;  // removed
            if (onces.find(ch)!=onces.end()) {          // remove
                onces.erase(ch);
                mores.insert(ch);
            } else onces.insert(ch);
            if (idxes.find(ch)==idxes.end()) {
                idxes[ch] = distance(str.begin(), it);
            }
        }

        if (onces.size()) {
            int min_idx = str.length();
            for (auto it=onces.begin(); it!=onces.end(); it++) {
                ch = *it;
                if (idxes[ch]<min_idx) min_idx=idxes[ch];
            }
            return min_idx;
        } else
            return -1;
    }
};

int main() {
    string text;
    Solution s;
    while (cin>>text)
        cout << s.FirstNotRepeatingChar(text) << endl;
    return 0;
}