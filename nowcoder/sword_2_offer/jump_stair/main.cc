#include <iostream>
#include <map>

class Solution {
    static std::map<int, int> records;
public:
    // another Fibonacci
    int jumpFloor(int number) {
        // recursion & backup
        if (records.find(number)==records.end()) {
            switch(number) {
                case 0:
                    records[number] = 1;
                    break;
                case 1:
                    records[number] = 1;
                    break;
                default: {
                    records[number] = jumpFloor(number-2) + jumpFloor(number-1);
                }   break;
            }
        }
        return records[number];
    }
};
std::map<int, int> Solution::records;

int main() {
    int n;
    while (std::cin>>n) {
        std::cout << Solution().jumpFloor(n) << std::endl;
    }
    return 0;
}

