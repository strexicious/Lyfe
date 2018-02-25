#include <array>
#include <iostream>

template<class T, int N, int M>
class Array2D {

    std::array<std::array<T, M>, N> array;

public:
    // mutators
    void set(T value, int i, int j);

    // retrievers
    T get(int i, int j) const;
};

template<class T, int N, int M>
void print_array2d(std::ostream &os, Array2D<T, N, M> array2d);


// Implementaion

template<class T, int N, int M>
void Array2D<T, N, M>::set(T value, int i, int j) {
    array[i][j] = value;
}

template<class T, int N, int M>
T Array2D<T, N, M>::get(int i, int j) const {
    return array[i][j];
}
