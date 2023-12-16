#include <iostream>
#include <string.h>
using namespace std;

#define OUTPUT_SIZE 8

int main(int argc, char *argv[]) {
    int count = 2, len, count_words, index, i, j;
    char input[100];

    while(count--) {
        cin >> input;
        len = (int)strlen(input);
        count_words = len % OUTPUT_SIZE ? (len / OUTPUT_SIZE + 1) : (len / OUTPUT_SIZE);

        index;
        for (i = 0; i < count_words; i++ ) {
            for (j = 0; j < OUTPUT_SIZE; j++) {
                index = i * OUTPUT_SIZE + j;
                if (index < len) putchar(input[index]);
                else putchar('0');
            }
            putchar('\n');
        }
    }
    return 0;
}
