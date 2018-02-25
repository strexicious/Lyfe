#include <iostream>
#include "gol.hh"

using namespace std;

int main() {
    // TODO make it work
    const GoL<10, 10>::Grid grid = {
        {true},
        {true},
        {true},
        {false}
    };

    cout << grid.get(4, 0) << " " << grid.get(2, 0) << endl;

    return 0;
}
