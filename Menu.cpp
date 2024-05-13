#include "Menu.h"
#include "math.h"
#include "queue"

using namespace std;

Menu::Menu() {
    this->d = Data();
}

Menu::Menu(string path) {
    this->d = Data();
    d.parseGraph(path);
    d.parseCoordinates();
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
        if (edge->getDest()->getInfo() == to->getInfo()) {
            return edge;
        }
    }
    return nullptr;
}
//Fully working!
double Menu::tspBacktracking(Graph<int> g) {
    for (auto v : g.vertex_map) {
        v.second->setVisited(false);
    }
    vector<int> bestRoute;
    vector<int> currentRoute;
    double minCost = std::numeric_limits<double>::max();
    Vertex<int> *v = g.vertex_map[0];
    v->setVisited(true);
    currentRoute.push_back(v->getInfo());
    tspUtil(g, v,currentRoute, 0, bestRoute, minCost, 1);
    for (auto it = bestRoute.begin(); it != bestRoute.end(); it++) {
        cout << *it << endl;
    }
    return minCost;
}

void Menu::tspUtil(Graph<int> g, Vertex<int> *current, vector<int> &currentRoute, double currentCost, vector<int> &bestRoute, double &minCost, int level) {
    if (level == g.vertex_map.size()) {
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
            tspUtil(g, next, currentRoute, currentCost + e->getWeight(), bestRoute, minCost, level + 1);
            next->setVisited(false);
            currentRoute.pop_back();
        }
    }
}

vector<Vertex<int>*> Menu::preOrderWalk(map<int,Vertex<int>*> MST){
    vector<Vertex<int>*> result;
    for(auto v : MST) v.second->setVisited(false);
    Vertex<int>* FirtNode = MST[0];

    PreOrderWalkDFS(FirtNode,result);
    return result;
}

void Menu::PreOrderWalkDFS(Vertex<int>* node,vector<Vertex<int>*>& result){
    result.push_back(node);
    node->setVisited(true);
    for(auto e : node->getAdj()){
        if(!e->getDest()->isVisited() && e->isSelected()) PreOrderWalkDFS(e->getDest(),result);
    }
}

double Menu::triangleApproximationTSP(Graph<int>& g, unordered_map<int,pair<double,double>> c) {

    vector<Vertex<int>*> Tour;
    prim(g); //PRIM WORKING!!

    vector<Vertex<int>*> preorderList = preOrderWalk(g.vertex_map);

    for(auto v : preorderList) cout << v->getInfo() << ' ';
    cout << '\n';
    unordered_set<int> visited; // To keep track of visited vertices
    double cost = 0;
    Vertex<int>* FirtNode = g.vertex_map[0];
    Vertex<int>* lastNode;
    bool first = true;
    for(auto v : preorderList) v->setVisited(false);
    double distance;
    for (const auto& node : preorderList) {

        if (!node->isVisited()) {
            // If lastNode is not empty, compute distance between lastNode and current node
            if (!first) {
                if(findEdge(lastNode,node) != nullptr) distance = findEdge(lastNode,node)->getWeight();
                else distance = haversine(c[lastNode->getInfo()].second, c[lastNode->getInfo()].first, c[node->getInfo()].second, c[node->getInfo()].first);
                cost += distance;
            }
            first = false;
            lastNode = node;
        }
    }
    /*
    cout << "The path is: ";
    vector<int> temp;
    for (auto it = visited.begin(); it != visited.end(); it++) {
        cout << *it << ' ';
    }

    cout << "0\n";
     */
    if(findEdge(lastNode,FirtNode) != nullptr) distance = findEdge(lastNode,FirtNode)->getWeight();
    else distance = haversine(c[lastNode->getInfo()].second, c[lastNode->getInfo()].first, c[FirtNode->getInfo()].second, c[FirtNode->getInfo()].first);

    cost += distance;
    return cost;
}
void Menu::prim(Graph<int>& g) {
    vector<Vertex<int> *> result;
    if (g.vertex_map.empty()) {
        cerr << "Graph is empty! Abort program!";
    }
    for (auto v: g.vertex_map) {
        v.second->setDist(INF);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
    }

    MutablePriorityQueue<Vertex<int>> q;
    for(auto v : g.vertex_map){
        q.insert(v.second);
    }
    g.vertex_map[0]->setDist(0);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        if(v->getPath() != nullptr){
            v->getPath()->setSelected(true);
            v->getPath()->getReverse()->setSelected(true);
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
vector<Edge<int>*> H;

void Menu::minimumWeightPerfectMatching(vector<Vertex<int>*>& odd_vertices){
    vector<Edge<int>*> result;
    vector<Edge<int>*> potencial_edges;

    for(auto v : odd_vertices) v->setVisited(false);

    for(auto v : odd_vertices){
        for(auto e : v->getAdj()){
            if(v->getInfo() < e->getDest()->getInfo() && (e->getDest()->getIncoming().size() + e->getDest()->getAdj().size()) % 2 != 0) potencial_edges.push_back(e);
        }
    }
    sort(potencial_edges.begin(),potencial_edges.end(),[](Edge<int>* first, Edge<int>* second) {
        return first->getWeight() < second->getWeight();
    }); //sort the edges by weight in order to find the minimum weight matching

    for(auto e : potencial_edges){
        if(!e->getOrig()->isVisited() && !e->getDest()->isVisited()){
            e->getOrig()->setVisited(true);
            e->getDest()->setVisited(true);
            H.push_back(e);
        }
    }


}

void Menu::heirholzer(Vertex<int>* v, vector<Vertex<int>*> &Ecircuit,unordered_map<Vertex<int>*, vector<Edge<int>*>> adjList){
    Ecircuit.push_back(v);
    for(auto e : adjList[v]){
        if(!e->isSelected()){
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            heirholzer(e->getDest(),Ecircuit,adjList);
        }
    }
}
/*
vector<Vertex<int>*> Menu::eulerianCircuit(const vector<Edge<int>*>& H){

    for(auto v : d.getGraph().vertex_map){
        for(auto e : v.second->getAdj()){

        }
    }
    vector<Vertex<int>*> Ecircuit;
    Vertex<int>* startingNode;
    for (auto e : H) {
        if (e->getOrig()->getInfo() == 0) {
            startingNode = e->getOrig();
            break;
        }
    }
    heirholzer(startingNode, Ecircuit,adjList);
    return Ecircuit;
}

vector<Vertex<int>*> Menu::ConvertToHamiltonianCircuit(vector<Vertex<int>*>& ECircuit){
    vector<Vertex<int>*> hamiltonianCircuit;
    for(auto v : ECircuit) v->setVisited(false);
    for (Vertex<int>* v : ECircuit) {
        if (!v->isVisited()) {
            hamiltonianCircuit.push_back(v);

        }
    }
    // Add the starting vertex again to complete the Hamiltonian circuit
    hamiltonianCircuit.push_back(ECircuit.front());
    return hamiltonianCircuit;
}
*/
double Menu::CalculateTotalCost(vector<Vertex<int>*> hamiltonianCircuit,unordered_map<int,pair<double,double>> c) {
    double cost = 0;
    Vertex<int>* FirtNode = d.getGraph().vertex_map[0];
    Vertex<int>* lastNode;
    bool first = true;
    for(auto v : hamiltonianCircuit) v->setVisited(false);
    double distance;
    for (const auto& node : hamiltonianCircuit) {

        if (!node->isVisited()) {
            // If lastNode is not empty, compute distance between lastNode and current node
            if (!first) {
                if(findEdge(lastNode,node) != nullptr) distance = findEdge(lastNode,node)->getWeight();
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
    prim2(g);
    vector<Vertex<int>*> odd_vertices;
    for(auto v : g.vertex_map){
        if(v.second->getIncoming().size() + v.second->getAdj().size() % 2 != 0) odd_vertices.push_back(v.second);
    }

    minimumWeightPerfectMatching(odd_vertices); //garante que todos os vertices tenham grau par, uma condiçao necessaria para encontrar um circuito euleriano
    //vector<Vertex<int>*> ECircuit = eulerianCircuit(H);
    vector<Vertex<int>*> hamiltonianCircuit = ConvertToHamiltonianCircuit(ECircuit);
    double totalcost = CalculateTotalCost(hamiltonianCircuit,c);
    cout << "The path is: ";
    for (auto v : hamiltonianCircuit) {
        cout << v->getInfo() << " ";
    }
    cout << "\n";
    return totalcost;
}

double Menu::Closest_Node(Graph<int> g, unordered_map<int,pair<double,double>> c){
    for(auto v : g.vertex_map) v.second->setVisited(false);
    double cost = 0;
    int counter = 0;
    Vertex<int>* Current_Node = g.vertex_map[0];
    Current_Node->setVisited(true);
    Vertex<int>* Target_node;
    vector<Vertex<int>*> path;
    path.push_back(Current_Node);

    while(counter < g.vertex_map.size() - 1){
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
    auto return_edge = findEdge(Current_Node,g.vertex_map[0]);
    if(return_edge != nullptr){
        cost += return_edge->getWeight();
    }
    else{
        cost += haversine(c[Current_Node->getInfo()].second, c[Current_Node->getInfo()].first, c[g.vertex_map[0]->getInfo()].second, c[g.vertex_map[0]->getInfo()].first);
    }
    cout << "The path is: ";
    for (auto p : path) {
        cout << p->getInfo() << " ";
    }
    cout << "\n";

    return cost;
}

double Menu::Closest_Node_Origin(Graph<int> g, unordered_map<int,pair<double,double>> c){
    for(auto v : g.vertex_map) v.second->setVisited(false);
    double cost = 0;
    int counter = 0;
    Vertex<int>* Current_Node = g.vertex_map[0];
    Current_Node->setVisited(true);
    Vertex<int>* Target_node;
    vector<Vertex<int>*> path;
    path.push_back(Current_Node);
    while(counter < g.vertex_map.size() - 1){
        double minimum_cost_edge = std::numeric_limits<double>::max();
        for(int i = 0; i < g.matrix[Current_Node->getInfo()].size(); i++){
            if(g.matrix[Current_Node->getInfo()][i] == 0 && Current_Node->getInfo() != i ) {
                g.matrix[Current_Node->getInfo()][i] = (int)haversine(c[Current_Node->getInfo()].second, c[Current_Node->getInfo()].first, c[i].second, c[i].first);
            }
            if(!g.vertex_map[i]->isVisited() && (g.matrix[Current_Node->getInfo()][i] != 0)){

                if(g.matrix[Current_Node->getInfo()][i] < minimum_cost_edge){
                    minimum_cost_edge = g.matrix[Current_Node->getInfo()][i];
                    Target_node = g.vertex_map[i];
                }
            }
        }
        cost += minimum_cost_edge;
        Target_node->setVisited(true);
        Current_Node = Target_node;
        path.push_back(Target_node);
        counter++;
    }

    cost += g.matrix[Current_Node->getInfo()][0];
    cout << "The path is: ";
    for (auto p : path) {
        cout << p->getInfo() << " ";
    }
    cout << '0' << "\n";
    return cost;
}



void Menu::prim2(Graph<int>& g) {

    for (auto v: g.vertex_map) {
        v.second->setDist(INF);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
    }

    MutablePriorityQueue<Vertex<int>> q;
    for(auto v : g.vertex_map){
        q.insert(v.second);
    }
    g.vertex_map[0]->setDist(0);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
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
    for (auto v : g.vertex_map) {
        if (v.second->getPath() != nullptr) {
            H.push_back(v.second->getPath());
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
/*
vector<int> twoOpt(const vector<int>& tour, const vector<vector<double>>& distanceMatrix){
    std::vector<int> newTour = tour;
    bool improved = true;

    while (improved) {
        improved = false;
        for (size_t i = 1; i < newTour.size() - 2; ++i) {
            for (size_t j = i + 1; j < newTour.size() - 1; ++j) {
                double delta = distanceMatrix[newTour[i - 1]][newTour[j]] + distanceMatrix[newTour[i]][newTour[j + 1]]
                               - distanceMatrix[newTour[i - 1]][newTour[i]] - distanceMatrix[newTour[j]][newTour[j + 1]];

                if (delta < 0) {
                    std::reverse(newTour.begin() + i, newTour.begin() + j + 1);
                    improved = true;
                }
            }
        }
    }

    return newTour;
}

// Function to perturb the solution (e.g., randomly swap a few edges)
vector<int> perturb(const vector<int>& tour){
    std::vector<int> perturbedTour = tour;

    // Randomly swap two edges in the tour
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(1, perturbedTour.size() - 2);
    size_t i = dist(gen);
    size_t j = dist(gen);
    std::swap(perturbedTour[i], perturbedTour[j]);

    return perturbedTour;
}

// Function to determine whether to accept a perturbed solution
bool acceptSolution(double oldCost, double newCost){
    return newCost < oldCost;
}

// Function to perform Iterated Local Search for TSP
vector<int> iteratedLocalSearch(const vector<vector<double>>& distanceMatrix, int iterations) {
    // Initialize with an initial solution (e.g., Nearest Neighbor)
    vector<int> bestTour = initialSolution(distanceMatrix);
    double bestCost = calculateCost(bestTour, distanceMatrix);

    // Main loop
    for (int iter = 0; iter < iterations; ++iter) {
        // Perform local search
        vector<int> newTour = twoOpt(bestTour, distanceMatrix);
        double newCost = calculateCost(newTour, distanceMatrix);

        // Perturb the solution
        newTour = perturb(newTour);

        // Accept the perturbed solution based on an acceptance criterion
        if (acceptSolution(bestCost, newCost)) {
            bestTour = newTour;
            bestCost = newCost;
        }
    }

    return bestTour;
}

*/