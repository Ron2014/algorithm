#include "../test.h"

// #include <math.h>
class Solution {
public:
    int Sum_Solution(int n) {
        int ans = n;
        ans && (ans += Sum_Solution(n-1));
        return ans;

        // 1.
        // return ((int)pow(n, 2) + n)>>1;

        // 2.
        // int left = (n-1) && Sum_Solution(n-1);
        // TEST_INFO2(----, n, left);
        // return n + left;
        // // return n && (n + Sum_Solution(n-1));
    }
};

int main() {
    int n;
    Solution s;
    while (cin>>n) {
        cout << s.Sum_Solution(n) << endl;
    }
}