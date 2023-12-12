/*
你驾驶出租车行驶在一条有 n 个地点的路上。这 n 个地点从近到远编号为 1 到 n ，你想要从 1 开到 n ，通过接乘客订单盈利。

你只能沿着编号递增的方向前进，不能改变方向。

乘客信息用一个下标从 0 开始的二维数组 rides 表示，其中 rides[i] = [starti, endi, tipi] 表示第 i 位乘客需要从地点 starti 前往 endi ，愿意支付 tipi 元的小费。

每一位 你选择接单的乘客 i ，你可以 盈利 endi - starti + tipi 元。你同时 最多 只能接一个订单。

给你 n 和 rides ，请你返回在最优接单方案下，你能盈利 最多 多少元。

注意：你可以在一个地点放下一位乘客，并在同一个地点接上另一位乘客。

示例 1：

输入：n = 5, rides = [[2,5,4],[1,5,1]]
输出：7
解释：我们可以接乘客 0 的订单，获得 5 - 2 + 4 = 7 元。

示例 2：

输入：n = 20, rides = [[1,6,1],[3,10,2],[10,12,3],[11,12,2],[12,15,2],[13,18,1]]
输出：20
解释：我们可以接以下乘客的订单：
- 将乘客 1 从地点 3 送往地点 10 ，获得 10 - 3 + 2 = 9 元。
- 将乘客 2 从地点 10 送往地点 12 ，获得 12 - 10 + 3 = 5 元。
- 将乘客 5 从地点 13 送往地点 18 ，获得 18 - 13 + 1 = 6 元。
我们总共获得 9 + 5 + 6 = 20 元。
*/

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>> &rides) {
        // 从 1 到 n，每个位置可以选择接或者不接
        unordered_map<int, vector<pair<int, int>>> mp;
        for (const vector<int> &v : rides)
        {
            int start = v[0];
            int end = v[1];
            int tips = v[2];
            mp[end].emplace_back(start, end - start + tips);
        }
        vector<long long> money(n+1, 0);        // momey[i] 到达i点，最多挣的钱
        long long last = 0;
        for (int i = 0; i <= n; ++i)
        {
            money[i] = last;
            const vector<pair<int, int>> &choises = mp[i];
            for (const auto &q : choises)
            {
                money[i] = max(money[i], money[q.first] + q.second);
            }
            last = money[i];
        }
        return last;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n, r;
    while (cin >> n >> r)
    {
        vector<vector<int>> rides(r, vector<int>(3));
        getchar();
        for (int i = 0; i < r; ++i)
        {
            scanf("[%d,%d,%d],", &rides[i][0], &rides[i][1], &rides[i][2]);
        }
        cout << s.maxTaxiEarnings(n, rides) << endl;
    }
    return 0;
}