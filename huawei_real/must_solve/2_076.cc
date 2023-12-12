/*
从一个N*M（N<=M)的矩阵中选出N个数，任意两个数字不能在同一行或同一列
求选出来的N个数中第K大的数字的最小值是多少。
*/

/**
 * 选N个数，即每行选一个数
 * 第K大的数字，即倒数第N-K小的数
 * 如果整个矩阵最小的N-K个数不同行、不同列，排序后第N-K即最优解
 * 
 * 如果暴力枚举
 * 则有M^N个数列需要判断
 * 为了缩减时间，采取贪心策略:
 * 每一行的数，应有一个排序序列，然后利用归并的思想
 * 1. 每次选取头节点最小的行，取其头节点占位
 * 2. 如果位置已经被占，因为已经占位的数字更小，该行排序序列下移一位，并跳至步骤1
*/
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include "common.h"
using namespace std;

class LineOrder
{
public:
    int i;
    int *phead;
    vector<pair<int,int>> *pv;
    vector<pair<int,int>>::iterator it;

    LineOrder():i(-1),pv(nullptr),phead(nullptr) {}
    LineOrder(int i, vector<pair<int,int>> &v, int *adv):i(i)
    {
        pv = &v;
        phead = adv;
        it = v.begin();
        advance(it, *adv);
    }

    bool operator ()(const LineOrder *a, const LineOrder *b) const
    {
        return a->it->first < b->it->first;
    }

    bool finished()
    {
        return it == pv->end();
    }

    void forward()
    {
        if (!finished())
        {
            ++it;
            (*phead)++;
        }
    }

    int pos()
    {
        return it->second;
    }

    int value()
    {
        return it->first;
    }
};

void dfs(vector<vector<pair<int,int>>> &orders, 
    int N, int M, int idx, vector<bool> &visited, vector<int> heads, vector<int> &result, int &fresult, int K)
{
    // if (idx >= N || idx >= K)
    if (idx >= N)
    {
        // SHOW(visited, M);
        // SHOW(heads, N);
        SHOW(result, idx);
        // cout << "------" << endl;

        if (result[K-1] < fresult)
        {
            fresult = result[K-1];
        }
        return;
    }

    // 解决 result[idx] = ?

    vector<LineOrder> lines;
    for (int i = 0; i < N; ++i)
    {
        lines.emplace_back(i, orders[i], &heads[i]);
    }

    priority_queue<LineOrder *, vector<LineOrder *>, LineOrder> targets;
    for (int i = 0; i < N; ++i)
    {
        if (!lines[i].finished())
        {
            targets.push(&lines[i]);
        }
    }

    while (!targets.empty())
    {
        LineOrder *pline = targets.top();
        while (visited[pline->pos()])
        {
            targets.pop();
            pline->forward();
            if (pline->finished()) return;
            targets.push(pline);
            pline = targets.top();
        }
        targets.pop();

        result.push_back(pline->value());
        visited[pline->pos()] = true;
        heads[pline->i] = M;    // 这一行结束

        dfs(orders, N, M, idx+1, visited, heads, result, fresult, K);
        
        heads[pline->i] = distance(pline->pv->begin(), pline->it);

        visited[pline->pos()] = false;
        result.pop_back();

        pline->forward();
        if (pline->finished()) return;
        targets.push(pline);
    }

}

void start(vector<vector<int>> &nums, int N, int M, int K)
{
    vector<int> result;                 // 结果数组
    vector<bool> visited(M, false);     // 列是否被占用

    vector<int> heads(N, 0);            // 每行遍历的起点

    vector<vector<pair<int,int>>> orders(N, vector<pair<int,int>>(M));   // 排序后的数字
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            orders[i][j].first = nums[i][j];
            orders[i][j].second = j;
        }
        sort(orders[i].begin(), orders[i].end(), [](const pair<int, int> &a, const pair<int, int> &b)
        {
            return a.first > b.first;
        });
    }

    int fresult = MAX_INT;
    dfs(orders, N, M, 0, visited, heads, result, fresult, K);
    cout << fresult << endl;
}

int main(int argc, char *argv[])
{
    int N, M, K;
    while (cin >> N >> M >> K)
    {
        vector<vector<int>> nums(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                cin >> nums[i][j];
            }
        }
        start(nums, N, M, K);
    }
    return 0;
}
