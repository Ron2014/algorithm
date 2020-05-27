#include "../test.h"

/**
 * 1 0
 * 01 00 X
 * 11 10 
 * 11 01 X
 * 10 00 X
 * 111 101 X
 * 111 110
*/
class GrayCode {
public:
    vector<string> getGray(int n) {
        vector<string> result;
        if (n==1) {
            result.push_back("0");
            result.push_back("1");
        } else {
            char *buff = new char[n+1];
            vector<string> tmp = getGray(n-1);
            int len = tmp.size();
            
            for (int i=0; i<len; i++) {
                sprintf(buff, "0%s", tmp[i].c_str());
                buff[n] = 0;
                result.push_back(buff);
            }
            for (int i=len-1; i>=0; i--) {
                sprintf(buff, "1%s", tmp[i].c_str());
                buff[n] = 0;
                result.push_back(buff);
            }
        }
        return result;
    }
};

int main() {
    GrayCode s;
    int iNum;
    while (cin>>iNum) {
        vector<string> result = s.getGray(iNum);
        TEST_SHOW_ARRAY(result, result.size());
    }
}