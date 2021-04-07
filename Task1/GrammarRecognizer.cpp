//
// Created by bloodik on 29.03.2021.
//

#include "GrammarRecognizer.h"

bool GrammarRecognizer::matchesPattern(string &what, string pattern) {
    if (what.length() != pattern.length()) return false;
    for (int i = 0; i < what.length(); i++) {
        if (isTerminal(what[i]) && pattern[i] != 'T') return false;
        if (isNonTerminal(what[i] && pattern[i] != 'N')) return false;
        if (isEpsilon(what[i]) && pattern[i] != 'E') return false;
    }
    return true;
}


bool GrammarRecognizer::isLeft(string &from, string &to) {
    if (!matchesPattern(from, "N")) return false;
    if (!matchesPattern(to, "T")
        &&
        !matchesPattern(to, "NT"))
        return false;
    return true;
}

bool GrammarRecognizer::isRight(string &from, string &to) {
    if (!matchesPattern(from, "N")) return false;
    if (!matchesPattern(to, "T")
        &&
        !matchesPattern(to, "TN"))
        return false;
    return true;
}


bool GrammarRecognizer::isRegular(string &from, string &to) {
    if (!matchesPattern(from, "N")) return false;
    if (!matchesPattern(to, "T")
        &&
        !matchesPattern(to, "TNT"))
        return false;
    return true;
}

bool GrammarRecognizer::isContextFree(string &from, string &to) {
    if (!matchesPattern(from, "N")) return false;
    return true;
}

bool GrammarRecognizer::isContext(string &from, string &to) {
    if (from.length() > to.length()) return false;
    for (int i = 0; i < from.length(); i++) {
        if (isNonTerminal(from[i])) {
            int leftLen = i, rightLen = from.length() - i - 1;
            if (from.substr(0, leftLen) == to.substr(0, leftLen)
                &&
                from.substr(from.length() - rightLen) == to.substr(to.length() - rightLen)) {
                return true;
            }
        }
    }
    return false;
}



GrammarRecognizer::GrammarType GrammarRecognizer::recognizeRule(string &from, string &to) {
    if (isLeft(from, to) && isRight(from, to)) return ANY;
    if (isLeft(from, to)) return LEFT;
    if (isRight(from, to)) return RIGHT;
    if (isRegular(from, to)) return REGULAR;
    if (isContextFree(from, to)) return CONTEXT_FREE;
    if (isContext(from, to)) return CONTEXT_SENSITIVE;
    return ZERO;
}

string GrammarRecognizer::recognizeGrammar(Grammar g) {
    if (g.P().empty()) return "zero";
    GrammarType type = recognizeRule(g.P()[0].from, g.P()[0].to);

    for (auto rule : g.P()) {
        GrammarType curType = recognizeRule(rule.from, rule.to);
        if (type == LEFT && curType == RIGHT
                ||
                type == RIGHT && curType == LEFT)
            type = REGULAR;
        else if (curType < type)
            type = curType;
    }
    if (type == LEFT) return "left";
    if (type == RIGHT) return "right";
    if (type == REGULAR) return "regular";
    if (type == CONTEXT_FREE) return "context free";
    if (type == CONTEXT_SENSITIVE) return "context sensitive";
    return "zero";
}








