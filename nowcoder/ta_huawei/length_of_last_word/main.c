#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 5000

int main(int argc, char *argv[]) {
    char input[MAX_SIZE];
    if (fgets(input, MAX_SIZE, stdin) == NULL)
        exit(1);

    size_t len = strlen(input) - 1; // remove \n
    int word_len = 0;
    
    while (len-- > 0) {
        if (input[len] == ' ') {
            if (word_len) break;
            continue;
        }
        word_len ++;
    }

    printf("%d\n", word_len);
    return 0;
}
