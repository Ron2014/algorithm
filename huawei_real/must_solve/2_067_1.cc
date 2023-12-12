/*
某公司部门需要派遣员工去国外做项目。现在，代号为x的国家和代号为y的国家分别需要cntx名和cnty名员工。部门每个员工有一个员工号(1,2,3……)，工号连续，从1开始。

部长派遣员工的规则：

规则1、从[1,k]中选择员工派遣出去
规则2、编号为x的倍数的员工不能去x国，编号为y的倍数的员工不能去y国
问题：
找到最小的k，使得可以将编号在[1,k]中的员工分配给x国和y国，且满足x国和y国的需求
*/

/*
对于k个员工，其中有k/x个员工去不了x国，k/y个员工去不了y国
但是不能简单认为 k-k/x-k/y >= cntx+cnty，因为这两拨不能去的员工可能有重叠，所以
上限：
    k <= (cntx+cnty)*xy/(xy-y-x)
下限
    k-k/x >= cntx   => k >= cntx*x/(x-1)
    k-k/y >= cnty   => k >= cnty*y/(y-1)
*/

/**
 * 二分查找
*/

#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
    int x, y, cntx, cnty;
    while (cin >> x >> y >> cntx >> cnty)
    {
        int mink = (int)floor(min(cntx*x*1.0/(x-1), cnty*y*1.0/(y-1)));
        int maxk = (int)ceil((cntx+cnty)*x*y*1.0/(x*y-x-y));
        cout << mink << " " << maxk << endl;
        while (mink <= maxk)
        {
            int mk = (mink + maxk)>>1;

            // bug_found: 这里有循环，开销略大
            int repeat = 0;
            for (int i = 1; i <= mk; ++i)
            {
                if (i%x!=0 && i%y!=0) repeat++;
            }
            cout << mk << " " << mk/x << " " << mk/y << " " << repeat << endl;

            if (repeat > 0)
            {
                if (mk - mk/x + mk - mk/y - repeat > cntx + cnty)
                {
                    maxk = mk - 1;
                }
                else if (mk - mk/x + mk - mk/y - repeat < cntx + cnty)
                {
                    mink = mk + 1;
                }
                else
                {
                    maxk = mk;
                    break;
                }
            }
            else
            {
                if (mk - mk/x == cntx && mk - mk/y == cnty)
                {
                    maxk = mk;
                    break;
                }
                else if (mk - mk/x > cntx && mk - mk/y > cnty)
                {
                    maxk = mk - 1;
                }
                else
                {
                    mink = mk + 1;
                }
            }
        }
        cout << maxk << endl;
    }
    return 0;
}