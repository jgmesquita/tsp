#ifndef PROJETO_2_DA_MENU_H
#define PROJETO_2_DA_MENU_H

#include "Data.h"
#include "vector"
#include "queue"

class Menu {
private:
    Data d;
    string path;
public:
    Menu(string path);
    Graph<string> getGraphMenu();
    unordered_map<int,pair<double,double>> getCoordinates();
    double tspBacktracking(Graph<string> g);
    void tspUtil(Graph<string> g, Vertex<string>* current, vector<string> &currentRoute, double currentCost, vector<string> &bestRoute, double &minCost, int level);
    double triangleApproximationTSP(const Graph<string>& g, unordered_map<int,pair<double,double>> c);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    void prim(const Graph<string>& g, unordered_map<string, vector<pair<string, double>>>& MSTadj);
    queue<Vertex<string>*> preOrderWalk(const Graph<string>& g, unordered_map<string, vector<pair<string, double>>>& MSTadj);
    void preOrder(const Graph<string>& g, Vertex<string>* v, queue<Vertex<string>*> &q, unordered_map<string, vector<pair<string, double>>>& MSTadj);
    Edge<string>* findEdge(Vertex<string>* from, Vertex<string>* to);
};

#endif //PROJETO_2_DA_MENU_H
