/*
请设计一个文件缓存系统，该文件缓存系统可以指定缓存的最大值（单位为字节）。

文件缓存系统有两种操作：存储文件(put)和读取文件(get)

操作命令为put fileName fileSize或者get fileName

存储文件是把文件放入文件缓存系统中；读取文件是从文件缓存系统中访问已存在的文件，如果文件不存在，则不作任何操作。

当缓存空间不足以存放新的文件时，根据规则删除文件，直到剩余空间满足新的文件大小为止，再存放新文件。
具体的删除规则为：
文件访问过后，会更新文件的最近访问时间和总的访问次数

**当缓存不够时，按照第一优先顺序为访问次数从少到多，第二顺序为时间从老到新的方式来删除文件***
*/

// LFU 回收

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include <deque>
using namespace std;

class CacheNode
{
public:
    string filename;
    int filesize;
    int cnt;
    CacheNode *prev;
    CacheNode *next;
    CacheNode():filename(""),filesize(0),cnt(0),prev(nullptr),next(nullptr) {}
    CacheNode(const char *filename, int filesize):filename(filename),filesize(filesize),cnt(0),prev(nullptr),next(nullptr) {}
};

class CacheHead
{
    CacheNode *m_pHead;
    CacheNode *m_pTail;
    deque<int> m_maxSize;

public:
    CacheHead():m_pHead(nullptr), m_pTail(nullptr) {}

    int get_maxsize()
    {
        if (m_maxSize.empty()) return 0;
        return *m_maxSize.begin();
    }

    void push_back(CacheNode *pnode)
    {
        while (!m_maxSize.empty() && m_maxSize.back() < pnode->filesize)
        {
            m_maxSize.pop_back();
        }
        m_maxSize.push_back(pnode->filesize);       // 递减：小于或等于

        if (m_pTail)
        {
            m_pTail->next = pnode;
            pnode->prev = m_pTail;
            pnode->next = nullptr;
            m_pTail = pnode;
        }
        else
        {
            m_pHead = m_pTail = pnode;
        }
    }

    void remove(CacheNode *pnode)
    {
        if (!m_maxSize.empty() && *m_maxSize.begin() == pnode->filesize)
        {
            m_maxSize.pop_front();
        }

        if (pnode->prev)
        {
            pnode->prev->next = pnode->next;
        }
        else
        {
            m_pHead = pnode->next;
        }

        if (pnode->next)
        {
            pnode->next->prev = pnode->prev;
        }
        else
        {
            m_pTail = pnode->prev;
        }

        pnode->prev = nullptr;
        pnode->next = nullptr;
    }

    CacheNode *recycle(int filesize)
    {
        if (get_maxsize() < filesize) return nullptr;

        CacheNode *pnode = m_pHead;
        while (pnode)
        {
            if (pnode->filesize >= filesize)
            {
                remove(pnode);
                return pnode;
            }
            pnode = pnode->next;
        }
        return nullptr;
    }

    void show(int idx)
    {
        if (m_pHead == nullptr) return;
        printf("[%3d]--------\n", idx);
        CacheNode *pnode = m_pHead;
        while (pnode)
        {
            cout << pnode->filename << " " << pnode->filesize << endl;
            pnode = pnode->next;
        }
    }
};

class FileCache
{
    int m_capacity;
    int m_used;
    map<int, CacheHead> m_order;
    unordered_map<string, CacheNode> m_data;

    bool recycle(int filesize)
    {
        for (map<int, CacheHead>::iterator it = m_order.begin(); it != m_order.end(); ++it)
        {
            CacheHead &head = it->second;
            CacheNode *pnode = head.recycle(filesize);
            if (pnode)
            {
                m_used -= pnode->filesize;
                m_data.erase(pnode->filename);
                return true;
            }
        }
        return false;
    }

public:
    FileCache(int capacity)
    {
        m_capacity = capacity;
        m_used = 0;
    }

    void put(const char *filename, int filesize)
    {
        CacheNode *pnode = get(filename);
        if (pnode != nullptr) return;

        if (m_capacity - m_used < filesize)
        {
            if (!recycle(filesize - (m_capacity - m_used)))
            {
                cout << "ERROR" << endl;
                return;
            }
        }

        pnode = &m_data[filename];
        pnode->filename = filename;
        pnode->filesize = filesize;
        m_order[pnode->cnt].push_back(pnode);
        m_used += filesize;
    }

    CacheNode *get(const char *filename)
    {
        unordered_map<string, CacheNode>::iterator it = m_data.find(filename);
        if (it == m_data.end()) return nullptr;

        CacheNode *pnode = &it->second;
        m_order[pnode->cnt].remove(pnode);
        m_order[++pnode->cnt].push_back(pnode);

        return pnode;
    }

    void show()
    {
        cout << m_capacity << " " << m_used << ":" << endl;
        for (map<int, CacheHead>::iterator it = m_order.begin(); it != m_order.end(); ++it)
        {
            it->second.show(it->first);
        }
    }
};


int main(int argc, char *argv[])
{
    int n;
    int filesize;
    string cmd;
    string filename;

    while (cin >> n)
    {
        FileCache sys(n);
        while (cin >> cmd)
        {
            if (cmd == "put")
            {
                cin >> filename >> filesize;
                sys.put(filename.c_str(), filesize);
            }
            else if (cmd == "get")
            {
                cin >> filename;
                CacheNode *pnode = sys.get(filename.c_str());
                if (pnode)
                {
                    cout << pnode->filename << " " << pnode->filesize << " " << pnode->cnt << endl;
                }
                else
                {
                    cout << "null" << endl;
                }
            }
            else if (cmd == "show")
            {
                sys.show();
            }
        }
    }
    return 0;
}
