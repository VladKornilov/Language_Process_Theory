#include "RegularRecognizer.h"


bool RegularRecognizer::matchesPattern(string &what, string pattern) {
    if (what.length() != pattern.length()) return false;
    for (int i = 0; i < what.length(); i++) {
        if (isTerminal(what[i]) && pattern[i] != 'T') return false;
        if (isNonTerminal(what[i]) && pattern[i] != 'N') return false;
        if (isEpsilon(what[i]) && pattern[i] != 'E') return false;
    }
    return true;
}

bool RegularRecognizer::isLeft(string &from, string &to) {
    if (!matchesPattern(from, "N")) return false;
    if (!matchesPattern(to, "T")
        &&
        !matchesPattern(to, "NT"))
        return false;
    return true;
}

bool RegularRecognizer::isRight(string &from, string &to) {
    if (!matchesPattern(from, "N")) return false;
    if (!matchesPattern(to, "T")
        &&
        !matchesPattern(to, "TN"))
        return false;
    return true;
}


bool RegularRecognizer::isRegular(string &from, string &to) {
    if (!matchesPattern(from, "N")) return false;
    if (!matchesPattern(to, "T")
        &&
        !matchesPattern(to, "TNT"))
        return false;
    return true;
}

RegularRecognizer::GrammarType RegularRecognizer::recognizeRule(string &from, string &to)
{
    if (isLeft(from, to) && isRight(from, to)) return ANY;
    if (isLeft(from, to)) return LEFT;
    if (isRight(from, to)) return RIGHT;
    if (isRegular(from, to)) return REGULAR;
    return OTHER;
}

string RegularRecognizer::recognizeGrammar(Grammar g) {
    if (g.P().empty()) return "other";
    GrammarType type = recognizeRule(g.P()[0].from, g.P()[0].to);

    for (auto rule : g.P()) {
        GrammarType curType = recognizeRule(rule.from, rule.to);
        if ((type == LEFT && curType == RIGHT)
                ||
                (type == RIGHT && curType == LEFT))
            type = REGULAR;
        else if (curType < type)
            type = curType;
    }
    if (type == LEFT) return "regular: left-linear";
    if (type == RIGHT) return "regular: right-linear";
    if (type == REGULAR) return "regular";
    return "other";
}
