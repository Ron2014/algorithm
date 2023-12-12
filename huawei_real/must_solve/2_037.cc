/*
Wonderland是小王居住地一家很受欢迎的游乐园。 Wonderland目前有4种售票方式，分别为一日票（1天）、三日票（3天）、周票（7天）和月票（30天）。

每种售票方式的价格将由一个数组给出，每种票据在票面时限内可以无限制的进行游玩。例如，小王在第10日买了一张三日票，小王可以在第10日、第11日和第12日进行无限制的游玩。 

小王计划在接下来一年内多次游玩该游乐园。小王计划的游玩日期将由一个数组给出。 现在，请您根据给出的售票价格数组和小王计划游玩日期数组，返回完成游玩计划所需要的最低消费。
*/

#include <iostream>
#include <vector>
using namespace std;

const int MAX_INT = 2147483647;
const int TICKET_TYPE = 4;
vector<int> ticket_days = {1, 3, 7, 30};
vector<int> ticket_price(TICKET_TYPE);

int main(int argc, char *argv[])
{
    for (int i = 0; i < TICKET_TYPE; ++i)
    {
        cin >> ticket_price[i];
    }

    int n;
    cin >> n;
    vector<int> play_days(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> play_days[i];
    }

    vector<int> costs(n, MAX_INT);     // cost[i] 玩到第i天的最小开销
    for (int i = 0; i < n; ++i)
    {
        int j = i;
        for (int k = 0; k < TICKET_TYPE; ++k)
        {
            while (j >= 0 && play_days[j] + ticket_days[k] > play_days[i]) --j;
            costs[i] = min(costs[i], (j < 0 ? 0 : costs[j]) + ticket_price[k]);
        }
    }
    cout << costs[n-1] << endl;

    return 0;
};