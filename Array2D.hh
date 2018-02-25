#pragma once
#include <array>

template<class T, int N, int M>
using Array2D = std::array<std::array<T, M>, N>;
