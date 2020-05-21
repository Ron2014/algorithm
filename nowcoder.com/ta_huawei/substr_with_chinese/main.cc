#include <iostream>
using namespace std;

string text;
int sublen;

int main(){
    while (cin>>text) {
        cin >> sublen;
        int length = text.length();
        printf("%d\n", length);

        const char *str_text = text.c_str();
        for (int i=0; i<length; i++) {
            char c = str_text[i];
            printf("%d %c\n", c, c);
        }
    }
    return 0;
}