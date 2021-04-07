//
// Created by bloodik on 29.03.2021.
//

#ifndef TASK1_GRAMMAR_H
#define TASK1_GRAMMAR_H

#include <iostream>
#include <vector>

using namespace std;

class Grammar {
private:
    struct Rule {
        string from;
        string to;
    };

    string nonTerminals;
    string terminals;
    vector <Rule> rules;
    char startSymbol;

public:
    Grammar();

    string N() { return nonTerminals; }
    string T() { return terminals; }
    vector <Rule> P() { return rules; }
    char S() { return startSymbol; }

    void addRule(string from, string to);

    void printRules();

    bool useRule(string &word);


};




#endif //TASK1_GRAMMAR_H
