#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

void parse(const char* text, int len) {
    bool quato = false;

    stringstream ss;
    char ch;
    int count = 0;

    for (int i=0; i<len; i++) {
        ch = text[i];
        if (ch!=' ' && ch!='\"') ss << ch;
        if (ch=='\"') quato=!quato;
        if (i==len-1 || ch ==' ' && !quato) {
            count++;
            ss << endl;
        }
    }
    cout << count << endl;
    cout << ss.str();
}

int main() {
    string text;
    while (getline(cin, text)) {
        // cout << "src:" << text << endl;
        parse(text.c_str(), text.length());
    }
    return 0;
}