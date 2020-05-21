#include <stack>
#include <assert.h>
#include <iostream>
#include <cstring>
using namespace std;

#define TEST
#define HAS_SCOPE

// 条件这么放开，真的该用python了
#define NO_ORDER        // 数字不是有序的
#define CAN_IDLE        // 可以有空闲数字

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
    std::cout << #t << (v) << endl;

#define TEST_INFO2(t,i,j) \
    std::cout << #t << (i) << " " << (j) << endl;

#define TEST_DEPTH(depth, v) \
    for(int i=0; i<(depth); i++) \
        std::cout << v;

#define TEST_DEPTH_INFO(t,v,d) \
    TEST_DEPTH(d, ' '); \
    TEST_INFO(t,(v));

#define TEST_DEPTH_INFO2(t,i,j,d) \
    TEST_DEPTH(d, ' '); \
    TEST_INFO2(t,(i),(j));

#else

#define TEST_SHOW_ARRAY(a,l)
#define TEST_SHOW_ARRAY2(a,r,c)
#define TEST_HINT(t)
#define TEST_INFO(t,v)
#define TEST_INFO2(t,i,j)
#define TEST_DEPTH(depth, v)
#define TEST_DEPTH_INFO(t,v,d)
#define TEST_DEPTH_INFO2(t,i,j,d)

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


#define TARGET_NUM 24
#define COUNT 4

int execute(const char &op, const int &oprandL, const int &oprandR) {
    switch (op) {
        case '+':
            return oprandL + oprandR;
        case '-':
            return oprandL - oprandR;
        case '*':
            return oprandL * oprandR;
        case '/':
            assert(oprandR && "divisor is zero!");
            return oprandL / oprandR;   // check 0
    }
    return 0;
}

#ifdef HAS_SCOPE
/**
 * 有括号的做法
 * 因为是穷举，括号其实是随意加的
 * 这样就没有优先级判断的需要了
 * 
 * 但是依然需要依赖递归实现穷举
 * 子计算一共有 len-1 个
 * 当前计算可以是其中任意一个，记录结果
 * 然后在下一次递归中计算状态更新后的 len-2 个子计算
 * 
 * 缺陷：
 * 1. 内存搬运（耗时）
 * 2. aOpera 没有用，因为 aNums 顺序总是乱的，无法将 aOpera 存储完整的指令序列
 * 
 * 改进：
 * 因为很多对节点的插入、删除操作，用链表结构可以完美解决问题
*/
bool canExpressNum(int* aNums, int len, char *aOpera, int step, int target) {
    if (len==1) {
        TEST_DEPTH_INFO(=:, aNums[0], step);
        return aNums[0] == target;
    }

    int backup0, backup1;
    for (int i=1; i<len; i++) {
        backup0 = aNums[i-1];
        backup1 = aNums[i];
        
        TEST_DEPTH_INFO2(+:, backup0, backup1, step);
        aNums[i] = aNums[i-1] + aNums[i];
        if(i-1) memcpy(aNums+1, aNums, i-1);
        if(canExpressNum(aNums+1, len-1, aOpera, step+1, target)) return true;
        if(i-1) memcpy(aNums, aNums+1, i-1);
        aNums[i-1] = backup0;
        aNums[i] = backup1;

        TEST_DEPTH_INFO2(-:, backup0, backup1, step);
        aNums[i] = aNums[i-1] - aNums[i];
        if(i-1) memcpy(aNums+1, aNums, i-1);
        if(canExpressNum(aNums+1, len-1, aOpera, step+1, target)) return true;
        if(i-1) memcpy(aNums, aNums+1, i-1);
        aNums[i-1] = backup0;
        aNums[i] = backup1;
        
        TEST_DEPTH_INFO2(*:, backup0, backup1, step);
        aNums[i] = aNums[i-1] * aNums[i];
        if(i-1) memcpy(aNums+1, aNums, i-1);
        if(canExpressNum(aNums+1, len-1, aOpera, step+1, target)) return true;
        if(i-1) memcpy(aNums, aNums+1, i-1);
        aNums[i-1] = backup0;
        aNums[i] = backup1;

        if (aNums[i] && aNums[i-1] % aNums[i] == 0) {
            TEST_DEPTH_INFO2(/:, backup0, backup1, step);
            aNums[i] = aNums[i-1] / aNums[i];
            if(i-1) memcpy(aNums+1, aNums, i-1);
            if(canExpressNum(aNums+1, len-1, aOpera, step+1, target)) return true;
            if(i-1) memcpy(aNums, aNums+1, i-1);
            aNums[i-1] = backup0;
            aNums[i] = backup1;
        }
    }

    return false;
}

#else

int priority(char ch) {
    switch(ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return 0;
}

/**
 * 没有括号的做法
 * 操作数的优先级是固定的，所以要判断优先级
 * 好处也有
 * 因为没有繁琐的嵌套关系，所以至多只有一个子计算处于等待状态
 * 我们计算完当前的子计算后，可以将等待的子计算的操作数和算子移位，利用一个数组 aCalcs 实现递归求解
*/
int resultExpress(int* aNums, int pos, int len, char *aOpera) {
    int oprandL = aNums[pos];
    if (pos==len-1) return oprandL;     // no operator; no operandR

    char currOpera = aOpera[pos];
    char nextOpera = 0;
    char lastOpera = 0;
    if (pos<len-1) nextOpera = aOpera[pos+1];
    if (pos>0) lastOpera = aOpera[pos-1];

    if (priority(currOpera) >= priority(nextOpera)) {
        int oprandR = aNums[pos+1];
        oprandL = execute(currOpera, oprandL, oprandR);
        aNums[pos+1] = oprandL; // backup result by oprandR

        if(lastOpera && priority(lastOpera)<priority(currOpera)) {
            // last Opera is waitting
            // move ahead oprand & operator to pos
            // recalculate at same pos
            oprandL = aNums[pos-1];
            aNums[pos] = oprandL;
            aOpera[pos] = lastOpera;
            return resultExpress(aNums, pos, len, aOpera);
        } else // no operator watting
            return resultExpress(aNums, pos+1, len, aOpera);
    } else {
        return resultExpress(aNums, pos+1, len, aOpera);
    }
}

bool canExpressNum(const int* aNums, int len, char *aOpera, int opCount, int target) {
    if (opCount < len - 1) {
        aOpera[opCount] = '+';
        if (canExpressNum(aNums, len, aOpera, opCount+1, target)) return true;
        aOpera[opCount] = '-';
        if (canExpressNum(aNums, len, aOpera, opCount+1, target)) return true;
        aOpera[opCount] = '*';
        if (canExpressNum(aNums, len, aOpera, opCount+1, target)) return true;
        aOpera[opCount] = '/';
        if (canExpressNum(aNums, len, aOpera, opCount+1, target)) return true;
        return false;
    } 

    // all operator is ready
    // calculate the result

#ifdef TEST
    // show expression
    for (int i=0; i<len; i++) {
        cout << aNums[i] << " ";
        if (i<len-1) cout << aOpera[i] << " ";
    }
#endif

    INIT_ARRAY(aCalcs, COUNT, int);
    memcpy(aCalcs, aNums, len);       // aCalcs 辅助计算，会有数据改动
    int result = resultExpress(aCalcs, 0, len, aOpera);
#ifdef TEST
    cout << " = " << result << endl;
#endif

    DELETE_ARRAY(aCalcs);
    return result == target;
}
#endif

int main() {
    INIT_ARRAY(aNums, COUNT, int);
    INIT_ARRAY(aOpera, COUNT-1, char);
    while (cin>>aNums[0]>>aNums[1]>>aNums[2]>>aNums[3]) {
        // 4 operator : + - * /
        // 4 ** (COUNT-1) ways = 64
        // use table to records operators for one way
        if (canExpressNum(aNums, COUNT, aOpera, 0, TARGET_NUM)) cout << "true" << endl;
        else cout << "false" << endl;

    }
    DELETE_ARRAY(aNums);
    DELETE_ARRAY(aOpera);
    return 0;
}