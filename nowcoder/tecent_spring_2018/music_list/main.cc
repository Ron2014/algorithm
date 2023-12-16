#include <iostream>
#include <memory.h>
using namespace std;

#define mod 1000000007
unsigned long long c[105][105];
// c[i][j]
// i 个元素中抽取 j 个的组合个数

void init()   //计算组合数
{
	c[0][0]=1;
	for(int i=1; i<=100; i++)
	{
		c[i][0] = 1;
		for(int j=1; j<=100; j++)
		    c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
/*
        公式：C(n,r)=C(n-1,r)+C(n-1,r-1)  这个公式用到了分类思想。对于n个元素的某个元素，要么选，要么不选。
        如果选了，只需在 剩下的n-1 个元素中选 r-1个；如果不选，则在剩下的n-1个元素中选r个（因为一共要选r个啊）。
        这个公式非常有用，这是杨辉三解公式：其中基准条件C(n,0)=1，C(i,i)=1
        C(0,0)
        C(1,0)   C(1,1)
        C(2,0)   C(2,1)   C(2,2)
        C(3,0)   C(3,1)   C(3,2)   C(3,3)
*/
	}
}

unsigned long long _Factorial(int n, int from=2) {
    unsigned long long ret = 1;
    for (int i=from; i<=n; i++) ret*=i;     // 此处阶乘溢出
    // if (ret==0) cout <<"ret is zero" << endl;
    return ret;
}

unsigned long long _Pick(int from, int get) {
    // return _Factorial(from, from-get+1) / _Factorial(get);
    return c[from][get];
}

unsigned long long getResult(int len, const int &len0, const int &len1, int num0, int num1) {
    int left;
    unsigned long long ret = 0;
    for (int i=0; i<=num0; i++) {
        left = len-i*len0;
        if (left<0) break;
        if (left>0) {
            if (left%len1==0 && left/len1<=num1)
                ret += _Pick(num0, i) * _Pick(num1, left/len1);
        } else {
            ret += _Pick(num0, i);
        }
    }
    return ret;
}

int main() {
    init();
    int len, len0, len1, num0, num1;
    while (cin>>len>>len0>>num0>>len1>>num1) {
        if (len0>len1) {
            int tmp = len0;
            len0 = len1;
            len1 = tmp;

            tmp = num0;
            num0 = num1;
            num1 = tmp;
        }

        unsigned long long ret = getResult(len, len0, len1, num0, num1);
        if (ret) cout << ret%mod << endl;
        else cout << 0 << endl;
    }
    return 0;
}