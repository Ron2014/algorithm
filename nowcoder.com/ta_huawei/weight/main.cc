#include <stdio.h>
#include <cstring>
#include <set>

int iKindOfWeight, iTotalWeight, iTotalCount;
int *aMassOfWeight, *aCountOfWeight;
int *aMaxKindOfWeight;
std::set<int> sWeightAchieved;
std::set<int> sWeightNew;

int main(int argc, char *argv[]) {
    while (scanf("%d", &iKindOfWeight) != EOF) {
        aMassOfWeight = new int[iKindOfWeight+1];
        aCountOfWeight = new int[iKindOfWeight+1];

        for (int i=1; i<=iKindOfWeight; i++) {
            scanf("%d", &aMassOfWeight[i]);
        }

        iTotalCount = 0;
        for (int i=1; i<=iKindOfWeight; i++) {
            scanf("%d", &aCountOfWeight[i]);
            iTotalCount += aCountOfWeight[i];
        }

        aMaxKindOfWeight = new int[iTotalCount+1];
        memset(aMaxKindOfWeight, 0, sizeof(int) * (iTotalCount+1));

        int idx = 0;
        for(int i=1; i<=iKindOfWeight; i++) {
            int count = aCountOfWeight[i];
            int weight = aMassOfWeight[i];

            for (int j=0; j<count; j++) {
                idx++;
                // weight[idx] added
                sWeightNew.clear();

                std::set<int>::iterator achievedEnd = sWeightAchieved.end();
                if (sWeightAchieved.find(weight) == achievedEnd) {
                    sWeightNew.insert(weight);
                }

                for (std::set<int>::iterator it = sWeightAchieved.begin(); it != achievedEnd; it++) {
                    int newWeight = *it + weight;
                    // printf("%d\n", newWeight);
                    if (sWeightAchieved.find(newWeight) == achievedEnd) {
                        sWeightNew.insert(newWeight);
                    }
                }
                sWeightAchieved.insert(sWeightNew.begin(), sWeightNew.end());
                aMaxKindOfWeight[idx] = aMaxKindOfWeight[idx-1] + sWeightNew.size();
                // printf("[%d]=%d\n", idx, aMaxKindOfWeight[idx]);
            }
        }

        printf("%d\n", aMaxKindOfWeight[iTotalCount] + 1); // include 0

        delete aMassOfWeight;
        delete aCountOfWeight;
        delete aMaxKindOfWeight;
        sWeightAchieved.clear();
    }
    return 0;
}