#include "../test.h"

#include <set>
#include <map>
#include <algorithm>

class Solution
{
private:
    int idx;
    set<char> onces;
    set<char> mores;
    map<char, int> idxes;
public:
    Solution():idx(0){}

    //Insert one char from stringstream
    void Insert(char ch)
    {
        idx++;
        if (mores.find(ch)!=mores.end()) return;  // removed

        if (onces.find(ch)!=onces.end()) {        // remove
            onces.erase(ch);
            mores.insert(ch);
        } else onces.insert(ch);

        if (idxes.find(ch)==idxes.end()) {
            idxes[ch] = idx-1;
        }
    }

    //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        char ch, ret = '#';
        if (onces.size()) {
            int min_idx = idx;
            for (auto it=onces.begin(); it!=onces.end(); it++) {
                ch = *it;
                if (idxes[ch] < min_idx) {
                    min_idx = idxes[ch];
                    ret = ch;
                }
            }
        } 
        return ret;
    }
};

int main() {
    string text;
    while (cin>>text) {
        Solution s;
        for (auto it=text.begin(); it!=text.end(); it++)
            s.Insert(*it);
        cout << s.FirstAppearingOnce() << endl;
    }
    return 0;
}