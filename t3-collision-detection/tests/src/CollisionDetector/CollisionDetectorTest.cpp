#include <gtest/gtest.h>

#include "CollisionDetector/CollisionDetector.h"

TEST(CollisionDetectorTest, SameSideCase1) {
    cd::vec2 p1 {2, 3};
    cd::vec2 p2 {3, 6};
    cd::vec2 a {1, 0};
    cd::vec2 b {4, 6};
    EXPECT_TRUE(cd::isSameSide(p1, p2, a, b));
}

TEST(CollisionDetectorTest, SameSideCase2) {
    cd::vec2 p1 {2, 3};
    cd::vec2 p2 {3, -6};
    cd::vec2 a {1, 0};
    cd::vec2 b {4, 6};
    EXPECT_FALSE(cd::isSameSide(p1, p2, a, b));
}

TEST(CollisionDetectorTest, PointOutsideTriangle) {
    cd::triangle t1 {{{
        {1, 1}, {3, 1}, {2, 2}
    }}};

    cd::vec2 p1 {0.5, 0.5};
    cd::vec2 p2 {1.5, 0.5};
    cd::vec2 p3 {1.5, 0.75};

    EXPECT_FALSE(cd::isInside(p1, t1));
    EXPECT_FALSE(cd::isInside(p2, t1));
    EXPECT_FALSE(cd::isInside(p3, t1));
}

TEST(CollisionDetectorTest, PointInsideTriangle) {
    cd::triangle t1 {{{
        {1, 1}, {3, 1}, {2, 2}
    }}};

    cd::vec2 p1 {2, 1.5};

    EXPECT_TRUE(cd::isInside(p1, t1));
}

TEST(CollisionDetectorTest, CollisionDetectorWithoutIntersection) {
    cd::triangle t1 {{{
        {1, 1}, {2, 2}, {1.5, 4}
    }}};

    cd::triangle t2 {{{
        {3, 1}, {5, 2}, {4, 4}
    }}};

    EXPECT_FALSE(cd::isColliding(t1, t2));
    EXPECT_FALSE(cd::isColliding(t2, t1));
}

TEST(CollisionDetectorTest, CollisionDetectorIntersection) {
    cd::triangle t1 {{{
        {1, 1}, {2, 2}, {1.5, 4}
    }}};

    cd::triangle t2 {{{
        {3, 1}, {1.5, 2}, {4, 4}
    }}};

    EXPECT_TRUE(cd::isColliding(t1, t2));
    EXPECT_TRUE(cd::isColliding(t2, t1));
}

TEST(CollisionDetectorTest, CollisionDetectorPenetration) {
    cd::triangle t1 {{{
        {1, 1}, {2, 2}, {1.5, 4}
    }}};

    cd::triangle t2 {{{
        {3, 1}, {0.5, 2}, {4, 4}
    }}};

    EXPECT_TRUE(cd::isColliding(t1, t2));
    EXPECT_TRUE(cd::isColliding(t2, t1));
}

TEST(CollisionDetectorTest, CollisionDetectorInside) {
    cd::triangle t1 {{{
        {1, 1}, {2, 2}, {1.5, 4}
    }}};

    cd::triangle t2 {{{
        {1.25, 1.5}, {1.75, 2}, {1.5, 3}
    }}};

    EXPECT_TRUE(cd::isColliding(t1, t2));
    EXPECT_TRUE(cd::isColliding(t2, t1));
}
