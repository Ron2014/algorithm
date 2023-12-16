/**
62
9360 2272 15078 15571 4734 18667 10392 17796 12207 14591 8380 10126 11627 1288 24523 568 15754 8400 11280 20964 15482 28433 26109 11147 9628 12296 8500 21628 22561 5532 8830 13253 3231 15580 27278 4824 19217 16038 10091 21071 19587 10243 8786 15529 23644 13228 21503 22706 13546 2937 24488 19924 16138 13815 22460 4122 26823 2987 25011 25469 27224 16237
--
26

38
25337 2817 17946 4973 13973 27161 11729 26509 21925 20578 25824 26728 7609 19330 13841 27168 21751 17414 28070 6368 21303 15087 5428 9005 20132 13445 19423 21448 509 15483 24242 23492 20717 14190 7808 9363 278 24852
--
18
*/

#include <stdio.h>
#include <cstring>
#include <map>
#include <set>

int iCount, *aMaxPairCount;
std::map<int, int> mPairedIdx;
std::set<int> sUnpairedIdx;

int aNumbers[101];

bool isPrime(int num) {
    for (int i=2; i < num/2; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

bool isPrimePartner(int a, int b) {
    return isPrime(a + b);
}

int searchInUnpaired(int num) {
    for(std::set<int>::iterator it = sUnpairedIdx.begin(); it != sUnpairedIdx.end(); it++) {
        int idx = *it;
        int unpairedNum = aNumbers[idx];
        if (isPrimePartner(num, unpairedNum)) {
            return idx;
        }
    }
    return 0;
}

// not work: dynamic planning
int main(int argc, char *argv[]) {
    while (scanf("%d", &iCount) != EOF) {
        aMaxPairCount = new int[iCount+1];
        memset(aMaxPairCount, 0, sizeof(int) * (iCount + 1));

        for (int i=1; i<=iCount; i++)
            scanf("%d", &aNumbers[i]);

        for(int i=1; i<=iCount; i++) {
            int newNum = aNumbers[i];
            int new_pair = 0;

            // search in unpaired idx
            int matchedIdx = searchInUnpaired(newNum);
            if (matchedIdx) {
                mPairedIdx[matchedIdx] = i;
                sUnpairedIdx.erase(matchedIdx);
                new_pair++;
                printf("matched %d[%d] %d[%d]\n", newNum, i, aNumbers[matchedIdx], matchedIdx);
            }

            // search in paired indx
            if (!new_pair) {
                for (std::map<int, int>::iterator it = mPairedIdx.begin(); it != mPairedIdx.end(); it++) {
                    int minIdx = it->first;
                    int maxIdx = it->second;

                    int pairNum0 = aNumbers[minIdx];
                    int pairNum1 = aNumbers[maxIdx];

                    int matchedIdx0 = searchInUnpaired(pairNum0);
                    int matchedIdx1 = searchInUnpaired(pairNum1);

                    if (isPrimePartner(newNum, pairNum0) && matchedIdx1) {
                        mPairedIdx[minIdx] = i;
                        if (maxIdx < matchedIdx1) 
                            mPairedIdx[maxIdx] = matchedIdx1;
                        else {
                            mPairedIdx.erase(maxIdx);
                            mPairedIdx[matchedIdx1] = maxIdx;
                        }
                        sUnpairedIdx.erase(matchedIdx1);
                        new_pair ++;
                        
                        printf("matched %d[%d] %d[%d]\n", newNum, i, pairNum0, minIdx);

                    } else if (isPrimePartner(newNum, pairNum1) && matchedIdx0) {
                        mPairedIdx[maxIdx] = i;
                        if (minIdx < matchedIdx0)
                            mPairedIdx[minIdx] = matchedIdx0;
                        else {
                            mPairedIdx.erase(minIdx);
                            mPairedIdx[matchedIdx0] = minIdx;
                        }
                        sUnpairedIdx.erase(matchedIdx0);
                        new_pair ++;
                        
                        printf("matched %d[%d] %d[%d]\n", newNum, i, pairNum1, maxIdx);
                    }
                    if(new_pair) break;
                }
            }

            if (!new_pair) sUnpairedIdx.insert(i);
            aMaxPairCount[i] = aMaxPairCount[i-1] + new_pair;
        }

        for (int i=0; i<=iCount; i++)
            printf("%d ", aMaxPairCount[i]);
        printf("\n");
        printf("%d\n", aMaxPairCount[iCount]);
        printf("%zd %zd\n", sUnpairedIdx.size(), mPairedIdx.size());
        
        mPairedIdx.clear();
        sUnpairedIdx.clear();
        delete aMaxPairCount;
    }
    return 0;
}