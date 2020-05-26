#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#define TEST

/**
 * repeat command in shell:
 * for i in {1..100}; do echo hello; done
 * 
 * infinite:
 * while true; do echo hello; sleep 1; done
*/

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode() : left(NULL), right(NULL) {}
};

struct ListNode {
      int val;
      struct ListNode *next;
      ListNode(int x) :
            val(x), next(NULL) {
      }
      ListNode() :
            next(NULL) {
      }
};

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
        for (int j=0; j<(c); j++) \
            std::cout << a[i][j] << " "; \
        std::cout << endl; \
    } }

#define TEST_HINT(t) \
    std::cout << #t << endl

#define TEST_INFO(t,v) \
    std::cout << #t << v << endl

#define TEST_INFO2(t,i,j) \
    std::cout << #t << i << " " << j << endl

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
#define TEST_DEPTH(depth, v) 
#define TEST_DEPTH_INFO(t,v,d)
#define TEST_DEPTH_INFO2(t,i,j,d)

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
    t *a = new t[l]
        
#define INPUT_ARRAY(a,l,t) \
    INIT_ARRAY(a,l,t); \
    { \
        for (int i=0; i<(l); i++) \
            cin >> a[i]; \
    } 

#define INPUT_VECTOR(a,l,t) \
    INPUT_ARRAY(a##Tmp,l,t) \
    vector<t> a(a##Tmp, a##Tmp+l); \
    DELETE_ARRAY(a##Tmp);

#define DELETE_ARRAY(a) \
    delete[] a

#define INIT_ARRAY2(a,r,c,t) \
    t **a = new t*[r]; \
    { \
        for (int i=0; i<(r); i++) \
            a[i] = new t[c]; \
    }

#define INIT_ARRAY_V(a,l,t,v) \
    INIT_ARRAY(a,l,t); \
    memset(a, (int)v, sizeof(t)*(l)); \

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

#define INPUT_LINKLIST(h,l,t) t *h = NULL; \
{ \
    t *pTail = NULL, *node; \
    int n; \
    while (l--) { \
        cin>>n;  \
        node = new t(n); \
        if (pTail) { \
            pTail->next = node; \
            pTail = node; \
        } else \
            h = pTail = node; \
    } \
}

#define SHOW_LINKLIST(h,t) \
    { \
        t *ph = h; \
        while (ph) { \
            cout << ph->val << " "; \
            ph = ph->next; \
        } \
        cout << endl; \
    }

#define SHOW_TREE_LINKLIST(h,t) \
    { \
        t *ph = h; \
        while (ph) { \
            cout << ph->val << " "; \
            ph = ph->right; \
        } \
        cout << endl; \
    }

#define DELETE_LINKLIST(h,t) \
    while (h) { \
        t *tmp = h->next; \
        delete h; \
        h = tmp; \
    }

TreeNode* BuildBinaryTree(vector<int>::iterator pre_begin, vector<int>::iterator pre_end, \
    vector<int>::iterator vin_begin, vector<int>::iterator vin_end) {
    if(pre_begin == pre_end) return NULL;
    
    int root_val = *pre_begin;
    TreeNode *node = new TreeNode(root_val);

    int len = distance(pre_begin, pre_end);
    if (len>1) {
        int mid_pos = distance(vin_begin, find(vin_begin, vin_end, root_val));

        if (mid_pos>0) {
            node->left = BuildBinaryTree(pre_begin+1, pre_begin+1+mid_pos, vin_begin, vin_begin+mid_pos);
        }

        if (mid_pos<len-1) {
            node->right = BuildBinaryTree(pre_begin+1+mid_pos, pre_end, vin_begin+mid_pos+1, vin_end);
        }
    }
    return node;
}

#define INPUT_TREE(h,lv,t) t* h; \
{ \
    int total_count = pow(2, lv)-1; \
    INIT_ARRAY_V(pNodes,total_count,t*,NULL); \
    int count = 1, iNum, idx0, idx1; \
    t *node; \
    string text; \
    for (int i=0; i<lv; i++) { \
        for (int j=0; j<count && cin>>text; j++) { \
            if (text[0]=='#') continue; \
            iNum = atoi(text.c_str()); \
            idx0 = pow(2,i)-1+j; \
            pNodes[idx0] = new t(iNum); \
            if (i>0) { \
                idx1 = pow(2,i-1)-1+j/2; \
                if (j%2) pNodes[idx1]->right = pNodes[idx0]; \
                else pNodes[idx1]->left = pNodes[idx0]; \
            } \
        } \
        count *= 2; \
    } \
    h = pNodes[0]; \
    DELETE_ARRAY(pNodes);\
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

#define PRE_SHOW_TREE(root) \
    TEST_HINT(------); \
    _PRE_SHOW_TREE(root, 0)

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
