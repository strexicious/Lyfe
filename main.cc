#include <iostream>
#include "gol.hh"

using namespace std;

constexpr unsigned WIDTH = 10;
constexpr unsigned HEIGHT = 10;

int main() {
    const GoL<HEIGHT, WIDTH>::Grid pattern = {{
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, true},
        {false, false, false, false, false, false, false, false, false, true},
        {false, false, false, false, false, false, false, false, false, true},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
    }};

    GoL<HEIGHT, WIDTH> gol(pattern);

    return 0;
}
