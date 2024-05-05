#include "Menu.h"

using namespace std;

Menu::Menu(string path) {
    this->d = Data();
    d.parseGraph(path);
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
    for (auto it = bestRoute.begin(); it != bestRoute.end(); it++) {
        cout << *it << endl;
    }
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
//This doesn't work yet!
double Menu::triangleApproximationTSP(Graph<string> g) {
    Vertex<string>* current = g.getVertexSet()[0];
    vector<string> route;
    double totalCost = 0;
    int n = g.getNumVertex();
    route.push_back(current->getInfo());
    current->setVisited(true);
    int visitCount = 1;

    while (visitCount < n) {
        double minDist = std::numeric_limits<double>::infinity();
        Vertex<string>* nextVertex = nullptr;
        Edge<string>* nextEdge = nullptr;
        for (Edge<string>* edge : current->getAdj()) {
            Vertex<string>* candidate = edge->getDest();
            if (!candidate->isVisited() && visitCount != 1) {
                bool triangleInequality = true;
                for (const string& visitedInfo : route) {
                    Vertex<string>* visitedVertex = g.findVertex(visitedInfo);
                    auto toCurrent = findEdge(candidate, current);
                    auto toVisited = findEdge(candidate, visitedVertex);
                    auto fromVisited = findEdge(visitedVertex, current);
                    if (toCurrent == nullptr || toVisited == nullptr || fromVisited == nullptr) {
                        triangleInequality = false;
                        continue;
                    }
                    else {
                        if (toCurrent->getWeight() > toVisited->getWeight() + fromVisited->getWeight()) {
                            triangleInequality = false;
                            break;
                        }
                    }
                }
                if (triangleInequality && edge->getWeight() < minDist) {
                    nextVertex = candidate;
                    nextEdge = edge;
                    minDist = edge->getWeight();
                }
            }
            if (visitCount == 1) {
                nextVertex = candidate;
                nextEdge = findEdge(current, nextVertex);
            }
        }

        current = nextVertex;
        current->setVisited(true);
        route.push_back(current->getInfo());
        totalCost += nextEdge->getWeight();
        visitCount++;
    }

    Edge<string>* returnEdge = findEdge(current, g.findVertex(g.getVertexSet()[0]->getInfo()));
    if (returnEdge) {
        totalCost += returnEdge->getWeight();
        route.push_back(g.getVertexSet()[0]->getInfo());
    }

    return totalCost;
}

Edge<string>* Menu::findEdge(Vertex<string>* from, Vertex<string>* to) {
    for (Edge<string>* edge : from->getAdj()) {
        if (edge->getDest() == to) {
            return edge;
        }
    }
    return nullptr;
}