#include <stdio.h>
#include <string.h>

#define OUTPUT_SIZE 8

int count;
int len, count_words, idx, i, j;
char input[100];

int main(int argc, char *argv[]) {
    while(scanf("%d", &count) != EOF) {
        while(count--) {
            scanf("%s", input);
            len = (int)strlen(input);
            count_words = len % OUTPUT_SIZE ? (len / OUTPUT_SIZE + 1) : (len / OUTPUT_SIZE);
            for (i = 0; i < count_words; i++ ) {
                for (j = 0; j < OUTPUT_SIZE; j++) {
                    idx = i * OUTPUT_SIZE + j;
                    if (idx < len) putchar(input[idx]);
                    else putchar('0');
                }
                putchar('\n');
            }
        }
    }
    return 0;
}
