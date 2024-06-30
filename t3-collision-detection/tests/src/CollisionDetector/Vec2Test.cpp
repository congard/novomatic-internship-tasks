#include <gtest/gtest.h>

#include "CollisionDetector/vec2.h"

TEST(Vec2Test, Construction) {
    cd::vec2 id;
    EXPECT_FLOAT_EQ(id.x, 0);
    EXPECT_FLOAT_EQ(id.y, 0);

    cd::vec2 v {-1, 2};
    EXPECT_FLOAT_EQ(v.x, -1);
    EXPECT_FLOAT_EQ(v.y, 2);
}

TEST(Vec2Test, Dot) {
    cd::vec2 v1 {1, 2};
    cd::vec2 v2 {2, -1};
    float expected = 0;
    float actual = cd::dot(v1, v2);
    EXPECT_FLOAT_EQ(expected, actual);
}

TEST(Vec2Test, OpPlus) {
    cd::vec2 v1 {1, 2};
    cd::vec2 v2 {2, -1};
    cd::vec2 expected {3, 1};
    auto actual = v1 + v2;

    EXPECT_FLOAT_EQ(expected.x, actual.x);
    EXPECT_FLOAT_EQ(expected.y, actual.y);
}

TEST(Vec2Test, OpMinus) {
    cd::vec2 v1 {1, 2};
    cd::vec2 v2 {2, -1};
    cd::vec2 expected {-1, 3};
    auto actual = v1 - v2;

    EXPECT_FLOAT_EQ(expected.x, actual.x);
    EXPECT_FLOAT_EQ(expected.y, actual.y);
}

TEST(Vec2Test, OpMutPlus) {
    cd::vec2 v1 {1, 2};
    cd::vec2 v2 {2, -1};
    cd::vec2 expected {3, 1};

    v1 += v2;

    EXPECT_FLOAT_EQ(expected.x, v1.x);
    EXPECT_FLOAT_EQ(expected.y, v1.y);
}

TEST(Vec2Test, OpMutMinus) {
    cd::vec2 v1 {1, 2};
    cd::vec2 v2 {2, -1};
    cd::vec2 expected {-1, 3};

    v1 -= v2;

    EXPECT_FLOAT_EQ(expected.x, v1.x);
    EXPECT_FLOAT_EQ(expected.y, v1.y);
}
