#ifndef PROJETO_2_DA_MENU_H
#define PROJETO_2_DA_MENU_H

#include "Data.h"
#include "vector"

class Menu {
private:
    Data d;
    string path;
public:
    Menu(string path);
    Graph<string> getGraphMenu();
    double tspBacktracking(Graph<string> g);
    void tspUtil(Graph<string> g, Vertex<string>* current, vector<string> &currentRoute, double currentCost, vector<string> &bestRoute, double &minCost, int level);
    double triangleApproximationTSP(Graph<string> g);
    Edge<string>* findEdge(Vertex<string>* from, Vertex<string>* to);
    double haversine(double lat1, double lon1, double lat2, double lon2);
};

#endif //PROJETO_2_DA_MENU_H
