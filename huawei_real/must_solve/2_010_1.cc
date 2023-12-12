#include <stdio.h>
#include <vector>
#include<iostream>
using namespace std;
std::vector<int> vec;
 
int dispatch(int nPeople, int nMoon, int nMin) {
    if (nMoon <= 0)
    {
        return 0; // 分配失败
    }
 
    if (nPeople <= 0)
    {
        return 0;
    }
    if (nPeople == 1) //处理人数为2的情况
    {
        if (nMoon >= nMin && nMoon <= nMin + 3)
        {
            vec.push_back(nMoon);
            cout << "nMoon = " << nMoon << endl;
            for (std::vector<int>::iterator x = vec.begin(); x != vec.end(); x ++)
            {
                printf("%d ", *x+1);
            }
            printf("\n");
            vec.pop_back();
            return 1;
        }
        return 0;
    }
 
    int nCount = 0;
    for (int got = nMin; got <= nMin+3; got++)
    {
        vec.push_back(got);
        cout << "dispatch: " << nPeople-1 << " " << nMoon-got << " " << got << endl;
        nCount += dispatch(nPeople-1, nMoon-got, got);//递归处理人数大于2的情况
        vec.pop_back();
    }
    cout << "return" << endl;
    return nCount;
}
 
 
int main(void)
{
    int nPeople, nMoon;
    while (cin >> nMoon >> nPeople)
    {
        nMoon -= nPeople;//每个人至少有一个月饼
 
        int nCount = 0;
        // 先确定分得月饼最少的那个人得到的月饼数
        for (int got = 0; got <= nMoon; got++) // got表示分到月饼最少的那个人得到的月饼数
        {
            vec.push_back(got);
            cout << "main dispatch: " << nPeople-1 << " " << nMoon-got << " " << got << endl;
            nCount += dispatch(nPeople-1, nMoon-got, got); // 第二少的人只能分[got,got+3]个
            vec.pop_back();
        }
 
        printf("%d\n", nCount);
    }
    return 0;
}