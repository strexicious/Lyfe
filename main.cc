#include <iostream>
#include "gol.hh"

using namespace std;

int main() {
    GoL<10, 10>::Grid grid;

    grid.set('k', 1, 1);
    grid.set('a', 2, 2);
    grid.set('\0', 3, 3);
    grid.set('p', 4, 4);
    grid.set('a', 5, 5);

    cout << grid.get(3, 3) << " " << grid.get(2, 2) << endl;

    return 0;
}
