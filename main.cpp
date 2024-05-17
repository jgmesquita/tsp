#include <iostream>
#include "Menu.h"
#include "chrono"
#include "stack"


using namespace std;

int main() {
    string path;
    string subpath;
    int boot_main;
    int boot;
    int size;
    cout << "Select the group of graphs you want to use:\n";
    cout << "[1] - Small;\n";
    cout << "[2] - Medium;\n";
    cout << "[3] - Large;\n";
    cin >> boot_main;
    switch (boot_main) {
        case 1: cout << "Select the graph:\n";
                cout << "[1] - Shipping;\n";
                cout << "[2] - Stadiums;\n";
                cout << "[3] - Tourism;\n";
                cin >> boot;
                switch (boot) {
                    case 1: path = "/small/shipping.csv"; size = 14; break;
                    case 2: path = "/small/stadiums.csv";  size = 11; break;
                    case 3: path = "/small/tourism.csv";  size = 5; break;
                    default: cerr << "Invalid input! Abort program!"; break;
                }
                break;
        case 2: cout << "Write the number of nodes: [25,50,75,100,200,300,400,500,600,700,800,900]!\n";
                cin >> subpath;
                path = "/medium/edges_" + subpath + ".csv";
                size = stoi(subpath);
                break;
        case 3: cout << "Select the graph:\n";
                cout << "[1] - Graph 1;\n";
                cout << "[2] - Graph 2;\n";
                cout << "[3] - Graph 3;\n";
                cin >> boot;
                switch (boot) {
                    case 1: path = "/large/graph1/edges.csv"; size = 1000; break;
                    case 2: path = "/large/graph2/edges.csv"; size = 5000; break;
                    case 3: path = "/large/graph3/edges.csv"; size = 10000; break;
                    default: cerr << "Invalid input! Abort program!"; break;
                }
                break;
        default: cerr << "Invalid input! Abort program!"; break;

    }
    Menu m;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    m = Menu(path,size);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double, std::milli> duration = chrono::duration_cast<chrono::duration<double, std::milli>>(
            end - start);
    double time = duration.count();
    cout << "The duration is: " << time << "ms" << "\n";


    unordered_map<int,pair<double,double>> c = m.getCoordinates();
    Graph<int> g = m.getGraphMenu();
    int choice;
    while (true) {
        cout << "\n";
        cout << "Choose one of the following options!\n";
        cout << "[1] - Backtracking TSP; \n";
        cout << "[2] - Triangular Inequality Approximation TSP; \n";
        cout << "[3] - Christofides TSP; \n";
        cout << "[4] - Greedy TSP;\n";
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
                double cost = m.christofides_tsp(g, c);
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
                    cout << "Select the origin node:\n";
                    cin >> origin;
                    if(origin > size) {
                        cerr << "Invalid input! Abort program!";
                        break;
                    }
                    chrono::steady_clock::time_point start = chrono::steady_clock::now();
                    double cost = m.greedyTSP(g, origin);
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
