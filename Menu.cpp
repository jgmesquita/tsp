#include "Menu.h"
#include "math.h"
#include "queue"

using namespace std;

Menu::Menu(string path) {
    this->d = Data();
    d.parseGraph(path);
    d.parseCoordinates();
}

Graph<string> Menu::getGraphMenu() {
    return this->d.getGraph();
}

unordered_map<int,pair<double,double>> Menu::getCoordinates() {
    return this->d.getCoordinates();
}

//Fully working!
double Menu::tspBacktracking(Graph<string> g) {
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    vector<string> bestRoute;
    vector<string> currentRoute;
    double minCost = std::numeric_limits<double>::max();
    Vertex<string> *v = g.getVertexSet()[0];
    v->setVisited(true);
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
//This doesn't work yet! Infinite loop or out of bounds access?
double Menu::triangleApproximationTSP(const Graph<string>& g, unordered_map<int,pair<double,double>> c) {
    unordered_map<string, vector<pair<string, double>>> MSTadj;
    double cost = 0;

    prim(g, MSTadj);

    auto t = preOrderWalk(g, MSTadj);
    t.push(g.getVertexSet()[0]);

    queue<Vertex<string>*> temp = t;
    Vertex<string>* current = temp.front();
    temp.pop();
    Vertex<string>* next = temp.front();
    while (!temp.empty()){
        cost += haversine(c[stoi(current->getInfo())].second, c[stoi(current->getInfo())].first, c[stoi(next->getInfo())].second, c[stoi(next->getInfo())].first);
        current = next;
        temp.pop();
        next = temp.front();
    }
    return cost;
}

void prim(const Graph<string>& g, unordered_map<string, vector<pair<string, double>>>& MSTadj) {
    if (g.getVertexSet().empty()) {
        cerr << "Graph is empty! Abort program!";
    }
    for (auto v: g.getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex<string> *s = g.getVertexSet().front();
    s->setDist(0);
    MutablePriorityQueue<Vertex<string>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        if (v->getPath() != nullptr) {
            Vertex<string> *w = v->getPath()->getOrig();
            MSTadj[w->getInfo()].push_back(make_pair(v->getInfo(), v->getPath()->getWeight()));
            MSTadj[v->getInfo()].push_back(make_pair(w->getInfo(), v->getPath()->getWeight()));
            for (auto &e: v->getAdj()) {
                Vertex<string> *w = e->getDest();
                if (!w->isVisited()) {
                    auto oldDist = w->getDist();
                    if (e->getWeight() < oldDist) {
                        w->setDist(e->getWeight());
                        w->setPath(e);
                        if (oldDist == INF) {
                            q.insert(w);
                        } else {
                            q.decreaseKey(w);
                        }
                    }
                }
            }
        }
    }
}

queue<Vertex<string>*> Menu::preOrderWalk(const Graph<std::string>& g, unordered_map<std::string, vector<pair<std::string, double>>> &MSTadj) {
    queue<Vertex<string>*> q;
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    Vertex<string>* start = g.getVertexSet()[0];
    preOrder(g, start,q, MSTadj);
    return q;
}

void preOrder(const Graph<string>& g, Vertex<string>* v, queue<Vertex<string>*> &q, unordered_map<string, vector<pair<string, double>>>& MSTadj) {
    q.push(v);
    v->setVisited(true);
    for (auto p : MSTadj[v->getInfo()]) {
        Vertex<string>* w = g.findVertex(p.first);
        if (!w->isVisited()) {
            preOrder(g, w, q, MSTadj);
        }
    }
}

double Menu::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double lat_a1 = lat1 * M_PI / 180.0;
    double lat_a2 = lat2 * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat_a1) * cos(lat_a2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    if (rad * c < 0) {
        return -rad * c;
    }
    return rad * c;
}

Edge<string>* Menu::findEdge(Vertex<string>* from, Vertex<string>* to) {
    for (Edge<string>* edge : from->getAdj()) {
        if (edge->getDest() == to) {
            return edge;
        }
    }
    return nullptr;
}
