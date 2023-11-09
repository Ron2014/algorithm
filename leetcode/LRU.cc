#include <list>
#include <map>
#include <algorithm>
using namespace std;


class LRUCache {
public:
    LRUCache(int capacity) {
        m_iCap = capacity;
        m_map.clear();
        m_list.clear();
    }
    
    int get(int key) {
        list<int>::iterator it = find(m_list.begin(), m_list.end(), key);
        if (it != m_list.end())
        {
            m_list.erase(it);
            m_list.push_back(key);
            return m_map[key];
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
                int last_key = m_list.front();
                m_list.pop_front();
                m_map.erase(last_key);
            }
            m_list.push_back(key);
        }
        m_map[key] = value;
    }

private:
    int m_iCap;
    map<int, int> m_map;
    list<int> m_list;
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