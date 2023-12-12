/*
服务之间交换的接口成功率作为服务调用关键质量特性
某个时间段内的接口失败率使用一个数组表示
数组中每个元素都是单位时间内失败率数值
数组中的数值为0~100的整数
给定一个数值(minAverageLost)表示某个时间段内平均失败率容忍值
即平均失败率小于等于minAverageLost

找出数组中最长时间段，如果未找到则直接返回NULL。
*/
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int n, minAvg;
    while (cin >> n >> minAvg)
    {
        vector<int> array(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> array[i];
        }

        int s = 0, e = 0;
        int sum = array[0];
        int maxs = -1;
        int maxl = 0;
        while (s < n)
        {
            while (e < n && sum <= minAvg*(e-s+1))
            {
                e++;
                if (e >= n) break;
                sum += array[e];
            }

            // 加上 array[e] 已经不满足条件了
            // s ~ e-1 是最长时间段
            if (e-s > maxl)
            {
                maxl = e-s;
                maxs = s;
            }

            if (e >= n) break;

            while (s < n && sum > minAvg*(e-s))
            {
                sum -= array[s];
                s++;
            }
        }

        if (maxs < 0)
        {
            cout << "null" << endl;
        }
        else
        {
            sum = 0;
            for (int i = 0; i < maxl; ++i)
            {
                sum += array[maxs + i];
                cout << array[maxs + i] << ",";
            }
            cout << endl;
            printf("[%d~%d]=%d\n", maxs, maxs+maxl-1, sum);
        }
    }
    return 0;
}

