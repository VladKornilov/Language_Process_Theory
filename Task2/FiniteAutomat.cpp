#include "FiniteAutomat.h"


FiniteAutomat::FiniteAutomat(Grammar &g)
{
    terminals = g.T();
    nonTerminals = g.N();
    nonTerminals.insert(finalNode);
    startSymbol = g.S();

    generateGraph(g);
}

void FiniteAutomat::generateGraph(Grammar &g)
{
    // create nodes
    for (auto rule : g.P()) {
        char from = rule.from[0];
        char to;
        if (rule.to.length() == 1) to = finalNode;
        else to = rule.to[1];

        bool exists = false;
        for (auto i : nodes)
            if (i == from)
                exists = true;
        if (!exists)
            nodes.push_back(from);

        exists = false;
        for (auto i : nodes)
            if (i == to)
                exists = true;
        if (!exists)
            nodes.push_back(to);
    }

    // create edges
    edges.resize(nodes.size());
    for (int i = 0; i < nodes.size(); i++)
        edges[i].resize(nodes.size(), 0);

    for (auto rule : g.P()) {
        char from = rule.from[0];
        char sym = rule.to[0];
        char to;
        if (rule.to.length() == 1) to = finalNode;
        else to = rule.to[1];

        for (int i = 0; i < nodes.size(); i++)
            for (int j = 0; j < nodes.size(); j++)
                if (nodes[i] == from && nodes[j] == to)
                    edges[i][j] = sym;
    }
}

void FiniteAutomat::transformDetGraph()
{
    vector <vector <set <char> > > table(1);
    // column consists of [term.size] rows + 1 for column name
    table[0].resize(terminals.size() + 1);
    table[0].back().insert(startSymbol);
    int curColumn = 0;
    while (curColumn < table.size()) {
        vector<int> usedNodes;
        // save nodes, that will be checked for future
        for (int i = 0; i < nodes.size(); i++)
            if (table[curColumn].back().count(nodes[i]))
                usedNodes.push_back(i);
        // fill current column
        for (int node : usedNodes) {
            for (int i = 0; i < edges[node].size(); i++) {
                if (edges[node][i] != 0) {
                    int pos = distance(terminals.begin(), terminals.find(edges[node][i]));
                    table[curColumn][pos].insert(nodes[i]);
                }
            }
        }
        for (int i = 0; i < terminals.size(); i++) {
            set<char> detNode = table[curColumn][i];
            if (detNode.empty()) continue;
            if (detNode.size() == 1 && detNode.count(finalNode)) continue;

            bool containsNode = false;
            for (int col = 0; col < curColumn; col++)
                if (table[col].back() == detNode)
                    containsNode = true;
            if (!containsNode) {
                table.resize(table.size() + 1);
                table.back().resize(terminals.size() + 1);
                table.back().back() = detNode;
            }
        }
        curColumn++;
    }

    printTable(table);

    for (int i = 0; i < table.size(); i++) {
        string nodeName;
        for (char c : table[i].back())
            nodeName += c;
        detNodes.push_back(nodeName);
    }
    string finalNodeName;
    finalNodeName += finalNode;
    detNodes.push_back(finalNodeName);
    int size = detNodes.size();
    detEdges.resize(size);
    for (int i = 0; i < size; i++)
        detEdges[i].resize(size, 0);
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size() - 1; j++) {
            set <char> connectedNode = table[i][j];
            if (connectedNode.size() == 1 && connectedNode.count(finalNode))
                detEdges[i][size - 1] = *(next(terminals.begin(), j));
            else
                for (int k = 0; k < table.size(); k++)
                    if (connectedNode == table[k].back())
                        detEdges[i][k] = *(next(terminals.begin(), j));
        }
    }
}

void FiniteAutomat::printTable(vector <vector <set <char> > > &table) {
    cout << "Temp table for det graph:\n";
    auto tmp = terminals.begin();
    for (int i = 0; i < table[0].size(); i++) {
        cout << *tmp << '\t';
        tmp++;
        for (int j = 0; j < table.size(); j++) {
            for (char c : table[j][i])
                cout << c;
            cout << '\t';
        }
        cout << endl;
    }
}


void FiniteAutomat::printGraph()
{
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            if (edges[i][j] != 0)
                cout << nodes[i] << " -- " << edges[i][j] << " -> " << nodes[j] << endl;
        }
    }
}

void FiniteAutomat::printDetGraph()
{
    for (int i = 0; i < detEdges.size(); i++) {
        for (int j = 0; j < detEdges[i].size(); j++) {
            if (detEdges[i][j] != 0)
                cout << detNodes[i] << " -- " << detEdges[i][j] << " -> " << detNodes[j] << endl;
        }
    }
}
