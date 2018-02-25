#include <array>
#include <iostream>

template<class T, int N, int M>
class Array2D {

    std::array<std::array<T, M>, N> array;

public:
    // TODO take an initializer list and initilize the "array" member
    Array2D(std::initializer_list<std::array<T, M>> initial_values):
        array(initial_values) { }

    // mutators
    void set(T value, int i, int j);

    // retrievers
    const T &get(int i, int j) const;
};

template<class T, int N, int M>
void print_array2d(std::ostream &os, Array2D<T, N, M> array2d);


// Implementaion

template<class T, int N, int M>
void Array2D<T, N, M>::set(T value, int i, int j) {
    array[i][j] = value;
}

template<class T, int N, int M>
const T &Array2D<T, N, M>::get(int i, int j) const {
    return array[i][j];
}
