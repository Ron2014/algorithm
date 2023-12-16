#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define TEST

/**
 * marco 定义，而不是 inline void 函数定义
 * 原因是：如果定义成函数，传参需要明确的数据类型
 * macro 定义可以保证对类型足够 open
 * 参考 INIT_ARRAY
*/

#ifdef TEST

#define TEST_SHOW_ARRAY(a,l) \
    for (int ii=0; ii<(l); ii++) \
        std::cout << a[ii] << " "; \
    std::cout << endl;

#define TEST_SHOW_ARRAY2(a,r,c) \
    for (int ii=0; ii<(r); ii++) {\
        for (int ij=0; ij<(c); ij++) \
            std::cout << a[ii][ij] << " "; \
        std::cout << endl; \
    } 

#define TEST_HINT(t) \
    std::cout << #t << endl;

#define TEST_INFO(t,v) \
    std::cout << #t << v << endl;

#define TEST_INFO2(t,i,j) \
    std::cout << #t << i << " " << j << endl;

#define TEST_DEPTH(depth, v) \
    for(int i=0; i<(depth); i++) \
        std::cout << v;

#define TEST_DEPTH_INFO(t,v,d) \
    TEST_DEPTH(d, ' ') \
    TEST_INFO(t,v)

#define TEST_DEPTH_INFO2(t,i,j,d) \
    TEST_DEPTH(d, ' ') \
    TEST_INFO2(t,i,j)

#else

#define TEST_SHOW_ARRAY(a,l)
#define TEST_SHOW_ARRAY2(a,r,c)
#define TEST_HINT(t)
#define TEST_INFO(t,v)
#define TEST_INFO2(t,i,j)

#endif

#define SHOW_ARRAY(a,l) \
    for (int i=0; i<(l); i++) \
        std::cout << a[i] << " "; \
    std::cout << endl;

#define SHOW_ARRAY2(a,r,c) \
    for (int i=0; i<(r); i++) {\
        for (int j=0; j<(c); j++) \
            std::cout << a[i][j] << " "; \
        std::cout << endl; \
    } 

#define INIT_ARRAY(a,l,t) \
    t *a = new t[l];
        
#define INPUT_ARRAY(a,l,t) \
    INIT_ARRAY(a,l,t); \
    for (int i=0; i<(l); i++) \
        cin >> a[i];

#define DELETE_ARRAY(a) \
    delete[] a;

#define INIT_ARRAY2(a,r,c,t) \
    t **a = new t*[r]; \
    for (int i=0; i<(r); i++) \
        a[i] = new t[c]; \

#define INIT_ARRAY_V(a,l,t,v) \
    INIT_ARRAY(a,l,t) \
    memset(a, v, sizeof(t)*(l)); \

#define INIT_ARRAY2_V(a,r,c,t,v) \
    t **a = new t*[r]; \
    for (int i=0; i<(r); i++) {\
        a[i] = new t[c]; \
        memset(a[i], v, sizeof(t)*(c)); \
    }
        
#define INPUT_ARRAY2(a,r,c,t) \
    INIT_ARRAY2(a,r,c,t); \
    for (int i=0; i<(r); i++) \
        for (int j=0; j<c; j++) \
            cin >> a[i][j];
        
#define DELETE_ARRAY2(a,r) \
    for (int i=0; i<(r); i++) \
        delete[] a[i]; \
    delete[] a;

#define SHOW_LINKLIST(h,t,v,n) \
    { \
        t *ph = h; \
        while (ph) { \
            cout << ph->m_##v << " "; \
            ph = ph->m_##n; \
        } \
        cout << endl; \
    }

#define DELETE_LINKLIST(h,t,n) \
    while (h) { \
        t *tmp = h->m_##n; \
        delete h; \
        h = tmp; \
    }

int aNumbersOdd[101];
int aNumbersEven[101];

int iCount;
int iCountOdd, iCountEven;

bool isPrime(int num) {
    for (int i=2; i < num/2; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

bool isPrimePartner(int a, int b) {
    return isPrime(a + b);
}

int canPair(int fromIdx, int *fromArr, int *toArr, int toLen, int *toMatched) {
    int num = fromArr[fromIdx];
    vector<int> need_deep;

    for (int i=1; i<=toLen; i++) {
        int pair = toArr[i];
        if (pair<=0) continue;

        if (isPrimePartner(num, pair)) {
            if (toMatched[i] == 0) {
                toMatched[i] = fromIdx;
                return i;
                // return true;
            // } else {
            //     need_deep.push_back(i);
            }
        }
    }
    // for (auto it=need_deep.begin(); it!=need_deep.end(); it++) {
    //     int i = *it;

    //     int pair = toArr[i];
    //     toArr[i] = toArr[toLen-1];
    //     toArr[toLen-1] = pair;

    //     bool ret = canPair(toMatched[i], fromArr, toArr, toLen-1, toMatched);

    //     pair = toArr[i];
    //     toArr[i] = toArr[toLen-1];
    //     toArr[toLen-1] = pair;

    //     if (ret) {
    //         toMatched[i] = fromIdx;
    //         return true;
    //     }
    // }

    // return false;
    return 0;
}

int main(int argc, char *argv[]) {
    while (scanf("%d", &iCount) != EOF) {
        iCountOdd = 0;
        iCountEven = 0;

        int n;
        for (int i=1; i<=iCount; i++) {
            scanf("%d", &n);
            if (n%2) {
                aNumbersOdd[++iCountOdd] = n;
            } else {
                aNumbersEven[++iCountEven] = n;
            }
        }

        INIT_ARRAY_V(aMatchOdd, iCountOdd+1, int, 0);
        INIT_ARRAY_V(aMatchEven, iCountEven+1, int, 0);

        INIT_ARRAY2_V(aMaxPairCount, iCountOdd+1, iCountEven+1, int, 0);

        TEST_HINT(odd-----------);
        TEST_SHOW_ARRAY(aNumbersOdd, iCountOdd+1);
        TEST_HINT(even----------);
        TEST_SHOW_ARRAY(aNumbersEven, iCountEven+1);

        for (int i=1; i<=iCountOdd; i++) {
            for (int j=1; j<=iCountEven; j++) {
                TEST_INFO2(calc:, i, j);

                int num_odd = aNumbersOdd[i];
                int num_even = aNumbersEven[j];

                int lessOdd = aMaxPairCount[i-1][j];
                int lessEven = aMaxPairCount[i][j-1];
                aMaxPairCount[i][j] = lessEven;
                int minNum;

                if (lessOdd <= lessEven) {
                    minNum = (i<j-1) ? i : j-1;
                    if (lessEven<minNum) {
                        if (aMatchEven[j]) {
                            aMaxPairCount[i][j] = lessEven + 1;
                        } else {
                            int matchIdx = canPair(j, aNumbersEven, aNumbersOdd, i, aMatchOdd);
                            if (matchIdx) {
                                aMaxPairCount[i][j] = lessEven + 1;
                                aMatchEven[j] = matchIdx;
                                TEST_INFO(more pair 1:, aMaxPairCount[i][j]);
                                TEST_SHOW_ARRAY(aMatchOdd, iCountOdd+1);
                                TEST_SHOW_ARRAY(aMatchEven, iCountEven+1);
                                TEST_SHOW_ARRAY2(aMaxPairCount, i+1, j+1);
                            } else
                                aMaxPairCount[i][j] = lessEven;
                        }
                    } else 
                        aMaxPairCount[i][j] = lessEven;
                } else {
                    minNum = (i-1<j) ? (i-1):j;
                    if (lessOdd<minNum) {
                        if (aMatchOdd[i]) {
                            aMaxPairCount[i][j] = lessOdd + 1;
                        } else {
                            int matchIdx = canPair(i, aNumbersOdd, aNumbersEven, j, aMatchEven);
                            if (matchIdx) {
                                aMaxPairCount[i][j] = lessOdd + 1;
                                aMatchOdd[i] = matchIdx;
                                TEST_INFO(more pair 2:, aMaxPairCount[i][j]);
                                TEST_SHOW_ARRAY(aMatchOdd, iCountOdd+1);
                                TEST_SHOW_ARRAY(aMatchEven, iCountEven+1);
                                TEST_SHOW_ARRAY2(aMaxPairCount, i+1, j+1);
                            } else
                                aMaxPairCount[i][j] = lessOdd;
                        }
                    } else
                        aMaxPairCount[i][j] = lessOdd;
                }
            }
        }

        TEST_HINT(max pair----------);
        TEST_SHOW_ARRAY2(aMaxPairCount, iCountOdd+1, iCountEven+1);

        cout << aMaxPairCount[iCountOdd][iCountEven] << endl;

        DELETE_ARRAY(aMatchOdd);
        DELETE_ARRAY(aMatchEven);
        DELETE_ARRAY2(aMaxPairCount, iCountOdd+1);
    }
}