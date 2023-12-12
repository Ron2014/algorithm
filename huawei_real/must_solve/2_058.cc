/*
给定M(0<M<=30)个字符（a-z），从中取出任意字符（每个字符只能用一次）拼接成长度为N(0<N<=5)的字符串
要求相同的字符不能相邻，计算出给定的字符列表能拼接出多少种满足条件的字符串，输入非法或者无法拼接出满足条件的字符串则返回0。
*/

#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

void dfs(unordered_map<char, int> &cnts, int idx, int n, char prev, vector<char> &result, long long &fresult)
{
    if (idx >= n)
    {
        // fresult += result;
        for (const char &c : result) cout << c;
        cout << endl;
        fresult++;
        return;
    }
    for (unordered_map<char, int>::iterator it = cnts.begin(); it != cnts.end(); ++it)
    {
        if (it->second <= 0) continue;
        if (it->first == prev) continue;
        it->second--;
        result.push_back(it->first);
        dfs(cnts, idx+1, n, it->first, result, fresult);
        result.pop_back();
        it->second++;
    }
}

int main(int argc, char *argv[])
{
    int N;
    string M;
    while (cin >> N >> M)
    {
        int len = M.length();
        if (len <= 0) break;

        unordered_map<char, int> cnts;
        for (const char &ch : M)
        {
            cnts[ch]++;
        }

        long long fresult = 0;
        vector<char> result;
        dfs(cnts, 0, N, 0, result, fresult);
        cout << fresult << endl;
    }
    return 0;
}