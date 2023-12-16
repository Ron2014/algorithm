#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

const int max_filename_len = 16;
const int max_record_len = 8;

int main(int argc, char *argv[])
{
    char line[101];
    int len;

    unordered_map<string, int> key2pos;
    vector<pair<string, int>> records(max_record_len);
    int index = 0;
    int count = 0;

    while (std::cin.getline(line, sizeof(line)))
    {
        int len = strlen(line);
        if (len <= 0) break;
        int i = len - 1;
        while (i >= 0 && line[i] != ' ') --i;
        // int lineno = atoi(line+1);
        int endIdx = i;
        while (i >= 0 && line[i] != '\\' && endIdx - i <= max_filename_len) --i;

        const char *key = line + i + 1;
        // cout << key << endl;

        unordered_map<string, int>::iterator it = key2pos.find(key);
        if (it != key2pos.end())
        {
            // cout << key << " " << it->second << endl;
            if (count - it->second > max_record_len)
            {
                continue;
            }
            records[it->second % max_record_len].second++;
        }
        else
        {
            // cout << key << " " << index << endl;
            key2pos[key] = count;
            pair<string, int> &p = records[index];
            p.first = key;
            p.second = 1;
            index = (index + 1) % max_record_len;
            count++;
        }
    }
    // cout << count << endl;
    if (count < max_record_len)
    {
        for (int i = 0; i < count; ++i)
        {
            cout << records[i].first << " " << records[i].second << endl;
        }
    }
    else
    {
        for (int i = 0; i < max_record_len; ++i)
        {
            cout << records[(i+index)%max_record_len].first << " " << records[(i+index)%max_record_len].second << endl;
        }
    }
    return 0;
}