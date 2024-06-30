#include <gtest/gtest.h>

#include <vector>

#include "DataCompressor.h"

namespace dc {
/**
 * Data Compressor for `std::vector`.
 * @tparam U The data type.
 */
template<typename U>
struct DataCompressor<std::vector<U>> {
    template<typename C = detail::Cmp<U>>
    CompressedData<U> operator()(const std::vector<U> &input, C &&cmp = {}) requires detail::Comparable<C, U> {
        return DataCompressor<std::span<U>> {}.template operator()<false>(input, std::forward<C>(cmp));
    }
};
}

using namespace dc;

TEST(VectorCompressionTest, CompressedLessThanOriginal) {
    std::vector<int> data {1, 1, 2, 3, 3, 3};

    CompressedData<int> expected = CompressedData<int>::value_type {
        {1, 2}, {2, 1}, {3, 3}
    };

    auto actual = DataCompressor<decltype(data)> {}(data);

    EXPECT_EQ(expected, actual);
}

/**
 * sizeof(data) == 6 and sizeof(compressedData) == 6,
 * therefore an empty optional will be returned
 */
TEST(VectorCompressionTest, CompressedEqualToOriginal) {
    std::vector<int16_t> data {1, 1, 2};

    CompressedData<int16_t> expected {};

    auto actual = DataCompressor<decltype(data)> {}(data);

    EXPECT_EQ(expected, actual);
}

/**
 * sizeof(data) == 4 but sizeof(compressedData) == 6,
 * therefore an empty optional will be returned
 */
TEST(VectorCompressionTest, CompressedBiggerThanOriginal) {
    std::vector<int16_t> data {1, 2};

    CompressedData<int16_t> expected {};

    auto actual = DataCompressor<decltype(data)> {}(data);

    EXPECT_EQ(expected, actual);
}