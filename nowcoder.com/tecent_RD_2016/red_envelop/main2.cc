#include "../test.h"

#include <map>
class Gift {
public:
    void _Swap(vector<int> &gifts, int i, int j) {
        int tmp = gifts[i];
        gifts[i] = gifts[j];
        gifts[j] = tmp;
    }

    void _Delete(vector<int> &gift, int i, int &len) {
        _Swap(gift, i, len-1);
        len--;
    }

    // 两两相消法
    // gift[0] 为候选人, count 记录其出现次数
    // 每次遇到不同的对象与之消除, 次数减1
    // 遇到相同的对象, 次数加1
    // 次数归0时, 更换候选人
    // 0 和 i 比较, 就表示前面 0 -> i-1 (共i个) 单位是相同的
    // 1 2 3 4 5 得到的候选人只是一个可能值
    int getValue(vector<int> gifts, int n) {
        int i=1;
        while (i<n) {
            if (gifts[0]!=gifts[i]) {
                _Delete(gifts, i, n);       // 消除对方
                _Delete(gifts, i-1, n);     // 消除自己相同单位
                i--;
                if (i==0) i++;              // 如果自己全部消除, 那也表示 gifts[0] 候选人已经更换
            } else i++;
        }
        if (i>0) return gifts[0];
        else return 0;
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