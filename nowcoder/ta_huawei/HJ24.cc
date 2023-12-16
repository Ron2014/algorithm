#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n)
    {
        vector<int> heights;
        for (int i = 0; i < n; ++i)
        {
            heights.push_back(0);
            cin >> heights[i];
        }
        vector<int> incrL(n, 0);
        vector<int> decrR(n, 0);
        for (int i = 0; i < n; ++i)
        {
            int j = i - 1;
            for (int j = 0; j < i; j++)
            {
                if (heights[i] > heights[j])
                {
                    incrL[i] = max(incrL[i], incrL[j]);
                }
            }
            incrL[i]++;
        }
        for (int i = n - 1; i >= 0; --i)
        {
            int j = i + 1;
            for (int j = n - 1; j >= i + 1; --j)
            {
                if (heights[i] > heights[j])
                {
                    decrR[i] = max(decrR[i], decrR[j]);
                }
            }
            decrR[i]++;
        }
        int maxn = -1;
        for (int i = 0; i < n; ++i)
        {
            if (incrL[i] + decrR[i] - 1 > maxn)
            {
                maxn = incrL[i] + decrR[i] - 1;
            }
        }
        cout << n - maxn << endl;

    }
    return 0;
}