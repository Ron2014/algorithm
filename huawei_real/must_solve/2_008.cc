/*
攀登者喜欢寻找各种地图，并且尝试攀登到最高的山峰。

地图表示为一维数组，数组的索引代表水平位置，数组的高度代表相对海拔高度。其中数组元素0代表地面。

例如[0,1,2,4,3,1,0,0,1,2,3,1,2,1,0], 代表如下图所示的地图
地图中有两个山脉位置分别为 1,2,3,4,5 和 8,9,10,11,12,13，最高峰高度分别为4,3。最高峰位置分别为3,10。
一个山脉可能有多座山峰(高度大于两边，或者在地图边界)。

               4 
             +---+ 
             |   | 
             |   | 3                       3 
             |   | 
             |   +---+                   ----- 
             |       |                   |   | 
           2 |       |                 2 |   |     2 
             |       |                   |   | 
         +---+       |               ----+   |   +---+ 
         |           |               |       |   |   | 
       1 |           | 1           1 |       | 1 |   | 1 
         |           |               |       |   |   | 
     +---+           +---+       +---+       +---+   +---+ 
     |                   |       |                       | 
   0 |                   | 0   0 |                       | 0 
     |                   |       |                       | 
 +---+                   +-------+                       +---+ 
 
   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
   
2. 登山时会消耗登山者的体力(整数)，上山时，消耗相邻高度差两倍的体力，下坡时消耗相邻高度差一倍的体力，平地不消耗体力，登山者体力消耗到零时会有生命危险。
    例如，上图所示的山峰，从索引0，走到索引1，高度差为1，需要消耗2x1=2的体力，从索引2高度2走到高度4索引3需要消耗2x2=4的体力。
    如果是从索引3走到索引4则消耗1x1的体力。
3. 登山者体力上限为999。
4. 登山时的起点和终点可以是地图中任何高度为0的地面。例如上图中的0,6,7,14 都可以作为登山的起点和终点

    攀登者想要评估一张地图内有多少座山峰可以进行攀登，且可以安全返回到地面，且无生命危险。

    例如上图中的数组，有3个不同的山峰
    登上位置在3的山可以从位置0或者位置6开始，从位置0登到山顶需要消耗体力1x2+1x2+2x2=8, 从山顶返回到地面0需要消耗体力2X1+1X1+1X1=4的体力
    按照登山路线0->3->0需要消耗体力12。攀登者至少需要12以上的体力（大于12）才能安全返回
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define SHOW(a, n)                \
    for (int q = 0; q < (n); ++q) \
    {                             \
        printf("%2d ", (a)[q]);   \
    }                             \
    cout << endl;

#define SHOW_M(a, n, m)                \
    for (int q = 0; q < (n); ++q)      \
    {                                  \
        for (int p = 0; p < (m); ++p)  \
        {                              \
            printf("%2d ", (a)[q][p]); \
        }                              \
        cout << endl;                  \
    }

#define IS_TOP(heights, i) \
    (i == 0 || heights[i] > heights[i - 1]) && (i == heights.size() - 1 || heights[i] > heights[i + 1])

class Node
{
public:
    int pos;    // 所在位置
    int hp;     // 剩余体力 
    int cnt;    // 爬过的山峰
    int step;   // 步数

    Node():pos(-1),hp(0),cnt(0),step(0) {}
    Node(int p, int h, int c, int s)
    {
        pos = p;
        hp = h;
        cnt = c;
        step = s;
    }
};

int main(int argc, char *argv[])
{
    int n, HP;
    while (cin >> n)
    {
        // 对同一个高度去重
        vector<int> heights;
        for (int i = 0; i < n; ++i)
        {
            int h;
            cin >> h;
            // if (heights.empty() || heights[heights.size()-1] != h)
            // {
                heights.push_back(h);
            // }
        }
        cin >> HP;
        n = heights.size();

        // cost[i][j], i走到j的消耗
        vector<vector<int>> cost(n, vector<int>(n));
        // ground[i], 地面的坐标
        vector<int> ground, marks;
        for (int i = 0; i < n; ++i)
        {
            if (heights[i] == 0)
            {
                cost[i][i] = 0;
                ground.push_back(i);
                marks.push_back(i);
            }
            if (IS_TOP(heights, i))
            {
                marks.push_back(i);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = i+1; j < n; ++j)
            {
                // 往右
                if (heights[j] >= heights[j-1])
                {
                    cost[i][j] = cost[i][j-1] + (heights[j] - heights[j-1]) * 2;
                }
                else
                {
                    cost[i][j] = cost[i][j-1] + (heights[j-1] - heights[j]);
                }
            }

            for (int j = i-1; j >= 0; --j)
            {
                // 往左
                if (heights[j] >= heights[j+1])
                {
                    cost[i][j] = cost[i][j+1] + (heights[j] - heights[j+1]) * 2;
                }
                else
                {
                    cost[i][j] = cost[i][j+1] + (heights[j+1] - heights[j]);
                }
            }
        }
        SHOW_M(cost, n, n);
        SHOW(ground, ground.size());
        SHOW(marks, marks.size());

        int maxn = -1;
        int m = marks.size();
        vector<int> left_tops(m);
        int left_len = 0;
        for (int i = 0; i < m; ++i)
        {
            int spos = marks[i];
            if (heights[spos] != 0)
            {
                left_tops[left_len++] = spos;
                continue;
            }

            int must_num = 0;
            for (int j = i; j < m; ++j)
            {
                int epos = marks[j];
                if (heights[epos] != 0)
                {
                    must_num++;
                    continue;
                }

                // spos -> epos 最少要保留的体力，必爬过的山头
                int must_cost = cost[spos][epos];
                if (must_cost > HP) break;
                if (must_cost > maxn)
                {
                    maxn = must_num;
                }

                // 以spos向左能爬的最多的体力
                // 以epos向右能爬的最多的体力
                int left_cost = HP - must_cost;
                if (left_cost <= 0) continue;

                for (int k = left_len - 1; k >= 0; --k)
                {
                    // 取左边最远
                    if (cost[spos][left_tops[k]] + cost[left_tops[k]][spos] > left_cost)
                    {
                        break;
                    }
                    if (must_num + left_len - k > maxn)
                    {
                        maxn = must_num + left_len - k;
                    }
                }

                int left_len_bak = left_len;

                for (int k = j + 1; k < m; ++k)
                {
                    if (heights[marks[k]] > 0)
                    {
                        left_tops[left_len++] = marks[k];
                        // 取右边最远
                        if (cost[epos][marks[k]] + cost[marks[k]][epos] > left_cost)
                        {
                            continue;
                        }
                        if (must_num + left_len - left_len_bak > maxn)
                        {
                            maxn = must_cost + left_len - left_len_bak;
                        }
                    }
                }

                int l = 0, r = left_len - 1;
                while (l < r && left_tops[l] < spos && left_tops[r] > epos)
                {
                    int l_cost = cost[spos][left_tops[l]] + cost[left_tops[l]][spos];    // 左边最远距离消耗
                    int r_cost = cost[epos][left_tops[r]] + cost[left_tops[r]][epos];    // 右边最远距离消耗
                    if (l_cost + r_cost <= left_cost)
                    {
                        if (must_num + left_len_bak - i + r - left_len_bak + 1 > maxn)
                        {
                            maxn = must_num + left_len_bak - i + r - left_len_bak + 1 > maxn;
                        }
                        break;
                    }
                    else
                    {
                        if (l_cost > r_cost) l++;
                        else r--;
                    }
                }

                left_len = left_len_bak;
            }
        }
        cout << maxn << endl;
    }
    return 0;
}