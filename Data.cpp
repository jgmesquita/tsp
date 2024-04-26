#include "Graph.h"
#include "Data.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"

using namespace std;

void Data::parseGraph() {
    ifstream in("../small/shipping.csv");
    string line;
    getline(in, line);
    while (getline(in, line)) {
        string orig, dest, dist;
        istringstream iss(line);
        getline(iss, orig, ',');
        getline(iss, dest, ',');
        getline(iss, dist, ',');
        g.addVertex(orig);
        g.addVertex(dest);
        g.addEdge(orig, dest, stod(dist));
    }
}

Graph<string> Data::getGraph() {
    return this->g;
}


