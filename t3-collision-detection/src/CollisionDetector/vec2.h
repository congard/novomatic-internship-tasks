#ifndef T3_COLLISION_DETECTION_VEC2_H
#define T3_COLLISION_DETECTION_VEC2_H

#include "vec.h"

namespace cd {
template<typename dtype>
struct vec<2, dtype> {
    inline vec(): x(), y() {}

    inline vec(dtype x, dtype y)
        : x(x), y(y) {}

    dtype x, y;
};

using vec2 = vec<2, float>;

template<typename dtype = float>
vec<2, dtype> operator+(const vec<2, dtype> &v1, const vec<2, dtype> &v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

template<typename dtype = float>
vec<2, dtype>& operator+=(vec<2, dtype> &v1, const vec<2, dtype> &v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

template<typename dtype = float>
vec<2, dtype> operator-(const vec<2, dtype> &v1, const vec<2, dtype> &v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

template<typename dtype = float>
vec<2, dtype>& operator-=(vec<2, dtype> &v1, const vec<2, dtype> &v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

template<typename dtype = float>
dtype dot(const vec<2, dtype> &v1, const vec<2, dtype> &v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
}

#endif //T3_COLLISION_DETECTION_VEC2_H
