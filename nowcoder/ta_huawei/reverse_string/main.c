#include <stdio.h>

char c;
char line[101];
int top = 0;

int main(int argc, char *argv[]) {
    while(scanf("%c", &c) != EOF) {
        if (c == '\n') {
            int i = top / 2;
            if (top % 2) i++;
            while(i<top) {
                c = line[i];
                line[i] = line[top-1-i];
                line[top-1-i] = c;
                i++;
            }
            line[top] = '\0';
            printf("%s\n", line);
            top = 0;
        } else 
            line[top++] = c;
    }
    return 0;
}