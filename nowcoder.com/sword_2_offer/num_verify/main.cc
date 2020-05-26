#include "../test.h"

#define N_STATE 9

class Solution {
public:
    // char arr[N_STATE+1] = "+-n.ne+-n";  // +1 for '\0'
    const char *arr = "+-n.ne+-n";
    int turn[N_STATE+1][N_STATE+1] = {
       //+  -  n  .  n  e  +  -  n  END
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},    // # start
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},    // +
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},    // -
        {0, 0, 1, 1, 0, 1, 0, 0, 0, 1},    // n        ----- VALID END
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1},    // .        ----- VALID END
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 1},    // n        ----- VALID END
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 0},    // e
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},    // +
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},    // -
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},    // n        ----- VALID END
    };

    bool isNumeric(const char* str)
    {
        int cur = 0, matched;
        for (int i=0; str[i]; i++) {
            matched = -1;
            for (int j=0; j<N_STATE; j++) {
                // cur: current state
                // j: next state
                if (turn[cur][j]) {     // can change
                    if ( arr[j]=='n' && str[i]>='0' && str[i]<='9' ||
                        arr[j]=='e' && (str[i]=='E' || str[i]=='e') ||
                        arr[j]==str[i] ) {
                            matched = j;
                            break;
                        }
                }
            }
            if (matched<0) return false;    // no more state can change: invalid
            cur = matched + 1;        // +1 for start
        }
        // TEST_INFO(state:, cur);
        if (turn[cur][N_STATE]) return true;
        return false;
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