#include <stdio.h>

#define BEGIN 2
#define STEP 3

int getValueAt(int n) {
    return BEGIN + n * STEP;
}

int main() {
    int frontN;
    while(scanf("%d", &frontN) != EOF) {
        int sum = 0;
        // while(frontN--) sum += getValueAt(frontN);

        int first = getValueAt(0);
        int last = getValueAt(frontN-1);
        int total = first + last;
        int midIdx = frontN / 2;

        sum += midIdx * total;
        if (frontN%2) sum += total / 2;

        printf("%d\n", sum);
    }
    return 0;
}