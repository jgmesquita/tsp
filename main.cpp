#include <iostream>
#include "Menu.h"

int main() {
    int choice;
    Menu m = Menu();
    Graph<string> g = m.getGraphMenu();
    while (true) {
        cout << "Choose one of the following options!\n";
        cout << "[1] - Backtracking TSP; \n";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "The result is: " << m.tspBacktracking(g) << "\n";
            default: break;
        }
    }
    return 0;
}
