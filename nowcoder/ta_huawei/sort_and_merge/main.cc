#include <iostream>
#include <stdlib.h>
using namespace std;

// #define TEST

#ifdef TEST

#define TEST_SHOW_ARRAY(a,l) \
    for (int i=0; i<l; i++) \
        std::cout << a[i] << " "; \
    std::cout << endl

#define TEST_SHOW_ARRAY2(a,r,c) \
    for (int i=0; i<r; i++) {\
        for (int j=0; j<c; j++) \
            std::cout << a[i][j] << " "; \
        std::cout << endl; \
    } \
    std::cout << endl

#define TEST_HINT(t) \
    std::cout << #t << endl

#define TEST_INFO(t,v) \
    std::cout << #t << v << endl

#define TEST_INFO2(t,i,j) \
    std::cout << #t << i << " " << j << endl

#else

#define TEST_SHOW_ARRAY(a,l)
#define TEST_SHOW_ARRAY2(a,r,c)
#define TEST_HINT(t)
#define TEST_INFO(t,v)
#define TEST_INFO2(t,i,j)

#endif

#define SHOW_ARRAY(a,l) \
    for (int i=0; i<l; i++) \
        std::cout << a[i]; \
    std::cout << endl

#define SHOW_ARRAY2(a,r,c) \
    for (int i=0; i<r; i++) {\
        for (int j=0; j<c; j++) \
            std::cout << a[i][j] << " "; \
        std::cout << endl; \
    } \
    std::cout << endl

#define INIT_ARRAY(a,l,t) \
    t *a = new t[l]
        
#define INPUT_ARRAY(a,l,t) \
    INIT_ARRAY(a,l,t); \
    for (int i=0; i<l; i++) \
        cin >> a[i]

#define INIT_ARRAY2(a,r,c,t) \
    t **a = new t*[r]; \
    for (int i=0; i<r; i++) \
        a[i] = new t*[c]
        
#define INPUT_ARRAY2(a,r,c,t) \
    INIT_ARRAY2(a,r,c,t); \
    for (int i=0; i<r; i++) \
        for (int j=0; j<c; j++) \
            cin >> a[i][j]


void Swap(int *pArray, const int i, const int j) {
    if (i==j) return;

    int tmp = pArray[i];
    pArray[i] = pArray[j];
    pArray[j] = tmp;

    TEST_INFO2(swap:, i, j);
}

void QuickSort(int *pArray, int iNum) {
    if (iNum<2) return;

    int baseIdx = rand() % iNum;
    Swap(pArray, 0, baseIdx);

    TEST_INFO(base and begin:, baseIdx);

    int headIdx = 1;
    int tailIdx = iNum-1;

    while(true) {
        while (tailIdx>0 && pArray[tailIdx]>pArray[0]) tailIdx--;
        while (headIdx<tailIdx && pArray[headIdx]<=pArray[0]) headIdx++;
        if (headIdx>=tailIdx) break;
        Swap(pArray, headIdx, tailIdx);
        headIdx++;
        tailIdx--;
    }
    
    Swap(pArray, 0, tailIdx);

    TEST_INFO2(more sort:, tailIdx, iNum-tailIdx-1);

    QuickSort(pArray, tailIdx);
    QuickSort(pArray+tailIdx+1, iNum-tailIdx-1);
}

/*********************************************
输入参数：
    int* pArray1 ：整型数组1
    intiArray1Num：数组1元素个数
    int* pArray2 ：整型数组2
    intiArray2Num：数组2元素个数
输出参数（指针指向的内存区域保证有效）：
    int* pOutputArray：合并后的数组
    int* iOutputNum：合并后数组元素个数
返回值：
    void
**********************************************/
void CombineBySort(int* pArray1, const int iArray1Num, int* pArray2, const int iArray2Num, int* pOutputArray, int* iOutputNum) {
    QuickSort(pArray1, iArray1Num);
    QuickSort(pArray2, iArray2Num);

    TEST_SHOW_ARRAY(pArray1, iArray1Num);
    TEST_SHOW_ARRAY(pArray2, iArray2Num);

    int tarIdx = 0;
    int idx0 = 0;
    int idx1 = 0;

    while(idx0<iArray1Num || idx1<iArray2Num) {
        if (idx0>=iArray1Num) {
            // move array2
            if (tarIdx==0 || pArray2[idx1]>pOutputArray[tarIdx-1])
                pOutputArray[tarIdx++] = pArray2[idx1];
            idx1++;

        } else if (idx1>=iArray2Num) {
            // move array1
            if (tarIdx==0 || pArray1[idx0]>pOutputArray[tarIdx-1])
                pOutputArray[tarIdx++] = pArray1[idx0];
            idx0++;

        } else {
            // compare
            if (pArray1[idx0] > pArray2[idx1]) {
                if (tarIdx==0 || pArray2[idx1]>pOutputArray[tarIdx-1])
                    pOutputArray[tarIdx++] = pArray2[idx1];
                idx1++;
            } else {
                if (tarIdx==0 || pArray1[idx0]>pOutputArray[tarIdx-1])
                    pOutputArray[tarIdx++] = pArray1[idx0];
                idx0++;
            }
        }
    }

    *iOutputNum = tarIdx;
}

int main() {
    int num0, num1;
    while (cin >> num0) {
        INPUT_ARRAY(aNum0, num0, int);
        
        cin >> num1;
        INPUT_ARRAY(aNum1, num1, int);

        int *aResult = new int[num0+num1];
        int iResult;
        CombineBySort(aNum0, num0, aNum1, num1, aResult, &iResult);
        SHOW_ARRAY(aResult, iResult);

        delete[] aNum1;

        // QuickSort(aNum0, num0);
        // TEST_SHOW_ARRAY(aNum0, num0);

        delete[] aNum0;
    }
    return 0;
}