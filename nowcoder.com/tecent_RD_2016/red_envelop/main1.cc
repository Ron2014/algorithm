#include "../test.h"

#include <map>
class Gift {
public:
    void _Merge(vector<int> &gifts, int start, int end, map<int, int> &candidate) {
        // TEST_INFO2(MERGE-----------------, start, end);
        if (start==end) {
            if (candidate.find(gifts[start])!=candidate.end())
                candidate[gifts[start]]++;
            return;
        }

        int mid = (start + end + 1) >> 1;
        int *tmp = new int[end-start+1];
        memset(tmp, 0, sizeof(int)*(end-start+1));
        int i=start, j=mid, t=0;

        // TEST_INFO(repeat before merge:, repeat);
        // TEST_INFO(start:,start);
        // TEST_INFO(mid:,mid);
        // TEST_INFO(end:,end);
        while (i<mid && j<=end) {
            if (gifts[i] > gifts[j]) {
                tmp[t++] = gifts[j++];
            } else if (gifts[i] < gifts[j]) {
                tmp[t++] = gifts[i++];
            } else {
                // equal
                candidate[gifts[i]] = candidate[gifts[i]] + 1;
                tmp[t++] = gifts[i++];
            }
        }

        /****
         * 归并排序是深度优先的, 这导致 中止条件 exist? 很难判断
         * 所以要想办法把它变成广度优先
         * 广度优先的归并算法, 你可以看到其流程是 1v1 合并/相消 -> 2v2 -> 4v4 ....
         * 可以借鉴这个思路用迭代法求解
         * 
        // first merge will find repeat
        // TEST_INFO(repeat:, repeat);
        if (mid-start==2 || end-mid==1)
            exist &= candidate.size()>0;
        else if(mid-start==4 || end-mid==3){

        }
        */

        while (i<mid) {
            if(tmp[t]==gifts[i]) candidate[gifts[i]] = candidate[gifts[i]] + 1;
            tmp[t++] = gifts[i++];
        }

        while (j<=end) {
            if(tmp[t]==gifts[j]) candidate[gifts[j]] = candidate[gifts[j]] + 1;
            tmp[t++] = gifts[j++];
        }

        for (int k=0; k<t; k++) {
            gifts[start+k] = tmp[k];
        }
        delete[] tmp;
    }

    // void _MergeSort(vector<int> &gift, int start, int end, int &repeat, bool &exist) {
    //     if (start==end) return;
    //     int mid = (start + end + 1) >> 1;
    //     _MergeSort(gift, start, mid-1, repeat, exist);
    //     _MergeSort(gift, mid, end, repeat, exist);
    //     _Merge(gift, start, mid, end, repeat, exist);
    // }

    // int getValue(vector<int> gifts, int n) {
    //     int repeat = 0;
    //     bool exist = true;
    //     _MergeSort(gifts, 0, n-1, repeat, exist);
    //     // TEST_SHOW_ARRAY(gifts, n);
    //     if (exist) return repeat;
    //     else return 0;
    // }

    int getValue(vector<int> gifts, int n) {
        map<int, int> candidate;
        int step = 2;

        for (int i=0; i<n; i+=step) {
            int start = i;
            int end = min(i+step, n)-1;
            _Merge(gifts, start, end, candidate);
        }
        TEST_SHOW_ARRAY(gifts, n);

        step *= 2;
        for (int i=0; i<n; i+=step) {
            int start = i;
            int end = min(i+step, n)-1;
            _Merge(gifts, start, end, candidate);
        }
        TEST_SHOW_ARRAY(gifts, n);

        TEST_INFO(candidates:, candidate.size());
        if (candidate.size() > (n/4+1))
            return 0;
        for (auto it = candidate.begin(); it!=candidate.end(); it++) {
            int val = it->first;
            int count = it->second + 1;
            TEST_INFO2(node:, val, count);
            if (count>n/2) return val;
        }
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