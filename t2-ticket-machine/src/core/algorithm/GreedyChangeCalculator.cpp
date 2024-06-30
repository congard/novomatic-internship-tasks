#include "algorithm/GreedyChangeCalculator.h"

#include <algorithm>
#include <unordered_map>

namespace tmc {
bool GreedyChangeCalculator::isAvailable(CoinValue value, const Coins &coins) {
    return calculateImpl(value, coins, nullptr);
}

ChangeCalculator::Coins GreedyChangeCalculator::calculate(CoinValue value, const Coins &coins) {
    Coins result;
    calculateImpl(value, coins, &result);
    return result;
}

bool GreedyChangeCalculator::calculateImpl(CoinValue value, Coins coins, Coins *result) {
    auto coinDescCmp = [](const CoinDesc &d1, const CoinDesc &d2) {
        return d1.value > d2.value;
    };

    // O(n)
    if (!std::ranges::is_sorted(coins, coinDescCmp))
        std::ranges::sort(coins, coinDescCmp); // O(nlogn)

    int coinIndex = 0;
    std::unordered_map<CoinValue, size_t> resultMap;

    while (coinIndex < coins.size() && value != 0) {
        if (auto &coin = coins[coinIndex]; coin.count == 0 || static_cast<int64_t>(value) - coin.value < 0) {
            ++coinIndex;
        } else {
            --coin.count;
            value -= coin.value;

            if (result != nullptr) {
                auto it = resultMap.try_emplace(coin.value, 0);
                ++it.first->second;
            }
        }
    }

    if (result != nullptr) {
        for (auto [coin, count] : resultMap) {
            result->emplace_back(coin, count);
        }
    }

    return value == 0;
}
} // tmc