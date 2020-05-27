#include "../test.h"

int getMaxLenOfPalindromic(const char *str, int len) {

    int **aLens = new int*[len];
    for (int i=0; i<len; i++) {
        aLens[i] = new int[len];
        memset(aLens[i], 0, sizeof(int)*len);
    }

    // aLens[i][j]
    // max len from str[i] to str[j]
    // aLens[i][i] = 1;
    for (int i=len-1; i>=0; i--) {
        char start = str[i];
        aLens[i][i] = 1;
        for (int j=i+1; j<len; j++) {
            char end = str[j];
            if (start==end) aLens[i][j] = aLens[i+1][j-1] + 2;
            else aLens[i][j] = (aLens[i+1][j]>aLens[i][j-1]) ? aLens[i+1][j] : aLens[i][j-1];
        }
    }

    TEST_SHOW_ARRAY2(aLens, len, len);

    int ret = aLens[0][len-1];
    for (int i=0; i<len; i++)
        delete[] aLens[i];
    delete[] aLens;

    return ret;
}

int getDeleteCount(const char *str, int len) {
    return len-getMaxLenOfPalindromic(str, len);
}

int main() {
    string text;
    while (cin>>text) {
        cout << getDeleteCount(text.c_str(), text.length()) << endl;
    }
}