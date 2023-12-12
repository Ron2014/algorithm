#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_INT 2147483647
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int sn = spells.size(), pn = potions.size();
        vector<int> pairs(sn);
        map<int, int> mp2count;
        sort(potions.begin(), potions.end());

        for (int i = 0; i < sn; i++)
        {
            pairs[i] = 0;
            long long target = success / spells[i];
            if (target < MAX_INT)
            {
                if (success % spells[i]) target++;
                pairs[i] = (int)target;
                mp2count[(int)target] = 0;
            }
            else
            {
                pairs[i] = 0;
            }
            printf("%d,%d\n", i, pairs[i]);
        }
        
        int k = 0;
        map<int, int>::iterator it = mp2count.begin();
        while (it != mp2count.end() && k < pn)
        {
            if (potions[k] < it->first)
            {
                k++;
            }
            else
            {
                it->second = pn-k;
                printf("%d,%d\n", it->first, it->second);
                it++;
            }
        }
        for (int i = 0; i < sn; i++)
        {
            pairs[i] = mp2count[pairs[i]];
        }
        return pairs;
    }
};