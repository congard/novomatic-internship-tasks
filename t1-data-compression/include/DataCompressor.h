#ifndef T1_DATA_COMPRESSION_DATACOMPRESSOR_H
#define T1_DATA_COMPRESSION_DATACOMPRESSOR_H

#include <span>

#include "CompressedData.h"
#include "Array2D.h"

namespace dc {
namespace detail {
template<typename C, typename T>
concept Comparable = std::is_invocable_r_v<bool, C, const T&, const T&>;

template<typename T>
using Cmp = std::equal_to<T>;
}

template<typename T>
struct DataCompressor;

/**
 * General-purpose data compressor
 * @tparam U Data type
 */
template<typename U>
struct DataCompressor<std::span<U>> {
    /**
     * Compresses [input].
     * @tparam plainData if `true`, just the result will be returned. Otherwise,
     * additional checks will be performed and an empty optional will be returned
     * in case if `sizeInBytes(compressedData) >= sizeInBytes(input)`.
     * @tparam C The comparator type
     * @param input The data to compress.
     * @param cmp The comparator.
     * @return `std::vector\<Data\<U\>\>` or `CompressedData\<U\>` depending on the
     * `plainData` template argument.
     */
    template<bool plainData = true, typename C = detail::Cmp<U>>
    auto operator()(std::span<const U> input, C &&cmp = {}) requires detail::Comparable<C, U> {
        using CompData = CompressedData<U>;
        using Result_t = CompData::value_type;

        if (input.empty()) {
            if constexpr (plainData) {
                return Result_t {};
            } else {
                return CompData {};
            }
        }

        Result_t result;
        result.reserve(input.size()); // reserve for the worst-case scenario

        size_t count = 1;
        auto value = &input[0];

        for (size_t i = 1; i < input.size(); ++i) {
            if (cmp(*value, input[i])) {
                ++count;
            } else {
                result.emplace_back(*value, count);
                count = 1;
                value = &input[i];
            }
        }

        result.emplace_back(*value, count);

        if constexpr (plainData) {
            return result;
        } else {
            // calculate data size in bytes
            size_t prevSize = input.size_bytes();
            size_t newSize = result.size() * sizeof(Data<U>);

            if (newSize < prevSize)
                return CompData {result};

            return CompData {};
        }
    }
};

/**
 * DataCompressor for `Array2D`
 * @tparam U The type.
 * @tparam sx The number of columns.
 * @tparam sy The number of rows.
 */
template<typename U, size_t sx, size_t sy>
struct DataCompressor<Array2D<U, sx, sy>> {
    template<typename C = detail::Cmp<U>>
    CompressedData<U> operator()(const Array2D<U, sx, sy> &input, C &&cmp = {}) requires detail::Comparable<C, U> {
        std::vector<Data<U>> result;

        for (auto &row : input) {
            auto data = DataCompressor<std::span<U>> {}(row, cmp);
            result.insert(
                result.end(),
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
        }

        // calculate data size in bytes
        size_t prevSize = sizeof(input);
        size_t newSize = result.size() * sizeof(Data<U>);

        if (newSize < prevSize)
            return result;

        return {};
    }
};

template<typename T, size_t sx, size_t sy, typename C = detail::Cmp<T>>
inline auto compressData(const Array2D<T, sx, sy> &input, C &&cmp = {}) {
    return DataCompressor<Array2D<T, sx, sy>>{}(input, std::forward<C>(cmp));
}
}

#endif //T1_DATA_COMPRESSION_DATACOMPRESSOR_H
