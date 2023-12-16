#include "../test.h"

#include <set>
#include <algorithm>
class Solution {
public:
    void _Swap(char *chArr, const int &i, const int &j) {
        char tmp = chArr[i];
        chArr[i] = chArr[j];
        chArr[j] = tmp;
    }

    void _Permutation(char *chArr, int len, vector<string> &all_records) {
        if (len==0) {
            return;
        } else if (len==1) {
            all_records.push_back(chArr);
            return;
        }

        set<char> tried;
        char ch;
        _Permutation(chArr, len-1, all_records);
        tried.insert(chArr[len-1]);

        for (int i=len-2; i>=0; i--) {
            ch = chArr[i];
            if (tried.find(ch)==tried.end()) {
                tried.insert(ch);
                _Swap(chArr, i, len-1);
                _Permutation(chArr, len-1, all_records);
                _Swap(chArr, i, len-1);
            }
        }
    }

    vector<string> Permutation(string str) {
        vector<string> result;
        int len = str.length();
        char *chArr = new char[len];
        strcpy(chArr, str.c_str());
        _Permutation(chArr, len, result);
        sort(result.begin(), result.end());
        return result;
    }
};

int main() {
    string text;
    Solution s;

    vector<string> result = s.Permutation("");    
    TEST_HINT(--------------)
    TEST_INFO(input:, text)
    for (auto it=result.begin(); it!=result.end(); it++)
        cout << *it << endl;

    while (cin>>text) {
        result = s.Permutation(text);
        
        TEST_HINT(--------------)
        TEST_INFO(input:, text)
        for (auto it=result.begin(); it!=result.end(); it++)
            cout << *it << endl;
    }
    return 0;
}