#include "../test.h"
/**
 * 1. math expression
 * 
 * (n + (n+m-1)) * m / 2 = sum
 * m : count of list (>=2 && <=sum/2)
 * n : minimum of list (>=1 && <=sum/m)
 * 
 * 2*sum = (2*n+m-1)*m = 2*n*m+m*m-m
 * 
 * 2. dynamic planning
 * records[i][j] :
 * j : count of list
 * i : maximum of the list
 * records[i-1][j-1] + i = records[i][j]
 * 
 * time : sum * sum
 * space : sum * sum
*/

class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int> > result;
        int len = 0;

/* WAY 1.
        int num0 = sum * 2, num1;
        int max_count = sum/2, max_oprand;
        if (max_count<2) max_count = 2;     // 3=1+2

        for (int m=max_count; m>=2; m--) {
            if (num0%m==0) {
                num1 = num0/m;
                max_oprand = sum/m;
                for (int n=1; n<=max_oprand; n++) {
                    if (2*n+m-1==num1) {
                        result.push_back({});
                        for (int i=0; i<m; i++)
                            result[len].push_back(n+i);
                        len++;
                    }
                }
            }
        }
*/

        int max_oprand = sum/2+1;
        int **aSumsOfFrontNums = new int*[max_oprand+1];
        for (int i=0; i<=max_oprand; i++) {
            aSumsOfFrontNums[i] = new int[max_oprand+1];
            if (i==0) memset(aSumsOfFrontNums[i], 0, sizeof(int)*(max_oprand+1));
            else aSumsOfFrontNums[i][0] = 0;
        }

        int val;
        for (int i=1; i<=max_oprand; i++) {
            for (int j=1; j<=i; j++) {
                val = aSumsOfFrontNums[i-1][j-1] + i;
                if (val==sum && j>=2) {
                    // j : count of list
                    // i : maximum of list
                    result.push_back({});
                    for (int k=(i-j+1); k<=i; k++)
                        result[len].push_back(k);
                    len++;
                }
                aSumsOfFrontNums[i][j] = val;
            }
        }

        TEST_SHOW_ARRAY2(aSumsOfFrontNums, max_oprand, max_oprand);

        return result;
    }
};

int main() {
    Solution s;
    int n;
    while (cin>>n) {
        vector<vector<int> > result = s.FindContinuousSequence(n);
        for (int i=0; i<result.size(); i++) {
            for (auto it=result[i].begin(); it!=result[i].end(); it++) {
                cout << *it << " ";
            }
            cout << endl;
        }
    }
    return 0;
}