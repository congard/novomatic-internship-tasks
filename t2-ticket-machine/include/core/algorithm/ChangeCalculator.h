#ifndef T2_TICKET_MACHINE_CHANGECALCULATOR_H
#define T2_TICKET_MACHINE_CHANGECALCULATOR_H

#include <vector>

#include "model/CoinDesc.h"

namespace tmc {
class ChangeCalculator {
public:
    using Coins = std::vector<CoinDesc>;

public:
    virtual ~ChangeCalculator() = default;

    virtual bool isAvailable(CoinValue value, const Coins &coins) = 0;
    virtual Coins calculate(CoinValue value, const Coins &coins) = 0;
};
} // tmc

#endif //T2_TICKET_MACHINE_CHANGECALCULATOR_H
