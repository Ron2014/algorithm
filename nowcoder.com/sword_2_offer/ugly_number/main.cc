#include "../test.h"

#include <map>
class Solution {
    static map<int, bool> ugly_backup;
public:
    bool _isUgly(int num) {
        if (ugly_backup.find(num)!=ugly_backup.end())
            return ugly_backup[num];
        
        bool value;
        if (num==1) value = true;
        else if (num%2==0) value = _isUgly(num/2);
        else if (num%3==0) value = _isUgly(num/3);
        else if (num%5==0) value = _isUgly(num/5);
        else value = false;
        ugly_backup[num] = value;
        
        return value;
    }
    
    int GetUglyNumber_Solution(int index) {
    
    }
};

map<int, bool> Solution::ugly_backup;