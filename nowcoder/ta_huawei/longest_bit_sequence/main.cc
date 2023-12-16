#include <iostream>
using namespace std;

// #define TEST

char num;

int getLongestLenOfBit(char num) {
    int bit_len = sizeof(num) * 8;
#ifdef TEST
    char *res = new char[bit_len+1];
#endif
    int max_len = 0;

    int cur_len = 0;
    for(int i=0; i<bit_len; i++) {
        if (num & 1<<i) {
#ifdef TEST
            res[bit_len-1-i] = '1';
#endif
            cur_len++;
        } else {
#ifdef TEST
            res[bit_len-1-i] = '0';
#endif
            if (cur_len > max_len) max_len = cur_len;
            cur_len = 0;
        }
    }

    if (cur_len > max_len) max_len = cur_len;
    cur_len = 0;

#ifdef TEST
    res[bit_len] = '\0';
    printf("%s\n", res);
#endif
    return max_len;
}

int main() {
    while(scanf("%d", &num) != EOF) {
        cout << getLongestLenOfBit(num) << endl;
    }
    return 0;
}
