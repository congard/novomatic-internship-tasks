#include <gtest/gtest.h>

#include <unordered_set>

#include "algorithm/GreedyChangeCalculator.h"

inline static auto toSet(const tmc::ChangeCalculator::Coins &coins) {
    auto hash = [](const tmc::CoinDesc &d1) {
        return d1.value * 31 + d1.count;
    };

    return std::unordered_set<tmc::CoinDesc, decltype(hash)> {coins.begin(), coins.end()};
}

static tmc::ChangeCalculator::Coins coinSet1 {
    {.value = 5, .count = 2},
    {.value = 2, .count = 2},
    {.value = 1, .count = 2}
};

// TODO: docs

TEST(GreedyChangeCalculatorTest, Case1Ok) {
    tmc::GreedyChangeCalculator calculator;

    tmc::CoinValue val = 8;

    auto expected = toSet({
        {.value = 5, .count = 1},
        {.value = 2, .count = 1},
        {.value = 1, .count = 1}
    });

    auto actual = toSet(calculator.calculate(val, coinSet1));

    EXPECT_TRUE(calculator.isAvailable(val, coinSet1));
    EXPECT_EQ(expected, actual);
}

TEST(GreedyChangeCalculatorTest, Case2Ok) {
    tmc::GreedyChangeCalculator calculator;

    tmc::CoinValue val = 12;

    auto expected = toSet({
        {.value = 5, .count = 2},
        {.value = 2, .count = 1}
    });

    auto actual = toSet(calculator.calculate(val, coinSet1));

    EXPECT_TRUE(calculator.isAvailable(val, coinSet1));
    EXPECT_EQ(expected, actual);
}

TEST(GreedyChangeCalculatorTest, Case3Ok) {
    tmc::GreedyChangeCalculator calculator;

    tmc::CoinValue val = 16;

    auto expected = toSet({
        {.value = 5, .count = 2},
        {.value = 2, .count = 2},
        {.value = 1, .count = 2}
    });

    auto actual = toSet(calculator.calculate(val, coinSet1));

    EXPECT_TRUE(calculator.isAvailable(val, coinSet1));
    EXPECT_EQ(expected, actual);
}

TEST(GreedyChangeCalculatorTest, Case4Ok) {
    tmc::GreedyChangeCalculator calculator;

    tmc::CoinValue val = 3;

    auto expected = toSet({
        {.value = 2, .count = 1},
        {.value = 1, .count = 1}
    });

    auto actual = toSet(calculator.calculate(val, coinSet1));

    EXPECT_TRUE(calculator.isAvailable(val, coinSet1));
    EXPECT_EQ(expected, actual);
}

TEST(GreedyChangeCalculatorTest, Case5MaxAvailable) {
    tmc::GreedyChangeCalculator calculator;

    tmc::CoinValue val = 17;

    auto expected = toSet({
        {.value = 5, .count = 2},
        {.value = 2, .count = 2},
        {.value = 1, .count = 2}
    });

    auto actual = toSet(calculator.calculate(val, coinSet1));

    EXPECT_FALSE(calculator.isAvailable(val, coinSet1));
    EXPECT_EQ(expected, actual);
}
