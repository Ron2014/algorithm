#include <iostream>
using namespace std;
#include <cstring>
#include <algorithm>
#include <vector>

char chText[1024];

const char* COMMANDS[] = {
    "reset", "reset what",
    "reset board", "board fault",
    "board add", "where to add",
    "board delet", "no board at all",
    "reboot backplane", "impossible",
    "backplane abort", "install first",
    NULL,
};

#define COMMAND_COUNT 6

int main() {
    string text;
    vector<string> matches;
    bool is_matched;
    while (getline(cin, text)) {
        strncpy(chText, text.c_str(), text.length()-1); // remove CR
        chText[text.length()-1] = '\0';

        matches.clear();
        for (int i=0; i<COMMAND_COUNT; i++) {
            string key = COMMANDS[i*2];
            string value = COMMANDS[i*2+1];

            int c = count(text.begin(), text.end(), ' ');
            if (c!= count(key.begin(), key.end(), ' ')) continue;

            string backup = chText;
            is_matched = true;
            while (c--) {
                int pos = text.find(' ');
                string token = backup.substr(0, pos);
                backup = backup.substr(pos+1, backup.length()-pos-1);

                pos = key.find(' ');
                string token_key =  key.substr(0, pos);
                key = key.substr(pos+1, key.length()-pos-1);

                if (token_key.find(token)!=0) {
                    // not match
                    is_matched = false;
                    break;
                }
            }

            if (is_matched && key.find(backup)==0)
                matches.push_back(value);
        }

        if (matches.size()==1) {
            cout << matches[0] << endl;
        } else {
            cout << "unkown command" << endl;
        }
    }
    return 0;
}