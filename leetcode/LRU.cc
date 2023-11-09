#include <map>
#include <iostream>
using namespace std;
typedef struct tagDLinkNode
{
    int key;
    int val;
    tagDLinkNode *prev;
    tagDLinkNode *next;
} DLinkNode;

class DLink
{
public:
    DLink()
    {
        m_pHead = NULL;
        m_pTail = NULL;
    }

    int pop_front()
    {
        // 淘汰链头
        if (m_pHead)
        {
            DLinkNode *pNode = m_pHead;           
            remove(pNode);
            return pNode->key;
        }
        return -1;
    }

    void push_back(DLinkNode *pNode)
    {
        // 最新访问插入链尾
        if (!pNode) return;
        if (m_pTail)
        {
            m_pTail->next = pNode;
        }
        else
        {
            m_pHead = pNode;
        }
        pNode->prev = m_pTail;
        pNode->next = NULL;
        m_pTail = pNode;
    }

    void remove(DLinkNode *pNode)
    {
        if (!pNode) return;
        if (pNode->prev)
        {
            pNode->prev->next = pNode->next;
        }
        if (pNode->next)
        {
            pNode->next->prev = pNode->prev;
        }
        if (m_pHead == pNode)
        {
            m_pHead = pNode->next;
        }
        if (m_pTail == pNode)
        {
            m_pTail = pNode->prev;
        }
        pNode->prev = NULL;
        pNode->next = NULL;
    }
private:
    DLinkNode *m_pHead;
    DLinkNode *m_pTail;
};

class LRUCache {
public:
    LRUCache(int capacity) {
        m_iCap = capacity;
        m_map.clear();
    }
    
    int get(int key) {
        map<int, DLinkNode>::iterator it = m_map.find(key);
        if (it != m_map.end())
        {
            m_dlink.remove(&it->second);
            m_dlink.push_back(&it->second);
            return it->second.val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (m_iCap <= 0)
        {
            return;
        }
        int old_val = get(key);
        if (old_val < 0)
        {
            if (m_iCap <= m_map.size())
            {
                int last_key = m_dlink.pop_front();
                m_map.erase(last_key);
            }
            DLinkNode &stNode = m_map[key];
            stNode.key = key;
            m_dlink.push_back(&stNode);
        }
        m_map[key].val = value;
    }

private:
    int m_iCap;
    map<int, DLinkNode> m_map;      // map 存放数据
    DLink m_dlink;                  // dlink 双链记录访问顺序
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(int argc, char *argv[])
{
    LRUCache lRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    // lRUCache.get(1);    // 返回 1
    // lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    // lRUCache.get(2);    // 返回 -1 (未找到)
    // lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    // lRUCache.get(1);    // 返回 -1 (未找到)
    // lRUCache.get(3);    // 返回 3
    // lRUCache.get(4);    // 返回 4
    return 0;
}