#include "../test.h"

#include <sstream>
class Solution {
public:
    string ReverseSentence(string str) {
        size_t pos;
        stringstream ss;
        string token = "";
        size_t len = str.length();

        while (len) {
            pos = str.find_last_of(' ');
            // TEST_INFO2(pos:, pos, len);
            if (pos != string::npos) {
                if (pos==len-1) // get space
                    pos = str.find_last_not_of(' ');
                token = str.substr(pos+1, len-pos-1);
                // TEST_INFO(token:, token);
                ss << token;
                str = str.substr(0, pos+1);                    
                len = pos+1;
            } else {
                ss << str;
                len = 0;
            }
        }
        return ss.str();
    }
};

int main() {
    Solution s;
    string text;
    while (getline(cin, text)) {
        if (text[text.length()-1] < 0x20) {
            printf("%d %d %d %d\n", text[text.length()-2], text[text.length()-1], '\n', '\r');
            TEST_HINT(---remove CR);
            text = text.substr(0, text.length()-1); // remove CR
        }
        cout << s.ReverseSentence(text) << endl;
    }
    return 0;
}