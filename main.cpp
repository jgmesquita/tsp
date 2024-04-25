#include <iostream>
#include "Menu.h"

int main() {
    int choice;
    Menu m = Menu();
    while (true) {
        cout << "Something... \n";
        cin >> choice;

        switch (choice) {
            case 1: cout << "Option 1... \n"; break;
            default: break;
        }
    }
    return 0;
}
