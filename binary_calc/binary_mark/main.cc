#include <iostream>
#include "bitmark.h"
using namespace std;

/**
 * 初始化 N 个数据
 * 标记 M 个数据, 每个数字在 [0, N-1] 之间
 * 输出标记后的值
*/
int main(int argc, char *argv[]) {
    size_t iN, iM, iMark;
    while (cin>>iN) {
        CBitMark *bm = new CBitMark(iN);
        cin >> iM;
        for (size_t i=0; i<iM; i++) {
            cin >> iMark;
            bm->Mark(iMark);
        }
        bm->Display();
        delete bm;
    }
}