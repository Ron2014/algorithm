#include "../test.h"

#include <memory.h>

class Solution {
public:
    bool match(const char* str, const char* pattern){
        int len_str = strlen(str);
        int len_pat = strlen(pattern);

        bool **aMatched = new bool*[len_pat+1];
        for (int i=0; i<=len_pat; i++) {
            aMatched[i] = new bool[len_str+1];
            memset(aMatched[i], false, sizeof(bool)*(len_str+1));
        }

        // aMatched[i][j]
        // patter[:i] matched str[:j] ???

        aMatched[0][0] = true;
            
        char ch;
        bool matched;
        for (int i=1; i<=len_pat; i++) {
            ch = pattern[i-1];
            matched = false;

            for (int j=0; j<=len_str; j++) {
                switch(ch) {
                    case '.':{
                        aMatched[i][j] = j>0 && aMatched[i-1][j-1];
                    }break;
                    case '*':{
                        aMatched[i][j] = i>=2 && (aMatched[i-2][j] || aMatched[i-1][j] || (j>1 && aMatched[i][j-1] && (pattern[i-2]=='.' || str[j-1]==pattern[i-2])));
                    }break;
                    default: {
                        aMatched[i][j] = j>0 && aMatched[i-1][j-1] && ch==str[j-1];
                    }break;
                }
                if (aMatched[i][j]) matched = true;
            }
            // if (!matched) break;
        }

        // TEST_SHOW_ARRAY2(aMatched, len_pat+1, len_str+1);

        bool ret = aMatched[len_pat][len_str];
        for (int i=0;i<=len_pat; i++)
            delete[] aMatched[i];
        delete[] aMatched;
        return ret;
    }
};

int main() {
    Solution s;
    
    if (s.match("", ".*")) cout << "true" << endl;
    else cout << "false" << endl;

    char str[1024], pattern[1024];
    while (cin>>str>>pattern) {
        if (s.match(str, pattern)) cout << "true" << endl;
        else cout << "false" << endl;
    }

    return 0;
}