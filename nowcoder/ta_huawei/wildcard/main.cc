#include <iostream>
using namespace std;
#include <cstring>
// #define TEST

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
    } \
    std::cout << endl;

#define TEST_HINT(t) \
    std::cout << #t << endl;

#define TEST_INFO(t,v) \
    std::cout << #t << v << endl;

#define TEST_INFO2(t,i,j) \
    std::cout << #t << i << " " << j << endl;

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
    } \
    std::cout << endl;

#define INIT_ARRAY(a,l,t) \
    t *a = new t[l]
        
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

#define INIT_ARRAY2_V(a,r,c,t,v) \
    t **a = new t*[r]; \
    for (int i=0; i<(r); i++) {\
        a[i] = new t[c]; \
        memset(a[i], 0, sizeof(t)*(c)); \
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


bool isWildcardMatched(string &strMatch, string& strTarget) {
    int lenM = strMatch.length();
    int lenT = strTarget.length();

    INIT_ARRAY2_V(lastMatched, lenM+1, lenT+1, int, 0);
    
    const char* chM = strMatch.c_str();
    const char* chT = strTarget.c_str();

    // lastMatched[i][j]:
    // chM[:i] matched chT[:j]?
    // chM[:0] matched chT[:0]
    lastMatched[0][0] = 1;

    char ch;
    bool matched;
    for (int i=1; i<=lenM; i++) {
        ch = chM[i-1];
        matched = false;
        for (int j=1; j<=lenT; j++) {
            switch(ch) {
                case '?':{
                    if (lastMatched[i-1][j-1]) {
                        lastMatched[i][j] = 1;
                        matched = true;
                    }
                } break;
                case '*': {
                    if (lastMatched[i-1][j] || lastMatched[i][j-1]) {
                        lastMatched[i][j] = 1;
                        matched = true;
                    }
                } break;
                default: {
                    if (lastMatched[i-1][j-1] && ch == chT[j-1]) {
                        lastMatched[i][j] = 1;
                        matched = true;
                    }
                } break;
            }
        }
        if (!matched) break;
    }

    int result = lastMatched[lenM][lenT];
    TEST_SHOW_ARRAY2(lastMatched, lenM+1, lenT+1);
    DELETE_ARRAY2(lastMatched, lenM+1);
    return result == 1;
}

int main() {
    string strMatch, strTarget;
    while (cin>>strMatch>>strTarget) {
        if (isWildcardMatched(strMatch, strTarget)) cout << "true" << endl;
        else cout << "false" << endl;
    }
    return 0;
}