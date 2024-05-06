#include "Menu.h"
#include "math.h"
#include "queue"

using namespace std;

Menu::Menu(string path) {
    this->d = Data();
    d.parseGraph(path);
    d.parseCoordinates();
}

Graph<int> Menu::getGraphMenu() {
    return this->d.getGraph();
}

unordered_map<int,pair<double,double>> Menu::getCoordinates() {
    return this->d.getCoordinates();
}

//Fully working!
double Menu::tspBacktracking(Graph<int> g) {
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    vector<int> bestRoute;
    vector<int> currentRoute;
    double minCost = std::numeric_limits<double>::max();
    Vertex<int> *v = g.getVertexSet()[0];
    v->setVisited(true);
    currentRoute.push_back(v->getInfo());
    tspUtil(g, v,currentRoute, 0, bestRoute, minCost, 1);
    for (auto it = bestRoute.begin(); it != bestRoute.end(); it++) {
        cout << *it << endl;
    }
    return minCost;
}

void Menu::tspUtil(Graph<int> g, Vertex<int> *current, vector<int> &currentRoute, double currentCost, vector<int> &bestRoute, double &minCost, int level) {
    //when it reaches the end
    //level is used to iterate over the right amount of nodes in the graph
    //stadium and tourism fully connected --- shipping not fully connected
    if (level == g.getVertexSet().size()) {
        for (Edge<int> *e : current->getAdj()) {
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
    //basically a DFS search
    for (Edge<int> *e : current->getAdj()) {
        Vertex<int> *next = e->getDest();
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

double Menu::triangleApproximationTSP(const Graph<int>& g, unordered_map<int,pair<double,double>> c) {
    vector<Vertex<int> *> MST;

    MST = prim(g); //PRIM WORKING!!
    vector<Vertex<int>*> preorderList = MST;

    /*
    for(auto v : MST){
        if(!v->isVisited()){
            preOrderWalk(v,preorderList);
        }
    }
    for(auto v : preorderList) cout << v->getInfo() << '\n';
    */
    unordered_set<int> visited; // To keep track of visited vertices
    double cost = 0;
    Vertex<int>* FirtNode = MST[0];
    Vertex<int>* lastNode;
    bool first = true;
    for (const auto& node : preorderList) {
        // If the current node has not been visited yet
        if (visited.find(node->getInfo()) == visited.end()) {

            // If lastNode is not empty, compute distance between lastNode and current node
            if (!first) {
                cout << lastNode->getInfo() << "-->" << node->getInfo() << '\n';
                double distance = findEdge(lastNode,node)->getWeight();
                //double distance = haversine(c[lastNode].second, c[lastNode].first, c[node].second, c[node].first);
                cout << distance << '\n';
                cost += distance;

            }
            first = false;
            visited.insert(node->getInfo());
            lastNode = node;
        }
    }
    cout << lastNode->getInfo() << "-->" << FirtNode->getInfo() << '\n';
    cost += findEdge(lastNode,FirtNode)->getWeight();

    return cost;
}


double Menu::Closest_Node(Graph<int> g){

    for(auto v : g.getVertexSet()) v->setVisited(false);
    double cost = 0;
    int counter = 0;
    Vertex<int>* Current_Node = g.getVertexSet()[0];
    Current_Node->setVisited(true);
    Vertex<int>* Target_node;
    vector<Vertex<int>*> path;
    path.push_back(Current_Node);
    int r = g.getNumVertex();
    while(counter < g.getNumVertex() - 1){
        double minimum_cost_edge = std::numeric_limits<double>::max();
        for(auto e : Current_Node->getAdj()){
            if(!e->getDest()->isVisited()){
                if(e->getWeight() < minimum_cost_edge){
                    minimum_cost_edge = e->getWeight();
                    Target_node = e->getDest();
                }
            }
        }
        cost += minimum_cost_edge;
        Target_node->setVisited(true);
        Current_Node = Target_node;
        path.push_back(Target_node);
        counter++;
    }
    cost += findEdge(Current_Node,g.getVertexSet()[0])->getWeight();
    return cost;
}

vector<Vertex<int> *> Menu::prim(const Graph<int>& g) {
    vector<Vertex<int> *> result;
    if (g.getVertexSet().empty()) {
        cerr << "Graph is empty! Abort program!";
    }
    for (auto v: g.getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    MutablePriorityQueue<Vertex<int>> q;
    for(auto v : g.getVertexSet()){
        q.insert(v);
    }
    g.getVertexSet()[0]->setDist(0);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        result.push_back(v);
        for(auto e : v->getAdj()){
            auto dest = e->getDest();
            if(!dest->isVisited()){

                if(e->getWeight() < dest->getDist()){
                    dest->setDist(e->getWeight());
                    dest->setPath(e); //ligar o vertice dest aglomerado principal via este edge

                    q.decreaseKey(dest); //updates the position of dest in the priority queue
                }
            }
        }
    }

    return result;
}

void Menu::preOrderWalk(Vertex<int>* v, vector<Vertex<int>*>& L) {
    if(v == nullptr) return;
    L.push_back(v);
    v->setVisited(true);
    // Recursively visit the left subtree
    for (auto edge : v->getAdj()) {
        auto dest = edge->getDest();
        if (!dest->isVisited()) {
            preOrderWalk(dest, L);
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
Edge<int>* Menu::findEdge(Vertex<int>* from, Vertex<int>* to) {
    for (Edge<int>* edge : from->getAdj()) {
        if (edge->getDest() == to) {
            return edge;
        }
    }
    return nullptr;
}