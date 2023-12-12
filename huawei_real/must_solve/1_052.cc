/*
给定两个整数数组array1、array2，数组元素按升序排列。
假设从array1、array2中分别取出一个元素可构成一对元素，现在需要取出k对元素，并对取出的所有元素求和，计算和的最小值
注意：两对元素如果对应于array1、array2中的两个下标均相同，则视为同一对元素。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Node
{
public:
    int i;
    int j;
    int num;
    Node():i(-1),j(-1),num(0) {}
    Node(int i, int j, int num):i(i),j(j),num(num) {}

    bool operator < (const Node &o) const
    {
        return num > o.num;
    }
};

int main(int argc, char *argv[])
{
    int n, m, k;
    while (cin >> n >> m >> k)
    {
        vector<int> array1(n), array2(m);
        for (int i = 0; i < n; ++i)
        {
            cin >> array1[i];
        }
        for (int i = 0; i < m; ++i)
        {
            cin >> array2[i];
        }
        sort(array1.begin(), array1.end());
        sort(array2.begin(), array2.end());
        
        priority_queue<Node> all;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                all.emplace(i, j, array1[i] + array2[j]);
            }
        }

        int sum = 0;
        for (int i = 0; i < k; ++i)
        {
            const Node &node = all.top();
            cout << node.i << " " << node.j << " " << node.num << endl;
            sum += node.num;
            all.pop();
        }
        cout << sum << endl;
    }
    return 0;
}