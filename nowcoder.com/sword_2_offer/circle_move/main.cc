#include "../test.h"

#include <sstream>
class Solution {
public:
    string LeftRotateString(string str, int n) {
        int len = str.length();
        if (len==0) return str;
        n = n % len;
        if (n==0) return str;
        int len_left = len - n;
        stringstream ss;
        ss << str.substr(n, len_left);
        ss << str.substr(0, n);
        return ss.str();
    }
};

int main() {
    Solution s;
    string text;
    int num;
    while (cin>>text>>num) {
        cout << s.LeftRotateString(text, num) << endl;
    }
    return 0;
}