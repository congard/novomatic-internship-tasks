#ifndef T2_TICKET_MACHINE_TICKET_H
#define T2_TICKET_MACHINE_TICKET_H

#include <string>
#include <cstdint>

#include "CoinValue.h"

namespace tmc {
struct Ticket {
    enum class Category {
        Normal, Reduced
    };

    size_t id;
    Category category;
    CoinValue price;
    uint32_t timeMinutes;
};
} // tmc

#endif //T2_TICKET_MACHINE_TICKET_H
