#ifndef T1_DATA_COMPRESSION_DATA_H
#define T1_DATA_COMPRESSION_DATA_H

#include <cstdint>

namespace dc {
/**
 * Represents compressed data.
 * @tparam T The data type.
 * @tparam count_t The counter type.
 * @note The structure is packed, as we want to know the _real_ size
 * of compressed data in bytes without any paddings.
 */
template<typename T, typename count_t = uint8_t>
struct __attribute__((packed)) Data {
    // since C++20 this ctor is unnecessary (previously needed for emplace_back)
    Data(T value, count_t count)
        : value(std::move(value)), count(count) {}

    bool operator==(const Data &other) const {
        return count == other.count && value == other.value;
    }

    T value;
    count_t count;
};
}

#endif //T1_DATA_COMPRESSION_DATA_H
