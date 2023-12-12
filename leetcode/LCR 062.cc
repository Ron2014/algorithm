#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Trie {
    unordered_map<char, Trie> m_mp;
    unordered_set<string> m_words;

    void insert(string &word, int idx)
    {
        if (idx >= word.length())
        {
            m_words.insert(word);
        }
        else
        {
            m_mp[word[idx]].insert(word, idx+1);
        }
    }

    bool search(string &word, int idx)
    {
        if (idx >= word.length())
        {
            return m_words.find(word) != m_words.end();
        }
        else
        {
            auto it = m_mp.find(word[idx]);
            if (it == m_mp.end()) return false;
            return it->second.search(word, idx+1);
        }
    }

    bool startsWith(const char *sz)
    {
        if (*sz == '\0') return m_mp.size() > 0 || m_words.size() > 0;
        auto it = m_mp.find(*sz);
        if (it == m_mp.end()) return false;
        return it->second.startsWith(sz+1);
    }

public:
    /** Initialize your data structure here. */
    Trie() {

    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        const char *sz = word.c_str();
        m_mp[*sz].insert(word, 1);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        const char *sz = word.c_str();
        auto it = m_mp.find(*sz);
        if (it == m_mp.end()) return false;
        return it->second.search(word, 1);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        const char *sz = prefix.c_str();
        auto it = m_mp.find(*sz);
        if (it == m_mp.end()) return false;
        return it->second.startsWith(sz+1);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main(int arg, char *argv[])
{
    Trie trie;
    string cmd;
    while (cin >> cmd)
    {
        int len = cmd.length();
        if (len <= 0) break;

        if (cmd == "insert")
        {
            string word;
            cin >> word;
            trie.insert(word);
        }
        else if (cmd == "search")
        {
            string word;
            cin >> word;
            cout << (int)trie.search(word) << endl;
        }
        else if (cmd == "startsWith")
        {
            string word;
            cin >> word;
            cout << (int)trie.startsWith(word) << endl;
        }
        else
        {
            cout << "ERROR" << endl;
        }
    }
    return 0;
}