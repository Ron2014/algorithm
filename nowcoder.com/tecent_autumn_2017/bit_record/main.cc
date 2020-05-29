#include <iostream>
using namespace std;

#define N_RECORDS 32
#include <memory.h>

int main() {
    unsigned int records[N_RECORDS];
    int taskId0, taskId1;
    while (cin>>taskId0>>taskId1) {
        int bit_count = sizeof(unsigned int);
        memset(records, 0, bit_count*N_RECORDS);

        if (taskId0<1 || taskId0>1024 || taskId1<1 || taskId1>1024)
            cout << -1 << endl;
        else {
            int rIdx0 =  (taskId0-1) / bit_count;
            int cIdx0 =  (taskId0-1) % bit_count;
            records[rIdx0] |= 1<<cIdx0;

            int rIdx1 =  (taskId1-1) / bit_count;
            int cIdx1 =  (taskId1-1) % bit_count;
            int ret = (records[rIdx1]>>cIdx1) & 1;
            cout << ret << endl;
        }
    }
}