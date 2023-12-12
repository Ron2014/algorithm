/*
有一个文件, 包含以一定规则写作的文本, 请统计文件中包含的文本数量


规则如下

1. 文本以";"分隔，最后一条可以没有";"，但空文本不能算语句，比如"COMMAND A; ;"只能算一条语句.
    注意, 无字符/空白字符/制表符都算作"空"文本
2. 文本可以跨行, 比如下面, 是一条文本, 而不是三条
    COMMAND A
        AND
    COMMAND B;
3. 文本支持字符串, 字符串为成对的单引号(')或者成对的双引号("), 字符串可能出现用转义字符(\)处理的单双引号(比如"your input is: \"")和转义字符本身, 比如
    COMMAND A "Say \"hello\"";
4. 支持注释, 可以出现在字符串之外的任意位置, 注释以"--"开头, 到换行结束, 比如
    COMMAND A; -- this is comment
    COMMAND -- comment
              A AND COMMAND B;
     注意, 字符串内的"--", 不是注释

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <set>
using namespace std;

/*
    'c': a-z A-Z 0-9
    's': ' ' \t \r
    'l': \n
    'b': \\
    'q': \'
    'p': \"
    '-': -
    ';': ;
    '*': 任意字符
*/

vector<unordered_map<char, int>> g_state = {
    /* 0*/{{'c',  1}, {'s',  0}, {'l', 0}, {'-', 4}, {';', 0}},                         // 语句第一个字符，可结束
    /* 1*/{{'c',  1}, {'s',  1}, {'l', 1}, {';', 0}, {'-', 2}, {'q', 6}, {'p', 12}},    // 语句内容，可结束

    /* 2*/{{'-',  3}},                                                                  // 语句内注释开始
    /* 3*/{{'*',  3}, {'l',  1},},                                                      // 语句内注释结束

    /* 4*/{{'-',  5}},                                                                  // 语句外注释开始
    /* 5*/{{'*',  5}, {'l',  0},},                                                      // 语句外注释结束

    /* 6*/{{'*',  6}, {'q',  1}, {'b', 7}, {'p', 18}, },                                // '开始字符串
    /* 7*/{{'q',  8}, {'p', 10}, },                                                     // 字符串内字符串开始
    /* 8*/{{'*',  8}, {'b',  9}, {'p', 18}, },                                          // \'开始
    /* 9*/{{'q',  6}, },                                                                // \'结束
    /*10*/{{'*', 10}, {'b', 11}, {'q', 18}, },                                          // \"开始
    /*11*/{{'p',  6}, },                                                                // \"结束

    /*12*/{{'*', 12}, {'p', 1}, {'b', 13}, {'q', 18}, },                                // "开始字符串
    /*13*/{{'q', 14}, {'p', 16},},                                                      // 字符串内字符串开始
    /*14*/{{'*', 14}, {'b', 15}, {'p', 18}, },                                          // \'开始
    /*15*/{{'q', 12}, },                                                                // \'结束
    /*16*/{{'*', 16}, {'b', 17}, {'q', 18}, },                                          // \"开始
    /*17*/{{'p', 12}, },                                                                // \"结束

    /*18*/{{';',  0}, {'l', 0}},
};

const int FIN_STATE = 1;
const int ERR_STATE = 18;

int main(int argc, char *argv[])
{
    string filename;
    while (cin >> filename)
    {
        fstream file(filename.c_str());
        if (!file.is_open()) break;

        char ch;
        int count = 0;
        int stateIdx = 0;
        while (file.get(ch))
        {
            if (ch == ';')
            {
                // 结束符 
                ch = ';';
            }
            else if (ch == '\n')
            {
                ch = 'l';
            }
            else if (isspace(ch))
            {
                // 空白符、制表符、换行符
                ch = 's';
            }
            else if (isalnum(ch))
            {
                // 内容
                ch = 'c';
            }
            else if (ch == '\'')
            {
                ch = 'q';
            }
            else if (ch == '\"')
            {
                ch = 'p';
            }
            else if (ch == '\\')
            {
                // 准备转义
                ch = 'b';
            }
            else if (ch == '-')
            {
                // 准备注释
                ch = '-';
            }
            else
            {
                ch = '?';
            }

            unordered_map<char, int>::iterator it = g_state[stateIdx].find(ch);
            if (it == g_state[stateIdx].end())
            {
                it = g_state[stateIdx].find('*');
            }

            if (it == g_state[stateIdx].end())
            {
                stateIdx = ERR_STATE;
            }
            else
            {
                if (ch == ';' && stateIdx == FIN_STATE)
                {
                    count++;
                }
                stateIdx = it->second;
            }
        }

        if (stateIdx == FIN_STATE)
        {
            count++;
        }
        cout << count << endl;

        file.close();
    }
    return 0;
}

