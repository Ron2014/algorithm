/*
从前有个村庄，村民们喜欢在各种田地上插上小旗子，旗子上标识了各种不同的数字。
某天集体村民决定将覆盖相同数字的最小矩阵形的土地的分配给为村里做出巨大贡献的村民，请问，此次分配土地，做出贡献的村民中最大会分配多大面积？
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int DIRECT_CNT = 4;
const int di[] = {0, 0, -1, 1};
const int dj[] = {1, -1, 0, 0};

int group_ground(vector<vector<int>> &ground, vector<vector<bool>> &visited, int num, int l, int t, int r, int b)
{
    bool can;
    vector<int> area;
    area.push_back((r-l+1) * (b-t+1));

    // to left
    can = true;
    for (int i = t; i <= b; ++i)
    {
        if (ground[i][l-1] != num)
        {
            can = false;
            break;
        }
    }
    if (can)
    {
        for (int i = t; i <= b; ++i) visited[i][l-1] = true;
        int area_l = group_ground(ground, visited, num, l-1, t, r, b);
        area.push_back(area_l);
    }

    // to right
    can = true;
    for (int i = t; i <= b; ++i)
    {
        if (ground[i][r+1] != num)
        {
            can = false;
            break;
        }
    }
    if (can)
    {
        for (int i = t; i <= b; ++i) visited[i][r+1] = true;
        int area_r = group_ground(ground, visited, num, l, t, r+1, b);
        area.push_back(area_r);
    }

    // to top
    can = true;
    for (int i = l; i <= r; ++i)
    {
        if (ground[t-1][i] != num)
        {
            can = false;
            break;
        }
    }
    if (can)
    {
        for (int i = l; i <= r; ++i) visited[t-1][i] = true;
        int area_t = group_ground(ground, visited, num, l, t-1, r, b);
        area.push_back(area_t);
    }

    // to bottom
    can = true;
    for (int i = l; i <= r; ++i)
    {
        if (ground[b+1][i] != num)
        {
            can = false;
            break;
        }
    }
    if (can)
    {
        for (int i = l; i <= r; ++i) visited[b+1][i] = true;
        int area_b = group_ground(ground, visited, num, l, t, r, b+1);
        area.push_back(area_b);
    }

    return *max_element(area.begin(), area.end());
}


int main(int argc, char *argv[])
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<int>> ground(n+2, vector<int>(m+2, -1));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                cin >> ground[i][j];
            }
        }
        vector<vector<bool>> visited(n+2, vector<bool>(m+2, false));

        vector<int> area;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (visited[i][j]) continue;
                int num = ground[i][j];
                visited[i][j] = true;
                area.push_back(group_ground(ground, visited, num, j, i, j, i));
            }
        }
        cout << *max_element(area.begin(), area.end()) << endl;
    }
    return 0;
}