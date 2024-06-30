#ifndef T2_TICKET_MACHINE_COINVALUE_H
#define T2_TICKET_MACHINE_COINVALUE_H

#include <cstdint>

namespace tmc {
using CoinValue = uint32_t;
constexpr static CoinValue CoinValueUnknown = -1;
}

#endif //T2_TICKET_MACHINE_COINVALUE_H
