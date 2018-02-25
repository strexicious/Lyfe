#include <array>
#include <iostream>

template<class T, int N, int M>
class Array2D {

    std::array<std::array<T, M>, N> array;

public:
    // TODO take an initializer list and initilize the "array" member
    Array2D(const std::initializer_list<std::array<T, M>> &initial_values);

    // mutators
    void set(const T &value, int i, int j);

    // retrievers
    const T &get(int i, int j) const;
};


// Implementaion

template<class T, int N, int M>
Array2D<T, N, M>::Array2D(const std::initializer_list<std::array<T, M>> &initial_values) {
    auto init_b = initial_values.begin(), init_e = initial_values.end();
    for (auto &row : array) {
        if (init_b != init_e) {
            row = *init_b;
            ++init_b;
        } else break;
    }        
}

template<class T, int N, int M>
void Array2D<T, N, M>::set(const T &value, int i, int j) {
    array[i][j] = value;
}

template<class T, int N, int M>
const T &Array2D<T, N, M>::get(int i, int j) const {
    return array[i][j];
}
