#include "../test.h"

void getResult(char* text, int len) {
    char *head = text+len-1, *tail = text+len-1;
    char temp, *mv;

    while(head>=text && tail>=text) {
        while(*tail>='A' && *tail<='Z') tail--;
        while(*head>='a' && *head<='z') head--;
        if (head<text || tail<text) break;
        if (head<tail) {
            // TEST_INFO2(char:,*head, *tail);
            temp = *head;
            mv = head;
            while(mv++<tail) *(mv-1) = *mv;
            // strncpy(head, head+1, tail-head);
            *tail = temp;
        }
        head--;
    }
    cout << text << endl;
}

int main() {
    string text;
    while (cin>>text) {
        getResult(const_cast<char*>(text.c_str()), text.length());
    }
}