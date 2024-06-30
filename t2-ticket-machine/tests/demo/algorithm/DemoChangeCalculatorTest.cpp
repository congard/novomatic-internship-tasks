#include <gtest/gtest.h>

#include <unordered_set>

#include "algorithm/DemoChangeCalculator.h"

inline static auto toSet(const tmc::ChangeCalculator::Coins &coins) {
    auto hash = [](const tmc::CoinDesc &d1) {
        return d1.value * 31 + d1.count;
    };

    return std::unordered_set<tmc::CoinDesc, decltype(hash)> {coins.begin(), coins.end()};
}

static tmc::ChangeCalculator::Coins coinSet1 {
    {.value = 10, .count = 2},
    {.value = 5,  .count = 2},
    {.value = 2,  .count = 2},
    {.value = 1,  .count = 2}
};

/**
 * Coin of value `10` will be ignored
 */
TEST(DemoChangeCalculatorTest, Case1Ok) {
    tmc::demo::DemoChangeCalculator calculator;

    tmc::CoinValue val = 12;

    auto expected = toSet({
        {.value = 5, .count = 2},
        {.value = 2, .count = 1}
    });

    auto actual = toSet(calculator.calculate(val, coinSet1));

    EXPECT_TRUE(calculator.isAvailable(val, coinSet1));
    EXPECT_EQ(expected, actual);
}