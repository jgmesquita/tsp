#ifndef PROJETO_2_DA_MENU_H
#define PROJETO_2_DA_MENU_H

#include "Data.h"
#include "vector"
#include "queue"
#include "unordered_set"
#include "set"
#include "stack"
#include <random>

/**
 * @class Menu
 * @brief Represents the user-friendly interface to Routing Algorithm for Ocean Shipping and Urban Deliveries.
 * It shows available functionalities, their corresponding outputs and performance in a clear, organized,
 * and logical manner, facilitating seamless program utilization and straightforward result
 * interpretation.
 */
class Menu {
private:
    Data d;
    string path;
public:
    /**
     * @brief * Default Menu constructor - creates a Data object and parse the csv files
     */
    Menu();
    /**
     *  @brief * Menu constructor - creates a Data object and parse the csv files, based on their path and number of
     *  nodes of each graph(size)
     * @param path of each csv file to parse
     * @param size number o nodes of each graph
     */
    Menu(string path, int size);
    /**
     * @brief This function has the purpose to get the Graph object from the Menu object.
     * @return Graph object.
     */
    Graph<int> getGraphMenu();
    /**
     * @brief This function has the purpose to get the coordinates of the nodes as an unordered_map.
     * @return Unordered_map of the nodes' coordinates.
     */
    unordered_map<int,pair<double,double>> getCoordinates();
    /**
     * @brief this function performs a backtracking algorithm, in order to find the minimum cost tour of a graph
     * @param g graph that contain all the information about the problem in question
     * @return the minimum cost of the tour started at a specific node(origin node)
     */
    double tspBacktracking(Graph<int> g);
    /**
     * @brief auxiliary function to the backtracking algorithm that is responsible for most of the work by using a dfs search style approach and bounding
     * @param g graph that contain all the information about the problem in question
     * @param current is the current node that is being visited
     * @param currentRoute the current route
     * @param currentCost the cost of the current route
     * @param bestRoute the route that will yield the overall minimum cost
     * @param minCost is the cost of the route with the minimum cost
     * @param level the level od depth of the backtracking tree
     */
    void tspUtil(Graph<int> g, Vertex<int>* current, vector<int> &currentRoute, double currentCost, vector<int> &bestRoute, double &minCost, int level);
    /**
 * @brief This function approximates the solution to the Traveling Salesman Problem (TSP) using a triangle inequality heuristic.
 * It has the temporal complexity of O(V^2).
 * This algorithm constructs a Minimum Spanning Tree (MST) of the input graph and then performs a preorder traversal of the MST
 * to create a Hamiltonian circuit. The triangle inequality ensures that the length of the approximated tour is at most twice
 * the length of the optimal tour. If direct distances between vertices are not available, it uses the Haversine formula
 * to compute distances based on geographical coordinates.
 *
 * @param g graph that contain all the information about the problem in question
 * @param c Unordered_map with the coordinates of the nodes.
 * @return the minimum cost of the tour started at a specific node(origin node).

 */
    double triangleApproximationTSP(Graph<int>& g, unordered_map<int,pair<double,double>> c);
    /**
 * @brief This function approximates the solution to the Traveling Salesman Problem (TSP) using Christofides' algorithm and improves the solution with a 2-opt optimization.
 * It has the temporal complexity of O(V^3).
 *
 * Christofides' algorithm is a well-known approximation algorithm for the TSP that guarantees a tour length within 1.5 times
 * the optimal solution. The algorithm consists of the following steps:
 * 1. Compute a Minimum Spanning Tree (MST) of the graph.
 * 2. Find a minimum weight perfect matching for the vertices with odd degree in the MST.
 * 3. Combine the edges of the MST and the perfect matching to form an Eulerian graph.
 * 4. Find an Eulerian tour in the Eulerian graph.
 * 5. Convert the Eulerian tour to a Hamiltonian circuit by shortcutting repeated vertices.
 * 6. Apply 2-opt optimization to the Hamiltonian circuit to further improve the tour by swapping pairs of edges to reduce the tour length.
 * If direct distances between vertices are not available, the function uses the Haversine formula to compute distances based
 * on geographical coordinates.
 *
 * @param g graph that contain all the information about the problem in question
 * @param c Unordered_map with the coordinates of the nodes.
 * @return the minimum cost of the tour started at a specific node(origin node).
 */
    double christofides_tsp(Graph<int> g, unordered_map<int,pair<double,double>> c);
    /**
    @brief This function finds a minimum weight perfect matching for a set of vertices with odd degree.
    * It has the temporal complexity of O(V^3).
    * The function takes a list of vertices with odd degree in the graph and finds a perfect matching where the sum of the weights
    * of the matched edges is minimized. This is an auxiliary function of Christofides' algorithm;
    *
    * @param odd_vertices A vector of pointers to vertices with odd degree in the graph.
    */
    void minimumWeightPerfectMatching(vector<Vertex<int>*>& odd_vertices);
    /**
     * @brief This function has the purpose to construct a vector of the Eularian Circuit.
     * It has the temporal complexity of O(VE).
     * @return Eularian Circuit as a vector.
     */
    vector<Vertex<int>*> eulerianCircuit();
    /**
     * @brief This is an auxiliary function for the eulerianCircuit().
     * It has the purpose to visit the edges which are also from the MST.
     * It has the temporal complexity of O(VE)
     * @param v Current node.
     * @param Ecircuit Vector with the Eulerian Circuit.
     */
    void heirholzer(Vertex<int>* v, vector<Vertex<int>*> &Ecircuit);
    /**
     * @brief This function has the purpose to convert a Eularian Circuit into an Halmitonian Circuit.
     * It has the complexity of O(V);
     * @param ECircuit Eularian Circuit as a vector.
     * @return Halmitonian Circuit as a vector.
     */
    vector<Vertex<int>*> ConvertToHamiltonianCircuit(vector<Vertex<int>*>& ECircuit);
    /**
     * @brief This function has the purpose to calculate the cost of the path from the Hamiltonian Circuit.
     * It has the complexity of O(V).
     * @param hamiltonianCircuit Vector with the Hamiltonian Circuit.
     * @param c Unordered_map with the coordinates of the nodes.
     * @return It returns the cost of the whole path.
     */
    double CalculateTotalCost(vector<Vertex<int>*> hamiltonianCircuit,unordered_map<int,pair<double,double>> c);
    /**
     * @brief This function has the purpose to calculate the distance in meters between two nodes.
     * It has a temporal complexity of O(1);
     * @param lat1 Latitude of the first node.
     * @param lon1 Longitude of the first node.
     * @param lat2 Latitude of the second node.
     * @param lon2 Longitude of the second node.
     * @return Distance between the two nodes in meters.
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);
    /**
     * @brief Prim's algorithm has the purpose to find the Minimum Cost Spanning Tree of a graph.
     * It has a temporal complexity of O(E*log(V)).
     * @param g Graph to apply the Prim's algorithm.
     */
    void prim(Graph<int>& g);
    /**
     * @brief the purpose of this function is to improve the tour obtained by the christofides algorithm, by performing
     * the swap of two edges a given number of tries until the there are no more improvements or the number of tries if exceeded
     * @param tour represent the initial tour obtain by the christofides algorithm that will be improved
     * @param c Unordered_map with the coordinates of the nodes.
     */
    void twoOpt2(std::vector<Vertex<int>*>& tour, unordered_map<int,pair<double,double>> c);
    /**
     * @brief This function has the purpose to iterate over the MST vector resulting from the Prim's algorithm.
     * It has a temporal complexity of 0(VE). It can be compared to the DFS algorithm.
     * @param MST Vector which has the vertexs from the Prim's algorithm.
     * @return Pre-order walk as a vector.
     */
    vector<Vertex<int>*> preOrderWalk(vector<Vertex<int>*> MST);
    /**
     * @brief This function is auxiliary for the preOrderWalk. It calls itself recursively until it visits all the possible nodes once.
     * It has a temporal complexity of O(E).
     * @param node
     * @param result
     */
    void PreOrderWalkDFS(Vertex<int>* node, vector<Vertex<int>*>& result);
    /**
     * @brief This function has the purpose to find a edge between two nodes. If it doesn't find, it will return nullptr.
     * It has a temporal complexity of O(E).
     * @param from Origin node.
     * @param to Destination node.
     * @return Edge between the origin and the destination.
     */
    Edge<int>* findEdge(Vertex<int>* from, Vertex<int>* to);
    /**
     * @brief This function is a possible implementation for the exercise 4.4. This method will start by the chosen origin node.
     * It will choose the best edges by measuring the ratio between the weight and the indegree.
     * It has a temporal complexity of O(V^2).
     * @param g Graph to apply the algorithm.
     * @param origin Starting node for the algorithm.
     * @return It will return the cost if there is a path or it will abort the program if it can't find a path.
     */
    double greedyTSP(Graph<int> g,int origin);
};

#endif //PROJETO_2_DA_MENU_H
