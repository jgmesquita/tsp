//
// Created by jorge on 25/04/2024.
//

#ifndef PROJETO_2_DA_DATA_H
#define PROJETO_2_DA_DATA_H

#include "Graph.h"
#include "string"
#include "unordered_map"

using namespace std;


class Data {
private:
    Graph<string> g;
    string path;
    unordered_map<int,pair<double,double>> coordinates;
public:
    void parseGraph(string path);
    void parseCoordinates();
    Graph<string> getGraph();
    unordered_map<int,pair<double,double>> getCoordinates();
};


#endif //PROJETO_2_DA_DATA_H
