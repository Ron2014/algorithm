/*
1.老李是货运公司承运人，老李的货车额定载货重量为wt
2.现有两种货物，货物A单件重量为wa，单件运费利润为pa，货物B单件重量为wb，单件运费利润为pb
3.老李每次发车时载货总重量刚好为货车额定载货重量wt，车上必须同时有货物A和货物B，货物A、B不可切割
4.老李单车次满载运输可获得的最高利润是多少
*/
#include <iostream>
#include <vector>
using namespace std;



int main(int argc, char *argv[])
{
    int wt, wa, pa, wb, pb;
    while (cin >> wt >> wa >> pa >> wb >> pb)
    {
        // dp[i][j], 载货额度重量i，载货A重为j的最高利润
        vector<vector<int>> dp(wt+1, vector<int>(wt+1, 0));

        // bug_found: 没有考虑 '车上必须同时有货物A和货物B' 这个条件
        for (int i = 1; i <= wt; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                int maxProfitA = (j >= wa) ? dp[i - wa][j - wa] + pa : 0;
                int maxProfitB = ((i - j) >= wb) ? dp[i - wb][j] + pb : 0;

                dp[i][j] = std::max(maxProfitA, maxProfitB);
            }
        }
        cout << dp[wt-wb][wt-wb] << endl;
    }
    return 0;
}