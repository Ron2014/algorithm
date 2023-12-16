#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    int N, m, v, p, q;
    scanf("%d %d", &N, &m);
    vector<vector<int>> val(m+1, vector<int>(3, 0));
    vector<vector<int>> wei(m+1, vector<int>(3, 0));
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d %d", &v, &p, &q);
        if (q == 0)
        {
            val[i][0] = v / 10;
            wei[i][0] = v * p / 10;
        }
        else if (val[q][1] == 0)
        {
            val[q][1] = v / 10;
            wei[q][1] = v * p / 10;
        }
        else
        {
            val[q][2] = v / 10;
            wei[q][2] = v * p / 10;
        }
    }
    vector<int> dp(3200, 0);
    for (int i = 1; i <= m; ++i)
    {
        if (val[i][0] == 0) continue;
        for (int j = N/10; j >= 0; --j)
        {
            if (val[i][0] <= j)
            {
                dp[j] = max(dp[j], wei[i][0] + dp[j - val[i][0]]);
                // cout << val[i][0] << " " << i << " " << j << " " << dp[j] << endl;
            }
            if (val[i][1] && (val[i][0] + val[i][1] <= j))
            {
                dp[j] = max(dp[j], wei[i][0] + wei[i][1] + dp[j - val[i][0] - val[i][1]]);
            }
            if (val[i][2] && (val[i][0] + val[i][2] <= j))
            {
                dp[j] = max(dp[j], wei[i][0] + wei[i][2] + dp[j - val[i][0] - val[i][2]]);
            }
            if (val[i][1] && val[i][2] && (val[i][0] + val[i][1] + val[i][2] <= j))
            {
                dp[j] = max(dp[j], wei[i][0] + wei[i][1] + wei[i][2] + dp[j - val[i][0] - val[i][1] - val[i][2]]);
            }
        }
    }
    cout << dp[N/10] * 10 << endl;
    return 0;
}