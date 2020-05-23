#include <iostream>
#include <cstring>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
      int val;
      struct ListNode *next;
      ListNode(int x) :
            val(x), next(NULL) {
      }
};

#define TEST

/**
 * marco 定义，而不是 inline void 函数定义
 * 原因是：如果定义成函数，传参需要明确的数据类型
 * macro 定义可以保证对类型足够 open
 * 参考 INIT_ARRAY
*/

#ifdef TEST

#define TEST_SHOW_ARRAY(a,l) { \
    for (int i=0; i<(l); i++) \
        std::cout << a[i] << " "; \
    std::cout << endl; }

#define TEST_SHOW_ARRAY2(a,r,c) { \
    for (int i=0; i<(r); i++) {\
        for (int i=0; i<(c); i++) \
            std::cout << a[i][i] << " "; \
        std::cout << endl; \
    } }

#define TEST_HINT(t) \
    std::cout << #t << endl;

#define TEST_INFO(t,v) \
    std::cout << #t << v << endl;

#define TEST_INFO2(t,i,j) \
    std::cout << #t << i << " " << j << endl;

#define TEST_DEPTH(depth, v) {\
    for(int i=0; i<(depth); i++) \
        std::cout << v; }

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

#define SHOW_ARRAY(a,l) { \
    for (int i=0; i<(l); i++) \
        std::cout << a[i] << " "; \
    std::cout << endl; }

#define SHOW_ARRAY2(a,r,c) { \
    for (int i=0; i<(r); i++) {\
        for (int j=0; j<(c); j++) \
            std::cout << a[i][j] << " "; \
        std::cout << endl; \
    } }

#define INIT_ARRAY(a,l,t) \
    t *a = new t[l];
        
#define INPUT_ARRAY(a,l,t) \
    INIT_ARRAY(a,l,t); \
    { \
        for (int i=0; i<(l); i++) \
            cin >> a[i]; \
    } 

#define DELETE_ARRAY(a) \
    delete[] a;

#define INIT_ARRAY2(a,r,c,t) \
    t **a = new t*[r]; \
    { \
        for (int i=0; i<(r); i++) \
            a[i] = new t[c]; \
    }

#define INIT_ARRAY_V(a,l,t,v) \
    INIT_ARRAY(a,l,t) \
    memset(a, v, sizeof(t)*(l)); \

#define INIT_ARRAY2_V(a,r,c,t,v) \
    t **a = new t*[r]; \
    { \
        for (int i=0; i<(r); i++) {\
            a[i] = new t[c]; \
            memset(a[i], v, sizeof(t)*(c)); \
        } \
    }
        
#define INPUT_ARRAY2(a,r,c,t) \
    INIT_ARRAY2(a,r,c,t); \
    { \
        for (int i=0; i<(r); i++) \
            for (int j=0; j<c; j++) \
                cin >> a[i][j]; \
    }
        
#define DELETE_ARRAY2(a,r) \
    { \
        for (int i=0; i<(r); i++) \
            delete[] a[i]; \
    } \
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

void _PRE_SHOW_TREE(TreeNode *root, int depth) {
    cout << root->val << " ";
#ifdef TEST
    cout << endl;
#endif

    if (root->left) {
        TEST_DEPTH(depth, '-')
        cout << 'L';
        _PRE_SHOW_TREE(root->left, depth+1);
    }
    if (root->right){
        TEST_DEPTH(depth, '-')
        cout << 'R';
        _PRE_SHOW_TREE(root->right, depth+1);
    }
#ifndef TEST
    if (!depth) cout << endl;
#endif
}

#define PRE_SHOW_TREE(root) _PRE_SHOW_TREE(root, 0)

void _MID_SHOW_TREE(TreeNode *root, int depth) {
    if (root->left) _MID_SHOW_TREE(root->left, depth+1);
    cout << root->val << " ";
    if (root->right) _MID_SHOW_TREE(root->right, depth+1);
    if (!depth) cout << endl;
}

#define MID_SHOW_TREE(root) _MID_SHOW_TREE(root, 0)

void _POS_SHOW_TREE(TreeNode *root, int depth) {
    if (root->left) _POS_SHOW_TREE(root->left, depth+1);
    if (root->right) _POS_SHOW_TREE(root->right, depth+1);
    cout << root->val << " ";
    if (!depth) cout << endl;
}

#define POS_SHOW_TREE(root) _POS_SHOW_TREE(root, 0)
