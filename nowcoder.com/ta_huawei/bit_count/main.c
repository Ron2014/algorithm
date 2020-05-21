#include <stdio.h>

int main(int argc, char *argv[]) {
    int input;
    int bit_count = (int)(sizeof(input) * 8);

    while(scanf("%d", &input) != EOF) {
        int count = 0;
        int i;
        for (i = 0; i < bit_count; i++) {
            if ((1<<i) & input) count++;
        }
        printf("%d\n", count);
    }
    return 0;
}