#ifndef T1_DATA_COMPRESSION_ARRAY2D_H
#define T1_DATA_COMPRESSION_ARRAY2D_H

#include <array>
#include <cstddef>

namespace dc {
namespace detail {
constexpr size_t sizeX {32};
constexpr size_t sizeY {16};

template<size_t s>
concept NonZero = s != 0;
}

template<typename T, size_t sizeX = detail::sizeX, size_t sizeY = detail::sizeY>
requires detail::NonZero<sizeX> && detail::NonZero<sizeY>
using Array2D = std::array<std::array<T, sizeX>, sizeY>;
}

#endif //T1_DATA_COMPRESSION_ARRAY2D_H
