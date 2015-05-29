#ifndef INITIALIZER_HPP
#define INITIALIZER_HPP

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

template<typename T = int>
std::vector<T> generate_vector_index(int size, T initial_value = {})
{
    std::vector<int> result(size);
    std::iota(std::begin(result), std::end(result), initial_value);

    return result;
}

#endif // INITIALIZER_HPP
