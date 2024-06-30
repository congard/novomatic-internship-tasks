#include "algorithm/DemoChangeCalculator.h"

namespace tmc::demo {
bool DemoChangeCalculator::calculateImpl(CoinValue value, Coins coins, Coins *result) {
    std::erase_if(coins, [](const CoinDesc &desc) {
        return desc.value != 1 && desc.value != 2 && desc.value != 5;
    });
    return GreedyChangeCalculator::calculateImpl(value, std::move(coins), result);
}
}