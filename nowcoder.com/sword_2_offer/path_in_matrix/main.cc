#include "../test.h"

#include <set>
class Solution {
public:
    bool _hasPath(char** boards, int rows, int cols, const char* str, int starti, int startj) {
        if (!str || !(*str)) return true;
        if (starti<0 || starti>=rows || startj<0 || startj>=cols) return false;

        char ch = *str;
        if (ch!=boards[starti][startj]) return false;

        boards[starti][startj] = 0;

        bool ret;
        // left
        ret = _hasPath(boards, rows, cols, str+1, starti, startj-1);
        if (ret) {
            boards[starti][startj] = ch;
            return true;
        }
        // right
        ret = _hasPath(boards, rows, cols, str+1, starti, startj+1);
        if (ret) {
            boards[starti][startj] = ch;
            return true;
        }
        // up
        ret = _hasPath(boards, rows, cols, str+1, starti-1, startj);
        if (ret) {
            boards[starti][startj] = ch;
            return true;
        }
        // down
        ret = _hasPath(boards, rows, cols, str+1, starti+1, startj);
        if (ret) {
            boards[starti][startj] = ch;
            return true;
        }

        boards[starti][startj] = ch;
        return false;
    }

    bool hasPath(const char* matrix, int rows, int cols, const char* str)
    {
        if(!matrix || !str || !(*str)) return false;

        char first = *str;
        set<int> starts;

        char **boards = new char*[rows];
        for (int i=0; i<rows; i++) {
            boards[i] = new char[cols];
            for (int j=0; j<cols; j++) {
                boards[i][j] = matrix[i*cols+j];
                if (first==matrix[i*cols+j]) starts.insert(i*cols+j);
            }
        }

        bool ret = false;
        int starti, startj;

        for (auto it=starts.begin(); it!=starts.end(); it++) {
            starti = (*it) / cols;
            startj = (*it) % cols;
            ret = _hasPath(boards, rows, cols, str, starti, startj);
            if (ret) break;
        }

        for (int i=0; i<rows; i++)
            delete[] boards[i];
        delete[] boards;

        return ret;
    }

};

int main() {
    Solution s;
    string text;
    string path;
    int rows, cols;
    while (cin>>rows>>cols) {
        cin>>text>>path;
        if (s.hasPath(text.c_str(), rows, cols, path.c_str())) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}
