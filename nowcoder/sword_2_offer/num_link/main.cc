#include "../test.h"

#include <sstream>
#include <set>

class Solution {
public:
    void _Swap(vector<int> &v, const int &i, const int &j) {
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    void _PrintMinNumber(vector<int> &numbers, int len, string &result) {
        if (len == 0) return;
        else if (len==1) {
            stringstream ss;
            for (auto it=numbers.begin(); it!=numbers.end(); it++)
                ss << *it;
            if (result.length()==0) result = ss.str();
            else if (ss.str() < result) result = ss.str();
            return;
        }

        set<int> tried;
        _PrintMinNumber(numbers, len-1, result);
        tried.insert(numbers[len-1]);

        int num;
        for (int i=len-2; i>=0; i--) {
            num = numbers[i];
            if (tried.find(num)==tried.end()) {
                tried.insert(num);
                _Swap(numbers, i, len-1);
                _PrintMinNumber(numbers, len-1, result);
                _Swap(numbers, i, len-1);
            }
        }
    }

    string PrintMinNumber(vector<int> numbers) {
        string result = "";
        _PrintMinNumber(numbers, numbers.size(), result);
        return result;
    }
};

int main() {
    int n, m;
    Solution s;
    while (cin>>n) {
        vector<int> nums;
        while(n--) {
            cin>>m;
            nums.push_back(m);
        }
        cout << s.PrintMinNumber(nums) << endl;
    }
    return 0;
}