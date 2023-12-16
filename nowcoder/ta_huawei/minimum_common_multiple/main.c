#include <stdio.h>

int maximum_commom_divisor(int a, int b) {
    int remainder = a % b;
    if (remainder == 0)
        return b;
    return maximum_commom_divisor(b, remainder);
}

int main(int argc, char *argv[]) {
    int a, b;
    while(scanf("%d %d", &a, &b) != EOF) {
        if (a == b) printf("%d\n", a);
        if (a < b) {
            int tmp = a;
            a = b;
            b = tmp;
        }

        int mcd = maximum_commom_divisor(a, b);
        printf("%d\n", (a/mcd) * (b/mcd) * mcd);
    }
    return 0;
}