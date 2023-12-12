/*
在学校中，N个小朋友站成一队， 第i个小朋友的身高为height[i]，
第i个小朋友可以看到的第一个比自己身高更高的小朋友j，那么j是i的好朋友(要求j>i)。
请重新生成一个列表，对应位置的输出是每个小朋友的好朋友位置，如果没有看到好朋友，请在该位置用0代替。 

小朋友人数范围是 [0, 40000]。
*/

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<int> heights(n, 0);
        vector<int> friends(n, 0);
        for (int i = 0; i < n; ++i)
        {
            cin >> heights[i];
        }
        for (int i = 0; i < n-1; ++i)
        {
            if (i>0 && heights[i] <= heights[i-1])
            {
                friends[i] = friends[i-1];
                continue;
            }

            for (int j = i+1; j<n; ++j)
            {
                if (heights[j] > heights[i])
                {
                    friends[i] = j;
                    break;
                }
            }
        }
        for (int i = 0; i < n; ++i)
        {
            cout << friends[i] << " ";
        }
        cout << endl;
    }
    return 0;
}