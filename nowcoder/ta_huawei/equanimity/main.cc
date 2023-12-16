#include <iostream>
using namespace std;

int iCount;
int iTopIdx;

int *aHeights;
int *aRoutes;
int *aMaxLens;

/*
30
186 13 322 264 328 110 120 73 20 35 240 97 150 221 284 324 46 219 239 284 128 251 298 319 304 36 144 236 163 122
---
10
*/

// #define TEST
// #define GET_TOP

int main() {
    while (cin >> iCount) {
        // all index from 1

        iTopIdx = 0;
        aHeights = new int[iCount+1];
        aMaxLens = new int[iCount+1];
        aRoutes = new int[iCount+1];

        for (int i=1; i<=iCount; i++) {
            cin >> aHeights[i];
#ifdef GET_TOP
            if (!iTopIdx) iTopIdx = i;
            else if (aHeights[i] >= aHeights[iTopIdx]) iTopIdx = i;
#endif
        }

#ifdef GET_TOP
        int startIdx = iTopIdx;
        int maxLen = 1;

        // left side
        while(startIdx) {
            if (aHeights[startIdx] == aHeights[iTopIdx]) {
                aMaxLens[startIdx] = 1;
                aRoutes[startIdx] = 0;

            } else {
                int nextIdx = -1;
                for (int i=startIdx+1; i<=iTopIdx; i++) {
                    if (aHeights[i] > aHeights[startIdx]) {
                        if (aMaxLens[i] + 1 > aMaxLens[startIdx]) {
                            aMaxLens[startIdx] = aMaxLens[i] + 1;
                            nextIdx = i;
                        }
                    }
                }
                aRoutes[startIdx] = nextIdx;
            }
            if (maxLen < aMaxLens[startIdx]) maxLen = aMaxLens[startIdx];
            startIdx--;
        }

        // right side
        startIdx = iTopIdx + 1;
        while(startIdx<=iCount) {
            if (aHeights[startIdx] == aHeights[iTopIdx]) {
                aMaxLens[startIdx] = 1;
                aRoutes[startIdx] = 0;

            } else {
                int nextIdx = -1;
                for (int i=startIdx-1; i>=iTopIdx; i--) {
                    if (aHeights[i] > aHeights[startIdx]) {
                        if (aMaxLens[i] + 1 > aMaxLens[startIdx]) {
                            aMaxLens[startIdx] = aMaxLens[i] + 1;
                            nextIdx = i;
                        }
                    }
                }
                aRoutes[startIdx] = nextIdx;
            }
            if (maxLen < aMaxLens[startIdx]) maxLen = aMaxLens[startIdx];
            startIdx++;
        }
#else
        int startIdx = iCount;
        int maxLen = 1;

        while(startIdx) {
            int nextIdx = 0;
            aMaxLens[startIdx] = 1;
            for (int i=startIdx+1; i<=iCount; i++) {
                if (aHeights[i] > aHeights[startIdx]) {
                    if (aMaxLens[i] + 1 > aMaxLens[startIdx]) {
                        aMaxLens[startIdx] = aMaxLens[i] + 1;
                        nextIdx = i;
                    }
                }
            }
            aRoutes[startIdx] = nextIdx;
            if (maxLen < aMaxLens[startIdx]) maxLen = aMaxLens[startIdx];
            startIdx--;
        }
#endif

#ifdef TEST
        cout << "top:" << iTopIdx << endl;
        
        for (int i=1; i<=iCount; i++) {
            cout << aHeights[i] << " ";
        }
        cout << endl;

        for (int i=1; i<=iCount; i++) {
            cout << aRoutes[i] << " ";
        }
        cout << endl;

        for (int i=1; i<=iCount; i++) {
            cout << aMaxLens[i] << " ";
        }
        cout << endl;
#endif
        cout << maxLen << endl;

        delete [] aHeights;
        delete [] aRoutes;
        delete [] aMaxLens;
    }
    return 0;
}