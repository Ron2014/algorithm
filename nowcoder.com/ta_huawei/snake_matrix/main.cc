#include <stdio.h>
#include <cstring>

int **aMatrix;

int main(int argc, char *argv[]) {
    int iCount;
    while(scanf("%d", &iCount) != EOF) {
        aMatrix = new int*[iCount];
        for (int i=0; i<iCount; i++){
            aMatrix[i] = new int[iCount];
            memset(aMatrix[i], 0, sizeof(int)*iCount);
        }

        int i=0, j=0, num=0, head_i=0;
        while(i<iCount && j<iCount) {
            num++;
            aMatrix[i][j] = num;

            i--;
            j++;

            if (i < 0) {
                head_i ++;
                i = head_i;
                j = 0;
            }
        }

        for (int i=0; i<iCount; i++) {
            for (int j=0; j<iCount-i; j++)
                printf("%d ", aMatrix[i][j]);
            printf("\n");
        }

        for (int i=0; i<iCount; i++)
            delete aMatrix[i];
        delete aMatrix;
    }
    return 0;
}