#include <iostream>
#include <cstring>
using namespace std;

// #define TEST

int leftTop2RightBottomWays(int &col, int &row) {
    int **aWays = new int*[row+1];
    for (int i=0; i<=row; i++){
        aWays[i] = new int[col+1];
        memset(aWays[i], 0, sizeof(int)*(col+1));
    }

    aWays[row][col] = 1;

    for (int i=row; i>=0; i--) {
        for (int j=col; j>=0; j--) {
            int left = j+1;
            int down = i+1;
            if (left<=col) aWays[i][j] += aWays[i][left];
            if (down<=row) aWays[i][j] += aWays[down][j];
        }
    }

#ifdef TEST
    for (int i=0; i<=row; i++) {
        for (int j=0; j<=col; j++)
            cout << aWays[i][j] << " ";
        cout << endl;
    }
#endif

    int result = aWays[0][0];

    for (int i=0; i<=row; i++)
        delete[] aWays[i];
    delete[] aWays;

    return result;
}

int main() {
    int col, row;
    while (cin >> col >> row) {
        cout << leftTop2RightBottomWays(col, row) << endl;
    }
    return 0;
}