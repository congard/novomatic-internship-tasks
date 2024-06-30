#ifndef T3_COLLISION_DETECTION_TRIANGLE_H
#define T3_COLLISION_DETECTION_TRIANGLE_H

#include <array>

#include "vec2.h"

namespace cd {
struct triangle {
    inline const vec2& operator[](size_t i) const {
        return points[i];
    }

    inline vec2& operator[](size_t i) {
        return points[i];
    }

    std::array<vec2, 3> points;
};
}

#endif //T3_COLLISION_DETECTION_TRIANGLE_H
