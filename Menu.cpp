#include "Menu.h"

using namespace std;

Menu::Menu() {
    this->d = Data();
    d.parseGraph();
}