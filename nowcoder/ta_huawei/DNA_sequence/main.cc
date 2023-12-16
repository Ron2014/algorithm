#include <iostream>
using namespace std;

string seq;
int minStrLen;

double GCRatio(const char* ch, int len) {
    int i = 0;
    int count = 0;

    while(i < len) {
        if (*(ch+i) == 'G' || *(ch+i) == 'C') count++;
        i++;
    }

    return count * 1.0 / len;
}

int main() {
    while (cin >> seq) {
        int iLen = seq.length();
        const char* chSeq = seq.c_str();

        // check valid sequence
        bool invalid = false;
        for (int i=0; i<iLen; i++) {
            if (chSeq[i] != 'A' && chSeq[i] != 'G' && chSeq[i] != 'C' && chSeq[i] != 'T') {
                invalid = true;
                break;
            }
        }
        if (invalid) continue;

        cin >> minStrLen;

        if (minStrLen >= iLen) {
            cout << chSeq << endl;
            continue;
        }

        double maxRatio = 0.0;
        int maxPos = 0;
        int maxLen = 0;

        for(int pos_s=0; pos_s<iLen-minStrLen; pos_s++) {
    
#ifdef EXTRA_STR
            for (int strLen=minStrLen; strLen<iLen-pos_s; strLen++) {
                double r = GCRatio(chSeq+pos_s, strLen);
                if (r > maxRatio) {
                    maxRatio = r;
                    maxPos = pos_s;
                    maxLen = strLen;
                }
            }
#else
            double r = GCRatio(chSeq+pos_s, minStrLen);
            if (r > maxRatio) {
                maxRatio = r;
                maxPos = pos_s;
                maxLen = minStrLen;
            }
#endif
        }

        for (int i=0; i<maxLen; i++)
            cout << *(chSeq+maxPos+i);
        cout << endl;

    }
    return 0;
}