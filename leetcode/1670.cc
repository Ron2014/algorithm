/*
1670. 设计前中后队列
请你设计一个队列，支持在前，中，后三个位置的 push 和 pop 操作。

请你完成 FrontMiddleBack 类：

FrontMiddleBack() 初始化队列。
void pushFront(int val) 将 val 添加到队列的 最前面 。
void pushMiddle(int val) 将 val 添加到队列的 正中间 。
void pushBack(int val) 将 val 添加到队里的 最后面 。
int popFront() 将 最前面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
int popMiddle() 将 正中间 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
int popBack() 将 最后面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
请注意当有 两个 中间位置的时候，选择靠前面的位置进行操作。比方说：

将 6 添加到 [1, 2, 3, 4, 5] 的中间位置，结果数组为 [1, 2, 6, 3, 4, 5] 。
从 [1, 2, 3, 4, 5, 6] 的中间位置弹出元素，返回 3 ，数组变为 [1, 2, 4, 5, 6] 。
 

示例 1：

输入：
["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
[[], [1], [2], [3], [4], [], [], [], [], []]
输出：
[null, null, null, null, null, 1, 3, 4, 2, -1]

解释：
FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [1]
q.pushBack(2);    // [1, 2]
q.pushMiddle(3);  // [1, 3, 2]
q.pushMiddle(4);  // [1, 4, 3, 2]
q.popFront();     // 返回 1 -> [4, 3, 2]
q.popMiddle();    // 返回 3 -> [4, 2]
q.popMiddle();    // 返回 4 -> [2]
q.popBack();      // 返回 2 -> []
q.popFront();     // 返回 -1 -> [] （队列为空）
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class FrontMiddleBackQueue {
    deque<int> m_front;
    deque<int> m_back;

    void normalize()
    {
        if (m_front.size() > m_back.size())
        {
            m_back.push_front(m_front.back());
            m_front.pop_back();
        }
        if (m_back.size() > m_front.size() + 1)
        {
            m_front.push_back(m_back.front());
            m_back.pop_front();
        }
    }

public:
    FrontMiddleBackQueue() {

    }

    void show()
    {
        cout << "f:";
        for (auto it = m_front.begin(); it != m_front.end(); ++it)
        {
            printf("%d ", *it);
        }
        cout << endl << "b:";
        for (auto it = m_back.begin(); it != m_back.end(); ++it)
        {
            printf("%d ", *it);
        }
        cout << endl;
    }
    
    void pushFront(int val) {
        m_front.push_front(val);
        normalize();
    }
    
    void pushMiddle(int val) {
        m_front.push_back(val);
        normalize();
    }
    
    void pushBack(int val) {
        m_back.push_back(val);
        normalize();
    }
    
    int popFront() {
        int ret = -1;
        if (!m_back.empty())
        {
            if (m_front.empty())
            {
                ret = m_back.front();
                m_back.pop_front();
            }
            else
            {
                ret = m_front.front();
                m_front.pop_front();
            }
            normalize();
        }
        return ret;
    }
    
    int popMiddle() {
        int ret = -1;
        if (!m_back.empty())
        {
            if (m_back.size() > m_front.size())
            {
                ret = m_back.front();
                m_back.pop_front();
            }
            else
            {
                ret = m_front.back();
                m_front.pop_back();
            }
        }
        return ret;
    }
    
    int popBack() {
        int ret = -1;
        if (!m_back.empty())
        {
            ret = m_back.back();
            m_back.pop_back();
            normalize();
        }
        return ret;
    }
};

int main(int argc, char *argv[])
{
    FrontMiddleBackQueue *q = new FrontMiddleBackQueue();
    q->pushFront(1);   // [1]
    q->show();
    q->pushBack(2);    // [1, 2]
    q->show();
    q->pushMiddle(3);  // [1, 3, 2]
    q->show();
    q->pushMiddle(4);  // [1, 4, 3, 2]
    q->show();
    q->popFront();     // 返回 1 -> [4, 3, 2]
    q->popMiddle();    // 返回 3 -> [4, 2]
    q->popMiddle();    // 返回 4 -> [2]
    q->popBack();      // 返回 2 -> []
    q->popFront();     // 返回 -1 -> [] （队列为空）
    return 0;
}
