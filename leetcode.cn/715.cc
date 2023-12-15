#include <iostream>
#include <cstdio>
using namespace std;

struct RangeNode
{
    int left;
    int right;
    RangeNode *prev;
    RangeNode *next;
    RangeNode(int l, int r)
    {
        left = l;
        right = r;
        prev = NULL;
        next = NULL;
    }
};

class RangeModule {
public:
    RangeModule() {
        m_pRangeHead = NULL;
    }
    
    void addRange(int left, int right) {
        if (!m_pRangeHead)
        {
            m_pRangeHead = new RangeNode(left, right);
            return;
        }

        RangeNode *pNode = m_pRangeHead, *pNewNode = NULL;
        while (pNode)
        {
            if (right < pNode->left)
            {
                // 在左侧
                if (pNewNode) break;
                pNewNode = new RangeNode(left, right);
                pNewNode->prev = pNode->prev;
                pNewNode->next = pNode;
                if (pNode->prev)
                {
                    pNode->prev->next = pNewNode;
                }
                else
                {
                    m_pRangeHead = pNewNode;
                }
                pNode->prev = pNewNode;
                break;
            }
            else if (left > pNode->right)
            {
                if (!pNode->next)
                {
                    // 在右侧且是最末端
                    pNode->next = new RangeNode(left, right);
                    pNode->next->prev = pNode;
                    break;
                }
            }
            else
            {
                if (pNewNode)
                {
                    if (pNewNode->prev)
                    {
                        pNewNode->prev->next = pNewNode->next;
                    }
                    else
                    {
                        m_pRangeHead = pNewNode->next;
                    }
                    if (pNewNode->next)
                    {
                        pNewNode->next->prev = pNewNode->prev;
                    }
                    delete pNewNode;
                }
                pNewNode = pNode;
                if (left < pNode->left)
                {
                    pNode->left = left;
                    if (right <= pNode->right)
                    {
                        // 左合并
                        right = pNode->right;
                    }
                    else
                    {
                        // 包含
                        pNode->right = right;
                    }
                }
                else
                {
                    if (right <= pNode->right)
                    {
                        // 被包含
                        break;
                    }
                    else
                    {
                        // 右合并
                        pNode->right = right;
                        left = pNode->left;
                    }
                }
            }
            pNode = pNode->next;
        }
    }
    
    bool queryRange(int left, int right) {
        if (!m_pRangeHead) return false;
        dump();
        // RangeNode *pNode = m_pRangeHead;
        // while (pNode)
        // {
        //     if (pNode->left <= left && pNode->right >= right) return true;
        //     pNode = pNode->next;
        // }
        // return false;
    }
    
    void removeRange(int left, int right) {
        if (!m_pRangeHead) return;

        RangeNode *pNode = m_pRangeHead, *pTemp, *pNewNode;
        while (pNode)
        {
            pTemp = pNode->next;
            if (right < pNode->left)
            {
                break;
            }
            else if (left > pNode->right)
            {
            }
            else
            {
                if (left <= pNode->left)
                {
                    if (right < pNode->right)
                    {
                        // 左消除
                        pNode->left = right;
                        break;
                    }
                    else
                    {
                        // 包含
                        // printf("-%d %d-\n", left, right);
                        // printf("-%d %d-\n", pNode->left, pNode->right);
                        left = pNode->right;
                        if (pNode->prev)
                        {
                            pNode->prev->next = pNode->next;
                        }
                        else
                        {
                            m_pRangeHead = pNode->next;
                        }
                        if (pNode->next)
                        {
                            pNode->next->prev = pNode->prev;
                        }
                        delete pNode;
                        // printf("-%d %d-\n", left, right);
                    }
                }
                else
                {
                    if (right < pNode->right)
                    {
                        // 被包含
                        pNewNode = new RangeNode(right, pNode->right);
                        pNewNode->prev = pNode;
                        pNewNode->next = pNode->next;
                        if (pNode->next)
                        {
                            pNode->next->prev = pNewNode;
                        }
                        pNode->next = pNewNode;
                        pNode->right = left;
                        break;
                    }
                    else
                    {
                        // 右消除
                        pNode->right = left;
                    }
                }
            }
            pNode = pTemp;
        }
    }

    void dump()
    {
        printf("================\n");
        RangeNode *pNode = m_pRangeHead;
        while (pNode)
        {
            printf("%d,%d,%p\n", pNode->left, pNode->right, pNode->prev);
            pNode = pNode->next;
        }
    }

private:
    RangeNode *m_pRangeHead;
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */

int main(int argc, char *argv[])
{
    RangeModule a;
    a.addRange(55,62);      // 55,62
    a.addRange(1,29);       // 1,29 55,62
    a.removeRange(18,49);   // 1,18 55,62
    a.dump();
    a.queryRange(6,98);
    a.queryRange(59,71);
    a.removeRange(40,45);   // 1,18 55,62
    a.removeRange(4,58);    // 1,4 58,62
    a.dump();
    a.removeRange(57,69);   // 1,4
    a.dump();
    // a.removeRange(20,30);
    // a.removeRange(1,40);
    // a.queryRange(73,93);
    // a.removeRange(32,93);
    // a.addRange(38,100);
    // a.removeRange(50,64);
    // a.addRange(26,72);
    // a.queryRange(8,74);
    // a.queryRange(15,53);
    // a.addRange(44,85);
    // a.addRange(10,71);
    // a.queryRange(54,70);
    // a.removeRange(10,45);
    // a.queryRange(30,66);
    // a.addRange(47,98);
    // a.queryRange(1,7);
    // a.removeRange(44,78);
    // a.removeRange(31,49);
    // a.addRange(62,63);
    // a.addRange(49,88);
    // a.removeRange(47,72);
    // a.removeRange(8,50);
    // a.removeRange(49,79);
    // a.addRange(31,47);
    // a.addRange(54,87);
    // a.queryRange(77,78);
    // a.queryRange(59,100);
    // a.queryRange(8,9);
    // a.queryRange(50,51);
    // a.queryRange(67,93);
    // a.removeRange(25,86);
    // a.removeRange(8,92);
    // a.queryRange(31,87);
    // a.addRange(90,95);
    // a.addRange(28,56);
    // a.addRange(10,42);
    // a.queryRange(27,34);
    // a.addRange(75,81);
    // a.addRange(17,63);
    // a.removeRange(78,90);
    // a.addRange(9,18);
    // a.queryRange(51,74);
    // a.removeRange(20,54);
    // a.addRange(35,72);
    // a.queryRange(2,29);
    // a.addRange(28,41);
    // a.addRange(17,95);
    // a.addRange(73,75);
    // a.queryRange(34,43);
    // a.addRange(57,96);
    // a.queryRange(51,72);
    // a.removeRange(21,67);
    // a.removeRange(40,73);
    // a.removeRange(14,26);
    // a.removeRange(71,86);
    // a.queryRange(34,41);
    // a.removeRange(10,25);
    // a.queryRange(27,68);
    // a.queryRange(18,32);
    // a.removeRange(30,31);
    // a.queryRange(45,61);
    // a.addRange(64,66);
    // a.addRange(18,93);
    // a.queryRange(13,21);
    // a.removeRange(13,46);
    // a.removeRange(56,99);
    // a.queryRange(6,93);
    // a.addRange(25,36);
    // a.removeRange(27,88);
    // a.removeRange(82,83);
    // a.addRange(30,71);
    // a.addRange(31,73);
    // a.addRange(10,41);
    // a.queryRange(71,72);
    // a.queryRange(9,56);
    // a.addRange(22,76);
    // a.queryRange(38,74);
    // a.removeRange(2,77);
    // a.queryRange(33,61);
    // a.removeRange(74,75);
    // a.addRange(11,43);
    // a.queryRange(27,75);
    return 0;
}