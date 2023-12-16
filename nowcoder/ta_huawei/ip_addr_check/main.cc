#include <iostream>
using namespace std;

#define LEN_TOKEN 4
#define MAX_DOT 3
#define MAX_NUM 0xFF

bool isValidIPAddr(const char* chIP, int len) {
    char ch;
    int dot_count = 0;

    char token[LEN_TOKEN];
    char token_len = 0;

    for (int i=0; i<len; i++) {
        ch = chIP[i];

        if (isdigit(ch)) {
            if (token_len>=LEN_TOKEN) return false;
            token[token_len++] = ch;
        } else if(ch!='.') return false;
        
        if(ch=='.' || i==len-1) {
            token[token_len] = '\0';
            token_len = 0;
            int num = atoi(token);
            if (num < 0 || num > MAX_NUM) return false;

            if (dot_count > MAX_DOT) return false;
            dot_count++;
        }
    }

    return true;
}

int main() {
    string text;
    while (cin >> text) {
        int len = text.length();
        const char* chIP = text.c_str();
        if (isValidIPAddr(chIP, len)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}