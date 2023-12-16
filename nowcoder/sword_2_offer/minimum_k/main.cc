#include "../test.h"

class Solution {
public:
    void _Swap(vector<int>::iterator i, vector<int>::iterator j) {
        int tmp = *i;
        *i = *j;
        *j = tmp;
    }
    
    void _QuickSort(vector<int>::iterator begin, vector<int>::iterator end) {
        if (end-begin<=1) return;
        int base = *begin;
        auto it0 = begin+1;
        auto it1 = end-1;

        while(true) {
            while (it1>begin && *it1>base) it1--;
            while (it0<it1 && *it0<=base) it0++;
            if (it0>=it1) break;
            _Swap(it0, it1);
            it1--;
            it0++;
        }
        _Swap(begin, it1);

        // for (auto it=begin; it!=end; it++)
        //     cout << *it << " ";
        // cout << endl;

        _QuickSort(begin, it1);
        _QuickSort(it1+1, end);
    }

    vector<int> GetLeastNumbers_Solution(vector<int> &input, int k) {
        _QuickSort(input.begin(), input.end());
        // TEST_SHOW_ARRAY(input, input.size());
        if (k<=input.size()) return vector<int>(input.begin(), input.begin()+k);
        else return vector<int>();
    }
};

int main() {
    int n;
    Solution s;
    while (cin>>n) {
        INPUT_ARRAY(aNums, n, int);
        vector<int> vNums(aNums, aNums+n);
        cin>>n;
        vector<int> result = s.GetLeastNumbers_Solution(vNums, n);
        TEST_SHOW_ARRAY(result, result.size());
    }
    return 0;
}