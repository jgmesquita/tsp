#ifndef PROJETO_2_DA_MENU_H
#define PROJETO_2_DA_MENU_H

#include "Data.h"
#include "vector"
#include "queue"
#include "unordered_set"
#include "set"
#include "stack"
#include <random>

class Menu {
private:
    Data d;
    string path;
public:
    Menu();
    Menu(string path);
    Menu(string path, int size);
    Graph<int> getGraphMenu();
    unordered_map<int,pair<double,double>> getCoordinates();
    double tspBacktracking(Graph<int> g);
    void tspUtil(Graph<int> g, Vertex<int>* current, vector<int> &currentRoute, double currentCost, vector<int> &bestRoute, double &minCost, int level);
    double triangleApproximationTSP(Graph<int>& g, unordered_map<int,pair<double,double>> c);
    double christofides_tsp(Graph<int> g, unordered_map<int,pair<double,double>> c);
    void minimumWeightPerfectMatching(vector<Vertex<int>*>& odd_vertices);
    vector<Vertex<int>*> eulerianCircuit(const vector<Edge<int>*>& H);
    void heirholzer(Vertex<int>* v, vector<Vertex<int>*> &Ecircuit,unordered_map<Vertex<int>*, vector<Edge<int>*>> adjList);
    vector<Vertex<int>*> ConvertToHamiltonianCircuit(vector<Vertex<int>*>& ECircuit);
    double CalculateTotalCost(vector<Vertex<int>*> hamiltonianCircuit,unordered_map<int,pair<double,double>> c);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    vector<Vertex<int> *> prim(Graph<int>& g, unordered_map<int,pair<double,double>> c);
    void prim2(const Graph<int>& g);
    Edge<int>* findEdge(Vertex<int>* from, Vertex<int>* to);
    double Closest_Node_Origin(Graph<int> g, unordered_map<int,pair<double,double>> c);
};

#endif //PROJETO_2_DA_MENU_H
