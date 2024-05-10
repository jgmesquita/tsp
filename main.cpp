#include <iostream>
#include "Menu.h"
#include "chrono"

using namespace std;

int main() {
    string path;
    string subpath;
    int size;
    int boot;
    cout << "Select the group of graphs you want to use:\n";
    cout << "[1] - Small;\n";
    cout << "[2] - Medium;\n";
    cout << "[3] - Large;\n";
    cin >> boot;
    switch (boot) {
        case 1: cout << "Select the graph:\n";
                cout << "[1] - Shipping;\n";
                cout << "[2] - Stadiums;\n";
                cout << "[3] - Tourism;\n";
                cin >> boot;
                switch (boot) {
                    case 1: path = "/small/shipping.csv";  break;
                    case 2: path = "/small/stadiums.csv";  break;
                    case 3: path = "/small/tourism.csv";  break;
                    default: cerr << "Invalid input! Abort program!"; break;
                }
                break;
        case 2: cout << "Write the number of nodes: [25,50,75,100,200,300,400,500,600,700,800,900]!\n";
                cin >> subpath;
                size = stoi(subpath);
                path = "/medium/edges_" + subpath + ".csv";
                break;
        case 3: cout << "Select the graph:\n";
                cout << "[1] - Graph 1;\n";
                cout << "[2] - Graph 2;\n";
                cout << "[3] - Graph 3;\n";
                cin >> boot;
                switch (boot) {
                    case 1: path = "/large/graph1/edges.csv";  break;
                    case 2: path = "/large/graph2/edges.csv";  break;
                    case 3: path = "/large/graph3/edges.csv";  break;
                    default: cerr << "Invalid input! Abort program!"; break;
                }
                break;
        default: cerr << "Invalid input! Abort program!"; break;

    }
    Menu m = Menu(path);
    unordered_map<int,pair<double,double>> c = m.getCoordinates();
    Graph<int> g = m.getGraphMenu();
    int choice;
    while (true) {
        cout << "\n";
        cout << "Choose one of the following options!\n";
        cout << "[1] - Backtracking TSP; \n";
        cout << "[2] - Triangular Inequality Approximation TSP; \n";
        cout << "[3] - Nearest Neighbour TSP; \n";
        cout << "[4] - Nearest Neighbour TSP (Select Origin!); \n";
        cin >> choice;
        cout << "\n";
        switch (choice) {
            case 1: {
                chrono::steady_clock::time_point start = chrono::steady_clock::now();
                double cost =  m.tspBacktracking(g);
                cout << "The cost is: " << cost << "\n";
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                chrono::duration<double, std::milli> duration = chrono::duration_cast<chrono::duration<double, std::milli>>(
                        end - start);
                double time = duration.count();
                cout << "The duration is: " << time << "ms" << "\n";
                break;
            }
            case 2: {
                chrono::steady_clock::time_point start = chrono::steady_clock::now();
                double cost = m.triangleApproximationTSP(g, c);
                cout << "The cost is: " << cost << "\n";
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                chrono::duration<double, std::milli> duration = chrono::duration_cast<chrono::duration<double, std::milli>>(
                        end - start);
                double time = duration.count();
                cout << "The duration is: " << time << "ms" << "\n";
                break;
            }
            case 3: {
                chrono::steady_clock::time_point start = chrono::steady_clock::now();
                double cost = m.Closest_Node(g, c);
                cout << "The cost is: " << cost << "\n";
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                chrono::duration<double, std::milli> duration = chrono::duration_cast<chrono::duration<double, std::milli>>(
                        end - start);
                double time = duration.count();
                cout << "The duration is: " << time << "ms" << "\n";
                break;
            }
            case 4: {
                int origin;
                cout << "Write the number of the origin node!\n";
                cin >> origin;
                chrono::steady_clock::time_point start = chrono::steady_clock::now();
                double cost = m.Closest_Node_Origin(g, c, origin);
                cout << "The cost is: " << cost << "\n";
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                chrono::duration<double, std::milli> duration = chrono::duration_cast<chrono::duration<double, std::milli>>(
                        end - start);
                double time = duration.count();
                cout << "The duration is: " << time << "ms" << "\n";
                break;

            }
            default: break;
        }
    }
    return 0;
}
