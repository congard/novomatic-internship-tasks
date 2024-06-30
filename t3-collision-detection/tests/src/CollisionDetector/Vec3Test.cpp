#include <gtest/gtest.h>

#include "CollisionDetector/vec3.h"

TEST(Vec3Test, Construction) {
    cd::vec3 id;
    EXPECT_FLOAT_EQ(id.x, 0);
    EXPECT_FLOAT_EQ(id.y, 0);
    EXPECT_FLOAT_EQ(id.z, 0);

    cd::vec3 v {-1, 2, 4};
    EXPECT_FLOAT_EQ(v.x, -1);
    EXPECT_FLOAT_EQ(v.y, 2);
    EXPECT_FLOAT_EQ(v.z, 4);

    cd::vec2 v2 {5, 7};
    cd::vec3 v3 {v2};
    EXPECT_FLOAT_EQ(v3.x, 5);
    EXPECT_FLOAT_EQ(v3.y, 7);
    EXPECT_FLOAT_EQ(id.z, 0);
}

TEST(Vec3Test, Dot) {
    cd::vec3 v1 {1, 2, 1};
    cd::vec3 v2 {2, -1, 3};
    float expected = 3;
    float actual = cd::dot(v1, v2);
    EXPECT_FLOAT_EQ(expected, actual);
}

TEST(Vec3Test, Cross) {
    cd::vec3 v1 {1, 2, 3};
    cd::vec3 v2 {1, 5, 7};
    cd::vec3 expected {-1, -4, 3};
    auto actual = cd::cross(v1, v2);

    EXPECT_FLOAT_EQ(expected.x, actual.x);
    EXPECT_FLOAT_EQ(expected.y, actual.y);
    EXPECT_FLOAT_EQ(expected.z, actual.z);
}

TEST(Vec3Test, OpPlus) {
    cd::vec3 v1 {1, 2, 3};
    cd::vec3 v2 {2, -1, -2};
    cd::vec3 expected {3, 1, 1};
    auto actual = v1 + v2;

    EXPECT_FLOAT_EQ(expected.x, actual.x);
    EXPECT_FLOAT_EQ(expected.y, actual.y);
    EXPECT_FLOAT_EQ(expected.z, actual.z);
}

TEST(Vec3Test, OpMinus) {
    cd::vec3 v1 {1, 2, 3};
    cd::vec3 v2 {2, -1, -2};
    cd::vec3 expected {-1, 3, 5};
    auto actual = v1 - v2;

    EXPECT_FLOAT_EQ(expected.x, actual.x);
    EXPECT_FLOAT_EQ(expected.y, actual.y);
    EXPECT_FLOAT_EQ(expected.z, actual.z);
}

TEST(Vec3Test, OpMutPlus) {
    cd::vec3 v1 {1, 2, 3};
    cd::vec3 v2 {2, -1, -2};
    cd::vec3 expected {3, 1, 1};

    v1 += v2;

    EXPECT_FLOAT_EQ(expected.x, v1.x);
    EXPECT_FLOAT_EQ(expected.y, v1.y);
    EXPECT_FLOAT_EQ(expected.z, v1.z);
}

TEST(Vec3Test, OpMutMinus) {
    cd::vec3 v1 {1, 2, 3};
    cd::vec3 v2 {2, -1, -2};
    cd::vec3 expected {-1, 3, 5};

    v1 -= v2;

    EXPECT_FLOAT_EQ(expected.x, v1.x);
    EXPECT_FLOAT_EQ(expected.y, v1.y);
    EXPECT_FLOAT_EQ(expected.z, v1.z);
}
