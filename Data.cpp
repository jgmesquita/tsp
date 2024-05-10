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
    if (this->path[1] == 'm' || this->path[1] == 's' || true) {
        while (getline(in, line)) {
            string orig, dest, dist;
            istringstream iss(line);
            getline(iss, orig, ',');
            getline(iss, dest, ',');
            getline(iss, dist);
            if (!g.findVertex(stoi(orig))) {
                g.addVertex(stoi(orig));
            }
            if (!g.findVertex(stoi(dest))) {
                g.addVertex(stoi(dest));
            }
            g.addBidirectionalEdge(stoi(orig), stoi(dest), stod(dist));
        }
    } /*else{
        vector<int> row;
        int curent = 0;
        g.addVertex(0);
        while (getline(in, line)) {
            string orig, dest, dist;
            istringstream iss(line);
            getline(iss, orig, ',');
            getline(iss, dest, ',');
            getline(iss, dist);
            row[]
            if(stoi(orig) != curent){
                g.addVertex(stoi(orig));
                curent = stoi(orig);
                g.matrix.push_back(row);
            }
        }*/
}


void Data::parseCoordinates() {
    if (this->path[1] == 'm') {
        ifstream in("../medium/nodes.csv");
        string line;
        getline(in, line);
        while (getline(in, line)) {
            string id, lon, lat;
            istringstream iss(line);
            getline(iss, id, ',');
            getline(iss, lon, ',');
            getline(iss, lat);
            coordinates[stoi(id)] = make_pair(stod(lon), stod(lat));
        }
    }
    else if (this->path[1] == 'l') {
        string subpath;
        switch (this->path[12]) {
            case '1': subpath = "../large/graph1/nodes.csv"; break;
            case '2': subpath = "../large/graph2/nodes.csv"; break;
            case '3': subpath = "../large/graph3/nodes.csv"; break;
        }
        ifstream in(subpath);
        string line;
        getline(in, line);

        while (getline(in, line)) {
            string id, lon, lat;
            istringstream iss(line);
            getline(iss, id, ',');
            getline(iss, lon, ',');
            getline(iss, lat);
            coordinates[stoi(id)] = make_pair(stod(lon), stod(lat));
        }
    }
}

Graph<int> Data::getGraph() {
    return this->g;
}

unordered_map<int,pair<double,double>> Data::getCoordinates() {
    return this->coordinates;
}

string Data::getPath() {
    return this->path;
}

