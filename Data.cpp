#include "Graph.h"
#include "Data.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"

using namespace std;

void Data::parseGraph(string path) {
    this->path = path;
    ifstream in(".." + path);
    string line;
    getline(in, line);
    while (getline(in, line)) {
        string orig, dest, dist;
        istringstream iss(line);
        getline(iss, orig, ',');
        getline(iss, dest, ',');
        getline(iss, dist, ',');
        if (!g.findVertex(orig)) {
            g.addVertex(orig);
        }
        if (!g.findVertex(dest)) {
            g.addVertex(dest);
        }
        g.addBidirectionalEdge(orig, dest, stod(dist));
    }
}

void Data::parseEdge() {
    if (this->path[1] == 'm') {
        ifstream in("../medium/nodes.csv");
        string line;
        getline(in, line);
        while (getline(in, line)) {
            string id, lon, lat;
            istringstream iss(line);
            getline(iss, id, ',');
            getline(iss, lon, ',');
            getline(iss, lat, ',');
            coordinates[stoi(id)] = make_pair(stod(lon), stod(lat));
        }
    }
    else if (this->path[2] == 'l') {
        string subpath;
        switch (this->path[11]) {
            case '1': subpath = "../large/graph1/nodes.csv"; break;
            case '2': subpath = "../large/graph2/nodes.csv"; break;
            case '3': subpath = "../large/graph1/nodes.csv"; break;
        }
        ifstream in(path);
        string line;
        getline(in, line);
        while (getline(in, line)) {
            string id, lon, lat;
            istringstream iss(line);
            getline(iss, id, ',');
            getline(iss, lon, ',');
            getline(iss, lat, ',');
            coordinates[stoi(id)] = make_pair(stod(lon), stod(lat));
        }
    }
}

Graph<string> Data::getGraph() {
    return this->g;
}

unordered_map<int,pair<double,double>> Data::getCoordinates() {
    return this->coordinates;
}


