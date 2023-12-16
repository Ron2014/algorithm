// #include "../test.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
    int time;
    int level;
};

int _Value(int time, int lv) {
    return time * 200 + lv * 3;
}

bool cmp(Node &a, Node &b) {
    int w0, w1, step;
    w0 = w1 = 0;
    step = 1;
    
    // 等级从小到大
    if (a.level < b.level)
        w1 += step;
    if (a.level > b.level)
        w0 += step;
    step *= 2;

    // 时间从小到大
    if (a.time < b.time)
        w1 += step;
    if (a.time > b.time)
        w0 += step;

    return w0 < w1;
}

/*
bool cmpM(Node &a, Node &b) {
    int w0, w1, step;
    w0 = w1 = 0;
    step = 1;

    // 时间小到大
    if (a.time < b.time)
        w1 += step;
    if (a.time > b.time)
        w0 += step;
    step *= 2;
    
    // 等级从小到大
    if (a.level < b.level)
        w1 += step;
    if (a.level > b.level)
        w0 += step;

    return w0 < w1;
}

// 逻辑出错
int _GetCloseOne(vector<Node> &vMachine, const int &time, const int& lv, int start, int end) {
    // TEST_INFO2(_GetCloseOne:, start, end);
    if (start>end) return -1;
    if (start==end) {
        if (vMachine[start].time < time || vMachine[start].level < lv)
            return -1;
        return start;
    }
    int mid = (start + end) >> 1;
    if (vMachine[mid].level < lv) {
        // on the right
        return _GetCloseOne(vMachine, time, lv, mid+1, end);
    } else {
        // 对于 lv 不满足的情况，可能存在 time 更小的 level更大
        // 如果没有，才往右搜
        if (vMachine[mid].time < time) {
            for (int i=start; i<mid; i++) {
                if (vMachine[i].time >= time && vMachine[i].level >= lv)
                    return i;
            }
            // on the right
            return _GetCloseOne(vMachine, time, lv, mid+1, end);
        } else {
            // on the left
            return _GetCloseOne(vMachine, time, lv, start, mid);
        }
    }
}
*/

/*
// 耗时
int _GetCloseOne(vector<Node> &vMachine, const int &time, const int& lv, int start, int end) {
    for (int i=start; i<=end; i++) {
        if (vMachine[i].time>=time && vMachine[i].level >= lv)
            return i;
    }
    return -1;
}
void _RemoveOne(vector<Node> &vMachine, int del, int &len) {
    Node tmp = vMachine[del];
    for (int i=del; i<len-1; i++) {
        vMachine[i] = vMachine[i+1];
    }
    vMachine[len-1] = tmp;
    len--;
}

*/

int main() {
    int iN, iM;
    while (cin>>iN>>iM) {
        // TEST_HINT(---------);
        vector<Node> vMachine(iN);
        vector<Node> vTask(iM);

        for (int i=0; i<iN; i++) {
            cin >> vMachine[i].time;
            cin >> vMachine[i].level;
        }

        for (int i=0; i<iM; i++) {
            cin >> vTask[i].time;
            cin >> vTask[i].level;
        }
        sort(vMachine.begin(), vMachine.end(), cmp);
        sort(vTask.begin(), vTask.end(), cmp);
        
        // for (int i=0; i<iN; i++) {
        //     TEST_INFO2(machine info:, vMachine[i].time, vMachine[i].level);
        // }
        
        // for (int i=0; i<iM; i++) {
        //     TEST_INFO2(task info:, vTask[i].time, vTask[i].level);
        // }

        unsigned long long maxValue = 0, maxNum = 0;
        int taskTime, taskLv, idleNum = iN, selectIdx;

/*
        for (int i=iM-1; i>=0; i--) {
            taskTime = vTask[i].time;
            taskLv = vTask[i].level;
            // TEST_INFO2(task:, taskTime, taskLv);

            selectIdx = _GetCloseOne(vMachine, taskTime, taskLv, 0, idleNum-1);
            if (selectIdx>=0) {
                // TEST_INFO2(--select:, vMachine[selectIdx].time, vMachine[selectIdx].level);
                maxNum ++;
                maxValue += _Value(taskTime, taskLv);
                _RemoveOne(vMachine, selectIdx, idleNum);
            }
            // else TEST_HINT(--no select);
        }
*/
        vector<int> count_of_level(101, 0);
        for(int i=iM-1, j=iN-1; i>=0; i--) {
            taskTime = vTask[i].time;
            taskLv = vTask[i].level;
            while (j>=0 && vMachine[j].time >= taskTime) {
                // 优先统计机器的time大的, 这样在后续的循环中, 任务的time肯定小于它
                count_of_level[vMachine[j].level]++;
                j--;
            }
            for (int k=taskLv; k<=100; k++) {
                if (count_of_level[k]) {
                    maxNum++;
                    count_of_level[k]--;
                    maxValue += _Value(taskTime, taskLv);
                    break;
                }
            }
        }
        cout << maxNum << " " << maxValue << endl;
    }

    return 0;
}