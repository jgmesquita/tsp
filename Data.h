//
// Created by jorge on 25/04/2024.
//

#ifndef PROJETO_2_DA_DATA_H
#define PROJETO_2_DA_DATA_H

#include "Graph.h"
#include "string"
#include "unordered_map"
#include "map"
#include "set"

using namespace std;

/**
 * @class Data
 * @brief This class is used to store all the contents from the .csv files into a graph.
 * It will be used by the menu class to implement the different proposed algorithms.
 */
class Data {
private:
    Graph<int> g;
    string path;
    unordered_map<int,pair<double,double>> coordinates;

public:
    /**
     * @brief  This is an auxiliary parameter to save all the distances between all the pairs.
     */
    std::vector<std::vector<double>> matrix;
    /**
     * @brief Constructor for the class Data.
     * It has the temporal complexity of O(N^2 + E), where E is the number of lines in the csv files
     * @param path Path for the respective file.
     * @param size Number of nodes in the graph.
     */
    void parseGraph(string path, int size);
    /**
     * @brief This method will parse the coordinates from the node.csv files.
     * It has the temporal complexity of O(N * log N), where E is the number of lines in the csv files
     */
    void parseCoordinates();
    /**
     * @brief This method will return the a Graph object.
     * It has the temporal complexity of O(1).
     * @return Graph object.
     */
    Graph<int> getGraph();
    /**
     * @brief This method will return the coordinates as an unordered_map.
      * It has the temporal complexity of O(1).
     * The index represents the id from the node and the value represents the pair of the coordinates.
     * @return Unordered_map for the coordinates of each node.
     */
    unordered_map<int,pair<double,double>> getCoordinates();
};


#endif //PROJETO_2_DA_DATA_H
