#include <SFML/Graphics.hpp>
#include "Array2D.hh"

template<int N, int M>
class GoL {

public:
    // Common interface type between this class and it's user
    using Grid = Array2D<bool, N, M>;

private:
    Grid buffer_one;
    Grid buffer_two;
    bool buffered = false; // false represents buffer_one is current

public:
    // GoL(Grid grid) uses grid as the initial state

    // mutators
    // Grid update() updates state and return it
};
