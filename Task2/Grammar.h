#ifndef TASK2_GRAMMAR_H
#define TASK2_GRAMMAR_H

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Grammar {
private:
    struct Rule {
        string from;
        string to;
    };

    set <char> nonTerminals;
    set <char> terminals;
    vector <Rule> rules;
    char startSymbol;

    bool isTerminal(char c) {
        return !isNonTerminal(c) && !isEpsilon(c);
    }
    bool isNonTerminal(char c) {
        return ('A' <= c && c <= 'Z');
    }
    bool isEpsilon(char c) {
        return c == '~';
    }

public:
    Grammar();

    set <char> N() { return nonTerminals; }
    set <char> T() { return terminals; }
    vector <Rule> P() { return rules; }
    char S() { return startSymbol; }

    void addRule(string from, string to);

    void printRules();

    bool useRule(string &word);


};




#endif //TASK2_GRAMMAR_H
