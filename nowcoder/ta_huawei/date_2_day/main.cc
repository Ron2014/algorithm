
#include <iostream>
using namespace std;

#define MONTH_COUNT 12

int MonthDay0[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int MonthDay1[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int Result;

bool isLeepYear(int year) {
    if (year % 100 == 0)
        return year % 400 == 0;
    return year % 4 == 0;
}

/*****************************************************************************
Description   : 数据转换
Input Param   : year 输入年份
            Month 输入月份
            Day 输入天
                
Output Param  :
Return Value  : 成功返回0，失败返回-1（如：数据错误）
*****************************************************************************/
int iConverDateToDay(int year, int month, int day)
{
    if (year<=0) return -1;
    if (month<=0 || month > MONTH_COUNT) return -1;

    int *monthDay = isLeepYear(year) ? MonthDay1 : MonthDay0;
    Result = 0;
    for (int i=1; i<month; i++) {
        Result += monthDay[i];
    }
    Result += day;

    return 0;
}

int main() {
    int year, month, day;
    while (cin >> year >> month >> day) {
        int ret = iConverDateToDay(year, month, day);
        if (ret == 0)
            cout << Result << endl;
        else
            cout << ret << endl;
    }
    return 0;
}