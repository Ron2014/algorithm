#include <iostream>
#include <time.h>
#include <math.h>
#include <stack>
#include "zone.h"
using namespace std;

#define MONTH_COUNT 12

#define MAX_AGE 100         // 注册的最大年龄
#define MIN_AGE 20          // 最小年龄(成年)

vector<char> nums;

#define MAX_LEN 18          // 身份真位数
vector<int> layout = { 6,       4,  2,  2,  2,      1,     1};  // 布局
                     //区域码   年  月  日  顺序码   性别   校验码

int MonthDay[][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},        // 非闰年日期布局
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},        // 闰年日期布局
};

bool isLeepYear(int year) {
    if (year % 100 == 0)
        return year % 400 == 0;
    return year % 4 == 0;
}

void fill(vector<char> &nums, vector<int> vn) {
    stack<int> st;
    for (int i=0; i<vn.size(); i++) {
        int num = vn[i];
        int len = layout[i];
        // cout << num << endl;
        while(len--) {
            st.push(num%10);
            num /= 10;
        }
        while(!st.empty()) {
            nums.push_back(st.top()+'0');
            st.pop();
        }
    }
}

char check(const vector<char> &nums) {
    int w;
    int s = 0;

    for (int i=0; i<nums.size(); i++) {
        w = (int)pow(2, MAX_LEN-i-1) % 11;
        s += w * (nums[i] - '0');
    }

    int n0 = (12 - s % 11) % 11;
    if (n0 < 10) return '0' + n0;
    else return 'X';
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "usage: gen <number>" << endl;
        return 0;
    }
    
    time_t now = time(NULL);
    srand(now);

    int count = atoi(argv[1]);
    while(count--) {
        nums.clear();
    
        int zone_id = zone[rand() % zone.size()];

        int age_len = MAX_AGE - MIN_AGE;
        int age = rand() % age_len + MIN_AGE;

        tm *gmtm = gmtime(&now);
        int year = gmtm->tm_year - age + 1900;
        int month = rand() % MONTH_COUNT + 1;

        int *month_list = MonthDay[isLeepYear(year)];
        int day = rand() % month_list[month] + 1;

        int seq = rand() % 100;

        int sex = rand() % 2;

        fill(nums, {zone_id, year, month, day, seq, sex});

        char ck = check(nums);
        nums.push_back(ck);

        for (int i=0; i<nums.size(); i++)
            cout << nums[i];
        cout << endl;
    }
    return 0;
}