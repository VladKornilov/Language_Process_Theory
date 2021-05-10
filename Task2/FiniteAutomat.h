#ifndef TASK2_FINITEAUTOMAT_H
#define TASK2_FINITEAUTOMAT_H

#include <vector>
#include "Grammar.h"

class FiniteAutomat
{
    set <char> terminals;
    set <char> nonTerminals;
    char startSymbol;

    vector <char> nodes;
    vector <vector <char> > edges;
    char finalNode = 'N';

    vector <string> detNodes;
    vector <vector <char> > detEdges;

    void generateGraph(Grammar &g);
    void printTable(vector <vector <set <char> > > &table);


public:
    FiniteAutomat(Grammar &g);

    void printGraph();
    void transformDetGraph();
    void printDetGraph();
};

#endif // TASK2_FINITEAUTOMAT_H
