#ifndef PROJETO_2_DA_MENU_H
#define PROJETO_2_DA_MENU_H

#include "Data.h"
#include "vector"
#include "queue"
#include "unordered_set"

class Menu {
private:
    Data d;
    string path;
public:
    Menu(string path);
    Graph<int> getGraphMenu();
    unordered_map<int,pair<double,double>> getCoordinates();
    double tspBacktracking(Graph<int> g);
    void tspUtil(Graph<int> g, Vertex<int>* current, vector<int> &currentRoute, double currentCost, vector<int> &bestRoute, double &minCost, int level);
    double triangleApproximationTSP(const Graph<int>& g, unordered_map<int,pair<double,double>> c);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    vector<Vertex<int> *> prim(const Graph<int>& g);
    void preOrderWalk(Vertex<int>* v, vector<Vertex<int>*>& L);
    Edge<int>* findEdge(Vertex<int>* from, Vertex<int>* to);
    double Closest_Node(Graph<int> g);
};

#endif //PROJETO_2_DA_MENU_H
