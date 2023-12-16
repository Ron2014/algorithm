#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

const int MIN_PASSWORD_LEN = 8;
const int KEY_NUM = 0;
const int KEY_LOWER = 1;
const int KEY_UPPER = 2;
const int KEY_OTHER = 3;
const int MIN_INCLUDE_TYPE_LEN = 3;
const int MIN_SUBSTR_LEN = 3;

int main(int argc, char *argv[])
{
    char line[101];
    while (std::cin.getline(line, sizeof(line)))
    {
        int len = strlen(line);
        if (len <= 0) break;

        bool bInvalid = false;

        do {
            if (len < MIN_PASSWORD_LEN)
            {
                bInvalid = true;
                // cout << "len err" << endl;
                break;
            }

            unordered_map<int, int> records;
            for (int i = 0; i < len; ++i)
            {
                if (isdigit(line[i]))
                {
                    records[KEY_NUM]++;
                }
                else if (line[i] >= 'a' && line[i] <= 'z')
                {
                    records[KEY_LOWER]++;
                }
                else if (line[i] >= 'A' && line[i] <= 'Z')
                {
                    records[KEY_UPPER]++;
                }
                else if (line[i] != ' ' && line[i] != '\r' && line[i] != '\n')
                {
                    records[KEY_OTHER]++;
                }
                else
                {
                    bInvalid = true;
                    // cout << "char err: " << line[i] << endl;
                    break;
                }
                if (i < len - MIN_SUBSTR_LEN + 1)
                {
                    for (int j = 0; j <= i - MIN_SUBSTR_LEN; ++j)
                    {
                        if (strncmp(line + i, line + j, MIN_SUBSTR_LEN) == 0)
                        {
                            // cout << "substr err: " << line + i << endl;
                            bInvalid = true;
                            break;
                        }
                    }
                    if (bInvalid) break;
                }
            }
            if (records.size() < MIN_INCLUDE_TYPE_LEN)
            {
                // cout << "type err: " << records.size() << endl;
                bInvalid = true;
            }
        } while (0);

        if (bInvalid)
        {
            cout << "NG" << endl;
        }
        else
        {
            cout << "OK" << endl;
        }
    }
    return 0;
}