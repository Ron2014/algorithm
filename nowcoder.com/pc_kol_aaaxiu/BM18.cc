#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Solution {
    bool bsearch(int target, vector<vector<int> >& array, int l, int t, int r, int b)
    {
        if (l > r || t > b) return false;

        int mi = (t+b)>>1;
        int mj = (l+r)>>1;
        cout << "["<< mi << "]" << "[" << mj << "]:" << array[mi][mj] << endl;

        if (array[mi][mj] > target)
        {
            if (bsearch(target, array, l, t, r, mi-1)) return true;     // 上边
            if (bsearch(target, array, l, mi, mj-1, b)) return true;    // 左下
        }
        else if (array[mi][mj] < target)
        {
            if (bsearch(target, array, l, mi+1, r, b)) return true;    // 下边
            if (bsearch(target, array, mj+1, t, r, mi)) return true;   // 右上
        }
        else
        {
            return true;
        }

        return false;
    }

public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param target int整型 
     * @param array int整型vector<vector<>> 
     * @return bool布尔型
     */
    bool Find(int target, vector<vector<int> >& array) {
        // write code here
        int n = array.size();
        if (n <= 0) return false;
        int m = array[0].size();
        if (m <= 0) return false;
        return bsearch(target, array, 0, 0, m-1, n-1);
    }
};

int main(int argc, char *argv[])
{
    Solution s;

    int target = atoi(argv[argc-1]);
    int n = atoi(argv[argc-2]);
    int m = (argc - 2) / n;
    vector<vector<int>> array;

    for (int i = 1; i < argc - 2; ++i)
    {
        if ((i - 1)%m == 0)
        {
            array.push_back({});
        }
        array[array.size() - 1].push_back(atoi(argv[i]));
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    s.Find(target, array);

    return 0;
}