#include <iostream>
using namespace std;

string strShort;
string strLong;

int getLongestCommonSubstr(const char *str0, int len0, const char *str1, int len1) {
    int maxLen = 0;

    for (int i=0; i<len1; i++) {
        for (int j=0; j<len0; j++) {
            int matchLen = 0;
            while (str1[i+matchLen] == str0[j+matchLen] && matchLen<len0-j)
                matchLen++;
            if (maxLen < matchLen)
                maxLen = matchLen;
        }
    }
    return maxLen;
}

int main() {
    while (cin >> strShort >> strLong) {
        if (strShort.length() > strLong.length()) {
            string tmp = strShort;
            strShort = strLong;
            strLong = tmp;
        }

        int maxLen = getLongestCommonSubstr(strShort.c_str(), strShort.length(), strLong.c_str(), strLong.length());
        cout << maxLen << endl;
    }
    return 0;
}