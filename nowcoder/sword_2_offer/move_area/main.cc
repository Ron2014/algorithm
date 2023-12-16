#include "../test.h"

#define P_UNREACHED 0
#define P_REACHED 1
#define P_WALL 2

#include <memory.h>
class Solution {
public:
    bool _isWall(int i, int j, const int &threshold) {
        int sum = 0;
        while(i) {
            sum += i%10;
            i /= 10;
        }
        while(j) {
            sum += j%10;
            j /= 10;
        }
        return threshold < sum;
    }

    void _movingCount(int **boards, const int &threshold, const int &rows, const int &cols, const int starti, const int startj, int &stat_count) {
        if (starti<0 || starti>=rows || startj<0 || startj>=cols) return;
        if (boards[starti][startj]==P_REACHED) return; // reached
        if (boards[starti][startj]==P_WALL || _isWall(starti, startj, threshold)) {
            boards[starti][startj] = P_WALL;
            return;
        }
        
        boards[starti][startj] = P_REACHED;
        stat_count++;

        // left
        _movingCount(boards, threshold, rows, cols, starti, startj-1, stat_count);
        // right
        _movingCount(boards, threshold, rows, cols, starti, startj+1, stat_count);
        // up
        _movingCount(boards, threshold, rows, cols, starti-1, startj, stat_count);
        // down
        _movingCount(boards, threshold, rows, cols, starti+1, startj, stat_count);
    }

    /**
     * boards[i][j]
     *  0:  init/unreached
     *  1:  reached
     *  2:  wall
    */
    int movingCount(const int &threshold, const int &rows, const int &cols) {
        int **boards = new int*[rows];
        for (int i=0; i<rows; i++) {
            boards[i] = new int[cols];
            memset(boards[i], P_UNREACHED, sizeof(int)*cols);
        }
        
        int ret = 0;
        _movingCount(boards, threshold, rows, cols, 0, 0, ret);

        // TEST_SHOW_ARRAY2(boards, rows, cols);
        // TEST_INFO(result:, ret);

        for (int i=0; i<rows; i++)
            delete[] boards[i];
        delete[] boards;

        return ret;
    }
};

int main() {
    Solution s;
    int threshold, rows, cols;
    while(cin>>threshold>>rows>>cols) {
        cout << s.movingCount(threshold, rows, cols) << endl;
    }
    return 0;
}