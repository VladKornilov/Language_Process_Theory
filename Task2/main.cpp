#include <iostream>
#include <fstream>
#include "Grammar.h"
#include "RegularRecognizer.h"
#include "FiniteAutomat.h"

using namespace std;

Grammar enterGrammar(istream &in) {
    Grammar g;
    int n;
    in >> n;
    for (int i = 0; i < n; i++) {
        string from, to;
        in >> from >> to;
        g.addRule(from, to);
    }
    return g;
}

int main()
{
    ifstream fin("input.txt");
    Grammar g = enterGrammar(fin);
    g.printRules();
    RegularRecognizer rr;

    string grammarType = rr.recognizeGrammar(g);
    if (grammarType.find("right") != string::npos) {
        FiniteAutomat automat(g);
        automat.printGraph();
        automat.transformDetGraph();
        cout << "\n---------------------------------------\n";
        automat.printDetGraph();
        cout << endl;
    }
}
