#include "../test.h"

#include <map>
class Gift {
public:
    int getValue(vector<int> gifts, int n) {
        map<int, int> records;
        int result = 0;
        for (int i=0; i<n; i++) {
            records[gifts[i]]++;
            if (!result || records[gifts[i]] > records[result]) {
                result = gifts[i];
            }
        }
        int max_count = records[result];
        // TEST_INFO2(stat:, result, max_count);
        if (n%2 && max_count>=n/2 || max_count>n/2)
            return result;
        return 0;
    }
};

int main() {
    Gift s;
    int iNum;
    while(cin>>iNum) {
        INPUT_VECTOR(vNums, iNum, int);
        cout << s.getValue(vNums, iNum) << endl;
    }
    return 0;
}