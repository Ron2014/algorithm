#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

void swap(char *sz, int i, int j)
{
    char tmp = sz[i];
    sz[i] = sz[j];
    sz[j] = tmp;
}

void full_permutation(char *sz, int s, int n, set<string> &fp)
{
    if (s >= n)
    {
        // cout << sz << endl;
        fp.insert(sz);
        return;
    }
    for (int i = s; i < n; ++i)
    {
        swap(sz, i, s);
        full_permutation(sz, s+1, n, fp);
        swap(sz, i, s);
    }
}

int main(int argc, char *argv[])
{
    int n, k;
    string s;
    char buf[11];
    while (cin >> n)
    {
        vector<string> lists;
        set<string> fp;
        for (int i = 0; i < n; ++i)
        {
            cin >> s;
            lists.push_back(s);
        }
        sort(lists.begin(), lists.end());

        cin >> s >> k;

        // cout << s << " " << k << endl;

        n = s.length();
        strncpy(buf, s.c_str(), n);
        buf[n] = '\0';
        full_permutation(buf, 0, n, fp);

        int count = 0;
        int target = -1;
        for (int i = 0; i < lists.size(); ++i)
        {
            if (s != lists[i] && fp.find(lists[i]) != fp.end())
            {
                count++;
                if (count == k)
                {
                    target = i;
                }
            }
        }
        cout << count << endl;
        if (target >= 0)
        {
            cout << lists[target] << endl;
        }
    }
    return 0;
}