#include <iostream>
#include <cstring>
using namespace std;

int iCountOfBasket;
int iCountOfApple;
int **aStoreWays;

/***
5 6
---
7

4 1
---
1
*/

// #define TEST

int main() {
    while (cin>>iCountOfApple>>iCountOfBasket) {
        aStoreWays = new int*[iCountOfApple+1];
        for (int i=0; i<=iCountOfApple; i++) {
            aStoreWays[i] = new int[iCountOfBasket+1];
            memset(aStoreWays[i], 0, sizeof(int)*(iCountOfBasket+1));
        }

        for (int i=1; i<=iCountOfApple; i++) {
            for (int j=1; j<=iCountOfBasket; j++) {
                if (i==1 || j==1) {
                    // 1 apple or 1 basket
                    // only 1 way
                    aStoreWays[i][j] = 1;
                } else {
                    // first parts: aStoreWays[i][j-1]
                    // use less basket to store i:
                    // at least 1 more basket is empty
                    if (j > i) {
                        // basket > apple
                        // each way has empty basket
                        aStoreWays[i][j] = aStoreWays[i][j-1];
                    } else if (j==i) {
                        // basket == apple
                        // only 1 way no empty basket: tile
                        aStoreWays[i][j] = aStoreWays[i][j-1] + 1;
                    }else{
                        // basket < apple
                        // aStoreWays[i-j][j] give the way no empty basket:
                        // extra apple i-j need to store
                        aStoreWays[i][j] = aStoreWays[i][j-1] + aStoreWays[i-j][j];
                    }
                }
            }
        }

#ifdef TEST
        for (int i=0; i<=iCountOfApple; i++) {
            for (int j=0; j<=iCountOfBasket; j++) {
                cout << aStoreWays[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
#endif

        cout << aStoreWays[iCountOfApple][iCountOfBasket] << endl;
        

        delete [] aStoreWays;
    }
    return 0;
}