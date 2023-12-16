#include <iostream>
#include <stack>
#include <sstream>
#include <cstring>
using namespace std;

// #define SHOW_OPERA
// #define TEST

/**
 * marco 定义，而不是 inline void 函数定义
 * 原因是：如果定义成函数，传参需要明确的数据类型
 * macro 定义可以保证对类型足够 open
 * 参考 INIT_ARRAY
*/

#ifdef TEST

#define TEST_SHOW_ARRAY(a,l) \
    for (int i=0; i<l; i++) \
        std::cout << a[i] << " "; \
    std::cout << endl;

#define TEST_SHOW_ARRAY2(a,r,c) \
    for (int i=0; i<r; i++) {\
        for (int j=0; j<c; j++) \
            std::cout << a[i][j] << " "; \
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
    TEST_INFO2(t,v)

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



/*  
 * 功能：计算两个字符串的距离 
 * 输入： 字符串A和字符串B
 * 输出：无
 * 返回：如果成功计算出字符串的距离，否则返回-1
*/
int calStringDistance(string &charA, string &charB) {
    const char *chA = charA.c_str();
    const char *chB = charB.c_str();

    int lenA = charA.length();
    int lenB = charB.length();

    INIT_ARRAY2(LD, lenA+1, lenB+1, int);

    /***
     * LD[i][j] :
     * distance of charA[:i] and charB[:j]
     */
    for (int i=0; i<=lenA; i++)
        LD[i][0] = i;
    for (int i=0; i<=lenB; i++)
        LD[0][i] = i;
    
    int ldAMore, ldBMore, ld2More;
    for (int i=1; i<=lenA; i++)
        for (int j=1; j<=lenB; j++) {
            ldAMore = LD[i-1][j];
            ldBMore = LD[i][j-1];
            ld2More = LD[i-1][j-1];
            
            if (ld2More<=ldAMore && ld2More<=ldBMore) {
                // for chA[:i-1],chB[:j-1]  add chA[i-1], chB[j-1]
                LD[i][j] = (chA[i-1]==chB[j-1]) ? ld2More : (ld2More+1);

            } else if(ldAMore < ldBMore) {
                // for chA[:i-1],chB[:j]    add chA[i-1]
                LD[i][j] = ldAMore+1;

            } else {
                // for chA[:i]  ,chB[:j-1]  add chB[j-1]
                LD[i][j] = ldBMore+1;
            }
        }

#ifdef SHOW_OPERA
    // charA -> charB
    stack<string> ops;
    stringstream ss;

    int ci = lenA, cj = lenB;
    while (ci>0 && cj>0) {
        ldAMore = LD[ci-1][cj];
        ldBMore = LD[ci][cj-1];
        ld2More = LD[ci-1][cj-1];

        ss.str("");
        // ss.clear();
        if (ld2More<=ldAMore && ld2More<=ldBMore) {
            // for chA[:i-1],chB[:j-1]  add chA[i-1], chB[j-1]
            if (chA[ci-1]==chB[cj-1]) ss << "add " << chA[ci-1];
            else ss << "change " << chA[ci-1] << " to " << chB[cj-1];
            ci = ci-1;
            cj = cj-1;

        } else if(ldAMore < ldBMore) {
            // for chA[:i-1],chB[:j]    add chA[i]
            ss << "add " << chA[ci-1];
            ci = ci-1;
        } else {
            // for chA[:i]  ,chB[:j-1]  add chB[j]
            ss << "add " << chB[cj-1];
            cj = cj-1;
        }
        ops.push(ss.str());
    }

    while(!ops.empty()) {
        cout << ops.top() << endl;
        ops.pop();
    }
#endif
    int result = LD[lenA][lenB];

    TEST_SHOW_ARRAY2(LD, lenA+1, lenB+1);
    DELETE_ARRAY2(LD, lenA+1);
    return result;
}

int main() {
    string a, b;
    while (cin>>a>>b) {
        cout << "1/" << 1+calStringDistance(a,b) << endl;
    }
    return 0;
}