#ifndef T3_COLLISION_DETECTION_VEC3_H
#define T3_COLLISION_DETECTION_VEC3_H

#include "vec2.h"

namespace cd {
template<typename dtype>
struct vec<3, dtype> {
    inline vec(): x(), y(), z() {}

    /* implicit */
    inline vec(const vec<2, dtype> &v2)
        : x(v2.x), y(v2.y), z() {}

    inline vec(dtype x, dtype y, dtype z)
        : x(x), y(y), z(z) {}

    dtype x, y, z;
};

using vec3 = vec<3, float>;

template<typename dtype = float>
vec<3, dtype> operator+(const vec<3, dtype> &v1, const vec<3, dtype> &v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

template<typename dtype = float>
vec<3, dtype>& operator+=(vec<3, dtype> &v1, const vec<3, dtype> &v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

template<typename dtype = float>
vec<3, dtype> operator-(const vec<3, dtype> &v1, const vec<3, dtype> &v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

template<typename dtype = float>
vec<3, dtype>& operator-=(vec<3, dtype> &v1, const vec<3, dtype> &v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

template<typename dtype = float>
vec<3, dtype> cross(const vec<3, dtype> &v1, const vec<3, dtype> &v2) {
    return {
        v1.y * v2.z - v1.z * v2.y,
        -(v1.x * v2.z - v1.z * v2.x),
        v1.x * v2.y - v1.y * v2.x
    };
}

template<typename dtype = float>
dtype dot(const vec<3, dtype> &v1, const vec<3, dtype> &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
}

#endif //T3_COLLISION_DETECTION_VEC3_H
