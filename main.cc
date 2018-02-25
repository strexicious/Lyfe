#include <iostream>
#include "gol.hh"

using namespace std;

constexpr unsigned WIDTH = 10;
constexpr unsigned HEIGHT = 10;

int main() {
    const GoL<HEIGHT, WIDTH>::Grid pattern = {{
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, true, false, false, false, false, false, false},
        {false, false, false, true, false, false, false, false, false, false},
        {false, false, false, true, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
    }};

    GoL<HEIGHT, WIDTH> gol(pattern);

    for (auto &row : gol.state()) {
        for (auto cell : row)
            cout << (cell ? 'O' : '-') << " ";
        cout << '\n';
    }

    cout << "=========\n";

    auto updated = gol.update();
    for (auto &row : updated) {
        for (auto cell : row)
            cout << (cell ? 'O' : '-') << " ";
        cout << '\n';
    }

    return 0;
}
