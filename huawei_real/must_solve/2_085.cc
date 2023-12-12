/*
1.老李是货运公司承运人，老李的货车额定载货重量为wt
2.现有两种货物，货物A单件重量为wa，单件运费利润为pa，货物B单件重量为wb，单件运费利润为pb
3.老李每次发车时载货总重量刚好为货车额定载货重量wt，车上必须同时有货物A和货物B，货物A、B不可切割
4.老李单车次满载运输可获得的最高利润是多少
*/

/**
 * 贪心
*/

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int wt, wa, pa, wb, pb;
    while (cin >> wt >> wa >> pa >> wb >> pb)
    {
        wt -= wa + wb;
        int maxp = pa + pb;
        int maxa = wt / wa;

        int maxn = -1;
        for (int i = 0; i < maxa + 1; ++i)
        {
            if ((wt-i*wa)%wb>0) continue;
            int nb = (wt - i * wa)/wb;
            int n = pa * i + pb * nb;
            if (n > maxn)
            {
                cout << i << " " << nb << endl;
                maxn = n;
            }
        }
        cout << maxp + maxn << endl;
    }
    return 0;
}
