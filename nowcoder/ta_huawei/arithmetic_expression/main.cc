#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <assert.h>
using namespace std;

// #define TEST

#ifdef TEST
#define SHOW show();
#else
#define SHOW
#endif

int priority(char ch) {
    switch(ch) {
        case '}':
        case ']':
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '(':
        case '[':
        case '{':
            return 4;
    }
    return 0;
}

bool isOperator(char ch) {
    switch(ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        return true;
    }
    return false;
}

bool isOpenScope(char ch) {
    switch(ch) {
        case '(':
        case '[':
        case '{':
        return true;
    }
    return false;
}

bool isCloseScope(char ch) {
    switch(ch) {
        case ')':
        case ']':
        case '}':
        return true;
    }
    return false;
}

bool matchScope(char open_scope, char ch) {
    bool matched = false;
    switch (open_scope) {
        case '(':
            if (ch == ')') matched = true;
            break;
        case '[':
            if (ch == ']') matched = true;
            break;
        case '{':
            if (ch == '}') matched = true;
            break;
    }
    return matched;
}

int execute(const char &op, const int &oprandL, const int &oprandR) {
    switch (op) {
        case '+':
            return oprandL + oprandR;
        case '-':
            return oprandL - oprandR;
        case '*':
            return oprandL * oprandR;
        case '/':
            assert(oprandR && "divisor is zero!");
            return oprandL / oprandR;   // check 0
    }
    return 0;
}

string StrExpression;
const char* Text;
int Length;
int Pos;

vector<char> Symbols;
vector<int> Nums;

// 1. get all oprand number
// 2. update pos: infer next
int getOperand() {
    stringstream ss;
    while(Pos<Length && isdigit(Text[Pos])) {
        ss << Text[Pos++];
    }
    return atoi(ss.str().c_str());
}

void show() {
    int size = Symbols.size();
    for (int i=0; i<size; i++)
        cout << Symbols[i] << " ";
    cout << endl;

    size = Nums.size();
    for (int i=0; i<size; i++)
        cout << Nums[i] << " ";
    cout << endl;
}

void calcNum(int &oprand) {
    // roll back the result by stacks

    char next = Text[Pos];
    char last = Symbols.empty() ? '\0' : Symbols[Symbols.size()-1];

    while (isOperator(last) && priority(last)>=priority(next)) {
        // last is higher operator
        // calculate
        assert(!Nums.empty() && "left oprand empty");
        
        int oprandL = Nums[Nums.size()-1];
        int op = last;
        int oprandR = oprand;
        
        Nums.pop_back();         // remove left oprand
        Symbols.pop_back();      // remove operator

        last = Symbols.empty() ? '\0' : Symbols[Symbols.size()-1];
        oprand = execute(op, oprandL, oprandR);
    }
}

int main() {
    while (cin >> StrExpression) {
        Symbols.clear();
        Nums.clear();

        Text = StrExpression.c_str();
        Length = StrExpression.length();
        Pos = 0;
    
        while(Pos<Length) {
            SHOW

            char ch = Text[Pos];
            char next = Text[Pos+1];
            char last = Symbols.empty() ? '\0' : Symbols[Symbols.size()-1];

            if (isdigit(ch)) {
                int oprand = getOperand();
                calcNum(oprand);
                Nums.push_back(oprand);

            } else if (isOperator(ch)) {
                if (Pos==0 || isOpenScope(Text[Pos-1])) {
                    assert((ch == '-' || ch == '+') && "unary operator error!");
                    Nums.push_back(0);
                }
                Symbols.push_back(ch);
                Pos++;

            } else if (isOpenScope(ch)) {
                Symbols.push_back(ch);
                Pos++;

            } else if (isCloseScope(ch)) {
                assert(matchScope(last, ch) && "scope not matched!");
                Symbols.pop_back();
                Pos++;

                // finished sub expression in scope means:
                // result saved in nums
                int oprand = Nums[Nums.size()-1];
                Nums.pop_back();

                calcNum(oprand);
                Nums.push_back(oprand);
            }
        }
        SHOW

        assert(Nums.size()==1 && "calc error!");
        cout << Nums[0] << endl;
    }

    return 0;
}