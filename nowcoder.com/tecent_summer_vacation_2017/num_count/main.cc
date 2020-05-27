#include "../test.h"
#include <iostream>
#include <vector>
#include <map>
#include <limits.h>
#include <algorithm>
// using namespace std;

void getResult(vector<int> &vNums) {
    sort(vNums.begin(), vNums.end());

    unsigned long long max_num = 1;
    unsigned long long min_num = 1;
    int i=0, j=vNums.size()-1;
    while (i<j) {
        if (vNums[i+1]==vNums[i]) min_num++;
        else break;
        i++;
    }
    if (vNums[i]==vNums[j]) {
        max_num = min_num * (min_num - 1) / 2;
    } else {
        while (j>0) {
            if (vNums[j-1]==vNums[j]) max_num++;
            else break;
            j--;
        }
        max_num *= min_num;
    }

    int min_dis = INT_MAX;
    unsigned long long stat_num = 0;
    i=0, j=vNums.size()-1;
    while (i<j) {
        if (vNums[i+1]-vNums[i]<min_dis) {
            min_dis = vNums[i+1]-vNums[i];
            min_num = 1;
        } else if (vNums[i+1]-vNums[i]==min_dis) {
            min_num++;
        } else {
            if (!min_dis) {
                stat_num += (min_num + 1) * min_num / 2;
                min_dis = 0;
            }
        }
        i++;
    }
    if (!min_dis) min_num = stat_num + (min_num + 1) * min_num / 2;
    cout << min_num << " " << max_num << endl;
}

int main() {
    int iNum, iVal;
    while (cin>>iNum) {
        vector<int> vNums;
        for (int i=0; i<iNum; i++) {
            cin >> iVal;
            vNums.push_back(iVal);
        }
        getResult(vNums);
    }
    return 0;
}