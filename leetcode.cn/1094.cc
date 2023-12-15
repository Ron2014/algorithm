/*
1094. 拼车
车上最初有 capacity 个空座位。车只能向一个方向行驶（也就是说，不允许掉头或改变方向）
给定整数 capacity 和一个数组 trips
trip[i] = [numPassengersi, fromi, toi] 表示第 i 次旅行有 numPassengersi 乘客，接他们和放他们的位置分别是 fromi 和 toi 。
这些位置是从汽车的初始位置向东的公里数。
当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。

示例 1：

输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false
示例 2：

输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true

提示：

1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengersi <= 100
0 <= fromi < toi <= 1000
1 <= capacity <= 10^5
*/

#include "common.h"

class Station
{
public:
    int up;
    int down;
    Station():up(0),down(0) {}
};

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        map<int, Station> stations;
        for (const auto &node : trips)
        {
            int num = node[0], from = node[1], to = node[2];
            stations[from].up += num;
            stations[to].down += num;
        }
        int free_num = capacity; // 空座位
        for (const auto &p: stations)
        {
            const Station &s = p.second;
            printf("[%d]:%d,%d\n", p.first, s.down, s.up);
            free_num += s.down;
            if (free_num < s.up)
            {
                return false;
            }
            free_num -= s.up;
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int n, cap;
    while (cin >> n >> cap)
    {
        vector<vector<int>> trips(n, vector<int>(3));
        for (int i = 0; i < n; ++i)
        {
            cin >> trips[i][0] >> trips[i][1] >> trips[i][2];
        }
        printf("%d\n", (int)s.carPooling(trips, cap));
    }
}