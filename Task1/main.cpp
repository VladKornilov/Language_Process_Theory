#include <iostream>
#include <fstream>
#include <vector>
#include "GrammarRecognizer.h"
#include "Grammar.h"

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

int main(int argc, char* argv[]) {
    Grammar grammar;

    if (argc > 1) {
        ifstream fin(argv[1]);
        grammar = enterGrammar(fin);
    }
    else {
        grammar = enterGrammar(cin);
    }

    grammar.printRules();

    GrammarRecognizer gr;
    string grammarType = gr.recognizeGrammar(grammar);
    cout << "Grammar type: " << grammarType << endl;

//    while (true) {
//        cout << "Enter word to process: ";
//        string word;
//        cin >> word;
//        cout << "Processed: " << word << endl;
//    }

}
