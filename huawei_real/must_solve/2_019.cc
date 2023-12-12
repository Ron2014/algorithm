/*
有一个总空间为100字节的堆，现要从中新申请一块内存，内存分配原则为优先[紧接着前一块已使用内存分配空间]足够且最接近申请大小的空闲内存。
*/

#include <iostream>
#include <map>
using namespace std;

class Solution
{
    int m_capacity;
    void *m_heap;
    map<int, int> m_used;

public:
    Solution()
    {
        m_capacity = 100;
        m_heap = malloc(m_capacity);
    }

    ~Solution()
    {
        free(m_heap);
        m_heap = nullptr;
    }

    void *get(int n)
    {
        if (n <= 0)
        {
            cerr << "invalid len: " << n << endl;
            return nullptr;
        }

        if (m_used.empty())
        {
            if (n > m_capacity)
            {
                cerr << "too large: " << n << endl;
                return nullptr;
            }
            m_used[0] = n;
            return m_heap + 0;
        }
        else
        {
            // bug_found: 通过freelist加速查找
            int tail = m_capacity;
            map<int,int>::reverse_iterator it = m_used.rbegin();
            while (tail - (it->first + it->second) < n && it != m_used.rend())
            {
                tail = it->first;
                ++it;
            }
            if (it == m_used.rend())
            {
                cerr << "too large: " << n << endl;
                return nullptr;
            }
            m_used[it->first + it->second] = n;
            return m_heap + it->first + it->second;
        }

        cerr << "get fail: " << n << endl;
        return nullptr;
    }

    void show()
    {
        for (map<int, int>::iterator it = m_used.begin(); it != m_used.end(); ++it)
        {
            cout << it->first << " " << it->second << endl;
        }
    }

    void release(void *memory)
    {
        release((size_t)memory - (size_t)m_heap);
    }

    void release(int idx)
    {
        map<int,int>::iterator it = m_used.find(idx);
        if (it != m_used.end())
        {
            m_used.erase(it);
        }
        else
        {
            cerr << "error idx: " << idx << endl;
        }
    }
};

int main(int argc, char *argv[])
{
    Solution s;

    string op;
    int n;
    while (cin >> op)
    {
        if (op == "quit")
        {
            break;
        }
        if (op == "get")
        {
            cin >> n;
            s.get(n);
        }
        else if (op == "release")
        {
            cin >> n;
            s.release(n);
        }
        else if (op == "show")
        {
            s.show();
        }

    }
    return 0;
}