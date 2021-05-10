#ifndef TASK2_REGULARRECOGNIZER_H
#define TASK2_REGULARRECOGNIZER_H

#include "Grammar.h"

class RegularRecognizer
{
    bool matchesPattern(string &what, string pattern);
    bool isTerminal(char c) {
        return !isNonTerminal(c) && !isEpsilon(c);
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

    enum GrammarType {OTHER, REGULAR, LEFT, RIGHT, ANY};

    GrammarType recognizeRule(string &from, string &to);

public:
    string recognizeGrammar(Grammar g);
};

#endif // TASK2_REGULARRECOGNIZER_H
