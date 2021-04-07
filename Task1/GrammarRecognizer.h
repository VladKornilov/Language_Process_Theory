//
// Created by bloodik on 29.03.2021.
//

#ifndef TASK1_GRAMMARRECOGNIZER_H
#define TASK1_GRAMMARRECOGNIZER_H

#include "Grammar.h"

class GrammarRecognizer {
    bool matchesPattern(string &what, string pattern);
    bool isTerminal(char c) {
        return ('a' <= c && c <= 'z');
    }
    bool isNonTerminal(char c) {
        return ('A' <= c && c <= 'Z');
    }
    bool isEpsilon(char c) {
        return c == '~';
    }

    bool isLeft(string &from, string &to);
    bool isRight(string &from, string &to);
    bool isRegular(string &from, string &to);

    bool isContextFree(string &from, string &to);

    bool isContext(string &from, string &to);


    enum GrammarType {ZERO, CONTEXT_SENSITIVE, CONTEXT_FREE, REGULAR, LEFT, RIGHT, ANY};

    GrammarType recognizeRule(string &from, string &to);

public:

    string recognizeGrammar(Grammar g);
};


#endif //TASK1_GRAMMARRECOGNIZER_H
