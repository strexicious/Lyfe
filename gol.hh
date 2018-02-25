#pragma once
#include <SFML/Graphics.hpp>
#include "Array2D.hh"

template<unsigned N, unsigned M>
class GoL {

public:
    // Common interface type between this class and it's user
    using Grid = Array2D<bool, N, M>;

private:
    Grid buffer_cur;
    Grid buffer_res;

    unsigned get_neighbours_count(unsigned row, unsigned col) const;

public:
    GoL(const Grid &initial_state): buffer_cur(initial_state) { }

    // mutators
    Grid update(); // updates state and return it

    // retrievers
    Grid state() const;
};


// implementation

template<unsigned N, unsigned M>
unsigned GoL<N, M>::get_neighbours_count(unsigned row, unsigned col) const {
    unsigned negs = 0;
    if (buffer_cur[((row-1 % N) + N) % N][((col-1 % M) + M) % M])
        ++negs;
    if (buffer_cur[((row-1 % N) + N) % N][col])
        ++negs;
    if (buffer_cur[((row-1 % N) + N) % N][(col+1) % M])
        ++negs;
    if (buffer_cur[row][((col-1 % M) + M) % M])
        ++negs;
    if (buffer_cur[row][(col+1) % M])
        ++negs;
    if (buffer_cur[(row+1) % N][((col-1 % M) + M) % M])
        ++negs;
    if (buffer_cur[(row+1) % N][col])
        ++negs;
    if (buffer_cur[(row+1) % N][(col+1) % M])
        ++negs;
    
    return negs;
}

template<unsigned N, unsigned M>
class GoL<N, M>::Grid GoL<N, M>::update() {
    buffer_res = buffer_cur;
    
    // for every cell...
    for (unsigned i = 0; i < N; ++i) {
        for (unsigned j = 0; j < M; ++j) {
            // ...apply the rules
            unsigned negs = get_neighbours_count(i, j);
            if (buffer_cur[i][j] && (negs < 2 || negs > 3))
                buffer_res[i][j] = false;
            else if (negs == 3)
                buffer_res[i][j] = true;                
        }
    }

    buffer_cur.swap(buffer_res);
    return buffer_cur;
}

template<unsigned N, unsigned M>
class GoL<N, M>::Grid GoL<N, M>::state() const {
    return buffer_cur;
}
