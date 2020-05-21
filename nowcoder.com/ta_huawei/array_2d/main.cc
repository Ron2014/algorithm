#include <sstream>

#include <iostream>
#include <cstring>
using namespace std;

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


int main() {
    int r, c, r0, c0, r1, c1;
    int **aMoves = nullptr;

    while (cin>>r>>c) {
        stringstream ss;
        if (r>0 && c>0) {
            // cout << 0 << endl;
            ss << 0 << endl;
            aMoves = new int*[r];
            for (int i=0; i<r; i++) {
                aMoves[i] = new int[c];
                memset(aMoves[i], 0, sizeof(int)*(c));
            }
        } else
            ss << -1 << endl;

        cin >> r0 >> c0 >> r1 >> c1;
        if (r0<0 || r0>=r ||
            r1<0 || r1>=r ||
            c0<0 || c0>=c ||
            c1<0 || c1>=c)
            // cout << -1 << endl;
            ss << -1 << endl;
        else {;
            // cout << 0 << endl;
            ss << 0 << endl;
            aMoves[r0][c0] = 0;
            aMoves[r1][c1] = 0;
        }

        TEST_HINT(-------)
        TEST_SHOW_ARRAY2(aMoves,r,c);

        cin >> r0 >> c0;
        if (r0<0 || r0>=r)
            // cout << -1 << endl;
            ss << -1 << endl;
        else{
            // cout << 0 << endl;
            ss << 0 << endl;
            r++;
            INIT_ARRAY(aNew, r, int*);
            // INIT_ARRAY_V(newMoves, c, int, -1);
            INIT_ARRAY_V(newMoves, c, int, 0);
            aNew[r0] = newMoves;
            for (int i=0; i<r0; i++)
                aNew[i] = aMoves[i];
            for (int i=r0+1; i<r; i++) {
                aNew[i] = aMoves[i-1];
                for (int k=0; k<c; k++)
                    aNew[i][k] = i<(r-1) ? aMoves[i-1][k] : -1;
            }

            if(aMoves) delete[] aMoves;
            aMoves = aNew;
        }

        TEST_HINT(-------)
        TEST_SHOW_ARRAY2(aMoves,r,c);

        if (c0<0 || c0>=c || !aMoves)
            // cout << -1 << endl;
            ss << -1 << endl;
        else {
            // cout << 0 << endl;
            ss << 0 << endl;
            c++;
            for (int i=0; i<r; i++) {
                INIT_ARRAY(aNew, c, int);
                aNew[c0] = c0<(c-1)? 0 : -1;
                for (int j=0; j<c0; j++)
                    aNew[j] = aMoves[i][j];
                for (int j=c0+1; j<c; j++) {
                    aNew[j] = j<(c-1) ? aMoves[i][j-1] : -1;
                }
                delete[] aMoves[i];
                aMoves[i] = aNew;
            }
        }

        TEST_HINT(-------)
        TEST_SHOW_ARRAY2(aMoves,r,c);

        cin >> r1 >> c1;
        cout << ss.str();

        if (r1<0 || r1>=r ||
            c1<0 || c1>=c) {
                cout << -1 << endl;
        } else 
            // cout << 0 << endl;
            cout << aMoves[r1][c1] << endl;

        DELETE_ARRAY2(aMoves, r);
    }
    return 0;
}