#include <iostream>

int main() {
    int a = -1;
    char b = (char)a;

    int bit_len = sizeof(b) * 8;
    char *res = new char[bit_len+1];
    for(int i=0; i<bit_len; i++) {
        if (b & 1<<i) res[bit_len-1-i] = '1';
        else res[bit_len-1-i] = '0';
    }
    res[bit_len] = '\0';
    printf("%s\n", res);
    printf("%x\n", b);

    delete res;
    return 0;
}
