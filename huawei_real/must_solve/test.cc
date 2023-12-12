#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int i;
    Node(int i):i(i) {}
    bool operator < (const Node &other) const { return i > other.i; }
};

bool customComparator(int a, int b) {
    return a < b; // 返回 true，如果 a 应该排在 b 之前
}

int main(int argc, char *argv[])
{
    priority_queue<Node> q;
    q.emplace(0);
    q.emplace(1);
    q.emplace(2);
    while (!q.empty())
    {
        cout << q.top().i << endl;
        q.pop();
    }

    std::vector<int> nums = {5, 2, 8, 3, 1, 6};
    std::sort(nums.begin(), nums.end(), customComparator);
    for (int &num : nums)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}