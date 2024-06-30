#ifndef T1_DATA_COMPRESSION_COMPRESSEDDATA_H
#define T1_DATA_COMPRESSION_COMPRESSEDDATA_H

#include <optional>
#include <vector>

#include "Data.h"

namespace dc {
template<typename T>
using CompressedData = std::optional<std::vector<Data<T>>>;
}

#endif //T1_DATA_COMPRESSION_COMPRESSEDDATA_H
