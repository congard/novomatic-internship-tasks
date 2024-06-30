#ifndef TMC_DEMO_DEMOCHANGECALCULATOR_H
#define TMC_DEMO_DEMOCHANGECALCULATOR_H

#include "algorithm/GreedyChangeCalculator.h"

namespace tmc::demo {
/**
 * The same as [GreedyChangeCalculator], but
 * only uses coins of values 1, 2 and 5.
 */
class DemoChangeCalculator : public GreedyChangeCalculator {
protected:
    bool calculateImpl(CoinValue value, Coins coins, Coins *result) override;
};
}

#endif //TMC_DEMO_DEMOCHANGECALCULATOR_H
