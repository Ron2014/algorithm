#include "../test.h"

#define D_LEFT 0
#define D_RIGHT 1
#define D_UP 3
#define D_DOWN 4

class Solution {
public:
    vector<int> printMatrix(const vector<vector<int> > &matrix) {
        int i, j, direct = D_RIGHT;
        i = j = 0;
        int iRow0=0, iRow1=matrix.size()-1, iCol0=0, iCol1=matrix[0].size()-1;

        vector<int> result;
        while(i>=iRow0 && i<=iRow1 && j>=iCol0 && j<=iCol1) {
            result.push_back(matrix[i][j]);
            switch (direct)
            {
            case D_RIGHT: {
                if (j<iCol1) {
                    j++;
                } else {
                    iRow0++;
                    direct=D_DOWN;
                    i++;
                }
            }
            break;
            case D_DOWN: {
                if (i<iRow1) {
                    i++;
                } else {
                    iCol1--;
                    direct=D_LEFT;
                    j--;
                }
            }
            break;
            case D_LEFT: {
                if (j>iCol0) {
                    j--;
                } else {
                    iRow1--;
                    direct = D_UP;
                    i--;
                }
            }
            break;
            case D_UP: {
                if (i>iRow0) {
                    i--;
                } else {
                    iCol0++;
                    direct = D_RIGHT;
                    j++;
                }
            }
            break;
            default:
                break;
            }
        }
        return result;       
    }
};

int main() {
    int iRow, iCol, iNum;
    Solution s;
    while (cin>>iRow>>iCol) {
        vector<vector<int> > matrix;
        for (int i=0; i<iRow; i++) {
            matrix.push_back({});
            for (int j=0; j<iCol; j++) {
                cin >> iNum;
                matrix[i].push_back(iNum);
            }
        }
        SHOW_ARRAY2(matrix, iRow, iCol);
        SHOW_ARRAY(s.printMatrix(matrix), iRow*iCol);
    }
    return 0;
}