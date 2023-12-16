#include <stdio.h>
#include <cstring>
#include <stack>

int iN, iM;
int **aMaze;
int **aMark;
bool foundRoute;

int coordinate2Idx(int row, int col) {
    return row * iM + col;
}

int isMarked(int row, int col) {
    return aMark[row][col];
}

int isBlocked(int row, int col) {
    if (row < 0) return 1;
    if (row >= iN) return 1;
    if (col < 0) return 1;
    if (col >= iM) return 1;
    return aMaze[row][col];
}

void getShortestRoute(int srow, int scol, int trow, int tcol, int fromIdx) {
    aMark[srow][scol] = fromIdx;

    if (srow==trow && scol==tcol) {
        foundRoute = true;
        return; // found
    }

    int curIdx = coordinate2Idx(srow, scol);

    // right
    if (!isBlocked(srow, scol+1) && !isMarked(srow, scol+1)) {
        getShortestRoute(srow, scol+1, trow, tcol, curIdx);
        if (foundRoute) return;
    }

    // down
    if (!isBlocked(srow+1, scol) && !isMarked(srow+1, scol)) {
        getShortestRoute(srow+1, scol, trow, tcol, curIdx);
        if (foundRoute) return;
    }

    // left
    if (!isBlocked(srow, scol-1) && !isMarked(srow, scol-1)) {
        getShortestRoute(srow, scol-1, trow, tcol, curIdx);
        if (foundRoute) return;
    }

    // up
    if (!isBlocked(srow-1, scol) && !isMarked(srow-1, scol)) {
        getShortestRoute(srow-1, scol, trow, tcol, curIdx);
        if (foundRoute) return;
    }

}

int main(int argc, char *argv[]) {
    while(scanf("%d %d", &iN, &iM) != EOF) {
        foundRoute = false;
        aMaze = new int*[iN];
        aMark = new int*[iN];

        for (int i=0; i<iN; i++) {
            aMaze[i] = new int[iM];
            aMark[i] = new int[iM];

            for (int j=0; j<iM; j++)
                scanf("%d", &aMaze[i][j]);
            memset(aMark[i], 0, sizeof(int)*iM);
        }

        getShortestRoute(0, 0, iN-1, iM-1, 0);

        std::stack<int> route;
        route.push(coordinate2Idx(iN-1, iM-1));

        int fromIdx = aMark[iN-1][iM-1];
        while (fromIdx) {
            route.push(fromIdx);
            fromIdx = aMark[fromIdx/iM][fromIdx%iM];
        }
        route.push(0);

        while(!route.empty()) {
            fromIdx = route.top();
            printf("(%d,%d)\n", fromIdx/iM, fromIdx%iM);
            route.pop();
        }

        for (int i=0; i<iN; i++)
            delete aMaze[i];
        delete aMaze;
        for (int i=0; i<iN; i++)
            delete aMark[i];
        delete aMark;
    }
    return 0;
}