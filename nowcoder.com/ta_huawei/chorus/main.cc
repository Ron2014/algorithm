#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int iNumOfSinger;

    while(scanf("%d", &iNumOfSinger) != EOF) {
        int *aHeightOfSinger = new int[iNumOfSinger];
        int *aMaxQueueL = new int[iNumOfSinger];
        int *aMaxQueueR = new int[iNumOfSinger];

        for (int i=0; i<iNumOfSinger; i++) cin>>aHeightOfSinger[i];
        
        // 1
        // 1 1 -> 1 2: if aHeightOfSinger[0] < aHeightOfSinger[1]
        for (int i=0; i<iNumOfSinger; i++) {
            // if the most height is singer at i
            // get the length of max queue

            aMaxQueueL[i] = 1; // by default, the max quene has ONLY ONE singer at i

            for (int j=0; j<i; j++) {
                if (aHeightOfSinger[j] < aHeightOfSinger[i] && aMaxQueueL[i] < aMaxQueueL[j] + 1)
                    aMaxQueueL[i] = aMaxQueueL[j] + 1;
            }
        }

        // reverse order
        for (int i=iNumOfSinger-1; i>=0; i--){
            aMaxQueueR[i] = 1;
            for (int j=iNumOfSinger-1; j>i; j--) {
                if (aHeightOfSinger[j] < aHeightOfSinger[i] && aMaxQueueR[i] < aMaxQueueR[j] + 1)
                    aMaxQueueR[i] = aMaxQueueR[j] + 1;
            }
        }

        int iMaxQueue = 0;
        for (int i=0; i<iNumOfSinger; i++) {
            if (aMaxQueueL[i] + aMaxQueueR[i] - 1 > iMaxQueue)
                iMaxQueue = aMaxQueueL[i] + aMaxQueueR[i] - 1;
        }
        printf("%d\n", iNumOfSinger-iMaxQueue);

        delete aMaxQueueR;
        delete aMaxQueueL;
    }
    return 0;
}