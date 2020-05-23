#include "../test.h"
#include <set>
#include <map>
#include <vector>
#include <algorithm>

#define ROW 9
#define COL 9
#define ZONE 9
#define NUM 9

int *aBoard[ROW+1];

set<int> left_row[ROW+1];
set<int> left_col[COL+1];
set<int> left_zone[ZONE+1];

int zoneIdx(int i, int j) {
    return ((i-1)/3)*3+(j-1)/3+1;
}

void fillBoard(int i, int j, int num) {
    int onum = aBoard[i][j];
    aBoard[i][j] = num;

    if (num) {
        left_row[i].erase(num);
        left_col[j].erase(num);
        left_zone[zoneIdx(i,j)].erase(num);
    }

    if (onum) {
        left_row[i].insert(onum);
        left_col[j].insert(onum);
        left_zone[zoneIdx(i,j)].insert(onum);
    }
}

int coor2idx(int i, int j) {
    return (i-1)*9+(j-1);
}

void solveBoard() {
    map<int, set<int> > mPossibles;
    vector<int> idx_list;

    for (int i=1; i<=ROW; i++) {
        for (int j=1; j<=COL; j++) {
            if (aBoard[i][j]) continue;
            int idx = coor2idx(i, j);
            idx_list.push_back(idx);
            mPossibles[idx] = {};
            mPossibles[idx].insert(left_zone[zoneIdx(i,j)].begin(), left_zone[zoneIdx(i,j)].end());
            set_intersection(mPossibles[idx].begin(), mPossibles[idx].end(), left_row[i].begin(), left_row[i].end(), mPossibles[idx].begin());
            set_intersection(mPossibles[idx].begin(), mPossibles[idx].end(), left_col[j].begin(), left_col[j].end(), mPossibles[idx].begin());
        }
    }

    sort(idx_list.begin(), idx_list.end(), [](const int &idx0, const int &idx1) -> bool {
        int w0 = 0, w1 = 0;
        int step = 1;
        if (idx0 < idx1) w1+=step;
        else if (idx0 > idx1) w0+=step;
        step *= 2;
        if (mPossibles[idx0].size() < mPossibles[idx1].size()) w1+=step;
        else if(mPossibles[idx0].size() > mPossibles[idx1].size()) w0+=step;
        return w0 < w1;
    });
}

int main() {
    for (int i=0; i<=ROW; i++) {
        aBoard[i] = new int[COL+1];
        memset(aBoard[i], 0, COL+1);
    }

    while (true) {
        for (int i=1; i<=ROW; i++)
            for (int n=1; n<=NUM; n++)
                left_row[i].insert(n);

        for (int i=1; i<=COL; i++)
            for (int n=1; n<=NUM; n++)
                left_col[i].insert(n);

        for (int i=1; i<ZONE; i++)
            for (int n=1; n<=NUM; n++)
                left_zone[i].insert(n);
        
        int num;
        for (int i=1; i<=ROW; i++) {
            for (int j=1; j<=COL; j++) {
                cin >> num;
                fillBoard(i, j, num);
            }
        }

        solveBoard();
    }
    return 0;
}