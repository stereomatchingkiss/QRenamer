#include "initializer.hpp"

#include <algorithm>
#include <iterator>

std::vector<int> initialize_vector_index(int size)
{
    std::vector<int> result(size);
    std::iota(std::begin(result), std::end(result), 0);

    return result;
}
