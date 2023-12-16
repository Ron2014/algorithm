#include "../test.h"

#define N_STATE 7

class Solution {
    const char *arr = "+-ne-+n";
    const int turn[N_STATE+1][N_STATE+1] = {
       //+  -  n  e  +  -  n  END
        {1, 1, 1, 0, 0, 0, 0, 0,},  // start
        {0, 0, 1, 0, 0, 0, 0, 0,},  // +
        {0, 0, 1, 0, 0, 0, 0, 0,},  // -
        {0, 0, 1, 1, 0, 0, 0, 1,},  // n        -- VALID END
        {0, 0, 0, 0, 1, 1, 1, 0,},  // e
        {0, 0, 0, 0, 0, 0, 1, 0,},  // +
        {0, 0, 0, 0, 0, 0, 1, 0,},  // -
        {0, 0, 0, 0, 0, 0, 1, 1,},  // n        -- VALID END
    };
    
public:
    long long _GetResult(long long result, bool negative, bool exponent, unsigned int value) {
        if (value==0) return result;

        double tmp = value;
        if (negative) tmp *= -1;
        if (exponent) {
            tmp = pow(10, tmp);
            tmp *= result;
        }
        return (long long)tmp;

    }
    void _StrToInt(const char *str, long long &result, int state, bool negative, bool exponent, unsigned int state_value) {
        if (!str || !(*str)) {
            result = _GetResult(result, negative, exponent, state_value);
            return;
        }

        char ch = *str;
        int next_state = -1;
        for (int i=0; i<N_STATE; i++) {
            if (turn[state][i]) {
                if (arr[i]=='n' && ch>='0' && ch<='9' ||
                    arr[i]=='e' && (ch=='e' || ch=='E') ||
                    arr[i]==ch) {
                        next_state = i;
                        break;
                    }
            }
        }
        
        if (next_state<0) {
            // ERROR
            result = 0;
            return;
        }

        if (arr[next_state]=='n') {
            state_value = state_value * 10 + (ch-'0');
        } else {
            if (state_value) {
                result = _GetResult(result, negative, exponent, state_value);
                state_value = 0;
                exponent = false;
                negative = false;
            }
            if (arr[next_state]=='-') negative = true;
            if (arr[next_state]=='e') exponent = true;
        }

        _StrToInt(str+1, result, next_state+1, negative, exponent, state_value);    // +1 for start

    }

    long long StrToInt(string str) {
        long long result = 0;
        bool negative = false;
        bool exponent = false;
        _StrToInt(str.c_str(), result, 0, negative, exponent, 0);
        return result;
    }
};

int main() {
    Solution s;
    string text;
    while(cin>>text) {
        cout << s.StrToInt(text) << endl;
    }
}