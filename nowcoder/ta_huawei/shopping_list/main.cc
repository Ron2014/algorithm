#include <iostream>
#include <cstring>
using namespace std;

/**
 * only consider major goods and it's possible combination
 * 100
 * 101
 * 110
 * 111
 * 

1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0
---
2200

6000 15  
100 3 0  
400 5 0  
300 5 0  
1400 2 3 
500 2 2  
800 2 3  
1400 5 0 
300 5 0  
1400 3 0 
500 2 0  
1800 4 0 
440 5 10 
1340 5 10
430 3 0  
500 2 0  
---
26400

*/

// #define TEST

typedef struct goods_data {
    int iPrice;
    int iWeight;
} goods_data;

typedef struct possible_combine {
    int iCount;
    goods_data aCombines[4];
} possible_combine;

typedef struct child_goods {
    int id;
    child_goods *next;
}child_goods;

int main(int argc, char *argv[]) {
    int iBudget;        // < 32000
    int iKindOfGoods;   // < 60

    while(scanf("%d %d", &iBudget, &iKindOfGoods) != EOF) {
        int iPrice, iWeight, iMajorKind, iMajorCount;

        int *aPrice     = new int[iKindOfGoods+1];
        int *aWeight    = new int[iKindOfGoods+1];
        int *aMajorKind = new int[iKindOfGoods+1];

        child_goods **major_heads = new child_goods*[iKindOfGoods+1];
        for (int i=0; i<=iKindOfGoods; i++) {
            major_heads[i] = nullptr;
        }

        iMajorCount = 0;
        for (int i=1; i<=iKindOfGoods; i++) {
            scanf("%d %d %d", &iPrice, &iWeight, &iMajorKind);
            aPrice[i]       = iPrice;
            aWeight[i]      = iPrice * iWeight;
            aMajorKind[i]   = iMajorKind;
            if (iMajorKind == 0) iMajorCount++;
            else {
                child_goods *node = new child_goods;
                node->id = i;
                node->next = major_heads[iMajorKind];
                major_heads[iMajorKind] = node;
            }
        }

        possible_combine *aPossibleCombines = new possible_combine[iMajorCount];
        int iMajorNewId = 0;
        for (int i=1; i<=iKindOfGoods; i++) {
            if (aMajorKind[i] > 0) continue;

            int majorId = i;
            #ifdef TEST
            printf("%d ", majorId);
            #endif
            //100
            aPossibleCombines[iMajorNewId].iCount = 1;
            aPossibleCombines[iMajorNewId].aCombines[0].iPrice = aPrice[majorId];
            aPossibleCombines[iMajorNewId].aCombines[0].iWeight = aWeight[majorId];

            child_goods *node = major_heads[i];
            while (node) {
                int childId = node->id;
                int curCount = aPossibleCombines[iMajorNewId].iCount;
                #ifdef TEST
                printf("->%d ", childId);
                #endif

                // 2 combine
                aPossibleCombines[iMajorNewId].aCombines[curCount].iPrice = aPrice[majorId] + aPrice[childId];
                aPossibleCombines[iMajorNewId].aCombines[curCount].iWeight = aWeight[majorId] + aWeight[childId];
                aPossibleCombines[iMajorNewId].iCount++;

                // 3 combine
                if (curCount > 1) {
                    aPossibleCombines[iMajorNewId].aCombines[curCount+1].iPrice = aPossibleCombines[iMajorNewId].aCombines[1].iPrice + aPrice[childId];
                    aPossibleCombines[iMajorNewId].aCombines[curCount+1].iWeight = aPossibleCombines[iMajorNewId].aCombines[1].iWeight + aWeight[childId];
                    aPossibleCombines[iMajorNewId].iCount++;
                }

                node = node->next;
            }

            #ifdef TEST
            printf("\n");
            #endif
            iMajorNewId++;
        }

        #ifdef TEST
        // test for possible
        for (int i=0; i<iMajorCount; i++) {
            int curCount = aPossibleCombines[i].iCount;
            for (int j=0; j<curCount; j++) {
                printf("%d %d\n", aPossibleCombines[i].aCombines[j].iPrice, aPossibleCombines[i].aCombines[j].iWeight);
            }
        }
        #endif

        // use money j, buy head major goods i, get maxWeight
        int **aMaxWeight = new int*[iMajorCount+1];
        for (int i=0; i<=iMajorCount; i++) {
            aMaxWeight[i] = new int[iBudget+1];
            memset(aMaxWeight[i], 0, sizeof(int) * (iBudget+1));
        }

        for (int count=1; count<=iMajorCount; count++) {
            for (int money=1; money<=iBudget; money++) {
                int iMajorNewId = count-1;
                possible_combine newPossible = aPossibleCombines[iMajorNewId];
                int iMaxWeight = aMaxWeight[count - 1][money];

                // at most 4 kind of combination: if i buy major goods at iMajorNewId
                for (int i = 0; i < newPossible.iCount; i++) {
                    iPrice = newPossible.aCombines[i].iPrice;
                    iWeight = newPossible.aCombines[i].iWeight;

                    // lastPrice
                    if (money >= iPrice) {
                        // use less money buy count-1 of goods
                        if ((aMaxWeight[count-1][money-iPrice] + iWeight) > iMaxWeight)
                            iMaxWeight = aMaxWeight[count-1][money-iPrice] + iWeight;
                    }
                }

                aMaxWeight[count][money] = iMaxWeight;
            }
        }

        printf("%d\n", aMaxWeight[iMajorCount][iBudget]);

        for (int i=0; i<=iMajorCount; i++) {
            delete aMaxWeight[i];
        }
        delete aMaxWeight;

        delete aPossibleCombines;

        for (int i=0; i<=iKindOfGoods; i++) {
            child_goods *node = major_heads[i];
            while (node) {
                child_goods *next = node->next;
                delete node;
                node = next;
            }
        }
        delete major_heads;

        delete aPrice;
        delete aWeight;
        delete aMajorKind;

    }
    return 0;
}