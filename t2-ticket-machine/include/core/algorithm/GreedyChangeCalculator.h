#ifndef T2_TICKET_MACHINE_GREEDYCHANGECALCULATOR_H
#define T2_TICKET_MACHINE_GREEDYCHANGECALCULATOR_H

#include "ChangeCalculator.h"

namespace tmc {
class GreedyChangeCalculator : public ChangeCalculator {
public:
    bool isAvailable(CoinValue value, const Coins &coins) override;
    Coins calculate(CoinValue value, const Coins &coins) override;

protected:
    virtual bool calculateImpl(CoinValue value, Coins coins, Coins *result);
};
} // tmc

#endif //T2_TICKET_MACHINE_GREEDYCHANGECALCULATOR_H
