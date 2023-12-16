#include "../test.h"
#include <memory.h>

class Solution {
private:
    int *data;
    int *mindata;            // minimum of front data;
    unsigned int capacity;
    unsigned int size;

public:
    Solution():capacity(8), size(0) {
        data = (int*)realloc(NULL, sizeof(int)*capacity);
        mindata = (int*)realloc(NULL, sizeof(int)*capacity);
    }

    void push(int value) {
        if (size==capacity) {
            capacity *= 2;
            data = (int*)realloc(data, sizeof(int)*capacity);
            mindata = (int*)realloc(data, sizeof(int)*capacity);
        }

        if (!size || mindata[size-1]>value)
            mindata[size] = value;
        else
            mindata[size] = mindata[size-1];
        data[size++] = value;
    }

    void pop() {
        if (size) size--;
    }

    int top() {
        if (size)
            return data[size-1];
        else
            return -1;
    }

    int min() {
        if (size)
            return mindata[size-1];
        else
            return -1;
    }
};

int main() {
    // int iCount, iNum;
    // while(cin>>iCount) {
    //     Solution s;

    //     for (int i=0; i<iCount; i++) {
    //         cin>>iNum;
    //         s.push(iNum);
    //         TEST_HINT(min:)
    //         cout << s.min() << endl;
    //     }

    //     TEST_HINT(pop-------------)
    //     for (int i=0; i<iCount; i++) {
    //         cout << s.top() << endl;
    //         s.pop();
    //     }

    // }

    Solution s;
    string text;
    while (cin>>text) {
        if (text.find("PSH")==0) {
            int iNum = atoi(text.c_str()+3);
            s.push(iNum);
        } else if (text.find("POP")==0) {
            s.pop();
        } else if (text.find("MIN")==0) {
            cout << s.min() << endl;
        }
    }
    return 0;
}