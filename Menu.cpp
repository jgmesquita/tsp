#include "Menu.h"

using namespace std;

Menu::Menu() {
    this->d = Data();
    d.parseGraph();
}

Graph<string> Menu::getGraphMenu() {
    return this->d.getGraph();
}

double Menu::tspBacktracking(Graph<string> g) {
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    vector<string> bestRoute;
    vector<string> currentRoute;
    double minCost = std::numeric_limits<double>::max();
    Vertex<string> *v = g.getVertexSet()[0];
    currentRoute.push_back(v->getInfo());
    tspUtil(g, v,currentRoute, 0, bestRoute, minCost, 1);
    return minCost;
}

void Menu::tspUtil(Graph<string> g, Vertex<string> *current, vector<string> &currentRoute, double currentCost, vector<string> &bestRoute, double &minCost, int level) {
    if (level == g.getVertexSet().size()) {
        for (Edge<string> *e : current->getAdj()) {
            if (e->getDest()->getInfo() == currentRoute[0]) {
                double totalCost = currentCost + e->getWeight();
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestRoute = currentRoute;
                    bestRoute.push_back(currentRoute[0]); // Complete the cycle
                }
                break;
            }
        }
        return;
    }

    for (Edge<string> *e : current->getAdj()) {
        Vertex<string> *next = e->getDest();
        if (!next->isVisited()) {
            next->setVisited(true);
            currentRoute.push_back(next->getInfo());
            tspUtil(g, next, currentRoute, currentCost + e->getWeight(), bestRoute, minCost, level + 1);
            next->setVisited(false);
            currentRoute.pop_back();
        }
    }
}