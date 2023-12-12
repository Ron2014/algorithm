/*
请实现一个简易内存池,根据请求命令完成内存分配和释放。
内存池支持两种操作命令，REQUEST和RELEASE，其格式为：
REQUEST=请求的内存大小 表示请求分配指定大小内存，如果分配成功，返回分配到的内存首地址；如果内存不足，或指定的大小为0，则输出error。
RELEASE=释放的内存首地址 表示释放掉之前分配的内存，释放成功无需输出，如果释放不存在的首地址则输出error。
注意：
1.内存池总大小为100字节。
2.内存池地址分配必须是连续内存，并优先从低地址分配。
3.内存释放后可被再次分配，已释放的内存在空闲时不能被二次释放。
4.不会释放已申请的内存块的中间地址。
5.释放操作只是针对首地址所对应的单个内存块进行操作，不会影响其它内存块。
*/

#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

class MemPool
{
    void *m_head;
    int m_capacity;
    map<int, int> m_used;

public:
    MemPool(int capacity)
    {
        m_head = malloc(capacity);
        m_capacity = capacity;
    }
    ~MemPool()
    {
        free(m_head);
        m_head = nullptr;
    }

    void *request(int n)
    {
        void *ret = nullptr;
        do
        {
            if (n <= 0 || n > m_capacity)
            {
                break;
            }

            int gap;
            if (m_used.size() > 0)
            {
                map<int, int>::iterator it, it1;
                it = it1 = m_used.begin();
                ++it1;
                while (it != m_used.end())
                {
                    if (it1 != m_used.end())
                    {
                        gap = it1->first - (it->first + it->second);
                    }
                    else
                    {
                        gap = m_capacity - (it->first + it->second);
                    }
                    if (gap >= n)
                    {
                        ret = (void *)((size_t)m_head + it->first + it->second);
                        m_used[it->first + it->second] = n;
                        break;
                    }
                    ++it;
                    ++it1;
                }
            }
            else
            {
                ret = m_head;
                m_used[0] = n;
            }

            if (ret == nullptr)
            {
                break;
            }

            return ret;
        } while (0);

        cerr << "error" << endl;
        return ret;
    }

    void release(int offset)
    {
        release((void *)((size_t)m_head + offset));
    }

    void show()
    {
        for (auto it = m_used.begin(); it != m_used.end(); ++it)
        {
            cout << it->first << " " << it->second << endl;
        }
    }
    
    void release(void *mem)
    {
        do
        {
            if (mem == nullptr)
            {
                break;
            }
            ssize_t offset = (ssize_t)(mem) - (ssize_t)m_head;
            if (offset < 0 || offset >= m_capacity)
            {
                break;
            }
            map<int, int>::iterator it = m_used.find(offset);
            if (it == m_used.end())
            {
                break;
            }

            // release succ
            m_used.erase(it);
            return;
        } while (0);
        
        cerr << "error" << endl;
    }
};

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        MemPool mp(n);

        string cmd;
        while (cin >> cmd)
        {
            if (cmd == "show")
            {
                mp.show();
            }
            else if (cmd == "new")
            {
                int n;
                cin >> n;
                mp.request(n);
            }
            else if (cmd == "del")
            {
                int n;
                cin >> n;
                mp.release(n);
            }
            else if (cmd == "quit")
            {
                return 0;
            }
        }
    }
    return 0;
}