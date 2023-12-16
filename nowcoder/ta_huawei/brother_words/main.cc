#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stdio.h>

int lenDict;
char word[51];
char searchWord[51];
int searchIndex;

std::map<std::string, std::vector<std::string> > brotherDict;

int main() {
    while(scanf("%d", &lenDict) != EOF) {
        brotherDict.clear();

        for (int i=0; i<lenDict; i++) {
            scanf("%s", word);

            std::string brotherKey = word;
            sort(brotherKey.begin(), brotherKey.end());

            if (brotherDict.find(brotherKey) != brotherDict.end()) {
                brotherDict[brotherKey].push_back(word);
            } else {
                std::vector<std::string> v;
                v.push_back(word);
                brotherDict[brotherKey] = v;
            }
        }

        scanf("%s %d", searchWord, &searchIndex);
        std::string brotherKey = searchWord;
        sort(brotherKey.begin(), brotherKey.end());

        int brotherCount = 0;
        std::string brotherWord = "";

        auto it = brotherDict.find(brotherKey);
        if (it != brotherDict.end()) {
            std::vector<std::string> &records = it->second;
            sort(records.begin(), records.end());

            auto it0 = records.begin();
            while(it0 != records.end()) {
                if (*it0 == searchWord){
                    it0++;
                    continue;
                }
                brotherCount++;
                if (brotherCount == searchIndex) brotherWord = *it0;
                it0++;
            }
        }

        printf("%d\n%s\n", brotherCount, brotherWord.c_str());
    }
    return 0;
}