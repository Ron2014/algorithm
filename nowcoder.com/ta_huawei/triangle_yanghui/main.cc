#include <iostream>
#include <cstring>
using namespace std;

// #define TEST

int main() {
    int n;

    while (cin>>n) {
        int countCur;
        int countLast = 0;

        int arrLen = 1 + (n-1) * 2;
        int *aLast = new int[arrLen];
        int *aCur = new int[arrLen];
        memset(aLast, 0, sizeof(int)*arrLen);
        memset(aCur, 0, sizeof(int)*arrLen);
        
        int top, left, right;
        for (int i=0; i<n; i++) {
            countCur = 1 + i*2;

            for (int j=0; j<countCur; j++) {
                // sum of 3 num
                top     = (j-1>=0 && j-1<countLast) ? aLast[j-1] : 0;
                left    = (j-2>=0 && j-2<countLast) ? aLast[j-2] : 0;
                right   = (j>=0 && j<countLast)     ? aLast[j] : 0;
                aCur[j] = top + left + right ;
                if(!aCur[j]) aCur[j] = 1;
#ifdef TEST
                cout << aCur[j] << " ";
#endif
            }

            countLast = countCur;
            int *tmp = aLast;
            aLast = aCur;
            aCur = tmp;
#ifdef TEST
            cout << endl;
#endif
        }
        
#ifdef TEST
        cout << "result:" << endl;
        for (int i=0; i<arrLen; i++)
            cout << aLast[i] << " ";
        cout << endl;

        for (int i=0; i<arrLen; i++)
            cout << aCur[i] << " ";
        cout << endl;
#endif

        for(int i=0; i<=arrLen; i++)
            if (aLast[i]%2==0) {
                cout << i+1 << endl;
                break;
            }
            
        delete[] aLast;
        delete[] aCur;
    }
    return 0;
}