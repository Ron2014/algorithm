#include <iostream>
using namespace std;

string strShort;
string strLong;

int getLongestCommonSubstr(const char *str0, int len0, const char *str1, int len1, int &maxLen) {
    int startIdx = -1;

    for (int i=0; i<len1; i++) {
        for (int j=0; j<len0; j++) {
            int matchLen = 0;
            while (str1[i+matchLen] == str0[j+matchLen] && matchLen<len0-j)
                matchLen++;

            if (maxLen < matchLen) {
                startIdx = j;
                maxLen = matchLen;
            }else if (matchLen && maxLen==matchLen && j < startIdx) {
                startIdx = j;
            }
        }
    }
    return startIdx;
}

int main() {
    while (cin >> strShort >> strLong) {
        if (strShort.length() > strLong.length()) {
            string tmp = strShort;
            strShort = strLong;
            strLong = tmp;
        }

        const char *chShort = strShort.c_str();
        int maxLen = 0;
        int idx = getLongestCommonSubstr(chShort, strShort.length(), strLong.c_str(), strLong.length(), maxLen);
        // cout << strShort.length() << " " <<  maxLen << " " << idx <<  endl;
        while(maxLen--)
            printf("%c", chShort[idx++]);
        cout << endl;
    }
    return 0;
}