#include "../test.h"

#ifdef TEST
#define ASSERT(e,msg) \
    if (!(e)) { \
        cout << msg << endl; \
        return false; \
    }
#else
#define ASSERT(e, msg) \
    if (!(e)) { \
        return false; \
    }
#endif \

#include <algorithm>
class Solution {
public:

    bool isInteger(string &text) {

    }

    bool isDecimal(string &text) {

    }

    bool isNumeric(const char* chText)
    {
        string text = chText;
        int len = text.length();

        string str_integer;
        string str_decimal;

        int dot_count = count(text.begin(), text.end(), '.');
        ASSERT(dot_count==1 || dot_count==0, "dot count");

        if (dot_count) {
            int dot_pos = text.find('.');
            str_integer = text.substr(0, dot_pos);
            str_decimal = text.substr(dot_pos, len-dot_pos-1);
        } else {
            str_integer = text;
            str_decimal = "";
        }

        return isInteger(str_integer) && isDecimal(str_decimal);
    }

};

int main() {
    string text;
    while (cin>>text) {
        Solution s;
        if (s.isNumeric(text.c_str())) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}