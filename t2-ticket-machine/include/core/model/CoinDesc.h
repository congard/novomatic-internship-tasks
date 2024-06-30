#ifndef TMC_TESTS_COINDESC_H
#define TMC_TESTS_COINDESC_H

#include "CoinValue.h"

namespace tmc {
struct CoinDesc {
    inline bool operator==(const CoinDesc &other) const {
        return value == other.value && count == other.count;
    }

    CoinValue value;
    size_t count;
};
}

#endif //TMC_TESTS_COINDESC_H
