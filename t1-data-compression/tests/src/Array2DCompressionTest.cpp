#include <gtest/gtest.h>

#include "Array2D.h"
#include "DataCompressor.h"

using namespace dc;

/**
 * an example from the task
 */
TEST(Array2DCompressionTest, Example7x3) {
    Array2D<int, 7, 3> data {{
        {0, 0, 0, 1, 1, 2, 3},
        {0, 0, 4, 4, 4, 2, 2},
        {2, 2, 2, 2, 2, 1, 2}
    }};

    CompressedData<int> expected = CompressedData<int>::value_type {
        {0, 3}, {1, 2}, {2, 1}, {3, 1},
        {0, 2}, {4, 3}, {2, 2},
        {2, 5}, {1, 1}, {2, 1}
    };

    auto actual = compressData(data);

    EXPECT_EQ(expected, actual);
}

/**
 * sizeof(data) == 4 and sizeof(compressedData) == 4,
 * therefore an empty optional will be returned
 */
TEST(Array2DCompressionTest, CompressedEqualToOriginal) {
    Array2D<uint8_t, 2, 2> data {{
        {1, 1},
        {2, 2}
    }};

    CompressedData<uint8_t> expected {};

    auto actual = compressData(data);

    EXPECT_EQ(expected, actual);
}

/**
 * sizeof(data) == 4 but sizeof(compressedData) == 6,
 * therefore an empty optional will be returned
 */
TEST(Array2DCompressionTest, CompressedBiggerThanOriginal) {
    Array2D<uint8_t, 2, 2> data {{
        {1, 1},
        {2, 3}
    }};

    CompressedData<uint8_t> expected {};

    auto actual = compressData(data);

    EXPECT_EQ(expected, actual);
}

/**
 * 32x16 array test
 * Because of the size, the test is generated by generating
 * 2D array (matrix) in which lower triangular matrix is filled with 0
 * and upper triangular is filled with row indices, i.e.:
 *   0000
 *   0111
 *   0022
 *   0003
 */
TEST(Array2DCompressionTest, DefaultSize) {
    using CompData = CompressedData<int>;

    Array2D<int> data {};
    auto rowCount = data.size();

    CompData::value_type expectedData;

    for (int y = 0; y < rowCount; ++y) {
        auto colCount = data[y].size();
        auto aspectRatio = colCount / rowCount; // yes, without casting to float
        auto start = y * aspectRatio;

        for (size_t x = start; x < colCount; ++x)
            data[y][x] = y;

        if (start != 0)
            expectedData.emplace_back(0, start);

        expectedData.emplace_back(y, colCount - start);
    }

    CompData expected {expectedData};
    auto actual = compressData(data);

    EXPECT_EQ(expected, actual);
}