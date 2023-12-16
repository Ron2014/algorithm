#include "../test.h"

class Solution {
public:
    unsigned long long _Merge(vector<int> &data, int start, int mid, int end) {
        // data[start:mid-1] in order
        // data[mid:end] in order
        int *temp = new int[end-start+1];
        int i=start, j=mid, t=0;
        unsigned long long pairs=0;
        while (i<mid && j<=end) {
            // temp[t++] = (data[i]<data[j]) ? data[i++] : data[j++];
            if (data[i] > data[j]) {
                // data[i:] in order
                // for data[j] - pairs count is mid-i
                pairs += mid-i;
                temp[t++] = data[j++];
            } else {
                temp[t++] = data[i++];
            }
        }
        
        while (i<mid) {
            temp[t++] = data[i++];
        }
        
        while (j<=end) {
            temp[t++] = data[j++];
        }

        for (int k=0; k<t; k++)
            data[start+k] = temp[k];

        delete[] temp;
        return pairs;
    }

    unsigned long long _MergeSort(vector<int> &data, int start, int end) {
        if (start==end) return 0;
        unsigned long long sum = 0;

        int mid = (start + end + 1) >> 1;
        sum += _MergeSort(data, start, mid-1);
        sum += _MergeSort(data, mid, end);
        sum += _Merge(data, start, mid, end);

        return sum;
    }

    int InversePairs(vector<int> data) {
        int len = data.size(), ret = 0;
        unsigned long long sum = 0;
        sum = _MergeSort(data, 0, len-1);
        // TEST_SHOW_ARRAY(data, len);
        ret = sum%1000000007;
        return ret;
    }
};

int main() {
    int iCount;
    while (cin>>iCount) {
        Solution s;
        INPUT_VECTOR(vNums, iCount, int);
        cout << s.InversePairs(vNums) << endl;
    }
    return 0;
}