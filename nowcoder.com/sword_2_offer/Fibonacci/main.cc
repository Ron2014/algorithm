#include <map>
#include <iostream>

class Solution {
    static std::map<int, int> records;
public:
    int Fibonacci(int n) {
        // recursion & backup
        if (records.find(n)==records.end()) {
            switch(n) {
                case 0:
                    records[n] = 0;
                    break;
                case 1:
                    records[n] = 1;
                    break;
                default:
                    records[n] = Fibonacci(n-2) + Fibonacci(n-1);
                    break;
            }
        }
        return records[n];

        // loop
        std::map<int, int> local_records;
        for (int i=0; i<=n; i++) {
            switch(i) {
                case 0:
                    local_records[i] = 0;
                    break;
                case 1:
                    local_records[i] = 1;
                    break;
                default: 
                    local_records[i] = local_records[i-1] + local_records[i-2];
                    break;
            }
        }
        return local_records[n];
    }
};
std::map<int, int> Solution::records;

int main() {
    int n;
    while (std::cin>>n) {
        std::cout << Solution().Fibonacci(n) << std::endl;
    }
    return 0;
}