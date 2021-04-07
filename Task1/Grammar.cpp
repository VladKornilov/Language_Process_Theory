//
// Created by bloodik on 29.03.2021.
//

#include "Grammar.h"

Grammar::Grammar() {
    startSymbol = 0;
}

void Grammar::addRule(string from, string to) {
    rules.push_back({from, to});
    if (startSymbol == 0)
        startSymbol = from[0];
}

void Grammar::printRules() {
    cout << "Grammar:\n";
    for (int i = 0; i < rules.size(); i++) {
        cout << i << ") " << rules[i].from << " -> " << rules[i].to << endl;
    }
    cout << endl;
}

bool Grammar::useRule(string &word) {
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j < rules.size(); j++) {
            int n = rules[j].from.length();
            if (word.substr(i, i + n) == rules[i].from) {
                string tmp = word.substr(0, i) + rules[i].to + word.substr(i + n);
                word = tmp;
                return true;
            }
        }
    }
    return false;
}

