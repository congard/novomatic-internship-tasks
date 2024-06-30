#ifndef T3_COLLISION_DETECTION_COLLISIONDETECTOR_H
#define T3_COLLISION_DETECTION_COLLISIONDETECTOR_H

#include "triangle.h"
#include "vec3.h"

namespace cd {
bool isSameSide(const vec3 &p1, const vec3 &p2, const vec3 &a, const vec3 &b);
bool isInside(const vec2 &p, const triangle &t);
bool isColliding(const triangle &t1, const triangle &t2);
}

#endif //T3_COLLISION_DETECTION_COLLISIONDETECTOR_H
