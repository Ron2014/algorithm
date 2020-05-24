#include "../test.h"

#include <math.h>
class Solution {
public:
    int Sum_Solution(int n) {
        int ans = n;
        // return ((int)pow(n, 2) + n)>>1;
        ans && (n + Sum_Solution(n-1));
        return ans;
    }
};

int main() {
    int n;
    Solution s;
    while (cin>>n) {
        cout << s.Sum_Solution(n) << endl;
    }
}