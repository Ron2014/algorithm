/*
项目组共有N个开发人员，项目经理接到了M个独立的需求，每个需求的工作量不同，且每个需求只能由一个开发人员独立完成，不能多人合作。
假定各个需求直接无任何先后依赖关系，请设计算法帮助项目经理进行工作安排，使整个项目能用最少的时间交付。
*/

/**
 * 贪心
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

class Node
{
public:
    int num;
    vector<int> list;
    Node():num(0) {}

    // 如果集合元素为指针，需要借助函数对象排序
    bool operator () (const Node *a, const Node *b) const
    {
        return a->num > b->num;
    }
};

int main(int argc, char *argv[])
{
    int N, M;
    while (cin >> N >> M)
    {
        vector<int> req(M);
        for (int i = 0; i < M; ++i)
        {
            cin >> req[i];
        }
        sort(req.begin(), req.end(), greater<int>());

        vector<Node> devs(N);

        priority_queue<Node *, vector<Node *>, Node> dispatcher;
        for (int i = 0; i < N; ++i)
        {
            dispatcher.push(&devs[i]);
        }

        cout << dispatcher.size() << endl;

        for (const int &r : req)
        {
            Node *pnode = dispatcher.top();
            dispatcher.pop();

            cout << pnode->num << endl;
            pnode->list.push_back(r);
            pnode->num += r;

            dispatcher.push(pnode);
        }

        int maxr = -1;
        for (int i = 0; i < N; ++i)
        {
            cout << i << " " << devs[i].num << " [ ";
            for (const int &r: devs[i].list) cout << r << " ";
            cout << "]" << endl;
            if (devs[i].num > maxr) maxr = devs[i].num;
        }
        cout << maxr << endl;

        // int sum = 0;
        // for (const int &r: req) sum += r;
        // int avg = sum / N;
        // if (sum % N > 0) avg++;
    }
    return 0;
}