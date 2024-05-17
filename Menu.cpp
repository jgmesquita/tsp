#include "Menu.h"
#include "math.h"
#include "queue"

using namespace std;

/**
 *
 */
Menu::Menu() {
    this->d = Data();
}

Menu::Menu(string path, int size) {
    this->d = Data();
    d.parseGraph(path, size);
    d.parseCoordinates();
}

Graph<int> Menu::getGraphMenu() {
    return this->d.getGraph();
}

unordered_map<int,pair<double,double>> Menu::getCoordinates() {
    return this->d.getCoordinates();
}

Edge<int>* Menu::findEdge(Vertex<int>* from, Vertex<int>* to) {
    for (Edge<int>* edge : from->getAdj()) {
        if (edge->getDest()->getInfo() == to->getInfo() && edge->isMST()) {
            return edge;
        }
        else if(edge->getDest()->getInfo() == to->getInfo()){
            return edge;
        }

    }
    return nullptr;
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

    for (Edge<int> *e : current->getAdj()) {
        Vertex<int> *next = e->getDest();
        if (!next->isVisited()) {
            next->setVisited(true);
            currentRoute.push_back(next->getInfo());
            if(currentCost < minCost) {
                tspUtil(g, next, currentRoute, currentCost + e->getWeight(), bestRoute, minCost, level + 1);}
                next->setVisited(false);
                currentRoute.pop_back();

        }
    }
}

vector<Vertex<int>*> Menu::preOrderWalk(vector<Vertex<int>*> MST){
    vector<Vertex<int>*> result;
    for(auto v : MST) v->setVisited(false);
    Vertex<int>* FirtNode = MST[0];

    PreOrderWalkDFS(FirtNode,result);
    return result;
}

void Menu::PreOrderWalkDFS(Vertex<int>* node,vector<Vertex<int>*>& result){
    result.push_back(node);
    node->setVisited(true);
    for(auto e : node->getAdj()){
        if(!e->getDest()->isVisited() && e->isMST()) {
            PreOrderWalkDFS(e->getDest(), result);
        }
    }
}

double Menu::triangleApproximationTSP(Graph<int>& g, unordered_map<int,pair<double,double>> c) {

    vector<Vertex<int>*> Tour;
    prim(g); //PRIM WORKING!!

    cout << '\n';
    vector<Vertex<int>*> preorderList = preOrderWalk(g.getVertexSet());

    for(auto v : preorderList) cout << v->getInfo() << ' ';
    cout << '\n';
    unordered_set<int> visited; // To keep track of visited vertices
    double cost = 0;
    Vertex<int>* FirtNode = g.getVertexSet()[0];
    Vertex<int>* lastNode;
    bool first = true;
    for(auto v : preorderList) v->setVisited(false);
    double distance;
    for (const auto& node : preorderList) {

        if (!node->isVisited()) {
            // If lastNode is not empty, compute distance between lastNode and current node
            if (!first) {
                Edge<int>* edge = findEdge(lastNode, node);
                if(edge != NULL){
                    distance = findEdge(lastNode,node)->getWeight();
                }
                else {
                    distance = haversine(c[lastNode->getInfo()].second, c[lastNode->getInfo()].first, c[node->getInfo()].second, c[node->getInfo()].first);
                }
                cost += distance;
            }
            first = false;
            lastNode = node;
        }
    }


    if(findEdge(lastNode,FirtNode) != NULL) distance = findEdge(lastNode,FirtNode)->getWeight();
    else distance = haversine(c[lastNode->getInfo()].second, c[lastNode->getInfo()].first, c[FirtNode->getInfo()].second, c[FirtNode->getInfo()].first);

    cost += distance;
    return cost;
}
void Menu::prim(Graph<int>& g) {
    vector<Vertex<int> *> result;
    if (g.getVertexSet().empty()) {
        cerr << "Graph is empty! Abort program!";
    }
    for (auto v: g.getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
        v->setIndegree(0);
        for(auto e : v->getAdj()){
            e->setMST(false);
            e->setSelected(false);
        }
    }

    MutablePriorityQueue<Vertex<int>> q;
    for(auto v : g.getVertexSet()){
        q.insert(v);
    }
    g.getVertexSet()[0]->setDist(0);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        if(v->getPath() != nullptr){
            v->getPath()->setMST(true);
            v->getPath()->getReverse()->setMST(true);
        }
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


}

void Menu::minimumWeightPerfectMatching(vector<Vertex<int>*>& odd_vertices){
    vector<Edge<int>*> result;
    vector<Edge<int>*> potencial_edges;
    for(auto v : odd_vertices) v->setVisited(false);



    for(auto v : odd_vertices){
        for(auto e : v->getAdj()){
            if(v->getInfo() < e->getDest()->getInfo() && (e->getDest()->getAdj().size() % 2 != 0)) potencial_edges.push_back(e);
        }
    }
    sort(potencial_edges.begin(),potencial_edges.end(),[](Edge<int>* first, Edge<int>* second) {
        return first->getWeight() < second->getWeight();
    }); //sort the edges by weight in order to find the minimum weight matching


    for(auto e : potencial_edges){
        if(!e->getOrig()->isVisited() && !e->getDest()->isVisited()){

            e->getOrig()->setVisited(true);
            e->getDest()->setVisited(true);
            e->setMST(true);
        }
    }


}

void Menu::heirholzer(Vertex<int>* v, vector<Vertex<int>*> &Ecircuit){
    Ecircuit.push_back(v);
    v->setVisited(true);
    for(auto e : v->getAdj()){
        if(!e->isSelected() && e->isMST() && !e->getDest()->isVisited()){
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            heirholzer(e->getDest(),Ecircuit);

        }
    }

}

vector<Vertex<int>*> Menu::eulerianCircuit(){
    for(auto v : d.getGraph().getVertexSet()) v->setVisited(false);
    vector<Vertex<int>*> Ecircuit;
    Vertex<int>* Starting_node = d.getGraph().getVertexSet()[0];
    Starting_node->setVisited(true);
    heirholzer(Starting_node,Ecircuit);

    return Ecircuit;
}

vector<Vertex<int>*> Menu::ConvertToHamiltonianCircuit(vector<Vertex<int>*>& ECircuit){
    vector<Vertex<int>*> hamiltonianCircuit;
    for(auto v : ECircuit) v->setVisited(false);
    for (Vertex<int>* v : ECircuit) {
        if (!v->isVisited()) {
            hamiltonianCircuit.push_back(v);
            v->setVisited(true);
        }
    }
    // Add the starting vertex again to complete the Hamiltonian circuit
    hamiltonianCircuit.push_back(ECircuit.front());
    return hamiltonianCircuit;
}

double Menu::CalculateTotalCost(vector<Vertex<int>*> hamiltonianCircuit,unordered_map<int,pair<double,double>> c) {
    double cost = 0;
    Vertex<int>* FirtNode = hamiltonianCircuit[0];
    Vertex<int>* lastNode;
    bool first = true;
    for(auto v : hamiltonianCircuit) v->setVisited(false);
    double distance;
    for (const auto& node : hamiltonianCircuit) {

        if (!node->isVisited()) {
            // If lastNode is not empty, compute distance between lastNode and current node
            if (!first) {
                if(d.matrix[lastNode->getInfo()][node->getInfo()] != 0) distance = d.matrix[lastNode->getInfo()][node->getInfo()];
                else distance = haversine(c[lastNode->getInfo()].second, c[lastNode->getInfo()].first, c[node->getInfo()].second, c[node->getInfo()].first);
                cost += distance;
            }
            first = false;
            lastNode = node;
        }
    }

    if(findEdge(lastNode,FirtNode) != nullptr) distance = findEdge(lastNode,FirtNode)->getWeight();
    else distance = haversine(c[lastNode->getInfo()].second, c[lastNode->getInfo()].first, c[FirtNode->getInfo()].second, c[FirtNode->getInfo()].first);

    cost += distance;
    return cost;
}

double Menu::christofides_tsp(Graph<int> g, unordered_map<int,pair<double,double>> c){
    prim(g);

    vector<Vertex<int>*> odd_vertices;
    for(auto v : g.getVertexSet()){
        if(v->getAdj().size() % 2 != 0) odd_vertices.push_back(v);
    }
    minimumWeightPerfectMatching(odd_vertices); //garante que todos os vertices tenham grau par, uma condiçao necessaria para encontrar um circuito euleriano

    vector<Vertex<int>*> ECircuit = eulerianCircuit();

    vector<Vertex<int>*> hamiltonianCircuit = ConvertToHamiltonianCircuit(ECircuit);

    twoOpt2(hamiltonianCircuit,c);
    double totalcost = CalculateTotalCost(hamiltonianCircuit,c);

    return totalcost;
}

void Menu::twoOpt2(std::vector<Vertex<int>*>& tour, unordered_map<int,pair<double,double>> c) {
    //this algorithm will try two swap two edges, n tries to see if the tour improves
    bool improved = true;
    double dAB = 0; //edges that will be swaped
    double dCD = 0;

    double dAC = 0; //edges that swap
    double dBD = 0;

    //4 distances in order to swap two edges at a time
    Vertex<int>* vertexA;
    Vertex<int>* vertexB;
    Vertex<int>* vertexC;
    Vertex<int>* vertexD;
    int n = 3; //numbers of tries to improve the tour

    while (improved && (n > 0)) {
        improved = false;

        for (int i = 0; i < tour.size() - 2; i++) {
            vertexA = tour[i];
            vertexB = tour[i + 1];
            if(d.matrix[vertexA->getInfo()][vertexB->getInfo()] == 0){
                dAB = haversine(c[vertexA->getInfo()].second, c[vertexA->getInfo()].first, c[vertexB->getInfo()].second, c[vertexB->getInfo()].first);
            }
            else {
                dAB = d.matrix[vertexA->getInfo()][vertexB->getInfo()];
            }
            for (int j = i + 2; j < tour.size()-1; j++) {
                vertexC = tour[j];
                vertexD = tour[j + 1];
                if(d.matrix[vertexC->getInfo()][vertexD->getInfo()] == 0){
                    dCD = haversine(c[vertexC->getInfo()].second, c[vertexC->getInfo()].first, c[vertexD->getInfo()].second, c[vertexD->getInfo()].first);
                }
                else {
                    dCD = d.matrix[vertexC->getInfo()][vertexD->getInfo()];
                }
                if(d.matrix[vertexA->getInfo()][vertexC->getInfo()] == 0){
                    dAC = haversine(c[vertexA->getInfo()].second, c[vertexA->getInfo()].first, c[vertexC->getInfo()].second, c[vertexC->getInfo()].first);
                }
                else {
                    dAC = d.matrix[vertexA->getInfo()][vertexC->getInfo()];
                }
                if(d.matrix[vertexB->getInfo()][vertexD->getInfo()] == 0){
                    dBD = haversine(c[vertexB->getInfo()].second, c[vertexB->getInfo()].first, c[vertexD->getInfo()].second, c[vertexD->getInfo()].first);
                }
                else {
                    dBD = d.matrix[vertexB->getInfo()][vertexD->getInfo()];
                }

                double currentDistance = dAB + dCD;
                double newDistance = dAC + dBD;

                if (newDistance < currentDistance) {
                    std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
                    improved = true;
                    vertexA = tour[i];
                    vertexB = tour[i + 1];
                    if(d.matrix[vertexA->getInfo()][vertexB->getInfo()] == 0 || d.matrix[vertexB->getInfo()][vertexA->getInfo()] == 0){
                        dAB = haversine(c[vertexA->getInfo()].second, c[vertexA->getInfo()].first, c[vertexB->getInfo()].second, c[vertexB->getInfo()].first);
                    }
                    else {
                        dAB = d.matrix[vertexA->getInfo()][vertexB->getInfo()];
                    }
                }
            }
        }
        n--;

    }
}

double Menu::greedyTSP(Graph<int> g,int origin) {
    // Prepare for loop!
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    double cost = 0;
    int counter = 0;
    Vertex<int>* current = g.getVertexSet()[origin];
    current->setVisited(true);
    Vertex<int>* target;
    vector<Vertex<int>*> path;
    path.push_back(current);


    //These nodes are important for the returning path!

    // Main Loop
    while (counter < g.getVertexSet().size() - 1) {
        auto adj = current->getAdj();
        double ratio = std::numeric_limits<double>::max();
        double cost_edge;
        for(auto e : adj){
            if(!e->getDest()->isVisited()){
                if((e->getWeight()/ e->getDest()->getIncoming().size()) < ratio){
                    cost_edge = e->getWeight();
                    ratio = e->getWeight() / e->getDest()->getIncoming().size();
                    target = e->getDest();
                }
            }
        }
        // Detect if it got stucked!
        if (ratio == std::numeric_limits<double>::max()) {
            cerr << "It is not possible to find a path!\n";
            return -1;
        }
        //Update Values
        cost += cost_edge;
        target->setVisited(true);
        current = target;
        path.push_back(target);
        counter++;
    }

    // Find the last edge!
    Edge<int>* returnEdge = findEdge(current,g.getVertexSet()[origin]);
    if (returnEdge != nullptr) {
        cost += returnEdge->getWeight();
    }
    else {
        cerr << "It doesn't have a path between the final node and the starting node!" << endl;
        return -1;
    }
    return cost;
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
        return -rad * c * 1000;
    }
    return rad * c * 1000;
}