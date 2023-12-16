#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    static bool Find(const int &target, const vector<vector<int> > &array) {
        int row = array.size();
        int col = array[0].size();

        {    
            // from left-bottom
            int i = row-1;
            int j = 0;
            while (j<col && i>=0) {
                if (array[i][j] > target) i--;
                else if(array[i][j] < target) j++;
                else return true;
            }
        }

        {
            // from right-top
            int i = 0;
            int j = col-1;
            while (i<row && j>=0) {
                if (array[i][j] > target) j--;
                else if (array[i][j] < target) i++;
                else return true;
            }
        }
        return false;
    }
};

int iRow, iCol;

int main() {
    vector< vector<int> > array;
    int n;
    while(cin>>iRow>>iCol) {
        array.clear();
        for (int i=0; i<iRow; i++) {
            array.push_back({});
            for (int j=0; j<iCol; j++){
                cin >> n;
                array[i].push_back(n);
            }
        }
        cin >> n;
        if (Solution::Find(n, array))
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
    return 0;
}