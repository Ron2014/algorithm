#include <stdio.h>
#include <stdlib.h>


int sumPossible(int sum, int addCount) {
    if (addCount == 1) return 1;
    if (addCount == 2) return sum / 2;

    int ret = 0;
    for (int i=1; i<=sum-addCount+1;i++)
        ret += sumPossible(sum-i, addCount-1);
    return ret;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: proc <num> <num>\n");
        return 0;
    }
    printf("%d\n", sumPossible(atoi(argv[1]), atoi(argv[2])));
    return 0;
}