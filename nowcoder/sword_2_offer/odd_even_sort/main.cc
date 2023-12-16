#include "../test.h"
#include <vector>

class Solution {
public:
    // void _reOrderArray(vector<int> &array, const int &last_odd_idx, int even_count) {
    //     if (even_count==0) return;

    //     // TEST_INFO(even:, even_count);
    //     int new_odd_idx = last_odd_idx-1;
    //     for (int i=last_odd_idx-1; i>=0; i--) {
    //         int tmp = array[i];
    //         array[i] = array[last_odd_idx];
    //         array[last_odd_idx] = tmp;

    //         if (array[last_odd_idx]%2==0) {
    //             break;
    //         }
    //     }
    //     // TEST_SHOW_ARRAY(array, array.size());
    //     _reOrderArray(array, new_odd_idx, even_count-1);
    // }

    // void reOrderArray(vector<int> &array) {
    //     int len = array.size();
    //     int last_odd_idx;
    //     int even_count = 0;
    //     int new_even = 0;
    //     for (int i=0; i<len; i++) {
    //         // TEST_INFO(odd:, array[i]%2);
    //         if (array[i]%2) {
    //             last_odd_idx = i;
    //             even_count += new_even;
    //             new_even = 0;
    //         }
    //         else new_even++;
    //     }
    //     _reOrderArray(array, last_odd_idx, even_count);
    // }

    void reOrderArray(vector<int> &array) {
        int len = array.size();
        vector<int> odds;
        vector<int> evens;

        for (int i=0; i<len; i++) {
            // TEST_INFO(odd:, array[i]%2);
            if (array[i]%2) odds.push_back(array[i]);
            else evens.push_back(array[i]);
        }

        int len_odds = odds.size();
        for (int i=0; i<len_odds; i++)
            array[i] = odds[i];
        for (int i=0; i<evens.size(); i++)
            array[i+len_odds] = odds[i];
    }
};


int main() {
    int len, n;
    vector<int> array;
    Solution s;
    while (cin>>len) {
        array.clear();
        for(int i=0; i<len; i++) {
            cin>>n;
            array.push_back(n);
        }
        s.reOrderArray(array);
        TEST_SHOW_ARRAY(array, len);
    }
    return 0;
}